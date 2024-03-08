#ifndef _PULINFO_
#define _PULINFO_
#include <kamek.hpp>

namespace Pulsar {

class Info {
public:
    friend class System;
    //User Options Getters
    static Info* sInstance;
    static inline u32  GetKey() { return sInstance->roomKey; }
    static inline bool HasTrophies() { return sInstance->hasTTTrophies; }
    static inline bool Has200cc() { return sInstance->has200cc; }
    static inline bool HasUMTs() { return sInstance->hasUMTs; }
    static inline bool HasFeather() { return sInstance->hasFeather; }
    static inline bool HasMegaTC() { return sInstance->hasMegaTC; }
    static inline u32 GetWiimmfiRegion() { return sInstance->wiimmfiRegion; }
    static inline u32 GetProb100() { return sInstance->prob100cc; }
    static inline u32 GetProb150() { return sInstance->prob150cc; }
    static inline u32 GetTrackBlocking() { return  sInstance->trackBlocking; }
    static inline u16 GetCupIconCount() { return sInstance->cupIconCount; }
    static inline u8 GetChooseNextTrackTimer() { return sInstance->chooseNextTrackTimer; }
    //Context checking
    static bool IsHAW(bool isHost);
    static bool Is200cc();
    static bool IsFeather();
    static bool IsUMTs();
    static bool IsMegaTC();

    /*
Wiimmfi being wiimmfi means I can't use a kmCall or a even a kmBranch because a wiimmfi function that USES THE LR gets injected,
meaning the LR needs to be preserved. The u64 return is just to prevent the register variable from using r3/r4 as they are not safe
This is insanely hacky but it works and there aren't a million solutions
*/
#define PatchRegion(addr)\
    static inline u64 GetWiimmfiRegionStatic##addr(u64 src) {\
        register const Info *sInstance = Info::sInstance;\
        asmVolatile(lwz r7, Info.wiimmfiRegion(sInstance););\
        return src;\
    };\
    kmBranch(addr, GetWiimmfiRegionStatic##addr);\
    kmPatchExitPoint(GetWiimmfiRegionStatic##addr, ##addr + 4);

private:
    Info(const Info& rawInfo) { memcpy(this, &rawInfo, sizeof(Info)); }
    u32 roomKey; //transmitted to other players
    u32 prob100cc;
    u32 prob150cc;
    u32 wiimmfiRegion;
    u32 trackBlocking;
    bool hasTTTrophies;
    bool has200cc;
    bool hasUMTs;
    bool hasFeather;
    bool hasMegaTC;
    u16 cupIconCount;
    u8 chooseNextTrackTimer;
    u8 reservedSpace[40];
};


}//namespace Pulsar

#endif