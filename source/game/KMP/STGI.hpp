
#ifndef _STGI_
#define _STGI_
#include <game/KMP/KMPBlockBase.hpp>

struct STGI {
    u8 lapCount; //0x0
    u8 polePosition; //0x1
    u8 narrow; //0x2
    u8 enableLensFlare; //0x3
    u32 flareColor; //0x4
    u8 flareAlpha; //0x8
    u8 padding; //0x9
    u16 speedMod; //0xA cusually 0 but for the code 
}; //total size 0xc

typedef struct KMPBlock<STGI> STGIBlock;

#endif
