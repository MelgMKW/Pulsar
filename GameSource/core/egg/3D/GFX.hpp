#ifndef _EGG_GFX_
#define _EGG_GFX_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/nw4r/ut/Color.hpp>
namespace EGG {

class GFXEngine {//unofficial
public:
    struct GFXEngineInitParams {
        GFXEngineInitParams(); //80229344

        u16 efbWidth; //608
        u16 efbHeight; //456
        nw4r::ut::Color clearColor; //0x4 from display
        u32 unknown_0x8;
        u16 unknown_0xC[3];
        u16 screenWidth4_3; //0x12 608
        u16 screenWidth16_9; //0x14 832
        u8 padding[2];
        virtual ~GFXEngineInitParams(); //0x18 80229068 vtable 80229068

    };
    static GFXEngine* sInstance; //80386E78
    static void Create(u16 efbWidth, u16 efbHeight, EGG::Heap* heap); //8022900c
    static void Initialize(const GFXEngineInitParams& params, EGG::Heap* heap); //802290a8
    static u16 efbHeight; //80386F48
    static u16 efbWidth; //80386f4a
    static nw4r::ut::Color clearColor; //80386f5c
    GFXEngine(); //80229328

    virtual ~GFXEngine(); //0xC 80229420 vtable 802a3098
};//0x10

}//namespace EGG
#endif