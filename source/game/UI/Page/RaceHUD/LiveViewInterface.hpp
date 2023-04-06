#ifndef _LIVEVIEW_
#define _LIVEVIEW_
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>

namespace Pages {
class LiveViewInterface : public RaceHUD { //ID 0x49
    LiveViewInterface(); //8062597c
    ~LiveViewInterface() override; //806335c0 vtable 808bdf78
    int GetRuntimeTypeInfo() const override; //0x60 8063362c
    PageId GetPausePageId() const override; //0x64 806335b8 returns -1 as you can't pause
    int GetEnabledCtrlRaceBases() const override; //0x68 806335b0
    int GetCtrlRaceNameBalloonCount() const override; //0x6c 806335a8
}; //total size 0x1dc
size_assert(LiveViewInterface, 0x1DC);
}//namespace Pages
#endif