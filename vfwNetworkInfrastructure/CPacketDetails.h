/*
 * CPacketDetails.h
 *
 *  Created on: May 25, 2017
 *      Author: root
 */

#ifndef CPACKETDETAILS_H_
#define CPACKETDETAILS_H_

#include "CBaseFacade.h"
#include "CNetworkTypes.h"
#include "SIpLayer.h"

class CPacketDetails
{

public:
	CPacketDetails(BU8* pi_pPacketBuff, const BU32& pi_nPacketLength/*, ETransportLayerProtocol pi_eTransportProtocol*/);
	virtual ~CPacketDetails();

	BU8 GetTransportLayerProtocol() const;

	CIpAddress GetSrcIp() const;
	CIpAddress GetDestIp() const;

private:
	//ETransportLayerProtocol m_eTransportProtocol;
	BU32 m_nPacketLength;
	BU16 m_nSrcPort;
	BU16 m_nDestPort;

	SIpLayer m_ipLayer;

	BU16 m_nApllicationLayerLength;
	BU8* m_pApplicationLayer;
};

#endif /* CPACKETDETAILS_H_ */
