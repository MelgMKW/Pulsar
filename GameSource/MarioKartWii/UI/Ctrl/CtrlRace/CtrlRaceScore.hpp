#ifndef _CTRLRACESCORE_
#define _CTRLRACESCORE_
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>


//_sinit_ at 807f7bb0

class CtrlRaceScore : public CtrlRaceBase { //https://imgur.com/6vAMhch "+5" in this screenshot
public:
    ~CtrlRaceScore() override; //807f7b48 vtable 808d3fc0
    void InitSelf() override; //0x18 807f76f8
    void OnUpdate() override; //0x1c 807f784c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807f7ba4
    const char* GetClassName() const override; //0x2c 807f76ec
    void Load(); //807f7914
    void SetMessage(u32 sameMissionParam); //807f7970
    u8 unknown_0x198[0x1A4 - 0x198];
    u32 bmgId; //0x198
    u32 someMissionParam; //0x19c
    u32 score; //0x1a0
}; //0x1a4

#endif