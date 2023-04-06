#ifndef _SHADOW_MODEL_DIRECTOR_
#define _SHADOW_MODEL_DIRECTOR_
#include <kamek.hpp>
#include <game/Visual/Model/ModelDirector.hpp>

using namespace nw4r;
class ShadowModelDirector : public ModelDirector {
public:
    ShadowModelDirector(ClipInfo *clipInfo, u32 r5, u32 bitfield); //805b8984
    ShadowModelDirector(u32 bitfield); //805b89f4
    ~ShadowModelDirector() override; //805b8a48 vtable 808b7340
    void SetScnMdlOptions(g3d::ScnMdl *scnMdl, bool enableOptions, bool doNotCalcWorldMatVtx) override; //0x20 805b8aa0
    ut::Link shadowLink; //0x4c
    u8 unknown_0x54;
    u8 padding[3];
}; //0x58
#endif