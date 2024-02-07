#ifndef _VSINTERFACE_
#define _VSINTERFACE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class VSInterface : public RaceHUD { //ID 0xF
    static const PageId id = PAGE_P2VS_INTERFACE;
    VSInterface();//806248f4
    ~VSInterface() override; //80633a10 vtable 808be2f8
    int GetRuntimeTypeInfo() const override; //0x60 80633A7C
    PageId GetPausePageId() const override; //0x64 80633a08
    int GetEnabledCtrlRaceBases() const override; //0x68 80633a00
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806339F8
}; //total size 0x1DC
size_assert(VSInterface, 0x1DC);
}//namespace Pages
#endif