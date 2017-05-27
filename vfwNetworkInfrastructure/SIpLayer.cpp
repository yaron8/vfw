/*
 * SIpLayer.cpp
 *
 *  Created on: May 26, 2017
 *      Author: root
 */

#include "SIpLayer.h"
#include <stdio.h>
#include <string.h>
#include "ByteUtils.h"

SIpLayer::SIpLayer() :
		m_eIpVersion(eIpV4),
		m_nHeaderLength(0),
		m_nTotalLength(0),
		m_nTimeToLive(0),
		m_nTransportLayerProtocol(0),
		m_nTransportLayerOffset(0)
{

}

HRESULT SIpLayer::Init(const BU8* pi_pIpDatagramBuff)
{
	HRESULT hRes = H_SUCCESS;
	if(pi_pIpDatagramBuff == NULL)
	{
		return H_FAIL;
	}

	//struct iphdr *pIpHeader = (struct iphdr *) pi_pPacketBuff;

	BU8 tmp;
	memcpy(&tmp, pi_pIpDatagramBuff, 1);
	BU8 nVersion = (tmp & 0xF0) >> 4;

	switch(nVersion)
	{
		case eIpV4:
		{
			m_eIpVersion = eIpV4;
		}
		break;

		case eIpV6:
		{
			m_eIpVersion = eIpV6;
		}
		break;

		default:
		{
			hRes = H_FAIL;
			std::cout << "Unsupported ip version. version is: " << BU32(nVersion) << std::endl;
		}
		break;
	}

	if(IsFailed(hRes))
	{
		return hRes;
	}

	switch(m_eIpVersion)
	{
		case eIpV4:
		{
			ProcessPacketIpV4(pi_pIpDatagramBuff);
		}
		break;

		case eIpV6:
		{
			ProcessPacketIpV6(pi_pIpDatagramBuff);
		}
		break;
	}

	return hRes;
}


HRESULT SIpLayer::ProcessPacketIpV4(const BU8* pi_pIpDatagramBuff)
{
	HRESULT hRes = H_SUCCESS;

	BU8 tmp;
	memcpy(&tmp, pi_pIpDatagramBuff, 1);

	m_nHeaderLength = tmp & 0x0F;
	memcpy(&m_nTotalLength, &pi_pIpDatagramBuff[2], 2);
	Reverse16bit(m_nTotalLength);

	printf("%02x %02x\n", pi_pIpDatagramBuff[2], pi_pIpDatagramBuff[3]);

	memcpy(&m_nTimeToLive, &pi_pIpDatagramBuff[8], 1);

	memcpy(&m_nTransportLayerProtocol, &pi_pIpDatagramBuff[9], 1);

	BU8 pSrcIp[4], pDestIp[4];
	memcpy(pSrcIp, &pi_pIpDatagramBuff[12], 4);
	memcpy(pDestIp, &pi_pIpDatagramBuff[16], 4);

	m_srcIpAddress.SetIpAddress(pSrcIp, IPV4_BYTES_LENGTH);
	m_destIpAddress.SetIpAddress(pDestIp, IPV4_BYTES_LENGTH);

	//if(m_srcIpAddress.ToString() == "192.168.221.128")
	//{
	static bool b = false;
	if(!b)
	{
		b = true;
		std::cout << "===============================" << std::endl;

		//PrintHexDump(const_cast<BU8*>(pi_pIpDatagramBuff), m_nTotalLength);

		std::cout << "Src IP: " << m_srcIpAddress.ToString() << std::endl;
		std::cout << "Dest IP: " << m_destIpAddress.ToString() << std::endl;
		std::cout << "Header Length: " << BU32(m_nHeaderLength) << std::endl;
		std::cout << "Total Length: " << BU32(m_nTotalLength) << std::endl;
		std::cout << "Transport Protocol: " << BU32(m_nTransportLayerProtocol) << std::endl;

		m_nTransportLayerOffset = 20;
		if(m_nHeaderLength > 5)
		{
			//TODO: ip header has Options
			m_nTransportLayerOffset = 36;
			std::cout << "ip header has Options" << std::endl;
		}
		std::cout << "===============================" << std::endl;
	}

	return hRes;
}

HRESULT SIpLayer::ProcessPacketIpV6(const BU8* pi_pIpDatagramBuff)
{
	HRESULT hRes = H_SUCCESS;

	return hRes;
}

SIpLayer::~SIpLayer()
{

}

