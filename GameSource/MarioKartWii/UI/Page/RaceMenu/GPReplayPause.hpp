#ifndef _GPREPLAYPAUSE_
#define _GPREPLAYPAUSE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class GPReplayPause : public RaceMenu { //ID 0x17
public:
    static const PageId id = PAGE_GP_REPLAY_PAUSE;
    GPReplayPause(); //806256f4
    ~GPReplayPause() override; //80633070 vtable 808bdb84
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 806330dc
    int GetMessageBMG() const override; //0x68 80632fec
    u32 GetButtonCount() const override; //0x6c 80633040
    const u32* GetVariantsIdxArray() const override; //0x70 80633034
    bool IsPausePage() const override; //0x74 80632ff4
    const char* GetButtonsBRCTRName() const override; //0x78 80632ffc
}; //total size 0x344
size_assert(GPReplayPause, 0x344);
}//namespace Pages
#endif