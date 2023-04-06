#ifndef _KTPT_
#define _KTPT_
#include <game/KMP/SectionBase.hpp>

struct KTPT {
    Vec3 position;
    Vec3 rotation;
    u16 playerId;
    u16 unknown_0x1A;
}; //total size 0x1C

typedef struct KMPSection<KTPT> KTPTSection;

#endif