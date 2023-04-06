#ifndef _BFG_
#define _BFG_
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>


struct BFGEntry {
    GXFogType type;
    float startZ; //0x4
    float endZ; //0x8
    GXColor color; //0xC
    u16 hasRangeCorrection; //0x10
    u16 rangeCorrectionCenter;
    float entriesTransitionSpeed; //0x14
    u8 unknown_0x18[2];
};

struct BFG {
    BFGEntry entries[4];
};

#endif