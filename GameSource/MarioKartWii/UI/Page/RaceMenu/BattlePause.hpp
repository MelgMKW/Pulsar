#ifndef _BATTLEPAUSE_
#define _BATTLEPAUSE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class BattlePause : public RaceMenu { //ID 0x1A
public:
    static const PageId id = PAGE_BATTLE_PAUSE_MENU;
    BattlePause(); //80624c28 
    ~BattlePause() override; //80633284 vtable 808bdcf8
    int GetRuntimeTypeInfo() const override; //0x60 806332f0
    int GetMessageBMG() const override; //0x68 80633238
    u32 GetButtonCount() const override; //0x6c 8063327c
    const u32* GetVariantsIdxArray() const override; //0x70 80633270
    bool IsPausePage() const override; //0x74 80633240
    const char* GetButtonsBRCTRName() const override; //0x78 80633248
}; //total size 0x344
size_assert(BattlePause, 0x344);
}//namespace Pages
#endif