#ifndef _FOGHOLDER_
#define _FOLHOLDER
#include <kamek.hpp>
#include <core/egg/3D/Fog.hpp>
#include <game/File/BFG.hpp>

class BFGHolder {
    explicit BFGHolder(BFG *raw); //805adff0 built with the 0th entry
    virtual ~BFGHolder(); //805ae774 vtable 808b6e64
    void Update(u8 bfgEntryIdx, float f1); //805ae0f8
    GXFogType type;
    float startZ;
    float endZ;
    u8 unknown_0x10;
    GXColor color; //0x10
    u16 hasRangeCorrection; //0x14
    float transitionSpeed; //0x18
    u8 unknown_0x1C[2]; //0x18/0x19 of the bfgentry
    u8 unknown_0x1E[0x24 - 0x1E];
    BFG *raw; //0x24
    float inverseThicknessRatio; //0x28 the lower, the thicker the fog, set to 1
    u8 unknown_0x2C[0x38 - 0x2C];
}; //0x38

class FogManager {
public:
    explicit FogManager(EGG::FogMgr *fogMgr); //805ae440
    virtual ~FogManager(); //805ae734 vtable 808b6e58
    void Update(u8 holderIdx); //805ae53c
    EGG::FogMgr *fogMgr; //0x4
    BFGHolder *bfgHolders; //0x8
    u32 bfgEntryCount; //0xC
    float unknown_0x10;
    u8 curBfgEntryIdx; //0x14
    u8 padding[3];
}; //0x18

#endif