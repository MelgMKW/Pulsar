#ifndef _GPRACEENDPAGE_
#define _GPRACEENDPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>

namespace Pages {
class GPRaceEnd : public RaceMenu { //ID 0x20
public:
    static const PageId id = PAGE_GP_ENDMENU;
    GPRaceEnd(); //80624dc0
    ~GPRaceEnd() override; //80632c2c vtable 808bd89c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80632c98
    int GetMessageBMG() const override; //0x68 80632ba8
    u32 GetButtonCount() const override; //0x6c 80632bfc
    const u32* GetVariantsIdxArray() const override; //0x70 80632bf0
    bool IsPausePage() const override; //0x74 80632bb0
    const char* GetButtonsBRCTRName() const override; //0x78 80632bb8
};//0x344
size_assert(GPRaceEnd, 0x344);
}//namespace Pages


#endif