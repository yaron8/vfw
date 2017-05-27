/*
 * SIpLayer.h
 *
 *  Created on: May 26, 2017
 *      Author: root
 */

#ifndef SIPLAYER_H_
#define SIPLAYER_H_

#include "CTypes.h"
#include "CIpAddress.h"

struct SIpLayer
{
	SIpLayer();
	virtual ~SIpLayer();

	HRESULT Init(const BU8* pi_pPacketBuff);

	HRESULT ProcessPacketIpV4(const BU8* pi_pIpBuff);
	HRESULT ProcessPacketIpV6(const BU8* pi_pIpBuff);



	EIpType 	m_eIpVersion;
	BU8 		m_nHeaderLength;
	BU16 		m_nTotalLength;
	//BU8 		m_nFlag;
	BU8			m_nTimeToLive;
	BU8			m_nTransportLayerProtocol;
	CIpAddress	m_srcIpAddress;
	CIpAddress	m_destIpAddress;
	BU16 		m_nTransportLayerOffset;

};

#endif /* SIPLAYER_H_ */
