#ifndef _WW_LEADERBOARDUPDATE_PAGE_
#define _WW_LEADERBOARDUPDATE_PAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Leaderboard/GPVSLeaderboardUpdate.hpp>

//_sinit_ at 8085e644
namespace Pages {
class WWLeaderboardUpdate : public GPVSLeaderboardUpdate { //ID 0x31
public:
    static const PageId id = PAGE_WW_LEADERBOARDS_UPDATE;
    WWLeaderboardUpdate(); //806252e4
    ~WWLeaderboardUpdate() override; //8085e4c4 vtable 808dab30
    PageId GetNextPage() const override; //0x10 8085d55c
    void OnInit() override; //0x28 8085cd18
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8085e534
    void FillRows() override; //0x68 8085ce8c
}; //total size 0x1A8
size_assert(WWLeaderboardUpdate, 0x1A8);
}//namespace Pages
#endif