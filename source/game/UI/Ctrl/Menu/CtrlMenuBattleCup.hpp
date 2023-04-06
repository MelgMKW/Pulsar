#ifndef _CTRLMENUBATTLECUPStage_
#define _CTRLMENUBATTLECUPStage_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuMovie.hpp>

//_sinit at 807e1260
class CtrlMenuBattleCupSelectCup : public LayoutUIControl {
    //no ctor
    ~CtrlMenuBattleCupSelectCup() override; //80629858 vtable 808d2ec4
    void InitSelf() override;  //807e0b50 0x18
    int GetRuntimeTypeInfo() const override; //0x28 807e1254
    const char *GetClassName() const override; //0x2c 807e093c
    void Load(u32 localPlayerBitfield, u32 r8); //807e0958 r8 is pushbutton's load r8
    PushButton cupButtons[2]; //0x174
    PtmfHolder_2A<CtrlMenuBattleCupSelectCup, void, PushButton *, u32> onCupButtonClickHandler; //0x61c 807e0d60
    PtmfHolder_2A<CtrlMenuBattleCupSelectCup, void, PushButton *, u32> onCupButtonSelectHandler; //0x630 807e0c90
    u32 curCupID; //0x644
    CtrlMenuMovieLayout ctrlMenuMovieLayout; //0x648
}; //total size 0x7d4
size_assert(CtrlMenuBattleCupSelectCup, 0x7d4);

class CtrlMenuBattleCupSelectStage : public LayoutUIControl {
    //no ctor
    ~CtrlMenuBattleCupSelectStage() override; //806298e0 vtable 808d2e88
    void InitSelf() override; //807e0fd0 0x18
    void OnUpdate() override; //807e10d4 0x1c
    int GetRuntimeTypeInfo() const override; //0x28 807e1248
    const char *GetClassName() const override; //0x2c 807e0948
    void Load(); //807e0dc0
    void UpdateStageList(u32 cupIndex); //807e0ee4
    LayoutUIControl stageNames[5]; //0x174 to 8b8
}; //total size 0x8b8
size_assert(CtrlMenuBattleCupSelectStage, 0x8b8);
#endif