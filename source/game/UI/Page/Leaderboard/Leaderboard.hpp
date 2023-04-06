#ifndef _LEADERBOARDPAGE_
#define _LEADERBOARDPAGE_
#include <game/UI/Page/Page.hpp>

//_sinit_ at 8085c3cc
namespace Pages {
class Leaderboard : public Page { //used for tt leaderboard, GP/VS score table etc..
public:
    Leaderboard(); //8085be44
    ~Leaderboard() override; //80625198 vtable 808da9cc
    virtual PageId GetNextPage() const = 0;
    virtual void OnInit() = 0; //0x28
    void OnActivate() override; //0x30 8085bf94
    void AfterControlUpdate() override; //0x4c 8085c0c4
    int GetRuntimeTypeInfo() const override; //0x60 8085c390
    virtual bool CanEnd() = 0; //0x64
    virtual void LoadRows() = 0; //0x68
    virtual void func_0x6c() = 0;
    virtual int GetRowCount() const = 0; //0x70, 6 for example in TTs (top 5 and flap)

    u32 maxDuration; //300 frames online, 600 online Compared to the page frame counter
    PtmfHolder_1A<Leaderboard, void, u32> onUnfocusHandler; //ends state
    PageManipulatorManager inputController; //0x5c ends at 0x1A0. The page's controlController is replaced by this 8085bf38
}; //total size 0x1A0
}//namespace Pages
#endif