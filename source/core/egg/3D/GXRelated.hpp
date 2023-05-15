#ifndef _EGG_GXRELATED_
#define _EGG_GXRELATED_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

namespace EGG {

class UnknownGX2 {
public:
    UnknownGX2(); //8023e724
    u8 unknown_0x0;
    u8 padding[3];
    virtual ~UnknownGX2(); //8021c330 vtable 802a3f20
}; //0x48

class UnknownGX : public UnknownGX2 {
public:
    UnknownGX(); //8023e748
    ~UnknownGX() override; //8023e86c vtable 802a3f30
    u8 unknown_0x8[2];
    u8 padding2[2];
    u32 unknown_0xC;
    float unknown_0x14[6];
    u8 unknown_0x2c[4];
    void* bloom; //0x30
    void* blur; //0x34
    u32 unknown_0x38;
}; //0x3c
}//namespace EGG
#endif