#ifndef _QUITCONFIRMATION_
#define _QUITCONFIRMATION_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>

namespace Pages {
class QuitConfirmation : public RaceMenu { //ID 0x2C
public:
    static const PageId id = PAGE_2P_QUIT_CONFIRMATION;
    QuitConfirmation(); //806250f0
    ~QuitConfirmation() override; //806324f4 vtable 808bd3c4
    int GetRuntimeTypeInfo() const override; //0x60 80632560
    int getmsgidBMG() const override; //0x68 806324c4
    u32 GetButtonCount() const override; //0x6c 806324ec
    const u32* GetVariantsIdxArray() const override; //0x70 806324e0
    bool IsPausePage() const override; //0x74 806324cc
    const char* GetButtonsBRCTRName() const override; //0x78 806324d4
}; //total size 0x344
size_assert(QuitConfirmation, 0x344);
}//namespace Pages
#endif