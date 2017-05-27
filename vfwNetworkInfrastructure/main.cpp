#include <iostream>
#include <stdio.h> //For standard things
#include <stdlib.h>    //malloc
#include <string.h>    //memset
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "CBaseFacade.h"
#include "CNetworkTypes.h"
#include "CTransportLayerProtocol.h"
#include "CPacketDetails.h"
#include "ByteUtils.h"



void ProcessPacket(BU8* , const BU32&);
void PrintIpHeader(unsigned char* , int);
void PrintTcpPacket(unsigned char* , const BU32& pi_nSize);
void PrintUdpPacket(BU8* , const BU32&);
void PrintIcmpPacket(unsigned char* , int);
void PrintData (unsigned char* , int);

BU64 sock_raw;
FILE *logfile;

BU64 nTcpCounter=0,nUdpCounter=0, nIcmpCounter=0,
		nOthersCounter=0,nIgmpCounter=0,total=0;

int i,j;

struct sockaddr_in source,dest;

int main()
{
	BU32 data_size;
    socklen_t saddr_size;
    struct sockaddr saddr;
    //struct in_addr in;

    BU8* pBuffer = (unsigned char *)malloc(PACKET_MAX_SIZE); //Its Big!

    logfile=fopen("/root/logfile_packet_sniffer/log.txt","w");
    if(logfile==NULL)
    {
    	std::cout << "Failed to create log file. Maybe try to login as admin (use command: sudo su)" << std::endl;
    	return 0;
    }

    printf("Starting...\n");
    //Create a raw socket that shall sniff
    sock_raw = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);

    if(sock_raw < 0)
    {
        printf("Socket Error\n");
        return 1;
    }


	/*int v=0;
    v = PACKET_MASK_ANY & ~(1<<PACKET_OUTGOING) & ~(1 << PACKET_LOOPBACK);*/
    int one = 1;
    const int* val = &one;
    if(setsockopt(sock_raw, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
    	std::cout << "failed to setsockopt" << std::endl;
    	return 0;
    }

    for(;;)
    {
        saddr_size = sizeof saddr;

        //Receive a packet
        data_size = recvfrom(sock_raw , pBuffer , PACKET_MAX_SIZE , 0 , &saddr , &saddr_size);
        if(data_size <0 )
        {
            std::cout << "Recvfrom error , failed to get packets." << std::endl;
            return 1;
        }
        //Now process the packet
        //ProcessPacket(pBuffer , data_size);
        CPacketDetails packetDetails(pBuffer, data_size);
    }
    close(sock_raw);
    std::cout << "Finished" << std::endl;
    return 0;
}

void ProcessPacket(BU8* pi_pBuff, const BU32& pi_nSize)
{
	std::cout << "*****************************" << std::endl;
	printf("%02x %02x %02x %02x\n", pi_pBuff[0], pi_pBuff[1], pi_pBuff[2], pi_pBuff[3]);
    //Get the IP Header part of this packet
    struct iphdr *pIpHeader = (struct iphdr*)pi_pBuff;
    ++total;
    switch (pIpHeader->protocol) //Check the Protocol and do accordingly...
    {
        case eIcmpTransportLayerProtocol:  //ICMP Protocol
            ++nIcmpCounter;
            //PrintIcmpPacket(Buffer,Size);
            break;

        case eIgmpTransportLayerProtocol:  //IGMP Protocol
            ++nIgmpCounter;
            break;

        case eTcpTransportLayerProtocol:  //TCP Protocol
            ++nTcpCounter;
            PrintTcpPacket(pi_pBuff , pi_nSize);
            break;

        case eUdpTransportLayerProtocol: //UDP Protocol
            ++nUdpCounter;
            PrintUdpPacket(pi_pBuff , pi_nSize);
            break;

        default: //Some Other Protocol like ARP etc.
            ++nOthersCounter;
            break;
    }
    std::cout << "TCP : " << nTcpCounter <<"  UDP : " << nUdpCounter << "   ICMP : " << nIcmpCounter << "   IGMP : " << nIgmpCounter << "   " <<"Others : " << nOthersCounter << "   Total : " << total << std::endl;
    std::cout << "*****************************" << std::endl;
}

void PrintIpHeader(unsigned char* pi_pBuff, int pi_nSize)
{
    unsigned short nIpHeaderLength;

    struct iphdr *pIpHeader = (struct iphdr *)pi_pBuff;
    nIpHeaderLength =pIpHeader->ihl*4;

    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = pIpHeader->saddr;

    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = pIpHeader->daddr;

    fprintf(logfile,"\n");
    fprintf(logfile,"IP Header\n");
    fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)pIpHeader->version);
    fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)pIpHeader->ihl,((unsigned int)(pIpHeader->ihl))*4);
    fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)pIpHeader->tos);
    fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(pIpHeader->tot_len));
    fprintf(logfile,"   |-Identification    : %d\n",ntohs(pIpHeader->id));
    //fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)pIpHeader->ttl);
    fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)pIpHeader->protocol);
    fprintf(logfile,"   |-Checksum : %d\n",ntohs(pIpHeader->check));
    fprintf(logfile,"   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    fprintf(logfile,"   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));

    CString sSrcIp = inet_ntoa(source.sin_addr);
    CString sDestIp = inet_ntoa(dest.sin_addr);

    std::cout << "src: " << sSrcIp << " , dest: " << sDestIp << std::endl;
}

void PrintTcpPacket(BU8* pi_pBuff, const BU32& pi_nSize)
{
    unsigned short nIpHeaderLength;

    struct iphdr *pIpHeader = (struct iphdr *)pi_pBuff;
    nIpHeaderLength = pIpHeader->ihl*4;

    struct tcphdr *pTcpHeader=(struct tcphdr*)(pi_pBuff + nIpHeaderLength);

    fprintf(logfile,"\n\n***********************TCP Packet*************************\n");

    PrintIpHeader(pi_pBuff,pi_nSize);

    fprintf(logfile,"\n");
    fprintf(logfile,"TCP Header\n");
    fprintf(logfile,"   |-Source Port      : %u\n",ntohs(pTcpHeader->source));
    fprintf(logfile,"   |-Destination Port : %u\n",ntohs(pTcpHeader->dest));
    fprintf(logfile,"   |-Sequence Number    : %u\n",ntohl(pTcpHeader->seq));
    fprintf(logfile,"   |-Acknowledge Number : %u\n",ntohl(pTcpHeader->ack_seq));
    fprintf(logfile,"   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)pTcpHeader->doff,(unsigned int)pTcpHeader->doff*4);
    //fprintf(logfile,"   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
    //fprintf(logfile,"   |-ECN Flag : %d\n",(unsigned int)pTcpHeader->ece);
    fprintf(logfile,"   |-Urgent Flag          : %d\n",(unsigned int)pTcpHeader->urg);
    fprintf(logfile,"   |-Acknowledgement Flag : %d\n",(unsigned int)pTcpHeader->ack);
    fprintf(logfile,"   |-Push Flag            : %d\n",(unsigned int)pTcpHeader->psh);
    fprintf(logfile,"   |-Reset Flag           : %d\n",(unsigned int)pTcpHeader->rst);
    fprintf(logfile,"   |-Synchronise Flag     : %d\n",(unsigned int)pTcpHeader->syn);
    fprintf(logfile,"   |-Finish Flag          : %d\n",(unsigned int)pTcpHeader->fin);
    fprintf(logfile,"   |-Window         : %d\n",ntohs(pTcpHeader->window));
    fprintf(logfile,"   |-Checksum       : %d\n",ntohs(pTcpHeader->check));
    fprintf(logfile,"   |-Urgent Pointer : %d\n",pTcpHeader->urg_ptr);
    fprintf(logfile,"\n");
    fprintf(logfile,"                        DATA Dump                         ");
    fprintf(logfile,"\n");

    fprintf(logfile,"IP Header\n");
    PrintData(pi_pBuff,nIpHeaderLength);

    fprintf(logfile,"TCP Header\n");
    PrintData(pi_pBuff+nIpHeaderLength,pTcpHeader->doff*4);

    fprintf(logfile,"Data Payload\n");
    PrintData(pi_pBuff + nIpHeaderLength + pTcpHeader->doff*4 , (pi_nSize - pTcpHeader->doff*4-pIpHeader->ihl*4) );

    unsigned char* pData = pi_pBuff + nIpHeaderLength + pTcpHeader->doff;
    printf("%02x %02x %02x %02x", pData[0], pData[1], pData[2], pData[3]);
    std::cout << std::endl;

    fprintf(logfile,"\n###########################################################");
}

void PrintUdpPacket(BU8* pi_pBuff , const BU32& pi_nSize)
{

    unsigned short nIpHeaderLength;

    struct iphdr *pIpHeader = (struct iphdr *)pi_pBuff;
    nIpHeaderLength = pIpHeader->ihl*4;

    struct udphdr *pUdpHeader = (struct udphdr*)(pi_pBuff + nIpHeaderLength);

    fprintf(logfile,"\n\n***********************UDP Packet*************************\n");

    PrintIpHeader(pi_pBuff,pi_nSize);

    fprintf(logfile,"\nUDP Header\n");
    fprintf(logfile,"   |-Source Port      : %d\n" , ntohs(pUdpHeader->source));
    fprintf(logfile,"   |-Destination Port : %d\n" , ntohs(pUdpHeader->dest));
    fprintf(logfile,"   |-UDP Length       : %d\n" , ntohs(pUdpHeader->len));
    fprintf(logfile,"   |-UDP Checksum     : %d\n" , ntohs(pUdpHeader->check));

    fprintf(logfile,"\n");
    fprintf(logfile,"IP Header\n");
    PrintData(pi_pBuff , nIpHeaderLength);

    fprintf(logfile,"UDP Header\n");
    PrintData(pi_pBuff+nIpHeaderLength , sizeof pUdpHeader);

    fprintf(logfile,"Data Payload\n");
    PrintData(pi_pBuff + nIpHeaderLength + sizeof pUdpHeader ,( pi_nSize - sizeof pUdpHeader - pIpHeader->ihl * 4 ));

    fprintf(logfile,"\n###########################################################");
}

void PrintIcmpPacket(unsigned char* pi_pBuff , int pi_nSize)
{
    unsigned short nIpHeaderLength;

    struct iphdr *pIpHeader = (struct iphdr *)pi_pBuff;
    nIpHeaderLength = pIpHeader->ihl*4;

    struct icmphdr *pIcmpHeader = (struct icmphdr *)(pi_pBuff + nIpHeaderLength);

    fprintf(logfile,"\n\n***********************ICMP Packet*************************\n");

    PrintIpHeader(pi_pBuff , pi_nSize);

    fprintf(logfile,"\n");

    fprintf(logfile,"ICMP Header\n");
    fprintf(logfile,"   |-Type : %d",(unsigned int)(pIcmpHeader->type));

    if((unsigned int)(pIcmpHeader->type) == 11)
        fprintf(logfile,"  (TTL Expired)\n");
    else if((unsigned int)(pIcmpHeader->type) == ICMP_ECHOREPLY)
        fprintf(logfile,"  (ICMP Echo Reply)\n");
    fprintf(logfile,"   |-Code : %d\n",(unsigned int)(pIcmpHeader->code));
    fprintf(logfile,"   |-Checksum : %d\n",ntohs(pIcmpHeader->checksum));
    //fprintf(logfile,"   |-ID       : %d\n",ntohs(icmph->id));
    //fprintf(logfile,"   |-Sequence : %d\n",ntohs(icmph->sequence));
    fprintf(logfile,"\n");

    fprintf(logfile,"IP Header\n");
    PrintData(pi_pBuff,nIpHeaderLength);

    fprintf(logfile,"UDP Header\n");
    PrintData(pi_pBuff + nIpHeaderLength , sizeof pIcmpHeader);

    fprintf(logfile,"Data Payload\n");
    PrintData(pi_pBuff + nIpHeaderLength + sizeof pIcmpHeader , (pi_nSize - sizeof pIcmpHeader - pIpHeader->ihl * 4));

    fprintf(logfile,"\n###########################################################");
}

void PrintData (unsigned char* pi_pData , int pi_nSize)
{

    for(i=0 ; i < pi_nSize ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            fprintf(logfile,"         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(pi_pData[j]>=32 && pi_pData[j]<=128)
                    fprintf(logfile,"%c",(unsigned char)pi_pData[j]); //if its a number or alphabet

                else fprintf(logfile,"."); //otherwise print a dot
            }
            fprintf(logfile,"\n");
        }

        if(i%16==0) fprintf(logfile,"   ");
            fprintf(logfile," %02X",(unsigned int)pi_pData[i]);

        if( i==pi_nSize-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) fprintf(logfile,"   "); //extra spaces

            fprintf(logfile,"         ");

            for(j=i-i%16 ; j<=i ; j++)
            {
                if(pi_pData[j]>=32 && pi_pData[j]<=128) fprintf(logfile,"%c",(unsigned char)pi_pData[j]);
                else fprintf(logfile,".");
            }
            fprintf(logfile,"\n");
        }
    }
}
