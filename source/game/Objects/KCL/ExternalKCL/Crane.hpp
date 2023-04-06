#ifndef _CRANE_
#define _CRANE_
#include <kamek.hpp>
#include <game/Objects/KCL/ExternalKCL/ObjectExternKCL.hpp>

namespace Objects {
class Crane : public ObjectExternKCL { //0x1fb
    explicit Crane(KMP::GOBJHolder *gobjHolder); //807fe658
    ~Crane() override; //807feb28 vtable 808d49e8
    void Update() override; //0x14 807fe7ec
    bool HasLod() override; //0x2c 807feb20
    float GetPeriod() const override; //0x134 807feaf0
    u8 unknown_0x104[0x128 - 0x104];
    u16 timeBeforeStarting; //0x128
    u16 amplitude; //0x12c
    u16 setting5; //0x12e
    u16 period; //0x130
    u16 setting6; //0x132
    u8 unknown_0x134[0x13c - 0x134];
}; //0x13C

}//namespace Objects
#endif