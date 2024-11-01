#ifndef _LIVEVIEW_
#define _LIVEVIEW_
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

namespace Pages {
class LiveViewHUD : public RaceHUD { //ID 0x49
    static const PageId id = PAGE_LIVEVS_VIEW_HUD;
    LiveViewHUD(); //8062597c
    ~LiveViewHUD() override; //806335c0 vtable 808bdf78
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8063362c
    PageId GetPausePageId() const override; //0x64 806335b8 returns -1 as you can't pause
    int GetEnabledCtrlRaceBases() const override; //0x68 806335b0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806335a8
}; //total size 0x1dc
size_assert(LiveViewHUD, 0x1DC);
}//namespace Pages
#endif