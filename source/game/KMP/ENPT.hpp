#ifndef _ENPT_
#define _ENPT_
#include <game/KMP/KMPBlockBase.hpp>

struct ENPT {
    Vec3 position;
    float width; //0xC
    u16 setting1; //0x10
    u8 setting2; //0x12
    u8 setting3; //0x13
}; //total size 0x14

typedef struct KMPBlock<ENPT> ENPTBlock;

#endif