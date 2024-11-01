#ifndef _GPREPLAYHUD_
#define _GPREPLAYHUD_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

// Contributors: Melg
namespace Pages {
class GPReplayHUD : public RaceHUD { //ID 0x36
    static const PageId id = PAGE_GP_REPLAY_HUD;
    GPReplayHUD(); //806255f4
    ~GPReplayHUD() override; //80633d5c vtable 808BE578
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633dc8
    PageId GetPausePageId() const override; //0x64 80633d54
    int GetEnabledCtrlRaceBases() const override; //0x68 80633d4c

}; //total size 0x1DC
size_assert(GPReplayHUD, 0x1DC);
}//namespace Pages
#endif