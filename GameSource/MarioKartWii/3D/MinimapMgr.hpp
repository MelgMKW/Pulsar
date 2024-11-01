#ifndef _MINIMAPMGR_
#define _MINIMAPMGR_
#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/3D/PostEffects/OutlineEffect.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
class MinimapMgr {
public:
    static MinimapMgr* sInstance; //809c3f58
    static MinimapMgr* CreateInstance(); //807df908
    static void DestroyInstance(); //807dfa04
    MinimapMgr(); //807dfad0 inlined
    ~MinimapMgr(); //807dfee4 

    static float* scale; //808a7780
    void Load(); //807dfba4
    void TryDraw(); //807dffa4 inlined
    void Draw(); //807e0028
    //returns percent values, 1 means fully to the right/top; if mirror, the x value is flipped x = (1 -x)
    void Convert3DPosToPercent(const Vec3& objPosition, Vec2& dest); //807e08e4
    void ApplyAREAType5(u32 areaSettingRelated); //807e057c
    EGG::TDisposer<MinimapMgr> disposer; //807df808 vtable 808d2e74
    u8 unknown_0x10[4];
    bool isMirror; //0x14
    u8 padding[3];
    EGG::OutlineEffect outlineEffect; //0x18
    EGG::CapTexture* capTexture; //0x54
    GX::TexObj texObj; //0x58
    Vec3 bottomleft; //0x78 posLDBone or KMP params
    Vec3 topRight; //0x84 posRUBone or KMP params
    Vec3 origin; //0x90 not sure used to position objects properly, x% = (xPos - 90.x / 90.x)
    float xOffset; //0x9c
    u8 unknown_0xa0[4];
    float yOffset; //0xa4 not sure
    ModelDirector* mapModel; //0xa8

}; //0xac
#endif