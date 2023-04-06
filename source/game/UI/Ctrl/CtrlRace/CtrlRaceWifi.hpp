#ifndef _CTRLRACEWIFI_
#define _CTRLRACEWIFI_
#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>
//_sinit_ at 807f9258
class CtrlRaceWifiStartMessage : public CtrlRaceBase {
public:
    //no ctor
    ~CtrlRaceWifiStartMessage() override; //807f91f0 vtable 808d4110 
    void OnUpdate() override; //0x1c 807f8c34
    int GetRuntimeTypeInfo() const override; //0x28 807f924c
    const char *GetClassName() const override; //0x2c 807f8988
    void SetPanePosition() override; //0x40 807f8be8
    nw4r::lyt::Pane *GetPane() const override; //0x44 807f91e8
    bool IsActive() override; //0x48 807f8bd8 check if raceinfo is above countdown stage, in which case control is made invisible
    bool HasStarted() override; //0x4c 807f8ba4 checks raceinfo->timer //0x4c


    void Load(u32 variant, u8 hudSlotId); //807f8994 variant = localPlayerCount except 3 where it's 4 gamemodeType determines the displayed message
    nw4r::lyt::Pane *textBox_00;
    u8 unknown_0x19C[0x1A0 - 0x19C];

}; //total size 0x1a0
//update pause position calls 807f8bd8 to make the state disappear
class CtrlRaceWaitSymbol : public CtrlRaceBase {
    //no ctor
    ~CtrlRaceWaitSymbol() override; //807f9110 vtable 808d4070
    void OnUpdate() override; //0x1c 807f90f8
    int GetRuntimeTypeInfo() const override; //0x28 807f916c
    const char *GetClassName() const override; //0x2c 807f8f9c
    void SetPanePosition() override; //0x40 807f90ac
    nw4r::lyt::Pane *GetPane() const override; //0x44 807f9108
    bool IsActive() override; //0x48 807f909c check if raceinfo is above countdown stage, in which case control is made invisible
    bool HasStarted() override; //0x4c 807f9068 checks raceinfo->timer //0x4c
    nw4r::lyt::Pane *parts_null; //0x198
    u8 unknown_0x19C[0x1A0 - 0x19C];
    void Load(u32 r4, u8 hudSlotId); //807f8fac r4 not used
};

class CtrlRaceWifiFinishMessage : public CtrlRaceBase {
    //no ctor
    ~CtrlRaceWifiFinishMessage() override; //807f9180 vtable 808d40c0
    void OnUpdate() override; //0x1c 807f8f8c
    int GetRuntimeTypeInfo() const override; //0x28 807f91dc
    const char *GetClassName() const override; //0x2c 807f8c44
    void SetPanePosition() override; //0x40 807f8d90
    nw4r::lyt::Pane *GetPane() const override; //0x44 807f9178
    bool IsActive() override; //0x48 807f8d88 check if raceinfo is above countdown stage, in which case control is made invisible
    bool HasStarted() override; //0x4c 807f8d08 checks raceinfo->timer //0x4c
    void Load(u32 variant, u8 hudSlotId); //807f8c54
    nw4r::lyt::Pane *textBox_00;
    u8 unknown_0x19C[0x1A0 - 0x19C];
}; //total size 0x1a0

#endif