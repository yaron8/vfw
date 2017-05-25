/*
 * CIpAddress.h
 *
 *  Created on: May 25, 2017
 *      Author: root
 */

#ifndef CIPADDRESS_H_
#define CIPADDRESS_H_

#include "CBaseFacade.h"

enum EIpType
{
	eIpV4,
	eIpV6
};

#define IPV4_BYTES_LENGTH	8
#define IPV6_BYTES_LENGTH	16

class CIpAddress {
public:
	CIpAddress(BU8* pi_pIpAddress, const BU8& pi_nLength);
	CIpAddress(BU8* pi_pIpAddress, const EIpType eIpType);
	virtual ~CIpAddress();

	CString ToString();

private:
	EIpType m_eIpType;
	BU8 m_nLength;
	BU8* m_pStartByte;
	CString m_sIpAsString;
};

#endif /* CIPADDRESS_H_ */
