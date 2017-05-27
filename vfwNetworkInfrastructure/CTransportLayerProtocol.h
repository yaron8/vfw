/*
 * CTransportLayerProtocol.h
 *
 *  Created on: May 27, 2017
 *      Author: root
 */

#ifndef CTRANSPORTLAYERPROTOCOL_H_
#define CTRANSPORTLAYERPROTOCOL_H_

#include "CBaseFacade.h"

enum ETransportLayerProtocol
{
	eIcmpTransportLayerProtocol 	= 1,
	eIgmpTransportLayerProtocol		= 2,
	eTcpTransportLayerProtocol 		= 6,
	eUdpTransportLayerProtocol		= 17,
	eUnkownTransportLayer
};

class CTransportLayerProtocol
{
public:
	CTransportLayerProtocol();
	virtual ~CTransportLayerProtocol() = 0;

	virtual HRESULT Init(BU8* pi_pTransportLayerDatagram) = 0;

	BU16 GetSrcPort();
	BU16 GetDestPort();

	BU16 GetChecksum();
	BU16 GetDataOffset();

protected:
	BU16 m_nSrcPort;
	BU16 m_nDestPort;
	BU16 m_nChecksum;
	BU8  m_nDataOffset;
};

#endif /* CTRANSPORTLAYERPROTOCOL_H_ */
