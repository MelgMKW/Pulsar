#ifndef _EGG_FOG_
#define _EGG_FOG_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

namespace EGG {
class Fog {
public:
    Fog(); //80226f04
    virtual void vf_0x08(); //802a3028
    virtual void vf_0x0c();
    virtual void vf_0x10();
    virtual void vf_0x14();
    virtual void vf_0x18();
    virtual void vf_0x1c();
    virtual ~Fog(); //80227174
    virtual void vf_0x24();
    virtual void SetGX(); //80226f60
    u8 unknown_0x4[0x20 - 0x4];
}; //0x20

class FogMgr {
public:
    explicit FogMgr(u16 maxFogCount); //802271bc
    virtual void Mount(); //8022734c vtable 802a3058
    virtual void Save();
    virtual void vf_0x10();
    virtual void vf_0x14();
    virtual void vf_0x18();
    virtual void vf_0x1c();
    virtual ~FogMgr();
    u8 unknown_0x4;
    u8 padding[3];
    u16 fogCount; //0x8 = pageCount
    u16 fogCount2; //0xA
    u8 padding2[2];
    Fog **fogs; //0xC
    u8 unknown_0x10[0x20 - 0xC];
}; //0x20
}//namespace EGG
#endif