#ifndef _CTRLMENUTEAMCONFIRMTEAM_
#define _CTRLMENUTEAMCONFIRMTEAM_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>

//_sinit_ at 807ea24c
class CtrlMenuTeamConfirmTeam : public LayoutUIControl {
    CtrlMenuTeamConfirmTeam(); //80628ab4
    ~CtrlMenuTeamConfirmTeam() override; //80628b10 vtable 808d37d8
    void InitSelf() override; //0x18 807e9f5c
    int GetRuntimeTypeInfo() const override; //0x28 807ea240
    const char *GetClassName() const override; //0x2c 807e9db0
    void Load(u32 Team); //807e9dc0
    u32 team; //1 red, 0 blue
    LayoutUIControl playerElements[6];
}; //0xa30
size_assert(CtrlMenuTeamConfirmTeam, 0xa30);
#endif