#ifndef _EGG_SHADOW_
#define _EGG_SHADOW_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Screen.hpp>

namespace EGG {

class ShadowTexture {

};


class ShadowTextureManager {
    ShadowTextureManager(); //8023ff24
    void Calc(); //8023ff88
    void Draw(const Screen& screen); //80240048

    u8 bitfield; //1 = enabled
    u8 padding;
    u16 unknown_0x2;
    u8 padding2[2];
    void* unknown_0x4[16];
    virtual ~ShadowTextureManager(); //0x44 8023c7e8 vtable 802a3f40
}; //0x48

class ShadowTextureDirector {
public:
    static ShadowTextureDirector* sInstance; //80386EE8
    static void CreateInstance(Heap* heap); //802384fc
    ShadowTextureDirector(); //80238580

    bool Insert(ShadowTextureManager* mgr); //802385b8 need to be inserted every frame
    bool Remove(ShadowTextureManager* mgr); //80238604
    void DrawAll(); //80238674 and then removes them all

    ShadowTextureManager* managers[8]; //0x0
    u16 mgrCount; //0x20
    u8 padding[2];

    virtual ~ShadowTextureDirector(); //80238540 vtable 802a3cd0

}; //0x28
}//namespace EGG
#endif