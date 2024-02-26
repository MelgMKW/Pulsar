#ifndef _GHOSTREPLAYPAUSE_
#define _GHOSTREPLAYPAUSE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>

/*
Contributors:
-stebler, Melg
*/

namespace Pages {
class GhostReplayPause : public RaceMenu { //ID 0x1f
public:
    static const PageId id = PAGE_GHOST_REPLAY_PAUSE_MENU;
    GhostReplayPause(); //80624d7c 808bdb08
    ~GhostReplayPause() override; //80632f74
    int GetRuntimeTypeInfo() const override; //0x60 80632fe0
    int getmsgidBMG() const override; //0x68 80632f44
    u32 GetButtonCount() const override; //0x6c 80632f6c
    const u32* GetVariantsIdxArray() const override; //0x70 80632f60
    bool IsPausePage() const override; //0x74 80632f4c
    const char* GetButtonsBRCTRName() const override; //0x78 80632f54
}; //total size 0x344
size_assert(GhostReplayPause, 0x344);
}//namespace Pages
#endif