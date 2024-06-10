#ifndef _CTRLRACERESULTTEAM_
#define _CTRLRACERESULTTEAM_
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>


//_sinit_ at 807f76c8
class CtrlRaceResultTeam : public LayoutUIControl { //one battle ldb column MAKE HPP
public:
    struct Player {
        u32 battleScore; //0x174 from RaceInfoPlayer
        u32 prevBattleScore; //0x178
        float unknown; //0x178
        u32 playerIdx; //0x180
    }; //0x14

    CtrlRaceResultTeam(); //80625388
    ~CtrlRaceResultTeam(); //806253ec vtable 80625388
    void InitSelf() override; //0x18 807f69e4
    void OnUpdate() override; //0x1c 807f6fb8
    int GetRuntimeTypeInfo() const override; //0x28 807f7660
    const char* GetClassName() const override; //0x2c 807f6510

    void Load(u32 idx); //807f651c
    void IsResultAnimDone() const; //807f7224
    static void ComparePlayers(const Player* first, const Player* second); //807f73c0 qsort func

    Player players[6];
    u32 idx; //0x1ec 0 or 1 since the page has 2
    LayoutUIControl items[6]; //0x1f0
    LayoutUIControl* resultTeamPoint; //0xaa8 above the column, only exists if the parent parent is Update ldb; 
    //if it is TOTAL then instead RaceCount amount of CtrlRaceBattleSetPoint are added as children
    Text::Info textInfo; //0xaac

    float currentScore; //0xb70 starts at 0 and increments to teamScore, used for animations
    u32 teamScore; //0xb74 sum of all raceinfo scores
    u8 unknown_0xb78[0x18];
}; //0xb90
#endif