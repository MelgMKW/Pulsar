#ifndef _GPINTERFACE_
#define _GPINTERFACE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class GPInterface : public RaceHUD { //ID 0xC
    static const PageId id = PAGE_GP_INTERFACE;
    GPInterface();//806246e4
    ~GPInterface() override; //80633b30 vtable 808be3f8
    int GetRuntimeTypeInfo() const override; //0x60 80633b9c
    PageId GetPausePageId() const override; //0x64 80633b28
    int GetEnabledCtrlRaceBases() const override; //0x68 80633b20
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633b18
}; //total size 0x1DC
size_assert(GPInterface, 0x1DC);
}//namespace Pages
#endif