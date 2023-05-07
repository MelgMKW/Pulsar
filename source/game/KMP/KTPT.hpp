#ifndef _KTPT_
#define _KTPT_
#include <game/KMP/SectionBase.hpp>

struct KTPT {
    Vec3 position;
    Vec3 rotation; //0xc
    u16 playerId; //0x18
    u16 unknown_0x1A;
}; //total size 0x1C

typedef struct KMPSection<KTPT> KTPTSection;

#endif