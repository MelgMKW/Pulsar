#ifndef _CHECKRANKINGSPAGE_
#define _CHECKRANKINGSPAGE_
#include <kamek.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>

namespace Pages {
class CheckRankings : public RaceMenu { //ID 0x2B "Go to the MK Channel to view rankings?"
public:
    CheckRankings(); //806250ac
    ~CheckRankings() override; //8063259c vtable 808bd440
    int GetRuntimeTypeInfo() const override; //0x60 80632608
    int GetMessageBMG() const override; //0x68 8063256c
    u32 GetButtonCount() const override; //0x6c 80632594
    const u32 *GetVariantsIdxArray() const override; //0x70 80632588
    bool IsPausePage() const override; //0x74 80632574
    const char *GetButtonsBRCTRName() const override; //0x78 8063257c
};//0x344
static_assert(sizeof(CheckRankings) = 0x344, "CheckRankings");
}//namespace Pages


#endif