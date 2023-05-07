#ifndef _VSINTERFACE_
#define _VSINTERFACE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class VSInterface: public RaceHUD { //ID 0xE
    VSInterface();//80624874
    ~VSInterface() override; //80633aa0 vtable 808be378
    int GetRuntimeTypeInfo() const override; //0x60 80633b0c
    PageId GetPausePageId() const override; //0x64 80633a98
    int GetEnabledCtrlRaceBases() const override; //0x68 80633a90
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633a88
}; //total size 0x1DC
size_assert(VSInterface, 0x1DC);
}//namespace Pages
#endif