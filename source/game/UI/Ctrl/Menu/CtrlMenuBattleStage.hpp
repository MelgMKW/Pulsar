#ifndef _CTRLMENUBATTLESTAGE_
#define _CTRLMENUBATTLESTAGE_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuMovie.hpp>

//_sinit_ at 807e2540
class StageButton : public CtrlMenuMovieButton {
public:
    StageButton(); //80629df0
    ~StageButton() override; //80629e50 vtable 808d2f40 CtrlMenuMovieHandler
    //virtual ~StageButton(); //thunk 807e2584 function 80629e50 vtable 808d2f58 pushbutton's 
    int GetRuntimeTypeInfo() const override; //0x28 thunk 807e2594 function 807e2514
    const char *GetClassName() const override; //0x2c thunk 807e258c function 807e12a8

}; //total size 0x26C
size_assert(StageButton, 0x26c);

class CtrlMenuBattleStageSelectCupSub : public LayoutUIControl {
    CtrlMenuBattleStageSelectCupSub(); //80629ce8
    ~CtrlMenuBattleStageSelectCupSub() override; //80629d24 vtable 808d2ff8
    void InitSelf() override; //807e15cc
    void OnUpdate() override; //807e1668
    int GetRuntimeTypeInfo() const override; //807e2534
    const char *GetClassName() const override; //807e127c
    virtual void SetRelativePosition(PositionAndScale *parentPosition); //807e1548
    u8 unknown_0x174[0x18c - 0x174];
}; //total size 0x18c
size_assert(CtrlMenuBattleStageSelectCupSub, 0x18c);

class CtrlMenuBattleStageSelectCup : public LayoutUIControl {
    //ctor inlined
    ~CtrlMenuBattleStageSelectCup() override; //80629d7c vtable 808d2fb8
    void InitSelf() override; //807e1444 0x18
    int GetRuntimeTypeInfo() const override; //0x28 807e2528
    const char *GetClassName() const override; //0x2c 807e1288
    void Load(); //807e12b8
    CtrlMenuBattleStageSelectCupSub cupIcons[2]; //0x174 cup icons after clicking the cup (above the 5 stages)
};  //total 0x48c
size_assert(CtrlMenuBattleStageSelectCup, 0x48c);

class CtrlMenuBattleStageSelectStage : public LayoutUIControl { //layoutUIControl are Stagebutton in the ptmfholder
    ~CtrlMenuBattleStageSelectStage() override; //80629eb0 vtable 808d2f00
    void InitSelf() override; //807e1ed0 0x18
    int GetRuntimeTypeInfo() const override; //0x28 807e2508
    const char *GetClassName() const override; //0x2c 807e1298
    void OnStageButtonClick(PushButton *stageButton, u32 hudSlotId); //807e22b4
    void OnStageButtonSelect(PushButton *stageButton, u32 hudSlotId); //807e230c
    void Load(u32 r8, bool inaccessible); //807e1d80 r8 is the same as pushbutton's r8
    StageButton StageButtons[5]; //0x174
    LayoutUIControl control; //0xd90
    PtmfHolder_2A<CtrlMenuBattleStageSelectStage, void, PushButton *, u32> onStageButtonClickHandler;  //0xf04 vtable 808bd078 807e22b4
    PtmfHolder_2A<CtrlMenuBattleStageSelectStage, void, PushButton *, u32> onStageButtonSelectHandler; //0xf18 vtable 808bd078 807e230c
}; //total size 0xF2C
size_assert(CtrlMenuBattleStageSelectStage, 0xF2C);

#endif