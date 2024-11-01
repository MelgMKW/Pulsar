#ifndef _BATTLEHUD_
#define _BATTLEHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class BattleHUD : public RaceHUD { //ID 0x12
    static const PageId id = PAGE_P1BATTLE_HUD;
    BattleHUD();//80624974
    ~BattleHUD() override; //80633980 vtable 808be278
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 806339ec
    PageId GetPausePageId() const override; //0x64 80633948
    int GetEnabledCtrlRaceBases() const override; //0x68 80633940
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633938
}; //total size 0x1DC
size_assert(BattleHUD, 0x1DC);

class BattleMultiHUD : public RaceHUD { //ID 0x13, ID 0x14, ID 0x15
    static const PageId id = PAGE_P2BATTLE_HUD;
    BattleMultiHUD();//806249f4
    ~BattleMultiHUD() override; //806338C0 vtable 808be1f8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8063392c
    PageId GetPausePageId() const override; //0x64 80633888
    int GetEnabledCtrlRaceBases() const override; //0x68 80633880
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633878
}; //total size 0x1DC
size_assert(BattleHUD, 0x1DC);

}//namespace Pages
#endif