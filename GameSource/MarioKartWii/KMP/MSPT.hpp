#ifndef _MSPT_
#define _MSPT_
#include <MarioKartWii/KMP/KMPBlockBase.hpp>

struct MSPT {
    Vec3 position;
    Vec3 angle;
    u16 id;
    u16 unknown_0x1A;
};

typedef KMPBlock<MSPT> MSPTBlock;

#endif