#ifndef _WFCMENU_
#define _WFCMENU_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Page/Other/Approve.hpp>

/*
Contributors:
-Melg
*/
//_sinit_ at 8064d804
class FriendStatusButton : public PushButton {
    FriendStatusButton(); //8064b2c0 inlined
    ~FriendStatusButton() override; //8064b2fc vtable 808bffc0
    void InitSelf(); //0x18 8064b444
    void OnUpdate(); //0x1c 8064b450
    int GetRuntimeTypeInfo() const override; //0x28 8064d69c
    const char* GetClassName() const override; //0x2c 8064b2b4
    void OnSelect() override; //0x40 8064b4c0
    void OnDeselect() override; //0x44 8064b4c4

    void Load(const char* folderName, const char* ctrName, const char* variant); //8064b354
    void UpdateButtonStatus(); //8064b4c8
    u32 frames; //increments by 1 each frame, resets at 300
    u32 unknown_0x25C; //idk
}; //total size 0x25C

namespace Pages {
class Approve2PWFC : public Page { //ID 0x8a, just a wrapper that activates Approve with "X and Y will connect to WFC together. Is this OK?"
    static const PageId id = PAGE_APPROVE2P_WFC;
    Approve2PWFC(); //8064aef8
    ~Approve2PWFC(); //8064af74 vtable 808c000c
    PageId GetNextPage() const override; //8064b224
    void OnInit() override; //0x28 8064afdc
    void OnActivate() override; //0x30 8064b048
    void BeforeEntranceAnimations() override; //0x38 8064b15c
    void BeforeExitAnimations() override; //0x40 8064b160
    void OnResume() override; //0x54 8064b164
    int GetRuntimeTypeInfo() const override; //0x60 8064d6a8

    void OnApprove(Approve& approvePage); //8064b23c

    PtmfHolder_1A<Approve2PWFC, void, Approve&> onApproveHandler; //0x44
    ManipulatorManager manipulatorManager; //0x58
};
size_assert(Approve2PWFC, 0x68);

class WFCMainMenu : public Page { //ID 0x8B
public:
    static const PageId id = PAGE_WFC_MAIN;
    WFCMainMenu(); //8064b640
    ~WFCMainMenu() override; //8064b850 vtable 808bff44 
    PageId GetNextPage() const override; //8064d688
    void OnInit() override; //8064b910 
    void OnActivate() override; //8064bc90
    int GetRuntimeTypeInfo() const override; //8064d690

    void OnWorldwideButtonClick(PushButton& button, u32 hudSlotId); //8064bce8
    void OnRegionalButtonClick(PushButton& button, u32 hudSlotId); //8064bdc4
    void OnFriendsButtonClick(FriendStatusButton& button, u32 hudSlotId); //8064bea0
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId); //8064bee4
    void OnButtonSelect(PushButton& button, u32 hudSlotId); //8064bf4c
    void OnBackPress(u32 hudSlotId); //8064bfb8

    PtmfHolder_2A<WFCMainMenu, void, PushButton&, u32> onWorldwideClick; //0x44 vtable 808bffb4 8064bce8
    PtmfHolder_2A<WFCMainMenu, void, PushButton&, u32> onRegionalClick; //0x58 vtable 808bffb4 8064bdc4
    PtmfHolder_2A<WFCMainMenu, void, FriendStatusButton&, u32> onFriendsClick; //0x6C vtable 808bffb4 8064bea0
    PtmfHolder_2A<WFCMainMenu, void, CtrlMenuBackButton&, u32> onBackButtonClick; //0x80 vtable 808bffb4 8064bee4 ctrlmenubackbutton
    PtmfHolder_2A<WFCMainMenu, void, PushButton&, u32> onButtonSelectHandler; //0x94 vtable 808bffb4 8064bf4c
    PtmfHolder_1A<WFCMainMenu, void, u32> onBackPress; //0xA8 vtable 808bffa8 8064bfb8
    CtrlMenuPageTitleText ctrlMenuPageTitleText; //0xBC
    PushButton worldwideButton; //0x230
    PushButton regionalButton; //0x484
    FriendStatusButton friendsButton; //0x6D8
    CtrlMenuBackButton backButton; //0x934
    CtrlMenuInstructionText bottomText; //0xb98
    ControlsManipulatorManager manipulatorManager; //0xd0c
    PageId nextPageId; //when you press a button
};//total size 0xf34
size_assert(WFCMainMenu, 0xf34);

class WFCModeSelect : public Page { //ID 0x8C
public:
    static const PageId id = PAGE_WFC_MODE_SELECT;
    WFCModeSelect(); //8064bfd8
    ~WFCModeSelect() override; //8064c170 vtable 808bfec8
    PageId GetNextPage() const override; //8064d674
    void OnInit() override; //8064c220
    void OnActivate() override; //8064c4f8
    int GetRuntimeTypeInfo() const override; //8064d67c

    void OnModeButtonClick(PushButton& modeButton, u32 hudSlotId); //8064c610
    void OnModeButtonSelect(PushButton& modeButton, u32 hudSlotId); //8064c718
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId); //8064c75c
    void OnBackPress(u32 hudSlotId); //8064c7b0

    PtmfHolder_2A<WFCModeSelect, void, PushButton&, u32> onModeButtonClickHandler; //0x44 8064c610
    PtmfHolder_2A<WFCModeSelect, void, PushButton&, u32> onBackButtonClickHandler; //0x58 8064c718
    PtmfHolder_2A<WFCModeSelect, void, PushButton&, u32> onButtonSelectHandler; //0x6c 8064c75c
    PtmfHolder_1A<WFCModeSelect, void, u32> onBackPressHandler; //0x80 8064c7b0
    CtrlMenuPageTitleText titleText; //0x94
    PushButton vsButton; //0x208
    PushButton battleButton; //0x45c
    CtrlMenuBackButton backButton; //0x6b0
    CtrlMenuInstructionText bottomText; //0x914
    ControlsManipulatorManager manipulatorManager; //0xa88
    PageId nextPage; //0xCAC
};//total size 0xf34
size_assert(WFCModeSelect, 0xcb0);

class WFCFriendsMenu : public Page { //ID 0x8D
public:
    static const PageId id = PAGE_WFC_FRIENDS_MENU;
    WFCFriendsMenu(); //8064c7c8
    ~WFCFriendsMenu() override; //8064c9d8 vtable 808bfe4c
    PageId GetNextPage() const override; //8064d660
    void OnInit() override; //8064ca98
    void OnActivate() override; //8064cf18
    void OnDeactivate() override; //8064cff8
    int GetRuntimeTypeInfo() const override; //8064d668

    void OnRosterButtonClick(FriendStatusButton& button, u32 hudSlotId); //8064d0a0
    void OnRegisterButtonClick(PushButton& button, u32 hudSlotId); //8064d1e8
    void OnCreateRoomButtonClick(PushButton& button, u32 hudSlotId); //8064d330
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId); //8064d4f4
    void OnButtonSelect(PushButton& button, u32 hudSlotId); //8064d5a0
    void OnBackPress(u32 hudSlotId); //8064d60c

    PtmfHolder_2A<WFCMainMenu, void, PushButton&, u32> onRosterButtonClick; //0x44 8064d0a0
    PtmfHolder_2A<WFCMainMenu, void, PushButton&, u32> onRegisterButtonClick; //0x58 8064d1e8
    PtmfHolder_2A<WFCMainMenu, void, FriendStatusButton&, u32> onCreateRoomButtonClick; //0x6C 8064d330
    PtmfHolder_2A<WFCMainMenu, void, CtrlMenuBackButton&, u32> onBackButtonClick; //0x80 8064d4f4
    PtmfHolder_2A<WFCMainMenu, void, PushButton&, u32> onButtonSelectHandler; //0x94 8064d5a0
    PtmfHolder_1A<WFCMainMenu, void, u32> onBackPress; //0xA8 vtable 808bffa8 8064d60c
    CtrlMenuPageTitleText titleText; //0xbc
    FriendStatusButton rosterButton; //0x230
    PushButton registerButton; //0x48c
    PushButton createRoomButton; //0x6e0
    CtrlMenuBackButton backButton; //0x934
    CtrlMenuInstructionText bottomText; //0xb98
    ControlsManipulatorManager manipulatorManager; //0xd0c
    PageId nextPage; //0xf30
};//total size 0xf34
size_assert(WFCFriendsMenu, 0xf34);

}//namespace Pages
#endif