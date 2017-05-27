/*
 * ByteUtils.h
 *
 *  Created on: May 27, 2017
 *      Author: root
 */

#ifndef BYTEUTILS_H_
#define BYTEUTILS_H_

void PrintHexDump(void* pi_pObj, BU64 pi_nBytesSize)
{
    std::cout << "Print HexDump, bytes: " << pi_nBytesSize << ":" << std::endl <<
    		"==========================="<< std::endl;
    BU8* p = reinterpret_cast<BU8*>(pi_pObj);
    for(BU64 i=0; i<pi_nBytesSize; i++)
    {
        if(i%16 == 0 && i!=0)
            std::cout << std::endl;

        printf("%02x ", p[i]);
    }
}

void Reverse16bit(BU16& pi_n2Bytes)
{
	pi_n2Bytes = (pi_n2Bytes >> 8) | (pi_n2Bytes << 8);
}

void Reverse32bit(BU32& pi_n4Bytes)
{
	pi_n4Bytes = (pi_n4Bytes >> 24) | (pi_n4Bytes << 24) | ((pi_n4Bytes >> 8) & 0xFF00) | ((pi_n4Bytes << 8) & 0xFF0000);
}

void Reverse64bit(BU64& pi_n8Bytes)
{
	pi_n8Bytes = (pi_n8Bytes >> 56) | (pi_n8Bytes << 56) |
					((pi_n8Bytes >> 40) & 0xFF00) | ((pi_n8Bytes << 40) & 0xFF000000000000) |
					((pi_n8Bytes >> 24) & 0xFF0000) | ((pi_n8Bytes << 24) & 0xFF0000000000) |
					((pi_n8Bytes >> 8) & 0xFF000000) | ((pi_n8Bytes << 8) & 0xFF00000000)
					;
}

#endif /* BYTEUTILS_H_ */
