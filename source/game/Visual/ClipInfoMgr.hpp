#ifndef _CLIP_INFO_MGR_
#define _CLIP_INFO_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/

enum AREARenderType {
    AREA_RENDERTYPE_CAN_DISABLE = 0,
    AREA_RENDERTYPE_CAN_DISABLE_AND_RECALCULATE = 1,
    AREA_RENDERTYPE_NONE = 2
};
class ClipInfo { //as with entity, used by items, karts, objects...
    ClipInfo(); //80787bd8
    ~ClipInfo(); //80787be4
    void Init(Vec3 *position, bool isDefaultyEnabled, u16 areaRef, AREARenderType type, u32 r7, u32 r8,
        float near, float f2, float farDistance); //80787c24
    Vec3 *position;
    float nearDistance; //0x4
    float farDistanceSquared; //0x8
    float unknown_0xC[4]; //0xC
    u16 areaRefs; //0x1C
    u8 areaRenderType; //0x1E
    u8 padding;
    u32 bitfield; //0x20
    /*
    0x10101010 = defaultyEnabled the opposite = defaultyDisabled?

    */
}; //0x24

class FrustumUnknown {
    FrustumUnknown(); //8078768c
    ~FrustumUnknown(); //80787690
    u8 unknown[0x60];
};

class ClipInfoMgr : public EGG::Disposer {
    static ClipInfoMgr *sInstance; //809c2ef8
    static ClipInfoMgr *GetStaticInstance(); //8078746c
    static void DestroyStaticInstance(); //80787538

    ClipInfoMgr(); //807875ec inlined
    ~ClipInfoMgr() override; //80787340 vtable 808d17f8
    void Update(); //80787774
    ClipInfo *Insert(Vec3 *position, bool isDefaultyEnabled, AREARenderType type, u32 r7, u32 r8,
        float backwardDrawDistance, float f2, float forwardDrawDistance); //80787ab8
    ClipInfo *clipInfoArray[512]; //0x10
    u32 maxClipInfoCount;
    u32 clipInfoCount; //renderer count?
    FrustumUnknown *unknown[4]; //0x1c

}; //0x20




#endif