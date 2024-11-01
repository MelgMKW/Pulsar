#ifndef _CTRLRACERESULTTEAM_
#define _CTRLRACERESULTTEAM_
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>


//_sinit_ at 807f76c8

class CtrlResultAddPoint : public CtrlRaceBase { //https://imgur.com/6vAMhch "+5" in this screenshot
public:
    ~CtrlResultAddPoint() override; //807f766c vtable 808d3f30
    void InitSelf() override; //0x18 807f7590
    void OnUpdate() override; //0x1c 807f75e4
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807f7654
    const char* GetClassName() const override; //0x2c 807f7458
    void Load(u32 idx, Team team); //807f7468
    u8 unknown_0x198[0x1A0 - 0x198];
};


class CtrlRaceResultTeam : public LayoutUIControl { //one battle ldb column MAKE HPP
public:
    struct Player {
        u32 battleScore; //0x174 from RaceinfoPlayer
        u32 prevBattleScore; //0x178
        float unknown; //0x178
        u32 playerIdx; //0x180
    }; //0x14

    CtrlRaceResultTeam(); //80625388
    ~CtrlRaceResultTeam(); //806253ec vtable 808d3f80
    void InitSelf() override; //0x18 807f69e4
    void OnUpdate() override; //0x1c 807f6fb8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807f7660
    const char* GetClassName() const override; //0x2c 807f6510

    void Load(Team team); //807f651c
    void IsResultAnimDone() const; //807f7224
    static void ComparePlayers(const Player* first, const Player* second); //807f73c0 qsort func

    Player players[6]; //0x174
    Team team; //0x1ec 0 or 1 since the page has 2, = team
    LayoutUIControl items[6]; //0x1f0
    LayoutUIControl* resultTeamPoint; //0xaa8 above the column, only exists if the parent parent is Update ldb; 
    //if it is TOTAL then instead RaceCount amount of CtrlRaceBattleSetPoint are added as children
    Text::Info textInfo; //0xaac

    float currentScore; //0xb70 starts at 0 and increments to teamScore, used for animations
    u32 teamScore; //0xb74 sum of all raceinfo scores
    CtrlResultAddPoint* addPoints[6]; //0xb78 only for battle WWs
}; //0xb90
#endif