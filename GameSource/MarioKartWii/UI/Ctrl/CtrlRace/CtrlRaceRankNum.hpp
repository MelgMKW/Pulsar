#ifndef _CTRLRACERANKNUM_
#define _CTRLRACERANKNUM_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_ at 807f4e48
class CtrlRaceRankNum : public CtrlRaceBase { //position tracker
public:
    //no ctor
    ~CtrlRaceRankNum() override; //807f4de0 vtable 808d3e98
    void Init() override; //0xc 807f48fc
    void OnUpdate() override; //0x1c 807f4a08
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807f4e3c
    const char* GetClassName() const override; //0x2c 807f48f0
    bool IsInactive() override; //0x48 807f4d40

    void Load(const char* variant, u8 hudSlotId); //807f4bb4
    u8 prevPosition; //0x198 compared against raceinfo's
    u8 padding2[3];
    u32 playerId; //0x19c
    lyt::Pane* position_1_00; //0x1a0
};//Total Size 0x1a4

#endif