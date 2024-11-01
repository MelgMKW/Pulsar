#ifndef _GPVS_LEADERBOARDUPDATE_PAGE_
#define _GPVS_LEADERBOARDUPDATE_PAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Leaderboard/Leaderboard.hpp>
#include <MarioKartWii/UI/Ctrl//CtrlRace/CtrlRaceResult.hpp>

//_sinit_ at 8085e644
namespace Pages {

class GPVSLeaderboardUpdate : public Leaderboard { //ID 0x2f
public:
    struct Player {
        u32 totalScore;
        u32 lastRaceScore; //the score just obtained
        u8 playerId; //0x8
        u8 padding[3];
    }; //total size 0xC
    static const PageId id = PAGE_GPVS_LEADERBOARD_UPDATE;
    GPVSLeaderboardUpdate(); //8062526c
    ~GPVSLeaderboardUpdate() override; //8085e5bc vtable 808dac18
    PageId GetNextPage() const override; //0x10 8085c974
    void OnInit() override; //0x28 8085c3e0
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8085e62c
    bool CanEnd() override; //0x64 8085c504
    void FillRows() override; //0x68 8085c858
    virtual void func_0x6c(); //0x6c 8085c5a0
    virtual int GetRowCount() const; //0x70, 8085c4f4 simply playerCount

    CtrlRaceResult** results; //0x1A0, size of the array = row count
    Player* sortedArray; //0x1a4
}; //total size 0x1A8
size_assert(GPVSLeaderboardUpdate, 0x1A8);
}//namespace Pages
#endif