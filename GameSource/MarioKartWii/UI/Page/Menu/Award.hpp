

#ifndef _AWARD_
#define _AWARD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>

class AwardCupModel;

namespace Pages {

//__sinit__ at 805bd370

class AwardDemoCongratulations : public LayoutUIControl {
public:
    AwardDemoCongratulations(); //805bb734
    ~AwardDemoCongratulations() override; //805bb770 vtable 808b75d4
    void InitSelf() override; //0x18 805bb8a0
    int GetRuntimeTypeInfo() const override; //0x28 805bd2f0
    const char* GetClassName() const override; //0x2c 805bb724

    void Load(bool isOnline, bool isSomeSections); //805bb7c8
}; //0x174

class AwardDemoResultItem : public LayoutUIControl {
public:
    AwardDemoResultItem(); //805bb958
    ~AwardDemoResultItem() override; //805bb994 vtable 808b7598
    void InitSelf() override; //0x18 805bbb98
    int GetRuntimeTypeInfo() const override; //0x28 805bb2e4
    const char* GetClassName() const override; //0x2c 805bb948

    void Load(u32 idx, bool isOnline, bool isSomeSections); //805bb9ec
    void SetValues(u32 idx, bool isTeams, bool r6); //805bbbd0
}; //0x174

class AwardFade : public Page { //ID 0x3b
public:
    static const PageId id = PAGE_PROBABLY_AWARD_INTERFACE;
    AwardFade(); //805bb2c4
    ~AwardFade() override; //805bb348 vtable 808b7610

    PageId GetNextPage() const override; //0x10 805bd2fc
    void OnInit() override; //0x28 805bb3bc
    void OnActivate() override; //0x30 805bb4dc 
    void BeforeEntranceAnimations() override; //0x38 805bb528
    void BeforeExitAnimations() override; //0x40 805bb52c
    void AfterControlUpdate() override; //0x4c 805bb530
    int GetRuntimeTypeInfo() const override; //0x60 805bd304
    void HandleClick(u32 hudSlotId); //805bb678

    Ptmf_1A<AwardFade, void, u32> onClickHandler; //0x54 805bb678
    PageManipulatorManager manipulatorManager; //0x58
    u8 unknown_0x19c[4];
    LayoutUIControl winningRunFade; //0x1a0
};
size_assert(AwardFade, 0x314);

class AwardResults : public Page {
public:
    static const PageId id = PAGE_PROBABLY_CONGRATS; //ID 0x3c
    AwardResults(); //805bc03c
    ~AwardResults() override; //805bc108 vtable 808b7528

    void OnInit() override; //0x28 805bc1b0
    void OnActivate() override; //0x30 805bc620
    void BeforeEntranceAnimations() override; //0x38 805bc640
    void AfterControlUpdate() override; //0x4c 805bc660
    int GetRuntimeTypeInfo() const override; //0x60 805bb2cc

    void HandleClick(u32 hudSlotId); //805bc73c 
    void InitConfig(); //805bc8dc
    void SetWinOrLose(); //805bc9dc bmgs, picture panes etc...
    void PrepareCongratulations(); //805bcc24
    void PrepareResultItems(); //805bcdc4
    void PrepareCup(); //805bcf30
    void InitRank(); //805bd050

    Ptmf_1A<AwardResults, void, u32> onClickHandler; //0x44 805bc73c
    AwardCupModel* awardCupModel; //0x58
    PageManipulatorManager manipulatorManager; //0x5c
    LayoutUIControl awardTypeWin; //0x1a0
    LayoutUIControl awardRankWin; //0x314
    AwardDemoCongratulations congratulations; //0x488
    AwardDemoResultItem demoResultItems[12]; //0x5fc
    bool isTeams; //0x176c
    u8 unknown_0x176d[3];
};
size_assert(AwardResults, 0x1770);

}//namespace Pages

#endif