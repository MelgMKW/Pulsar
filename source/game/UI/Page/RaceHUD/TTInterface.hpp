#ifndef _TTINTERFACE_
#define _TTINTERFACE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class TTInterface : public RaceHUD { //ID 0xd
    TTInterface();//806247cc
    ~TTInterface() override; //80633c04 0x808be478
    int GetRuntimeTypeInfo() const override; //0x60 80633c70
    PageId GetPausePageId() const override; //0x64 80633bb8
    int GetEnabledCtrlRaceBases() const override; //0x68 80633bb0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633ba8 returns 1
}; //total size 0x1DC
size_assert(TTInterface, 0x1DC);
}//namespace Pages
#endif