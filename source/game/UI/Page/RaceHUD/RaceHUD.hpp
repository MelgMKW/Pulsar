#ifndef _RACEHUDPAGE_
#define _RACEHUDPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceCount.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceWifi.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBalloon.hpp>

class Pause;

namespace Pages {
class RaceHUD : public Page {
public:
    //ctor inlined
    static RaceHUD *sInstance;
    ~RaceHUD() override; //80624764 vtable 808da710
    PageId GetNextPage() const override; //80633510
    void func_0x20() override; //80858a34
    void OnInit() override; //80856278
    void OnDispose() override; //80858a24
    void OnDeactivate() override; //80858a18
    void BeforeControlUpdate() override; //0x48 80856cec extensively patched in advanced watch replay
    void AfterControlUpdate() override; //0x4c 808574b8 also patched in advanced watch replay
    int GetRuntimeTypeInfo() const override; //0x60 80858c10 returns 809C4640
    virtual PageId GetPausePageId() const = 0; //0x64
    virtual int GetEnabledCtrlRaceBases() const = 0; //0x68, used for initctrlracebase
    virtual int GetCtrlRaceNameBalloonCount() const; //0x6c 80633d44, returns 0, 3 (as 0 counts) in vs mode, 1 in TTracepage etc...
    virtual void OnPause(u32 hudSlotId); //0x70 808569bc
    virtual void HasPlayerRaceEnded(u8 id); //0x74 808572d4 based on raceinfoplayer stateflags
    virtual bool HasRaceEnded(); //0x78 808573ac also if online, changes next page to 0x48
    virtual bool HasRaceEndedReplay(); //0x7c 8085732c only if gametype == replay
    int GetCtrlRaceBaseCount() const; //80857b08 returns how page elements there should be
    void InitCtrlRaceBase(u32 bitField); //80857cc0 inits all of the page elements 
    void InitActions(); //80856664, sets up the handlers and then stores the page input controller
    void ChangeFocusedPlayer(u32 hudSlotId, u8 type); //80856b74 type = 0 -> next, type = 1 -> prev
    void OnNextPlayerSwitch(u32 hudSlotId); //808569ac
    void OnPrevPlayerSwitch(u32 hudSlotId); //808569b4
    static int GetLocalPlayerCount(); //80856ccc
    u32 nextPageId;
    Timer timer; //0x48
    u8 countDown; //0x54 0 1 2 3 4, 4 at GO
    u8 unknown_0x55[3]; //probs padding
    CtrlRaceCount *ctrlRaceCountArray;  //0x58, 2 elements per hudSlot
    LayoutUIControl *ghostMessage; //GHOST CANNOT BE SAVED //0x5C
    bool hudHasPlayer[4]; //is true if there's a player 0x60
    u32 playerCount;
    u8 unknown_0x68; //8085629c
    u8 unknown_0x69[0x70 - 0x69];
    CtrlRaceWifiStartMessage **ctrlRaceWifiStartMessageArray; //0x70 one per hud slot only online
    CtrlRaceWifiFinishMessage **CtrlRaceWifiFinishMessageArray; //0x74 one per hud slot
    u32 framesAfterFinish; //0x78, interface fades at 120 frames
    Pause *pausePage; //0x7C, only set when in an actual pause, as an added page layer
    PageManipulatorManager inputController;
    PtmfHolder_1A<Page, void, u32> *onPauseHandler; //0x1c4
    PtmfHolder_1A<Page, void, u32> *onNextPlayerSwitchHandler; //0x1c8
    PtmfHolder_1A<Page, void, u32> *onPrevPlayerSwitchHandler; //0x1cc
    CtrlRaceNameBalloon *ctrlRaceNameBalloonArray; //0x1d0 as many as GetCtrlRaceNameBalloonCount, 3 names max?
    RaceBalloons *balloonClassArray; //0x1D4 one per hudslot
    CtrlRaceItemBalloon *ctrlRaceItemBalloon; //0x1d8 one per hudslot
}; //Total Size 0x1DC
size_assert(RaceHUD, 0x1DC);
}//namespace Pages
#endif