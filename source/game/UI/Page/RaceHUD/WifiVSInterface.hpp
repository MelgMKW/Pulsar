#ifndef _WIFIVSINTERFACE_
#define _WIFIVSINTERFACE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class WiFiVSInterface : public RaceHUD { //ID 0x42
    WiFiVSInterface();//8062587c
    ~WiFiVSInterface() override; //806336e0 vtable 808be078
    int GetRuntimeTypeInfo() const override; //0x60 8063374c
    PageId GetPausePageId() const override; //0x64 806336d8
    int GetEnabledCtrlRaceBases() const override; //0x68 806336d0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806336d8 returns -1
}; //total size 0x1DC
size_assert(WiFiVSInterface, 0x1DC);
}//namespace Pages
#endif