/*
 * CIpAddress.cpp
 *
 *  Created on: May 25, 2017
 *      Author: root
 */

#include "CIpAddress.h"
#include <stdio.h>
#include <string.h>
#include <sstream>

CIpAddress::CIpAddress() :
	m_eIpType(eIpV4),
	m_nLength(0),
	m_pStartByte(NULL)
{

}

CIpAddress::CIpAddress(BU8* pi_pIpAddress, const BU8& pi_nLength) :
	m_eIpType(eIpV4),
	m_nLength(pi_nLength),
	m_pStartByte(NULL)
{
	SetIpAddress(pi_pIpAddress, pi_nLength);
}

CIpAddress::CIpAddress(BU8* pi_pIpAddress, const EIpType pi_eIpType) :
		CIpAddress(pi_pIpAddress, (pi_eIpType==eIpV4 ? IPV4_BYTES_LENGTH : IPV6_BYTES_LENGTH))
{
}

CIpAddress::~CIpAddress() {
	if(m_pStartByte != NULL)
	{
		delete[] m_pStartByte;
		m_pStartByte = NULL;
	}
}

HRESULT CIpAddress::SetIpAddress(BU8* pi_pIpAddress, const BU8 pi_nLength)
{
	HRESULT hRes = H_SUCCESS;
	if(pi_nLength == IPV4_BYTES_LENGTH)
	{
		m_pStartByte = new (std::nothrow) BU8[IPV4_BYTES_LENGTH];
		if(m_pStartByte != NULL)
		{
			memcpy(m_pStartByte, pi_pIpAddress, IPV4_BYTES_LENGTH);
		}
		else
		{
			hRes = H_FAIL;
		}
	}
	else
	{
		m_pStartByte = new (std::nothrow) BU8[IPV6_BYTES_LENGTH];
		if(m_pStartByte != NULL)
		{
			memcpy(m_pStartByte, pi_pIpAddress, IPV4_BYTES_LENGTH);
		}
		else
		{
			hRes = H_FAIL;
		}
	}
	return hRes;
}

CString CIpAddress::ToString()
{
	if(m_sIpAsString.empty())
	{
		std::stringstream ss;
		int nLength = (m_eIpType == eIpV4 ? IPV4_BYTES_LENGTH : IPV6_BYTES_LENGTH);
		for(int i=0; i<nLength; i++)
		{
			ss << (i>0 ? "." : "") << BU32(m_pStartByte[i]);
		}
		m_sIpAsString = ss.str();
	}
	return m_sIpAsString;
}

bool CIpAddress::IsEmpty()
{
	return m_pStartByte==NULL;
}
