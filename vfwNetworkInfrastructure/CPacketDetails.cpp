/*
 * CPacketDetails.cpp
 *
 *  Created on: May 25, 2017
 *      Author: root
 */

#include "CPacketDetails.h"
#include <stdio.h>
#include <string.h>

CPacketDetails::CPacketDetails(BU8* pi_pPacketBuff, const BU32& pi_nLength/*, ETransportLayerProtocol pi_eTransportProtocol*/) :
		//m_eTransportProtocol(pi_eTransportProtocol),
		m_nPacketLength(pi_nLength),
		m_nSrcPort(0),
		m_nDestPort(0),
		m_nApllicationLayerLength(0),
		m_pApplicationLayer(NULL)
{
	m_ipLayer.Init(pi_pPacketBuff);
}

CPacketDetails::~CPacketDetails()
{
	if(m_pApplicationLayer != NULL)
	{
		delete m_pApplicationLayer;
		m_pApplicationLayer = NULL;
	}
}

BU8 CPacketDetails::GetTransportLayerProtocol() const
{
	return m_ipLayer.m_nTransportLayerProtocol;
}


CIpAddress CPacketDetails::GetSrcIp() const
{
	return m_ipLayer.m_srcIpAddress;
}

CIpAddress CPacketDetails::GetDestIp() const
{
	return m_ipLayer.m_destIpAddress;
}
