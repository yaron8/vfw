/*
 * CTcpTransportLayer.h
 *
 *  Created on: May 27, 2017
 *      Author: root
 */

#ifndef CTCPTRANSPORTLAYER_H_
#define CTCPTRANSPORTLAYER_H_

#include "CBaseFacade.h"
#include "CTransportLayerProtocol.h"

class CTcpTransportLayer : public CTransportLayerProtocol
{
public:
	CTcpTransportLayer();
	virtual ~CTcpTransportLayer();

	HRESULT Init(BU8* pi_pTransportLayerDatagram);

	BU32 GetSequenceNumber();
	BU32 GetAckNumber();
	BU8 GetReserved();
	bool IsNsFlagSet();
	bool IsCwrFlagSet();
	bool IsUrgFlagSet();
	bool IsAckFlagSet();
	bool IsPushFlagSet();
	bool IsResetFlagSet();
	bool IsSynFlagSet();
	bool IsFinFlagSet();

private:
	BU32 m_nSequenceNumber;
	BU32 m_nAckNumber; // if ack set
	BU8  m_nReserved;
	BU8  m_nNS;
	BU8  m_nFlags;		// CWR, ECE, URG, ACK, PSH, RST, SYN, FIN
	BU16 m_nWindowSize;
	BU16 m_nUrgentPointer; // if URG is set
};

#endif /* CTCPTRANSPORTLAYER_H_ */
