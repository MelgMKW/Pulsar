
#ifndef _STGI_
#define _STGI_
#include <game/KMP/SectionBase.hpp>

struct STGI {
    u8 lapCount;
    u8 polePosition;
    u8 narrow;
    u8 enableFlashing;
    u8 padding;
    u8 flareColor[4]; //at offset 0x5
    u8 unknown_0x9;
    u16 speedMod; //usually 0 but for the code
}; //total size 0xc

typedef struct KMPSection<STGI> STGISection;

#endif
