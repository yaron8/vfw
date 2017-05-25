/*
 * CTypes.h
 *
 *  Created on: May 23, 2017
 *      Author: root
 */

#ifndef CTYPES_H_
#define CTYPES_H_

#include <inttypes.h>
#include <iostream>

typedef char			BS8;
typedef unsigned char	BU8;

typedef int16_t			BS16;
typedef uint16_t		BU16;

typedef int32_t			BS32;
typedef uint32_t		BU32;

typedef int64_t			BS64;
typedef int64_t			BS64;
typedef uint64_t		BU64;

typedef std::string 	CString;

// HRESULT
typedef BU8 HRESULT;
#define H_SUCCESS	0;
#define H_FAIL		1;
#define H_IGNORE	2;
#define H_INVALID	4;
// next value will be 8, because each status is represented by a bit.

inline bool IsFailed(const BU8& pi_hResult)
{
	return pi_hResult == H_FAIL;
}

inline bool IsSucceeded(const BU8& pi_hResult)
{
	return pi_hResult == H_SUCCESS;
}

#endif /* CTYPES_H_ */
