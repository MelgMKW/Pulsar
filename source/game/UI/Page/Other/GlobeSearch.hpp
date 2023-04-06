#ifndef _GLOBESEARCHPAGE_
#define _GLOBESEARCHPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Ctrl/CountDown.hpp>

//_sinit_ at 805e6b2c
namespace Pages {

class RandomMatchingPlayer : public LayoutUIControl {
    RandomMatchingPlayer(); //80607158
    ~RandomMatchingPlayer(); //806071cc vtable 808bab7c
    void InitSelf() override; //0x18 80607368
    void OnUpdate() override; //0x1c 806074c0
    int GetRuntimeTypeInfo() const override; //0x28 8060a698
    const char *GetClassName() const override; //0x2c 8060714c
    void Load(u32 idx); //80607224
    void SetMii(); //80607b58 inlined
    bool IsShowing(); //80607be4 checks if Fade anim group is currently on "Show"
    void CalcAngle(); //80607cdc
    PtmfHolder_0A<RandomMatchingPlayer, void> unknown_0x174; //0x174 80607c1c
    lyt::Pane *all_null; //0x188
    u8 unknown_0x18c[4];
    u32 idx; //0x190
    u8 unknown_0x188[0x19c - 0x194]; //0x18C
    float angle; //0x19c 90deg - 2pi * (idx / 12)
    float unknown_0x1a0[2];
    MiiGroup *miiGroup; //0x1a8
    u32 miiIdx; //0x1ac
    u8 unknown_0x1b0[0x1b8 - 0x1b0]; //0x1b0

}; //0x1b8

class MatchingMessageWindow : public LayoutUIControl {
    MatchingMessageWindow(); //80607d98
    ~MatchingMessageWindow(); //80607dd4 vtable 808bab40
    void InitSelf() override; //0x18 80607e90
    void OnUpdate() override; //0x1c 80607ef4
    int GetRuntimeTypeInfo() const override; //0x28 8060a68c
    const char *GetClassName() const override; //0x2c 80607d88
    void Load(const char *variant); //80607e2c
    void SetMsgId(u32 bmgId, const TextInfo *text = NULL); //80607ef8
    void Hide(); //80607fb0
}; //0x174

class GlobeSearch : public Page { //ID 0x8f
    GlobeSearch(); //80608060
    ~GlobeSearch(); //80608194 vtable 808baad0
    PageId GetNextPage() const override; //8060a670
    int IsHomeMenuWorking() override; //8060a678
    void OnInit() override; //0x28 80608268
    void OnActivate() override; //0x30 80608494
    void BeforeEntranceAnimations() override; //0x38 80608d18
    void BeforeExitAnimations() override; //0x40 80608d1c
    void BeforeControlUpdate() override; //0x48 80608d6c
    void AfterControlUpdate() override; //0x4c 806092c0
    void OnResume() override; //0x54 80609a30
    int GetRuntimeTypeInfo() const override; //0x60 8060a680
    u8 unknown_0x44[4];
    PageManipulatorManager manipulatorManager; //0x48
    u8 unknown_0x18c[4];
    CtrlMenuPageTitleText titleText; //0x190
    RandomMatchingPlayer matchingPlayers[12]; //0x304
    MatchingMessageWindow messageWindow; //0x17a4
    CountDownTimerControl countdownControl; //0x1918
    CtrlMenuDummyBack dummyBack; //0x1a94
    MiiGroup miiGroup; //0x1c20
    u8 unknown_0x1cb8[4];
    CountDown countdown; //0x1cbc
    PtmfHolder_0A<GlobeSearch, void> unknown_0x1cc8; //0x1cc8
    PtmfHolder_0A<GlobeSearch, void> unknown_0x1cdc; //0x1cdc
    u8 unknown_0x1cf0[0x1d00 - 0x1cf0]; //0x1cc8
    PageId nextPageId; //0x1d00

};
size_assert(GlobeSearch, 0x1d04);

}//namespace Pages
#endif