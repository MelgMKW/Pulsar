#ifndef _TTENDPAGE_
#define _TTENDPAGE_
#include <kamek.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>

namespace Pages {
class TTEnd : public RaceMenu { //ID 0x21
public:
    TTEnd(); //80624e04
    ~TTEnd() override; //80632cd4 vtable 808bd918
    int GetRuntimeTypeInfo() const override; //0x60 80632d40
    int GetMessageBMG() const override; //0x68 80632ca4
    u32 GetButtonCount() const override; //0x6c 80632ccc
    const u32 *GetVariantsIdxArray() const override; //0x70 80632cc0
    bool IsPausePage() const override; //0x74 80632cac
    const char *GetButtonsBRCTRName() const override; //0x78 80632cb4
};//0x344
static_assert(sizeof(TTEnd) = 0x344, "TTEnd");
}//namespace Pages


#endif