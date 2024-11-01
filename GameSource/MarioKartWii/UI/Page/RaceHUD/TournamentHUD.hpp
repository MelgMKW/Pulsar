#ifndef _TOURNAMENTHUD_
#define _TOURNAMENTHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

namespace Pages { //also mission
class TournamentHUD : public RaceHUD { //ID 0x16
    static const PageId id = PAGE_MISSION_TOURNAMENT_HUD;
    TournamentHUD(); //80624a74
    ~TournamentHUD() override; //80858b98 vtable 808da690
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80858c04
    PageId GetPausePageId() const override; //0x64 80858b90
    int GetEnabledCtrlRaceBases() const override; //0x68 8085896c
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80858b88
}; //total size 0x1DC
size_assert(TournamentHUD, 0x1DC);
}//namespace Pages
#endif