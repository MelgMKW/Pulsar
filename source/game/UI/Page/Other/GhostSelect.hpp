#ifndef _GHOSTSELECT_
#define _GHOSTSELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>

#include <game/UI/Page/Other/GhostManager.hpp>
#include <game/Visual/Mii.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Ctrl/GhostInfoControl.hpp>

/*
Contributors:
-stebler, Melg
*/

//_sinit_ at 8063a570

namespace Pages {
class GhostSelectSupporting : public Page { //ID 0x70
    GhostSelectSupporting(); //80638e88
    ~GhostSelectSupporting() override; //80638ecc vtable 808becd8
    PageId GetNextPage() const override; //8063a4cc
    void OnInit() override; //80638f34
    void OnActivate() override; //80638fa0 updates state to 0x0
    void BeforeEntranceAnimations() override; //80639144
    void BeforeExitAnimations() override; //80639148
    void AfterControlUpdate() override; //8063914c
    void OnResume() override; //80639260
    int GetRuntimeTypeInfo() const override; //8063a4d4
    void InitGhostList(); //based on state 806393c8
    ManipulatorManager controller; //0x44 to 0x54
    PageId nextPageId; //set to -1 by OnDeactivate, then by 0x71 by
    u32 state; //0x0 list not init, 0x1 update GhostList, 0x2 list init
}; //total size 0x5C
size_assert(GhostSelectSupporting, 0x5C);


class GhostSelect : public Page { //ID 0x71
public:
    GhostSelect(); //0x806395ec vtable 808bec2c
    ~GhostSelect() override; //0x8063982c
    PageId GetNextPage() const override; //8063a4b8
    void OnInit() override; //80639908
    void OnActivate() override; //80639bd0
    void BeforeEntranceAnimations() override; //80639d34
    void OnResume() override; //80639d6c
    int GetRuntimeTypeInfo() const override; //8063a4c0

    void OnChallengeGhostPress(PushButton *button, u32 hudSlotId);
    void OnWatchReplayPress(PushButton *button, u32 hudSlotId);
    void OnRightArrowPress(SheetSelectControl *control, u32 hudSlotId); //8063a1a4
    void OnLeftArrowPress(SheetSelectControl *control, u32 hudSlotId); //8063a2a4
    void OnBackPress(u32 hudSlotId); //8063a444
    ControlsManipulatorManager manipulatorManager; //0x44
    CtrlMenuPageTitleText ctrlMenuPageTitleText; //0x268
    GhostInfoControl ghostInfo; //0x3DC loads GhostInfo brctr
    GhostInfoControl ghostInfo2; //0x628 first for easy, 2nd for expert?
    SheetSelectControl arrowPairControl; //0x874
    LayoutUIControl pageNumber; //0xDAC
    PushButton challengeGhostButton; //0xf20
    PushButton watchReplayButton; //0x1174
    PushButton soloTTButton; //0x13c8
    CtrlMenuBackButton backButton; //0x161c
    GhostInfoControl *info; //0x1880 they alternate even and odd pages
    GhostInfoControl *info2;
    u32 selectedButtonId; //0x1888
    PtmfHolder_2A<Page, void, SheetSelectControl *, u32> onRightArrowPressHandler;  //8063a1a4 0x188c
    PtmfHolder_2A<Page, void, SheetSelectControl *, u32> onLeftArrowPressHandler;  //8063a2a4 0x18a0
    PtmfHolder_2A<Page, void, PushButton *, u32> onChallengeGhostClickHandler;  //8063a3a0 0x18B4
    PtmfHolder_2A<Page, void, PushButton *, u32> onWatchReplayClickHandler;  //8063a3c0 0x18C8
    PtmfHolder_2A<Page, void, PushButton *, u32> onSoloTimeTrialClickHandler; //8063a3e0 0x18DC
    PtmfHolder_2A<Page, void, CtrlMenuBackButton *, u32> onBackButtonClickHandler; //8063a444 0x18F0
    PtmfHolder_1A<Page, void, u32> onBackPress; //8063a400 0x1904
    GhostList *ghostList; //0x1918 from page 0xA7
    u32 page; //0x191C
    PageId nextPageId; //0x1920
}; //total size 0x1924
size_assert(GhostSelect, 0x1924);
}//namespace Pages
#endif