#ifndef _BATTLEEND_
#define _BATTLEEND_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class BattleEnd : public RaceMenu { //ID 0x23
public:
    static const PageId id = PAGE_BATTLEENDMENU;
    BattleEnd(); //80624e8c
    ~BattleEnd() override; //80632a34 vtable 808bd7a4
    int GetRuntimeTypeInfo() const override; //0x60 80632aa0
    int GetMessageBMG() const override; //0x68 80632a04
    u32 GetButtonCount() const override; //0x6c 80632a2c
    const u32* GetVariantsIdxArray() const override; //0x70 80632a20
    bool IsPausePage() const override; //0x74 80632a0c
    const char* GetButtonsBRCTRName() const override; //0x78 80632a14
}; //total size 0x344
size_assert(BattleEnd, 0x344);

class BattleFinalRaceEnd : public RaceMenu { //ID 0x24
public:
    static const PageId id = PAGE_BATTLE_FINALRACE_ENDMENU;
    BattleFinalRaceEnd(); //80624ed0
    ~BattleFinalRaceEnd() override; //8063298c vtable 808bd728
    int GetRuntimeTypeInfo() const override; //0x60 806329f8
    int GetMessageBMG() const override; //0x68 8063295c
    u32 GetButtonCount() const override; //0x6c 80632984
    const u32* GetVariantsIdxArray() const override; //0x70 80632978
    bool IsPausePage() const override; //0x74 80632964
    const char* GetButtonsBRCTRName() const override; //0x78 8063296c
}; //total size 0x344
size_assert(BattleEnd, 0x344);
}//namespace Pages
#endif