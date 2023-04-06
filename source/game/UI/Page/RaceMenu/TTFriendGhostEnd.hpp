#ifndef _TTFRIENDGHOSTENDPAGE_
#define _TTFRIENDGHOSTENDPAGE_
#include <kamek.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>

namespace Pages {
class TTFriendGhostEnd : public RaceMenu { //ID 0x29 "Congrats you beat XXX's ghost, Would you like to send"
public:
    TTFriendGhostEnd(); //80625024
    ~TTFriendGhostEnd() override; //80632644 vtable 808bd4bc
    int GetRuntimeTypeInfo() const override; //0x60 806326b0
    int GetMessageBMG() const override; //0x68 80632414
    u32 GetButtonCount() const override; //0x6c 8063263c
    const u32 *GetVariantsIdxArray() const override; //0x70 80632630
    bool IsPausePage() const override; //0x74 8063231c
    const char *GetButtonsBRCTRName() const override; //0x78 80632614
};//0x344
static_assert(sizeof(TTFriendGhostEnd) = 0x344, "TTFriendGhostEnd");
}//namespace Pages


#endif