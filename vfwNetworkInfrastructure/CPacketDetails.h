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

class CPacketDetails
{

public:
	CPacketDetails();
	virtual ~CPacketDetails();

private:
	ETransportLayerProtocol m_eTransportProtocol;
	BU16 m_nSrcPort;
	BU16 m_nDestPort;

};

#endif /* CPACKETDETAILS_H_ */
