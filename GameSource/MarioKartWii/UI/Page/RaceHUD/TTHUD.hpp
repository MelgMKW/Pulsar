#ifndef _TTHUD_
#define _TTHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class TTHUD : public RaceHUD { //ID 0xD
    static const PageId id = PAGE_TT_HUD;
    TTHUD();//806247cc
    ~TTHUD() override; //80633c04 vtable 808be478
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633c70
    PageId GetPausePageId() const override; //0x64 80633bb8
    int GetEnabledCtrlRaceBases() const override; //0x68 80633bb0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633ba8 returns 1
}; //total size 0x1DC
size_assert(TTHUD, 0x1DC);
}//namespace Pages
#endif