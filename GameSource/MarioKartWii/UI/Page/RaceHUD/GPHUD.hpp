#ifndef _GPHUD_
#define _GPHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class GPHUD : public RaceHUD { //ID 0xC
    static const PageId id = PAGE_GP_HUD;
    GPHUD();//806246e4
    ~GPHUD() override; //80633b30 vtable 808be3f8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633b9c
    PageId GetPausePageId() const override; //0x64 80633b28
    int GetEnabledCtrlRaceBases() const override; //0x68 80633b20
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633b18
}; //total size 0x1DC
size_assert(GPHUD, 0x1DC);
}//namespace Pages
#endif