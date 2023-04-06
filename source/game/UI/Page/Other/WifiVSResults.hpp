#ifndef _WIFIVSRESULTSPAGE_
#define _WIFIVSRESULTSPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>


//_sinit_ at 

namespace Pages {

//_sinit_ at 806467ac
class WifiAwardResultItem : public LayoutUIControl {
public:
    WifiAwardResultItem(); //806455dc
    ~WifiAwardResultItem(); //80645618 vtable 808bf854
    void InitSelf() override; //0x18 806457e8
    int GetRuntimeTypeInfo() const override; //0x28 80646764
    const char *GetClassName() const override; //0x2c 806455cc
    void Load(u8 idx, bool hasTwoColumns); //80645670 bools depends on isTeamVS and localPlayerCount
};
class WiFiVSResults : public Page { //ID 0x44
public:
    WiFiVSResults(); //80645bc8
    ~WiFiVSResults() override; //80645c8c vtable 808bf7e4
    PageId GetNextPage() const override; //80646750
    void OnInit() override; //0x28 80645d28
    void OnActivate() override; //0x30 8064605c
    void BeforeEntranceAnimations() override; //0x38 80646148
    void AfterEntranceAnimations() override; //0x3c 8064615c
    void BeforeExitAnimations() override; //0x40 806461b4
    void AfterControlUpdate() override; //0x4c 806461c8
    int GetRuntimeTypeInfo() const override; //0x60 80646758

    void OnClick(u32 hudSlotId); //80646200
    Ptmf_1A<WiFiVSResults, void, u32> onClickHandler; //0x44 80646200
    PageManipulatorManager pageManipulatorManager; //0x58
    LayoutUIControl modeName; //0x19c
    LayoutUIControl congratulations; //0x310 "Better luck next time!"
    WifiAwardResultItem results[12]; //0x484, result rows
    bool isTeamVS; //0x15f4
    u8 localPlayerCount; //0x15f5 1 or 2
    u8 playerCount; //0x15f6
    u8 unknown_0x15f7[5];
}; //total size 0x15fc
size_assert(WiFiVSResults, 0x15fc);
}//namespace Pages
#endif