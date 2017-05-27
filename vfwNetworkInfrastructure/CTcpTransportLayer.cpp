/*
 * CTcpTransportLayer.cpp
 *
 *  Created on: May 27, 2017
 *      Author: root
 */

#include "CTcpTransportLayer.h"
#include "ByteUtils.h"

CTcpTransportLayer::CTcpTransportLayer() :
		m_nSequenceNumber(0),
		m_nAckNumber(0),
		m_nReserved(0),
		m_nNS(0),
		m_nFlags(0),
		m_nWindowSize(0),
		m_nUrgentPointer(0)
{

}

CTcpTransportLayer::~CTcpTransportLayer()
{

}

HRESULT CTcpTransportLayer::Init(BU8* pi_pTransportLayerDatagram)
{
	HRESULT hRes = H_SUCCESS;

	memcpy(&m_nSrcPort, pi_pTransportLayerDatagram, 2);
	memcpy(&m_nDestPort, pi_pTransportLayerDatagram + 2, 2);

	Reverse16bit(m_nSrcPort);
	Reverse16bit(m_nDestPort);

	memcpy(&m_nSequenceNumber, pi_pTransportLayerDatagram + 4, 4);
	Reverse32bit(m_nSequenceNumber);

	memcpy(&m_nAckNumber, pi_pTransportLayerDatagram + 8, 4);
	Reverse32bit(m_nAckNumber);

	BU8 tmp;
	memcpy(&tmp, pi_pTransportLayerDatagram + 12, 1);

	m_nDataOffset = tmp >> 4;
	m_nReserved = (tmp & 0x0F) >> 1;
	m_nNS = tmp & 1;

	memcpy(&m_nFlags, pi_pTransportLayerDatagram + 13, 1);

	memcpy(&m_nWindowSize, pi_pTransportLayerDatagram + 14, 2);
	Reverse16bit(m_nWindowSize);

	memcpy(&m_nChecksum, pi_pTransportLayerDatagram + 16, 2);
	Reverse16bit(m_nChecksum);

	memcpy(&m_nUrgentPointer, pi_pTransportLayerDatagram + 18, 2);
	Reverse16bit(m_nUrgentPointer);

	return hRes;
}


BU32 CTcpTransportLayer::GetSequenceNumber()
{
	return m_nSequenceNumber;
}

BU32 CTcpTransportLayer::GetAckNumber()
{
	return m_nAckNumber;
}

BU8 CTcpTransportLayer::GetReserved()
{
	return m_nReserved;
}

bool CTcpTransportLayer::IsNsFlagSet()
{
	return m_nNS != 0;
}

bool CTcpTransportLayer::IsCwrFlagSet()
{
	return (m_nFlags & (1 << 7)) != 0;
}

bool CTcpTransportLayer::IsUrgFlagSet()
{
	return (m_nFlags & (1 << 6)) != 0;
}

bool CTcpTransportLayer::IsAckFlagSet()
{
	return (m_nFlags & (1 << 5)) != 0;
}

bool CTcpTransportLayer::IsPushFlagSet()
{
	return (m_nFlags & (1 << 4)) != 0;
}

bool CTcpTransportLayer::IsResetFlagSet()
{
	return (m_nFlags & (1 << 3)) != 0;
}

bool CTcpTransportLayer::IsSynFlagSet()
{
	return (m_nFlags & (1 << 2)) != 0;
}

bool CTcpTransportLayer::IsFinFlagSet()
{
	return (m_nFlags & 1) != 0;
}
