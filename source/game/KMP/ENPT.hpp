#ifndef _ENPT_
#define _ENPT_
#include <game/KMP/SectionBase.hpp>

struct ENPT {
    Vec3 position;
    float width;
    u16 setting1;
    u8 setting2;
    u8 setting3;
}; //total size 0x14

typedef struct KMPSection<ENPT> ENPTSection;

#endif