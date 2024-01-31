#ifndef _VSPAUSE_
#define _VSPAUSE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class VSPause : public RaceMenu { //ID 0x18
public:
    static const PageId id = PAGE_VS_RACE_PAUSE_MENU;
    VSPause(); //80624ba0 
    ~VSPause() override; //80633348 vtable 808bdd74
    int GetRuntimeTypeInfo() const override; //0x60 806333b4
    int GetMessageBMG() const override; //0x68 806332fc
    u32 GetButtonCount() const override; //0x6c 80633340
    const u32* GetVariantsIdxArray() const override; //0x70 8063334
    bool IsPausePage() const override; //0x74 80633304
    const char* GetButtonsBRCTRName() const override; //0x78 8063330c
}; //total size 0x344
size_assert(VSPause, 0x344);
}//namespace Pages
#endif