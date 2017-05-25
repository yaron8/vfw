/*
 * CNetworkTypes.h
 *
 *  Created on: May 23, 2017
 *      Author: root
 */

#ifndef CNETWORKTYPES_H_
#define CNETWORKTYPES_H_


#define PACKET_MAX_SIZE		65536

enum ETransportLayerProtocol
{
	eIcmpTransportLayerProtocol 	= 1,
	eIgmpTransportLayerProtocol		= 2,
	eTcpTransportLayerProtocol 		= 6,
	eUdpTransportLayerProtocol		= 17,
	eUnkownTransportLayer
};


#endif /* CNETWORKTYPES_H_ */
