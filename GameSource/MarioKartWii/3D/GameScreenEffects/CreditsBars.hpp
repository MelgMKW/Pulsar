#ifndef _CREDITSBARS_
#define _CREDITSBARS_

#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/nw4r/ut.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

using namespace nw4r;

class CreditsBars { //https://imgur.com/6NhidNt because credits are not meant for widescreen
public:
    CreditsBars(); //8054e8cc inlined
    virtual ~CreditsBars(); //8054fab0 vtable 808b3e10
    void Init(bool isWideScreen); //8054e9ac inlined
    void Draw(); //8054e9d4 inlined
    float screenWidth; //0x4
    float screenHeight; //0x8
    float* heightOfBars; //0xC
    bool isInitialized; //0x10
    u8 padding[3];
}; //0x14

#endif