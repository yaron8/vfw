/*
 * Utils.h
 *
 *  Created on: May 27, 2017
 *      Author: root
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "CBaseFacade.h"

void PrintHexDump(void* pi_pObj, BU64 pi_nLength)
{
    std::cout << "Print HexDump:" << std::endl << "==========================="<< std::endl;
    BU8* p = reinterpret_cast<BU8*>(pi_pObj);
    for(BU64 i=0; i<pi_nLength; i++)
    {
        if(i%16 == 0 && i!=0)
            std::cout << std::endl;

        printf("%02x ", p[i]);
    }
}

#endif /* UTILS_H_ */
