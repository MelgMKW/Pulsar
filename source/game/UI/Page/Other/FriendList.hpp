#ifndef _FRIENDLISTPAGE_
#define _FRIENDLISTPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>

//_sinit_ at 805d7f40
class FriendButton: public PushButton {
public:
    FriendButton(); //805d380c
    ~FriendButton() override; //805d3850 vtable 808b8d04
    void InitSelf() override; //0x18 805d3c54
    void OnUpdate() override; //0x1c 805d3c58
    int GetRuntimeTypeInfo() const override; //0x28 805d7de4
    const char* GetClassName() const override; //0x2c 805d3800
    void OnSelect() override; //0x40 805d4028
    void OnDeselect() override; //0x44 805d4120

    void Load(u32 id, MiiGroup* miiGroup); //805d38a8 inlined
    void SetMii(u32 friendIdx); //805d3980

    MiiGroup* miiGroup; //0x254
    u32 friendIdx; //0x258
    u32 status; //0x25c 2 = has friend loaded? unsure
    bool isSelected; //0x260
    u8 padding[3];
};
size_assert(FriendButton, 0x264);

class JoinFriendButton: public PushButton {
public:
    JoinFriendButton(); //805d5510 inlined
    ~JoinFriendButton() override; //805d554c vtable 808b8c0c
    void OnUpdate() override; //0x1c 805d5818
    int GetRuntimeTypeInfo() const override; //0x28 805d7dc4
    const char* GetClassName() const override; //0x2c 805d5500
    void Toggle(u32 enabled); //805d56ac
};
size_assert(JoinFriendButton, 0x254);

namespace Pages {
class FriendList: public Page { //ID 0x96
public:
    FriendList(); //805d41c8
    ~FriendList() override; //805d43a8 vtable 808b8c58
    PageId GetNextPage() const override; //805d7dd0
    void OnInit() override; //0x28 805d446c
    void OnDispose() override; //0x2c 805d4830
    void OnActivate() override; //0x30 805d4834
    void OnDeactivate() override; //0x34 805d4b70
    void BeforeEntranceAnimations() override; //0x38 805d4a54
    void BeforeExitAnimations() override; //0x40 805d4b5c
    void AfterControlUpdate() override; //0x4c 805d4c10
    int GetRuntimeTypeInfo() const override; //0x60 805d7dd8

    void AddNewFriend(u32 idx); //805d4c8c adds mii inlined
    void OnFriendButtonClick(FriendButton& friendButton, u32 hudSlotId); //805d4d08
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId); //805d4e50
    void OnRightArrowPress(SheetSelectControl& control, u32 hudSlotId); //805d4ee4
    void OnLeftArrowPress(SheetSelectControl& control, u32 hudSlotId); //805d5014
    void OnBackPress(u32 hudSlotId); //805d510c
    static int CompareFriendIndexes(u32* idx1, u32* idx2); //805d518c for qsort
    static int FriendStatusToValue(u32 friendStatus); //805d521c used as part of the comparison, friendStatus can be 0/1/-1
    void UpdatePageCounter(); //805d5330 inlined
    void UpdateMiiGroup(); //805d53f8  

    ControlsManipulatorManager manipulatorManager; //0x44
    FriendButton friendButtons[5]; //0x268
    CtrlMenuPageTitleText titleText; //0xe5c
    CtrlMenuBackButton backButton; //0xfd0
    SheetSelectControl arrows; //0x1234
    LayoutUIControl pageCounter; //0x176c
    MiiGroup miiGroup; //0x18e0
    u32 sortedFriendsIdx[32]; //0x1978
    u8 unknown_0x19f0[0x4];
    u32 curPageIdx; //0x19f4
    u32 updateFrequency; //0x19f8 every 300 frames, updates the list, which is useful for newly registered friends
    PageId nextPage;
    PtmfHolder_2A<FriendList, void, FriendButton&, u32> onFriendButtonClickHandler;  //0x1a00 805d4d08
    PtmfHolder_2A<FriendList, void, CtrlMenuBackButton&, u32> onBackButtonClickHandler; //0x1a14 805d4e50
    PtmfHolder_2A<FriendList, void, SheetSelectControl&, u32> onRightArrowPressHandler; //0x1a28 805d4ee4
    PtmfHolder_2A<FriendList, void, SheetSelectControl&, u32> onLeftArrowPressHandler; //0x1a3c 805d5014
    PtmfHolder_1A<FriendList, void, u32> onBackPressHandler; //0x1a50 805d510
};
size_assert(FriendList, 0x1a64);

class FriendInfo: public Page { //ID 0x97
public:
    FriendInfo(); //805d585c
    ~FriendInfo() override; //805d5a14 vtable 808b8b90
    PageId GetNextPage() const override; //805d7db0
    void OnInit() override; //0x28 805d5af4
    void OnActivate() override; //0x30 805d6000
    void AfterControlUpdate() override; //0x4c 805d6128
    int GetRuntimeTypeInfo() const override; //0x60 805d7db8

    void PlaySound(u32 friendStatus); //805d6390
    void SetInfoText(MiiGroup& miiGroup, u32 friendIdx); //805d6470
    void OnJoinButtonClick(JoinFriendButton& joinButton, u32 hudSlotId);   //805d6678
    void OnRemoveButtonClick(PushButton& removeButton, u32 hudSlotId);  //805d690c
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId);  //0805d6950 
    void OnBackPress(u32 hudSlotId);   //805d6994

    PtmfHolder_2A<FriendInfo, void, JoinFriendButton&, u32> onJoinButtonClickHandler;  //0x44 805d6678
    PtmfHolder_2A<FriendInfo, void, PushButton&, u32> onRemoveButtonClick; //0x58 805d690c
    PtmfHolder_2A<FriendInfo, void, CtrlMenuBackButton&, u32> onBackButtonClickHandler; //0x6c 805d6950 
    PtmfHolder_1A<FriendInfo, void, u32> onBackPressHandler; //0x80 805d6994
    ControlsManipulatorManager manipulatorManager; //0x94
    CtrlMenuPageTitleText titleText; //0x2b8
    JoinFriendButton joinButton; //0x42c
    PushButton removeButton; //0x680
    CtrlMenuBackButton backButton; //0x8d4
    LayoutUIControl control1; //0xb38
    LayoutUIControl control2; //0xcac
    LayoutUIControl control3; //0xe20
    LayoutUIControl control4; //0xf94
    u32 selectedFriendIdx; //0x1108
    MiiGroup miiGroup; //0x110c
    u8 unknown_0x11a4[4];
    PageId nextPage; //0x11a8
    u32 isFriend; //0x11ac returns value of IsFriend
};
size_assert(FriendInfo, 0x11b0);

class FriendRemove: public Page { //ID 0x98
public:
    FriendRemove(); //805d69ac
    ~FriendRemove() override; //805d6b04 vtable 808b8b14
    PageId GetNextPage() const override; //805d7d9c
    void OnInit() override; //0x28 805d6ba4
    void OnActivate() override; //0x30 805d6d40
    void OnDeactivate() override; //0x34 805d6e10
    void OnResume() override; //0x54 805d6ec8
    int GetRuntimeTypeInfo() const override; //0x60 805d7da4

    void OnRemoveButtonClick(PushButton& button, u32 hudSlotId);  //805d6f9c
    void OnCancelAndBackButtonClick(PushButton& button, u32 hudSlotId);  //805d7190
    void OnBackPress(u32 hudSlotId);   //805d71ec

    PtmfHolder_2A<FriendRemove, void, PushButton&, u32> onRemoveButtonClickHandler;  //0x44 805d6f9c
    PtmfHolder_2A<FriendRemove, void, PushButton&, u32> onCancelAndBackButtonClickHandler; //0x58 805d7190
    PtmfHolder_1A<FriendRemove, void, u32> onBackPressHandler; //0x6c 805d71ec
    ControlsManipulatorManager manipulatorManager; //0x80
    CtrlMenuPageTitleText titleText; //0x2a4
    PushButton removeButton; //0x418
    PushButton cancelButton; //0x66c
    CtrlMenuBackButton backButton; //0x8c0
    PageId nextPage; //0xb24
};
size_assert(FriendRemove, 0xb28);

class FriendRemoving: public Page { //ID 0x99, the wait after clicking remove friend code on the previous page
public:
    enum Status {
        FRIEND_REMOVE_IDLE = 0,
        FRIEND_REMOVE_STARTING = 1,
        FRIEND_REMOVE_WAITING = 2, //waiting for save license request
        FRIEND_REMOVE_REQUEST_COMPLETE = 3,
        FRIEND_REMOVE_DONE = 4
    };
    FriendRemoving(); //805d7204
    ~FriendRemoving() override; //805d7278 vtable 808b8ab0
    PageId GetNextPage() const override; //805d7d88
    int IsHomeMenuWorking() const override; //0x14 805d7d80
    void OnInit() override; //0x28 805d7308
    void OnActivate() override; //0x30 805d7404
    void BeforeExitAnimations(); //0x40 805d74f4
    void AfterControlUpdate(); //0x4c 805d7658
    int GetRuntimeTypeInfo() const override; //0x60 805d7d90

    ManipulatorManager manipulatorManager;
    CtrlMenuPageTitleText titleText;
    BusySymbol busySymbol;
    MessageWindowControl messageWindow;
    Status removeStatus; //0x4b0
    u32 removedIdx; //0x4b4
    u8 unknown_0x4b4[0x4];
};
size_assert(FriendRemoving, 0x4bc);

}//namespace Pages
#endif