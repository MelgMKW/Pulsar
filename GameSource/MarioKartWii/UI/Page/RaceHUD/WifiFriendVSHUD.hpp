#ifndef _WIFIFRIENDVSHUD_
#define _WIFIFRIENDVSHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class WifiFriendVSHUD : public RaceHUD { //ID 0x42
    static const PageId id = PAGE_WIFI_FRIENDVS_HUD;
    WifiFriendVSHUD();//8062587c
    ~WifiFriendVSHUD() override; //806336e0 vtable 808be078
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8063374c
    PageId GetPausePageId() const override; //0x64 806336d8
    int GetEnabledCtrlRaceBases() const override; //0x68 806336d0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806336d8 returns -1
}; //total size 0x1DC
size_assert(WifiFriendVSHUD, 0x1DC);

class WifiFriendTeamVSHUD : public RaceHUD { //ID 0x43
    static const PageId id = PAGE_WIFI_FRIENDTEAMVS_HUD;
    WifiFriendTeamVSHUD();//806258fc
    ~WifiFriendTeamVSHUD() override; //80633650 vtable 808bdff8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 806336bc
    PageId GetPausePageId() const override; //0x64 80633648
    int GetEnabledCtrlRaceBases() const override; //0x68 80633640
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633638
}; //total size 0x1DC
size_assert(WifiFriendVSHUD, 0x1DC);
}//namespace Pages
#endif