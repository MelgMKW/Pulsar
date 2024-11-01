#ifndef _BITROTATOR_
#define _BITROTATOR_
#include <kamek.hpp>

struct BitRotator { //rotates bit starting from 0x80000000 and decreasing for as many frames as totalCount, before resetting
    BitRotator(u32 totalCount); //805506ec
    void Update(); //8055070c
    u32 enabledBits; //0x4 from count
    u32 curVal; //0x8 cntlzw to get the idx
};

#endif