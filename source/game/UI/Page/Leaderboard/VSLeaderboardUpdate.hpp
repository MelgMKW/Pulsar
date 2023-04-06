#ifndef _VS_LEADERBOARDUPDATE_PAGE_
#define _VS_LEADERBOARDUPDATE_PAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Leaderboard/Leaderboard.hpp>
#include <game/UI/Ctrl//CtrlRace/CtrlRaceResult.hpp>

//_sinit_ at 8085e644
namespace Pages {
class VSLeaderboardUpdate : public Leaderboard { //ID 0x2f
public:
    VSLeaderboardUpdate(); //8062526c
    ~VSLeaderboardUpdate() override; //8085e5bc vtable 808dac18
    PageId GetNextPage() const override; //0x10 8085c974
    void OnInit() override; //0x28 8085c3e0
    int GetRuntimeTypeInfo() const override; //0x60 8085e62c
    bool CanEnd() override; //0x64 8085c504
    void LoadRows() override; //0x68 8085c858
    void func_0x6c() override; //0x6c 8085c5a0
    int GetRowCount() const override; //0x70, 8085c4f4 simply playerCount

    CtrlRaceResult **results; //0x1A0, size of the array = row count
    u8 unknown_0x1A4[0x1A8 - 0x1A4];
}; //total size 0x1A8
size_assert(VSLeaderboardUpdate, 0x1A8);
}//namespace Pages
#endif