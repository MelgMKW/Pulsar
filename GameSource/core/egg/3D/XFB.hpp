#ifndef _EGG_XFB_
#define _EGG_XFB_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {

class Xfb {
public:
    Xfb(Heap* heap); //80244160
    static u32 CalcBufferSize(u16 width, u16 height); //802441ec
    u16 width;
    u16 height; //0x2
    void* frameBuffer; //0x4
    nw4r::ut::Link xfbLink; //0x8
}; //0x10

class XfbManager {
public:
    bool Attach(Xfb* xfb); //80244200 returns true if it attached a new xfb
    void CopyEFB(bool clear); //80244268
    void SetNextFrameBuffer(); //802442e8
    void PostVRetrace(); //80244350
    Xfb* xfb[4]; //current one is [1]
}; //0x10



}//namespace EGG

#endif