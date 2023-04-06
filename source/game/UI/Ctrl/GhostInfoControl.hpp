#ifndef _GHOSTINFOCONTROL_
#define _GHOSTINFOCONTROL_

#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>


//_sinit_ at 805e2f4c
class GhostInfoControl : public LayoutUIControl {
public:
    GhostInfoControl(); //0x805e274c
    ~GhostInfoControl() override; //0x805e27dc vtable 808b92c0
    void InitSelf() override; //0x18 805e2964
    void OnUpdate() override; //0x1c 805e2968
    int GetRuntimeTypeInfo() const override; //0x28 805e2f40
    const char *GetClassName() const override; //0x2c 805e2740
    void Load(const char *variantName); //805e2844
    void UpdateInfoAnimate(GhostData *header, bool isNew, u32 animationId); //805e2d40
    void UpdateInfo(GhostData *header, bool isNew); //805e296c
    MiiGroup miiGroup; //0x174
    //0x20c
    u8 unknown_0x20C[0x234 - 0x20c];
    u32 unknown_0x234; //set to 0
    u16 unknown_0x238; //set to 0
    u16 unknown_0x23A; //set to 0
    float unknown_0x23C;
    float unknown_0x240;
    u16 unknown_0x244;
    u16 unknown_0x246;
    u32 unknown_0x248; //gets set to 0x00080000 in the ctor
}; //total size 0x24C
size_assert(GhostInfoControl, 0x24C);

#endif