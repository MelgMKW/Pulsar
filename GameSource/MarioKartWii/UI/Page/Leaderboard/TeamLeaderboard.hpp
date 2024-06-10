#ifndef _TEAMLEADERBOARD_
#define _TEAMLEADERBOARD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Leaderboard/GPVSLeaderboardUpdate.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceCount.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceResultTeam.hpp>


//_sinit_ at 8085f084
namespace Pages {

class TeamLeaderboardBase : public Leaderboard {
public:
    ~TeamLeaderboardBase() override; //80625460 vtable 808dae44
    void OnInit() override; //0x28 8085e674
    void AfterControlUpdate() override; //0x4c 8085e7a0
    int GetRuntimeTypeInfo() const override; //0x60 8085f078
    bool CanEnd() override; //0x64 8085e7fc
    static int CalcTeamScoreDiff(); //8085e85c

    CtrlRaceResultTeam results[2]; //0x1a0
    CtrlRaceCount* ctrlRaceCount; //0x18c0 THE BLUE TEAM WINS

}; //0x18c4
size_assert(TeamLeaderboardBase, 0x18c4);

class TeamVSLeaderboardTotal : public Leaderboard { //ID 0x32
public:
    static const PageId id = PAGE_TEAMVS_TOTAL_LEADERBOARDS;
    TeamVSLeaderboardTotal(); //80625320
    ~TeamVSLeaderboardTotal() override; //8085efe0 vtable 808dadd8
    PageId GetNextPage() const override; //0x10 8085edb4
    int GetRuntimeTypeInfo() const override; //0x60 8085f06c
    void FillRows() override; //0x68 8085e9e4

};
size_assert(TeamVSLeaderboard, 0x18c4);


class BattleLeaderboardUpdate : public Leaderboard { //ID 0x33
public:
    static const PageId id = PAGE_BATTLE_LEADERBOARDS_UPDATE;
    BattleLeaderboardUpdate(); //806254e8
    ~BattleLeaderboardUpdate() override; //8085ef48 vtable 808dad6c
    PageId GetNextPage() const override; //0x10 8085ede4
    int GetRuntimeTypeInfo() const override; //0x60 8085efd4
    void FillRows() override; //0x68 8085ea64

}; //total size 0x18c4

class BattleLeaderboardTotal : public Leaderboard { //ID 0x34
public:
    static const PageId id = PAGE_BATTLE_TOTAL_LEADERBOARDS;
    BattleLeaderboardTotal(); //80625550
    ~BattleLeaderboardTotal() override; //8085eeb0 vtable 808dad00
    PageId GetNextPage() const override; //0x10 8085ee14
    int GetRuntimeTypeInfo() const override; //0x60 8085ef3c
    void FillRows() override; //0x68 8085ea54

}; //total size 0x18c4

}//namespace Pages
#endif