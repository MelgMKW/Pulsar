#ifndef _COUNTDOWNTIMERPAGE_
#define _COUNTDOWNTIMERPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/Mii/MiiGroup.hpp>
#include <MarioKartWii/UI/Ctrl/CountDown.hpp>
#include <MarioKartWii/UI/Page/Other/Message.hpp>

/*
Contributors:
-Melg
*/
//_sinit_ at 80651bec
enum CountDownPageStatus {
    COUNTDOWN_STATUS_WAITING = 0x2,
    COUNTDOWN_STATUS_VR_PAGE,
    COUNTDOWN_STATUS_CUP_SELECT,
    COUNTDOWN_STATUS_VOTES_PAGE,
    COUNTDOWN_STATUS_DISCONNECTED,
    COUNTDOWN_STATUS_DISCONNECT_NO_MSG,
    COUNTDOWN_STATUS_DISCONNECT_MSG = 0x8
};

struct PlayerInfo {
    u8 aid; //shared by players on the same console
    u8 hudSlotid; //0 for P1, 1 for P2 on the same console etc....
    u8 unknown_0x2[2]; //never stored likely padding
    u32 team; //0x2 if no team (depending on the section), 0x0 blue, 0x1 red 0x1F8
    u16 randomThing; //806519c4, no idea, gets the current license then does a bunch of operations 0x1FC
    u16 randomThing2; //80651a20, very similar, but uses a different address to start the operations
};//total size0xC

namespace Pages {
class CountDownTimer : public Page { //ID 0x90
public:
    static const PageId id = PAGE_COUNTDOWN;
    CountDownTimer(); //8064fbdc 
    ~CountDownTimer() override; //8064fc70 vtable 808c069c
    int IsHomeMenuWorking() const override; //0x14 80651ba8 return 3, so home is disabled
    void OnInit() override; //0x28 8064fcfc
    void OnDispose() override; //0x2c 8064fe30
    void OnActivate() override; //0x30 8064fe34   
    void OnDeactivate() override; //0x34 80650214
    void BeforeControlUpdate() override; //0x48 80650218
    void AfterControlUpdate() override; //0x4c 80650274
    void OnResume() override; //0x54 806507a0
    int GetRuntimeTypeInfo() const override; //0x60 80651bb0
    int GetOnlineMode() const;
    bool IsPublicBattle(); //80650af4
    u8 GetPlayerId(u8 aid, u8 hudSlotId); //80650ddc
    u32 GetInstructionBmgId() const; //80650be0
    u32 GetEngineClass() const; //80650b40
    u32 GetBattleType() const; //80650b90
    void PrepareRace(); //80650e24 using RKNetSelect, sets stuff like racedata etc..
    void UpdateFriendParams(); //806515cc to rename
    void OnDisconnect(MessageBox& messageBox); //806517b0
    void SetModeTypes(); //80651854 from RKNetSELECT
    static void TriggerPtmf(PtmfHolder_1A<CountDownTimer, void, MessageBox&>, MessageBox&); //80651bbc
    PtmfHolder_1A<CountDownTimer, void, MessageBox&> onDisconnectHandler; //0x44, 0x806517b0, selects next page
    ManipulatorManager manipulatorManager;
    CountDownPageStatus status; //0x68
    CountDown countdown; //0x6C
    CountDownTimerControl timerControl; //0x78
    PlayerInfo infos[12]; //0x1f4 large loop at 0x80651980, one per player it seems
    u32 playerCount; //0x284
    u32 engineClass;
    u32 battleType; //init at 2 8064fe14
    MiiGroup miiGroup; //0x290
}; //total size 0x328

size_assert(CountDownTimer, 0x328);
}//namespace Pages
#endif