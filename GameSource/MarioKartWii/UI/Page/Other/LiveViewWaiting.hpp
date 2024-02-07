#ifndef _LIVEVIEWWAITINGPAGE_
#define _LIVEVIEWWAITINGPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>

//_sinit_ at 8064a3e0

namespace Pages {

class LiveViewWaiting : public Page { //ID 0x93
    static const PageId id = PAGE_LIVE_VIEW_WAITING;
    LiveViewWaiting(); //8064a0b0
    ~LiveViewWaiting() override; //8064a10c vtable 808bfc18
    PageId GetNextPage() const override; //0x10 8064a2d8
    void OnInit() override; //0x28 8064a198
    void BeforeEntranceAnimations() override; //0x38 8064a370
    void BeforeExitAnimations() override; //0x40 8064a324
    void AfterExitAnimations() override; //0x44 8064a3c8
    void AfterControlUpdate() override; //0x4c 8064a298

    BusySymbol busySymbol; //0x44
    MessageWindowControlScaleFade messageWindow; //0x1b8
    BlackBackControlForMessage blackBg; //0x32c
    ManipulatorManager manipulatorMgr; //0x4a0
}; //total size 0x4b0

size_assert(LiveViewWaiting, 0x4b0);

}//namespace Pages
#endif