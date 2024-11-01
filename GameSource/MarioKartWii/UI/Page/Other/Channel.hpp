/*
Credits:
kHacker35000vr and the Sanbo team (dolphin map, PageText)
stebler (names for some of the classes)
Melg
*/

#ifndef _CHANNELPAGE_
#define _CHANNELPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>

//_sinit_ at 805c1c94
class NotifyButton : public PushButton {
public:
    enum Status {
        DOWNLOAD_LATEST = 0,
        NEW_FRIEND_CHALLENGE = 1,
        SPECIAL_GHOST = 2,
        COMPETITION_INPROGRESS = 3,
        LATEST_RANKINGS_AVAILABLE = 4,
        START_GHOST_RACE = 5,
        NEW_FRIEND_RECORDS = 6,
        ADD_CHANNEL = 7,
        JOIN_NWC24 = 8,
        SET_REGION = 9,
        INVITE_FRIENDS_VIA_MSGBOARD = 10
    };
    NotifyButton(); //805bf3dc
    ~NotifyButton() override; //805bf418 vtable 808b7bd0
    void InitSelf() override; //0x18 805bf52c
    void OnUpdate() override; //0x1c 805bf600
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805c1b68
    const char* GetClassName() const override; //0x2c 805bf3d0
    void OnClick() override; //0x48 805bf998
    void Load(); //805bf470
    void UpdateText(); //805bfe1c
    void CheckStatusAvailabilities(); //805bfbf4
    bool isStatusAvailable[10]; //0x254
    bool unknown_0x25e;
    u8 padding;
    Status status; //0x260
    u8 unknown_0x264[4];
}; //0x268
namespace Pages {
class Channel : public Page { //ID 0xA2
public:
    static const PageId pageId = PAGE_MKCHANNEL;
    Channel(); //805bff18
    ~Channel() override; //805c0118 vtable 808b7b3c
    PageId GetNextPage() const override; //0x10 805c1b54
    void OnInit() override; //0x28 805c01fc
    void OnDispose() override; //0x2c 805c0884
    void OnActivate() override; //0x30 805c0888
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805c1b5c

    void OnButtonClick(PushButton& button, u32 hudSlotId); //805c08e0
    void OnButtonSelect(PushButton& button, u32 hudSlotId); //805c0b78
    void OnBackPress(u32 hudSlotId); //805c0c90

    ControlsManipulatorManager controlsManipulatorManager; //0x44
    CtrlMenuPageTitleText titleText; //0x268
    PushButton friendsButton; //0x3dc
    PushButton ghostButton;
    PushButton rankingsButton;
    PushButton competitionsButton;
    NotifyButton notifyButton; //0xd2c
    CtrlMenuBackButton backButton; //0xf94
    CtrlMenuInstructionText bottomText; //0x11f8
    PtmfHolder_2A<Channel, void, PushButton&, u32> onButtonClickHandler; //0x136c 805c08e0
    PtmfHolder_2A<Channel, void, PushButton&, u32> onButtonSelectHandler; //0x1380 805c0b78
    PtmfHolder_1A<Channel, void, u32> onBackPressHandler; //0x1394 805c0c90
    u8 unknown_0x13a8[4];
    PageId nextPage; //0x13ac
    MiiGroup miiGroup; //0x13b0
}; //0x1448
size_assert(Channel, 0x1448);

class ChannelRankingChoice : public Page { //ID 0xA3 2 buttons, TTRankings or Competition Rankings
public:
    static const PageId pageId = PAGE_CHANNEL_RANKING_CHOICE;
    ChannelRankingChoice(); //805c13ac
    ~ChannelRankingChoice() override; //805c151c vtable 808b7a44
    PageId GetNextPage() const override; //0x10 805c188c
    void OnInit() override; //0x28 805c15cc
    void OnActivate() override; //0x30 805c183c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805c1b34
    void OnButtonClick(PushButton& button, u32 hudSlotId); //805c18a4
    void OnButtonSelect(PushButton& button, u32 hudSlotId); //805c1ad0
    void OnBackPress(u32 hudSlotId); //805c1b24
    PtmfHolder_2A<ChannelRankingChoice, void, PushButton&, u32> onButtonClickHandler; //0x44 805c18a4
    PtmfHolder_2A<ChannelRankingChoice, void, PushButton&, u32> onButtonSelectHandler; //0x58 805c1ad0
    PtmfHolder_1A<ChannelRankingChoice, void, u32> onBackPressHandler; //0x6c 805c1b24
    ControlsManipulatorManager controlsManipulatorManager; //0x80
    CtrlMenuPageTitleText titleText; //0x2a4
    PushButton ttRankingsButton; //0x418
    PushButton competitionRankingsButton; //0x66c
    CtrlMenuBackButton backButton; //0x8c0
    CtrlMenuInstructionText bottomText; //0xb24
}; //0xc98

class ChannelGhostChoice : public Page { //ID 0xA4
public:
    static const PageId pageId = PAGE_CHANNEL_GHOST_CHOICE;
    ChannelGhostChoice(); //805c0cc8
    ~ChannelGhostChoice() override; //805c0e38 vtable 808b7ac0
    PageId GetNextPage() const override; //0x10 805c1b40
    void OnInit() override; //0x28 805c0ee8
    void OnActivate() override; //0x30 805c1200
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805c1b48
    void OnButtonClick(PushButton& button, u32 hudSlotId); //805c1258
    void OnButtonSelect(PushButton& button, u32 hudSlotId); //805c1340
    void OnBackPress(u32 hudSlotId); //805c1394

    PtmfHolder_2A<ChannelGhostChoice, void, PushButton&, u32> onButtonClickHandler; //0x44 805c1258
    PtmfHolder_2A<ChannelGhostChoice, void, PushButton&, u32> onButtonSelectHandler; //0x58 805c1340
    PtmfHolder_1A<ChannelGhostChoice, void, u32> onBackPressHandler; //0x6c 805c1394
    ControlsManipulatorManager controlsManipulatorManager; //0x80
    CtrlMenuPageTitleText titleText; //0x2a4
    PushButton ghostRaceButton; //0x418
    PushButton dlDGhostListButton; //0x66c
    CtrlMenuBackButton backButton; //0x8c0
    CtrlMenuInstructionText bottomText; //0xb24
    u8 unknown_0xc98[4];
    PageId nextPage; //0xc9c
}; //0xcA0
}//namespace Pages

#endif