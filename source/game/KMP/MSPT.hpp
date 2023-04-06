#ifndef _MSPT_
#define _MSPT_
#include <game/KMP/SectionBase.hpp>

struct MSPT {
    Vec3 position;
    Vec3 angle;
    u16 id;
    u16 unknown_0x1A;
};

typedef KMPSection<MSPT> MSPTSection;

#endif