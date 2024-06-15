#ifndef _EGG_SCREEN_
#define _EGG_SCREEN_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Frustum.hpp>

namespace EGG {

struct ViewPort { //unofficial
    float left;
    float top;
    float wd;
    float ht;
    float nearz;
    float farz;
};

class Screen : public Frustum {
public:
    struct InitParams {
        static InitParams* params; //802a3ee8
        u16 width4_3; //608 
        u16 height4_3; //480 most often

        float efbScreenWidthRatio4_3; //efbWidth / screenWidth
        float efbScreenHeightRatio4_3;
        u16 width16_9; //0xc used by 8023e53c 832, which is the value used by textures
        u16 height16_9; //0xe 456
        float efbScreenWidthRatio16_9; //0x10 efbWidth / screenWidth
        float efbScreenHeightRatio16_9; //0x14
        u16 efbWidth; //0x18
        u16 efbHeight;
        float unknown_0x1c;
        float unknown_0x20;

    };
    static void CreateDummy(u16* widths, u16* heights, u32 r5); //8023d0f8 4/3 & 16/9, this func is used to set the params
    static u32 aspectRatio; //80386F10 1 for 16/9
    static bool isDummyCreated; //80386F30
    static Screen* dummy; //803843b0

    Screen(); //8023d2b4
    Screen(const Screen& other); //8023d840
    ~Screen() override; //8022014c vtable 802a3f0c
    void LoadDirectly() override; //8023d4e8
    void CopyToG3D(g3d::Camera& camera) override; //8023d67c

    ViewPort& GetViewPort(); //8023dbd8

    u32 unknown_0x3C;
    float unknown_0x40[2];

    ViewPort viewPort; //0x48
}; //0x60
}//namespace EGG
#endif