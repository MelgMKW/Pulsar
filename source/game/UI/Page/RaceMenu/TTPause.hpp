#ifndef _TTPAUSE_
#define _TTPAUSE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class TTPause : public RaceMenu { //ID 0x19
public:
    TTPause(); //80624be4 
    ~TTPause() override; //80633498 vtable 808bde6c
    int GetRuntimeTypeInfo() const override; //0x60 80633504
    int GetMessageBMG() const override; //0x68 80633468
    u32 GetButtonCount() const override; //0x6c 80633490
    const u32 *GetVariantsIdxArray() const override; //0x70 80633484
    bool IsPausePage() const override; //0x74 80633470
    const char *GetButtonsBRCTRName() const override; //0x78 80633478
}; //total size 0x344
size_assert(TTPause, 0x344);
}//namespace Pages
#endif