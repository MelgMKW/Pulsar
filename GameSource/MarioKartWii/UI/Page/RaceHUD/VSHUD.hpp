#ifndef _VSHUD_
#define _VSHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class VSHUD : public RaceHUD { //ID 0xE
    static const PageId id = PAGE_P1VS_HUD;
    VSHUD();//80624874
    ~VSHUD() override; //80633aa0 vtable 808be378
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633b0c
    PageId GetPausePageId() const override; //0x64 80633a98
    int GetEnabledCtrlRaceBases() const override; //0x68 80633a90
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633a88
}; //total size 0x1DC
size_assert(VSHUD, 0x1DC);

class VSMultiHUD : public RaceHUD { //ID 0xF, 0x10, 0x11
    static const PageId id = PAGE_P2VS_HUD;
    VSMultiHUD();//806248f4
    ~VSMultiHUD() override; //80633a10 vtable 808be2f8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633A7C
    PageId GetPausePageId() const override; //0x64 80633a08
    int GetEnabledCtrlRaceBases() const override; //0x68 80633a00
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806339F8
}; //total size 0x1DC
size_assert(VSMultiHUD, 0x1DC);
}//namespace Pages
#endif