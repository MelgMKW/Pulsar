#ifndef _VS_LEADERBOARDTOTAL_PAGE_
#define _VS_LEADERBOARDTOTAL_PAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Leaderboard/VSLeaderboardUpdate.hpp>

//_sinit_ at 8085e644
namespace Pages {
class VSLeaderboardTotal : public VSLeaderboardUpdate { //ID 0x30
public:
    VSLeaderboardTotal(); //806252a8
    ~VSLeaderboardTotal() override; //8085e540 vtable 808daba4
    PageId GetNextPage() const override; //0x10 8085cc40
    void OnInit() override; //0x28 8085c9b0
    int GetRuntimeTypeInfo() const override; //0x60 8085e5b0
    void LoadRows() override; //0x68 8085cae8
}; //total size 0x1A8
size_assert(VSLeaderboardTotal, 0x1A8);
}//namespace Pages
#endif