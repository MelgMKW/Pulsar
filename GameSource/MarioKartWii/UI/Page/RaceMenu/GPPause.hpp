#ifndef _GPPAUSE_
#define _GPPAUSE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class GPPause : public RaceMenu { //ID 0x17
public:
    static const PageId id = PAGE_GP_PAUSE_MENU;
    GPPause(); //80624af4 
    ~GPPause() override; //806333f0 vtable 808bddf0
    int GetRuntimeTypeInfo() const override; //0x60 8063345c
    int getmsgidBMG() const override; //0x68 806333c0
    u32 GetButtonCount() const override; //0x6c 806333e8
    const u32* GetVariantsIdxArray() const override; //0x70 806333dc
    bool IsPausePage() const override; //0x74 806333c8
    const char* GetButtonsBRCTRName() const override; //0x78 806333d0
}; //total size 0x344
size_assert(GPPause, 0x344);
}//namespace Pages
#endif