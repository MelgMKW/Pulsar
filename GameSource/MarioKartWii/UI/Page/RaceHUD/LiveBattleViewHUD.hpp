#ifndef _LIVEBATTLEVIEW_
#define _LIVEBATTLEVIEW_
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

namespace Pages {
class LiveBattleViewHUD : public RaceHUD { //ID 0x4A
    static const PageId id = PAGE_LIVEBATTLE_VIEW_HUD;
    LiveBattleViewHUD(); //806259fc
    ~LiveBattleViewHUD() override; //80633530 vtable 808bdef8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8063359c
    PageId GetPausePageId() const override; //0x64 80633528
    int GetEnabledCtrlRaceBases() const override; //0x68 80633520
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 80633518
}; //total size 0x1dc
size_assert(LiveBattleViewHUD, 0x1DC);
}//namespace Pages
#endif