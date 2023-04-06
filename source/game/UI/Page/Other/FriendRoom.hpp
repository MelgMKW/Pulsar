#ifndef _FRIENDROOMPAGE_
#define _FRIENDROOMPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Other/GlobeSearch.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Ctrl/CountDown.hpp>
#include <game/Network/RKNetRoom.hpp>


namespace Pages {
class FriendRoomMessages;
}

class UnkUnkFriendRoomManager {
    ROOMPacket packet;
    u8 index; //id * 2 + isGuest
    u8 unknown_0x5[0x8 - 0x5];
};

class UnkFriendRoomManager {
    ~UnkFriendRoomManager(); //805dae80
    UnkFriendRoomManager(); //805daec0
    UnkUnkFriendRoomManager packetHolders[12];
    u8 unknown[0xf0 - 0x60];
    u32 lastSentAid;
    ROOMPacket receivedPackets[24]; //0xf4 arranged by pairs
}; //0x158



class FriendMatchingPlayer : public LayoutUIControl {
    FriendMatchingPlayer(); //805d945c
    ~FriendMatchingPlayer() override; //805d94d0 vtable 808b8f90
    void InitSelf() override; //0x18 805d9614
    void OnUpdate() override; //0x1c 805d9700
    int GetRuntimeTypeInfo() const override; //0x28 805de884
    const char *GetClassName() const override; //0x2c 805d944c
    void Load(MiiGroup *miiGroup, u8 id, bool isGuest); //805d9528
    void OnMessageSent(Mii *mii); //805d9aa8 just does the animation, mii isn't actually used
    PtmfHolder_1A<FriendMatchingPlayer, void, Mii *> onMessageSentHandler; //0x174 805d9aa8
    MiiGroup *miiGroup; //0x188
    u8 id; //0x18c
    bool isGuest; //0x18d
    u8 padding[2];
    u32 managerArrayIndex; //0x190 id * 2 + isGuest
    nw4r::lyt::Pane *all_null; //0x194
    float slidingXPos; //some kind of sliding thing, changing it makes the icon slide
    bool hasJoined; //0x19c 0->1 triggers the join animation
    u8 padding2[3];
}; //total size 0x1a0
size_assert(FriendMatchingPlayer, 0x1a0);

class MessageSelectControl : public LayoutUIControl {
public:
    MessageSelectControl(); //805db6c8
    ~MessageSelectControl() override; //805db724 vtable 808b8ef0
    void InitSelf() override; //0x18 805db8ec
    void OnUpdate() override; //0x1c 805db8f0
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20  805db9e8
    int GetRuntimeTypeInfo() const override; //0x28 805de86c
    const char *GetClassName() const override; //0x2c 805db6b8
    void Load(); //805db798
    void Activate(); //805dba20 plays show anim + sets playerbitfield
    void Deactivate(); //805dbab8 opposite plays hide anim
    void ChangeToPage(u8 direction); //805dbb28 0 for right plays slide in animation
    void ChangeFromPage(u8 direction); //805dbb88 plays slide out animation and disables buttons
    bool IsActivated(); //805dbc20
    bool IsDeactivated(); //805dbc58
    void SetButtonBmg(u8 id, u32 r5, u32 bmgId, const TextInfo *text); //805dbc8c
    void SetOnClickHandler(PtmfHolder_2A<Pages::FriendRoomMessages, void, PushButton *, u32> *handler); //805dbcc4
    void SelectInitialButton(u32 hudSlotId, u8 id); //805dbd24
    u32 GetSelectedButtonId() const; //805dbd34
    PushButton buttons[4]; //0x174
}; //total size 0xac4
size_assert(MessageSelectControl, 0xAC4);

namespace Pages {

class FriendRoomWaiting : public Page { //ID 0x9b
public:
    FriendRoomWaiting(); //805dd330
    ~FriendRoomWaiting(); //805dd38c vtable 808b8df8
    PageId GetNextPage() const override; //0x10 805de844
    int IsHomeMenuWorking() override; //0x14 805de84c
    void OnInit() override; //0x28 805dd418
    void OnActivate() override; //0x30 805dd5ac
    void OnDeactivate() override; //0x34 805dd724
    void BeforeEntranceAnimations() override; //0x38 805dd734
    void BeforeExitAnimations() override; //0x40 805dd7c0
    void AfterControlUpdate() override; //0x4c 805dd7c4
    void OnResume() override; //0x54 805ddcc8
    int GetRuntimeTypeInfo() const override; //0x60 805de854
    ManipulatorManager manipulatorManager; //0x44
    MatchingMessageWindow messageWindow; //0x54
    CountDownTimerControl countdownControl; //0x1c8
    CountDown countdown; //0x344
    u8 unknown_0x350[0x360 - 0x350];
    PageId nextPageId;
};
size_assert(FriendRoomWaiting, 0x364);

class FriendRoomManager : public Page { //ID 0x9c
public:
    FriendRoomManager(); //805d9b38
    ~FriendRoomManager() override; //805d9bcc vtable 808b8f2c
    void OnInit() override; //0x28 805d9c74
    void OnActivate() override; //0x30 805d9db0
    void OnDeactivate() override; //0x34 805da0f4
    void AfterEntranceAnimations() override; //0x3c 805d9f20
    void BeforeExitAnimations() override; //0x40 805da028
    void AfterControlUpdate() override; //0x4c 805da140
    int GetRuntimeTypeInfo() const override; //0x60 805de878
    static u32 GetMessageBmg(ROOMPacket *packet, u32 r4); //805dacb0
    void SetToSendPacket(ROOMPacket *packet); //805dae30
    void SetPacket(ROOMPacket *packet, u8 id); //805dae58

    ManipulatorManager manipulatorManager; //0x44
    CtrlMenuPageTitleText titleText; //0x54
    FriendMatchingPlayer miiIcons[24]; //0x1c8 work by pairs of 2, normal player and guest
    BusySymbol busySymbol; //0x28C8
    u32 unknown_0x2A3C;
    bool friendRoomIsEnding; //0x2a40 either by leaving/a gp starting, leads to the globe animation
    u8 padding[3];
    MiiGroup miiGroup; //0x2a44
    u8 aidsBelongingToPlayerIds[12]; //0x2adc
    u32 playerCount; //0x2ae8
    u32 waitingDuration; //0x2aec at 3600 frames something happens with the globe (reset?)
    bool isWaiting; //0x2af0 if true, busySymbol is made visible
    u8 unknown_0x2af1[0x2af8 - 0x2af1];
    u8 lastMessageId; //1 to 4 
    u8 unknown_0x2af8[0x2b08 - 0x2af8]; //0x2af1
    UnkFriendRoomManager unknownStruct; //0x2b08
    ROOMPacket lastSentPacket; //0x2c60
    u8 localAid; //0x2c64
    u8 padding2[3];
}; //0x2c68
size_assert(FriendRoomManager, 0x2c68);

class FriendRoom : public Page { //ID 0x9d
public:
    FriendRoom(); //805d7f78
    ~FriendRoom() override; //805d8160 vtable 808b8fd8
    void OnInit() override; //0x28 805d820c
    void OnActivate() override; //0x30 805d8444
    void OnDeactivate() override; //0x34 805d84fc
    void AfterControlUpdate() override; //0x4c 805d8508
    void OnResume() override; //0x54 805d8c98
    int GetRuntimeTypeInfo() const override; //0x60 805de890
    void SetStatus(u32 status); //805d8f40
    void OnMessagesButtonClick(PushButton *button, u32 hudSlotId); //805d8f84
    void OnStartButtonClick(PushButton *button, u32 hudSlotId); //805d906c
    void OnAddFriendsButtonClick(PushButton *button, u32 hudSlotId); //805d9154
    void OnBackButtonClick(PushButton *button, u32 hudSlotId); //805d9160
    void OnButtonSelect(PushButton *button, u32 hudSlotId); //805d92a0
    void OnBackPress(u32 hudSlotId); //805d930c
    PtmfHolder_2A<FriendRoom, void, PushButton *, u32> onMessagesButtonsClickHandler; //0x44 805d8f84
    PtmfHolder_2A<FriendRoom, void, PushButton *, u32> onStartButtonClickHandler; //0x58 805d906c
    PtmfHolder_2A<FriendRoom, void, PushButton *, u32> onAddFriendsButtonClickHandler; //0x6c 805d9154
    PtmfHolder_2A<FriendRoom, void, PushButton *, u32> onBackButtonClickHandler; //0x80 805d9160
    PtmfHolder_2A<FriendRoom, void, PushButton *, u32> onButtonSelectHandler; //0x94 805d92a0
    PtmfHolder_1A<FriendRoom, void, u32> onBackPressHandler; //0xa8 805d930c
    ControlsManipulatorManager manipulatorManager; //0xbc
    PushButton messagesButton; //0x2e0
    PushButton startButton; //0x534
    PushButton addFriendsButton; //0x788
    CtrlMenuBackButton backButton; //0x9dc
    CtrlMenuInstructionText bottomText; //0xc40
    u32 status; //0xdb4 0 waiting
    u32 displayedPage; //0xdb8 0 for none, 1 for messages, 3 for start, 4 for back?
    u32 unknown_0xDBC;
    bool unknown_0xdc0;
    bool hasClickedAddFriends; //0xdc1
    u8 unknown_0xdc2[2];
}; //total size 0xdc4
size_assert(FriendRoom, 0xdc4);

class FriendRoomMessages;

class FriendRoomMessages : public Page { //ID 0x9e
public:
    FriendRoomMessages(); //805dbd94
    ~FriendRoomMessages() override; //805dc034 vtable 808b8e5c
    void OnInit() override; //0x28 805dc104
    void OnActivate() override; //0x30 805dc378
    void OnDeactivate() override; //0x34 805dc71c
    void BeforeControlUpdate() override; //0x48 805dc7b8
    int GetRuntimeTypeInfo() const override; //0x60 805de860
    void UpdateMessages(); //805dcab4
    void OnMessageButtonClick(PushButton *button, u32 hudSlotId); //805dcc70
    void OnModeButtonClick(PushButton *button, u32 hudSlotId); //805dcd78
    void OnAddFriendsButtonClick(PushButton *button, u32 hudSlotId); //805dce80
    void OnRightArrowPress(SheetSelectControlScaleFade *control, u32 hudSlotId); //805dd0c8
    void OnLeftArrowPress(SheetSelectControlScaleFade *control, u32 hudSlotId); //805dd1d4
    void OnBackButtonClick(CtrlMenuBackButton *backButton, u32 hudSlotId); //805dd2dc
    void OnBackPress(u32 hudSlotId);  //805dd318
    void End(); //805dca9c sets animLength and isEnding
    PtmfHolder_2A<FriendRoomMessages, void, PushButton *, u32> onMessageButtonClickHandler; //0x44 805dcc70
    PtmfHolder_2A<FriendRoomMessages, void, PushButton *, u32> onModeButtonClickHandler; //0x58 805dcd78
    PtmfHolder_2A<FriendRoomMessages, void, PushButton *, u32> onAddFriendsButtonClickHandler; //0x6c 805dce80
    PtmfHolder_2A<Page, void, SheetSelectControlScaleFade *, u32> onRightArrowPressHandler; //0x80 805dd0c8
    PtmfHolder_2A<Page, void, SheetSelectControlScaleFade *, u32> onLeftArrowPressHandler; //0x94 805dd1d4
    PtmfHolder_2A<FriendRoomMessages, void, CtrlMenuBackButton *, u32> onBackButtonClick; //0xa8 805dd2dc
    PtmfHolder_1A<Page, void, u32> onBackPress; //0xbc 805dd318
    ControlsManipulatorManager manipulatorManager; //0xd0
    LayoutUIControlScaleFade messageBase; //0x2f4
    MessageSelectControl messages[2]; //0x468 one for the purple, the other the blue?
    SheetSelectControlScaleFade sheetSelect; //0x19f0
    LayoutUIControlScaleFade pageNumber; //0x1f28
    LayoutUIControl obiBottom; //0x209c
    CtrlMenuBackButton backButton; //0x2210
    MessageSelectControl *messagesPtrs[2]; //0x2474
    u32 location; //0x247c messages = 0, mode selection = 1, add friends = 2
    u32 msgCount; //0x2480
    u32 pageCount; //0x2484
    u32 curPageIdx; //0x2488
    bool isEnding; //0x248c
    u8 padding[3];
    float animLength; //0x2490
    MiiGroup miiGroup; //0x2494
    u8 unknown_0x252c[0x2680 - 0x252c]; //0x252c

}; //total size 0x2680
size_assert(FriendRoomMessages, 0x2680);
}//namespace Pages
#endif