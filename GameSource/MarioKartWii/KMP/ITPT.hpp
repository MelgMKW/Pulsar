#ifndef _ITPT_
#define _ITPT_
#include <MarioKartWii/KMP/KMPBlockBase.hpp>

struct ITPT {
    Vec3 position;
    float width;
    u16 setting1; //0x10
    u16 setting2;
}; //total size 0x14

typedef struct KMPBlock<ITPT> ITPTBlock;


#endif