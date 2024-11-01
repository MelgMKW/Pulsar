#ifndef _TTREPLAYPAUSE_
#define _TTREPLAYPAUSE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>


namespace Pages {
class TTReplayPause : public RaceMenu { //ID 0x39
public:
    static const PageId id = PAGE_TT_REPLAY_PAUSE;
    TTReplayPause(); //80625738
    ~TTReplayPause() override; //80633118 vtable 808bdc00
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80633184
    int GetMessageBMG() const override; //0x68 80630e8
    u32 GetButtonCount() const override; //0x6c 8063110
    const u32* GetVariantsIdxArray() const override; //0x70 80633104
    bool IsPausePage() const override; //0x74 806330f0
    const char* GetButtonsBRCTRName() const override; //0x78 806330f8
}; //total size 0x344
size_assert(TTReplayPause, 0x344);
}//namespace Pages
#endif