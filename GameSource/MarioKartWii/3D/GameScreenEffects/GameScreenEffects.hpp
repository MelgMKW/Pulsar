#ifndef _GAMESCREENEFFECTSMGR_
#define _GAMESCREENEFFECTSMGR_

#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/nw4r/ut.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>
#include <MarioKartWii/3D/GameScreenEffects/LensFlare.hpp>
#include <MarioKartWii/3D/GameScreenEffects/CreditsBars.hpp>
#include <MarioKartWii/3D/GameScreenEffects/FilterEffect.hpp>

using namespace nw4r;

//_sinit_ at 8054faf0
class GameScreenEffectsMgr { //lensflare, filters, etc...
public:

    explicit GameScreenEffectsMgr(u32 screenCount); //8054eb54
    virtual ~GameScreenEffectsMgr(); //8054f120 vtable 808b3e04
    void Update(); //8054f1b0
    void Draw(); //8054f41c
    void DrawFilterCourseFilterEffects(u32 screenIdx); //8054f7a4
    void CopyEFBToLensFlareTextures(); //8054f8e0
    void AddLensFX(const KMP::Holder<GOBJ>& gobjHolder); //8054f9a8
    static u16 GetRootScreenWidth(); //8054adb4
    static u16 GetRootScreenHeight(); //8054add0
    static void ResetGX(); //8054f3c8
    void RequestWhiteCourseFilter(u32 screenIdx); //8054fa94 
    void EnableExternalLensFlare(const Vec3& externalPosition); //8054fa10
    u32 screenCount; //0x4
    LensFlareMgr* lensFlare; //0x8
    FilterEffectMgr* filterEffectMgr; //0xC
    CourseFilterEffectMgr* courseFilterEffectMgr; //0x10
    CreditsBars* creditsBars; //0x14 only for credits
    bool isSinglePlayer; //0x18
    bool isSinglePlayer2; //0x19
    u8 padding[2];
}; //0x1c

#endif