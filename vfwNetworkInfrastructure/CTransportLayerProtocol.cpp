/*
 * CTransportLayerProtocol.cpp
 *
 *  Created on: May 27, 2017
 *      Author: root
 */

#include "CTransportLayerProtocol.h"

CTransportLayerProtocol::CTransportLayerProtocol() :
		m_nSrcPort(0),
		m_nDestPort(0),
		m_nChecksum(0),
		m_nDataOffset(0)
{

}

CTransportLayerProtocol::~CTransportLayerProtocol()
{

}

BU16 CTransportLayerProtocol::GetSrcPort()
{
	return m_nSrcPort;
}

BU16 CTransportLayerProtocol::GetDestPort()
{
	return m_nDestPort;
}

BU16 CTransportLayerProtocol::GetChecksum()
{
	return m_nChecksum;
}

BU16 CTransportLayerProtocol::GetDataOffset()
{
	return m_nDataOffset;
}

