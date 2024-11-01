#ifndef _CTRLRACEBATTLEPOINT_
#define _CTRLRACEBATTLEPOINT_
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_ at 807edcbc
class CtrlRaceBattlePoint : public CtrlRaceBase { //bottomleft
public:
    //no ctor
    ~CtrlRaceBattlePoint() override; //807edbec vtable 808d3b38
    void Init() override; //0xc 807ed098
    void OnUpdate() override; //0x1c 807ed134
    void SetPositionAnim(PositionAndScale& positionAndScale, float curFrame) override; //0x20 807ecfac
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807edc48
    const char* GetClassName() const override; //0x2c 807ecd88
    void SetPanePosition() override; //0x40 807ecd98

    void Load(const char* ctrName, u8 hudSlotId); //807ed1f0

    u32 curScore; //0x198
};//Total Size 0x19c

class CtrlRaceBattleAddPoint : public CtrlRaceBase { //+1 -1 on scorechange
public:
    //no ctor
    ~CtrlRaceBattleAddPoint() override; //807edc60 vtable 808d3b88
    void InitSelf() override; //0x18 807ec9ac
    void OnUpdate(); //0x1c 807eca8c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807edc54
    const char* GetClassName() const override; //0x2c 807ec90c

    void Load(const char* ctrName, u8 hudSlotId); //807ec918

    u32 curScore; //0x198
    s8 changeOfPoints; //0x19c -1 or +1 in battle
    u8 unknown_0x19d[0x200 - 0x19d];
    u32 pointsChangeCount; //0x200 setting it to 3 would play the +- animation 3 times, 
    //this exists in case there is a change of pts while the anim is already playing, ie to queue the next ones
    u32 unknown_0x204; //related to page duration
};//Total Size 0x208

class CtrlRaceBattleTotalPoint : public CtrlRaceBase { //+1 -1 on scorechange
public:
    //no ctor
    ~CtrlRaceBattleTotalPoint() override; //807edb84 vtable 808d3ae8
    void Init() override; //0xc 807ed268
    void OnUpdate(); //0x1c 807ed364
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807edbe0
    const char* GetClassName() const override; //0x2c 807ed258

    void Load(); //807ed9e8
    u32 redScore; //0x198
    u32 blueScore; //0x19c
    lyt::Pane* red_a; //0x1a0
    lyt::Pane* red_b; //0x1a4 
    lyt::Pane* red_c; //0x1a8
    lyt::Pane* blue_a; //0x1ac
    lyt::Pane* blue_b; //0x1b0 
    lyt::Pane* blue_c; //0x1b4

};//Total Size 0x1b8
#endif