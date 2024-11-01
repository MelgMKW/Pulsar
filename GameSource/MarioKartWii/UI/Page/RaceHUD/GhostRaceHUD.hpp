#ifndef _GHOSTRACEHUD_
#define _GHOSTRACEHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class GhostRaceHUD : public RaceHUD { //ID 0x37
    static const PageId id = PAGE_GHOST_RACE_HUD;
    GhostRaceHUD();//80625674
    ~GhostRaceHUD() override; //80633ccc vtable 808be4f8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633d38
    PageId GetPausePageId() const override; //0x64 80633c8c
    int GetEnabledCtrlRaceBases() const override; //0x68 80633c84
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633c7c
}; //total size 0x1DC
size_assert(GhostRaceHUD, 0x1DC);
}//namespace Pages
#endif