#ifndef _WWRACESUPPORTINGPAGES_
#define _WWRACESUPPORTINGPAGES_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/CountDown.hpp>

//_sinit_ at 8064fba8
class FriendStatusButtonRaceAfter : public PushButton {
public:
    FriendStatusButtonRaceAfter() {}; //8064db68
    ~FriendStatusButtonRaceAfter() override; //8064dba4 vtable 808c0350
    void InitSelf() override; //0x18 8064dd38
    void OnUpdate() override; //0x1c 8064dd3c
    int GetRuntimeTypeInfo() const override; //0x28 8064fb28
    const char* GetClassName() const override; //0x2c 8064db5c

    void Load(); //8064dbfc
};//Total Size 0x254
size_assert(FriendStatusButtonRaceAfter, 0x254);

namespace Pages { //WW means continental races too

class WWRaceEndCountDown : public Page { //ID 0x45
public:
    static const PageId id = PAGE_WWRACEEND_COUNTDOWN;
    WWRaceEndCountDown(); //8064d834
    ~WWRaceEndCountDown() override; //8064d888 vtable 808c039c
    PageId GetNextPage() const override; //0x10 8064fb34
    void OnInit() override; //0x28 8064d908 
    void OnActivate() override; //0x30 8064d994
    void BeforeControlUpdate() override; //0x48 8064db00
    int GetRuntimeTypeInfo() const override; //0x60 8064fb3c

    ManipulatorManager manipulatorManager; //0x44
    CountDownTimerControl countdownControl; //0x54
    CountDown countdown; //0x1d0
    PageId nextPageId; //0x1dc
};
size_assert(WWRaceEndCountDown, 0x1e0);

class WWRaceEnd : public Page { //ID 0x46
public:
    static const PageId id = PAGE_WWRACEEND_MENU;
    WWRaceEnd(); //8064dee8
    ~WWRaceEnd() override; //8064e014 vtable 808c02d4
    PageId GetNextPage() const override; //0x10 8064fb14
    void OnInit() override; //0x28 8064e0b0
    void OnActivate() override; //0x30 8064e3d8
    void BeforeEntranceAnimations() override; //0x38 8064e4dc
    void AfterControlUpdate() override; //0x4c 8064e4f0
    int GetRuntimeTypeInfo() const override; //0x60 8064fb1c

    void OnContinueRaceClick(PushButton& continueButton, u32 hudSlotId); //8064e690
    void OnFriendButtonClick(FriendStatusButtonRaceAfter& friendButton, u32 hudSlotId); //8064e80c
    void OnQuitClick(PushButton& quitButton, u32 hudSlotId); //8064e8ec

    ControlsManipulatorManager manipulatorManager; //0x44
    LayoutUIControl layout; //0x268
    PushButton continueRace; //0x3dc
    FriendStatusButtonRaceAfter friendButton; //0x630
    PushButton quit; //0x884
    PtmfHolder_2A<WWRaceEnd, void, PushButton&, u32> onContinueRaceClickHandler; //0xad8 8064e690
    PtmfHolder_2A<WWRaceEnd, void, FriendStatusButtonRaceAfter&, u32> onFriendButtonClickHandler; //0xaec 8064e80c
    PtmfHolder_2A<WWRaceEnd, void, PushButton&, u32> onQuitClickHandler; //0xb00 8064e8ec
    PageId nextPage; //0xb14
    u8 unknown_0xb18[0xb20 - 0xb18];
};//0x344
size_assert(WWRaceEnd, 0xb20);

class WWRaceEndQuit : public Page { //ID 0x47
public:
    static const PageId id = PAGE_WWRACEEND_QUIT;
    WWRaceEndQuit(); //8064e9d0
    ~WWRaceEndQuit() override; //8064ea94 vtable 808c0264
    PageId GetNextPage() const override; //0x10 8064fb00
    void OnInit() override; //0x28 8064eb20
    void OnDispose() override; //0x2c 8064ecb4
    void OnActivate() override; //0x30 8064ed34
    void OnDeactivate() override; //0x34 8064edf8
    void AfterControlUpdate() override; //0x4c 8064ee04
    int GetRuntimeTypeInfo() const override; //0x60 8064fb08

    void OnYesButtonClick(PushButton& button, u32 hudSlotId); //8064efa4
    void OnNoButtonClick(PushButton& button, u32 hudSlotId); //8064f124

    PtmfHolder_2A<WWRaceEndQuit, void, PushButton&, u32> onYesButtonClickHandler; //0x44 8064efa4
    PtmfHolder_2A<WWRaceEndQuit, void, PushButton&, u32> onNoButtonClickHandler; //0x58 8064f124
    u8 unknown_0x6c[0x4];
    ControlsManipulatorManager manipulatorManager; //0x70
    LayoutUIControl raceMsgWindow; //0x294 "Are you sure you want to quit?"
    PushButton yesButton; //0x408 
    PushButton noButton; //0x65c
    PageId nextPageId;
    u8 unknown_0x8b4[0x8];
};
size_assert(WWRaceEndQuit, 0x8bc);

class WWRaceEndWait : public Page { //ID 0x48 "Please wait a moment" at the end of online races
public:
    static const PageId id = PAGE_WWRACEEND_WAIT;
    WWRaceEndWait(); //8064f168
    ~WWRaceEndWait() override; //8064f1b4 vtable 808c0200
    void OnInit() override; //0x28 8064f228
    void OnActivate() override; //0x30 8064float0
    void AfterControlUpdate() override; //0x4c 8064f374 very interesting, sets next section
    int GetRuntimeTypeInfo() const override; //0x60 8064faf4
    ManipulatorManager manipulatorManager; //0x44
    SimpleMessageWindowControl msgWindow; //0x54
    u32 state; //0x1c8 0 nothing, 1 isDisplayingText? unsure
};
size_assert(WWRaceEndWait, 0x1cc);

class DisableHomeButton : public Page { //ID 0x94 used in online races
public:
    static const PageId id = PAGE_DISABLEHOMEMENU;
    DisableHomeButton(); //8064f9d8
    ~DisableHomeButton() override; //8064fa1c vtable 808c019c
    int IsHomeMenuWorking() const override; //0x14 8064fae0 returns 3
    void OnInit() override; //0x28 8064fa84
    int GetRuntimeTypeInfo() const override; //0x60 8064fae8
    ManipulatorManager manipulatorManager; //0x44
}; //total size 0x54
size_assert(DisableHomeButton, 0x54);



}//namespace Pages
#endif