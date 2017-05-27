/*
 * CPacketDetails.cpp
 *
 *  Created on: May 25, 2017
 *      Author: root
 */

#include "CPacketDetails.h"
#include "CBaseFacade.h"
#include "CTcpTransportLayer.h"

CPacketDetails::CPacketDetails(BU8* pi_pPacketBuff, const BU32& pi_nLength/*, ETransportLayerProtocol pi_eTransportProtocol*/) :
		//m_eTransportProtocol(pi_eTransportProtocol),
		m_nPacketLength(pi_nLength),
		m_nSrcPort(0),
		m_nDestPort(0),
		m_pTransportLayer(NULL),
		m_nApllicationLayerLength(0),
		m_pApplicationLayer(NULL)
{
	HRESULT hRes = H_SUCCESS;
	hRes = m_ipLayer.Init(pi_pPacketBuff);

	if(IsSucceeded(hRes))
	{
		switch(m_ipLayer.m_nTransportLayerProtocol)
		{
			case eTcpTransportLayerProtocol:
			{
				m_pTransportLayer = new (std::nothrow) CTcpTransportLayer();
				if(m_pTransportLayer == NULL)
				{
					hRes = H_FAIL;
					std::cout << "Failed to allocate pointer to transport layer" << std::endl;
				}
				else
				{
					m_pTransportLayer->Init(pi_pPacketBuff + m_ipLayer.m_nTransportLayerOffset);
				}
			}
		}
	}
}

CPacketDetails::~CPacketDetails()
{
	if(m_pApplicationLayer != NULL)
	{
		delete m_pApplicationLayer;
		m_pApplicationLayer = NULL;
	}

	if(m_pTransportLayer != NULL)
	{
		delete m_pTransportLayer;
		m_pTransportLayer = NULL;
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
