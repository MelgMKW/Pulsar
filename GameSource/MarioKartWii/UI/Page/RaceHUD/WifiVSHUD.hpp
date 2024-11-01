#ifndef _WIFIVSHUD_
#define _WIFIVSHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class WifiVSHUD : public RaceHUD { //ID 0x40
    static const PageId id = PAGE_WIFI_VS_HUD;
    WifiVSHUD();//8062577c
    ~WifiVSHUD() override; //80633800 vtable 808be178
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8063386c
    PageId GetPausePageId() const override; //0x64 806337f8
    int GetEnabledCtrlRaceBases() const override; //0x68 806337f0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806337e8
}; //total size 0x1DC
size_assert(WifiVSHUD, 0x1DC);

class WifiVSMultiHUD : public RaceHUD { //ID 0x41
    static const PageId id = PAGE_P2WIFI_VS_HUD;
    WifiVSMultiHUD();//806257fc
    ~WifiVSMultiHUD() override; //80633770 vtable 808be0f8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 806337dc
    PageId GetPausePageId() const override; //0x64 80633768
    int GetEnabledCtrlRaceBases() const override; //0x68 80633760
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633758
}; //total size 0x1DC
size_assert(WifiVSHUD, 0x1DC);
}//namespace Pages
#endif