#ifndef _VSRACEENDPAGE_
#define _VSRACEENDPAGE_
#include <kamek.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>

namespace Pages {
class VSRaceEnd : public RaceMenu { //ID 0x22
public:
    VSRaceEnd(); //80624e48
    ~VSRaceEnd() override; //80632b30 vtable 808bd820
    int GetRuntimeTypeInfo() const override; //0x60 80632b9c
    int GetMessageBMG() const override; //0x68 80632aac
    u32 GetButtonCount() const override; //0x6c 80632b00
    const u32 *GetVariantsIdxArray() const override; //0x70 80632af4
    bool IsPausePage() const override; //0x74 80632ab4
    const char *GetButtonsBRCTRName() const override; //0x78 80632abc
};//0x344
static_assert(sizeof(VSRaceEnd) = 0x344, "VSRaceEnd");
}//namespace Pages


#endif