#ifndef _KINOKO_
#define _KINOKO_
#include <kamek.hpp>
#include <game/Objects/KCL/ExternalKCL/ObjectExternKCL.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class Kinoko_kuki : public ObjectCollidable { //ObjectNum 0x201 = 513 stem
public:
    ~Kinoko_kuki() override; //80807e90 vtable 808d582c
    bool HasLod() override; //0x2c 80807e88
    const char* GetSubFileName() const override; //0x38 80807e64
    void UpdateModelScale() override; //0x78 80807e84
    virtual void vf_0xec(); //0xec 80807e5c just a blr
    virtual void vf_0xf0(); //0xf0 80807e60 just a blr
    u16 textureSetting;
    u8 padding4[2];
}; //0xb4

class Kinoko : public ObjectExternKCL {
public:
    Kinoko(const KMP::Holder<GOBJ>& gobjHolder); //8080761c
    ~Kinoko() override; //80807a14 vtable 808d56d8
    void OnStart() override; //0xC 808077ec
    void Update() override; //0x14 8080782c
    bool HasLod() override; //0x2c 80807dac
    const char* GetSubFileName() const override; //0x38 80807d8c
    void vf_0xb4() override; //0xb4 80807d84
    void SetYScale() override; //0x124 80807d88
    virtual void UpdateSpecific() = 0; //0x150

    u16 textureSetting; //0x104
    u8 padding4[2];
    Vec3 position2; //0x108
    Vec3 scale2; //0x114
    Vec3 rotation2; //0x120
    Kinoko_kuki* stem;
    u16 idx; //0x130
    u16 unknown_0x132[3];
    float unknown_0x138[2]; //0.1, unk
    float maxExpansion; //0x140 0.0008 by default the bigger, the more the mushroom will expand at the apex of the cycle
    float unknown_0x144; //0x144 6pi/40
}; //0x148

class Kinoko_bend : public Kinoko { //ObjectNum 0x1f6 = 502
public:
    Kinoko_bend(const KMP::Holder<GOBJ>& gobjHolder); //80807b7c
    ~Kinoko_bend() override; //80807db4 vtable 808d5430
    void UpdateSpecific() override; //0x150 80807c98 

    u8 unknown_0x148[0x14c - 0x148];
    float unknown_0x14c; //0x14c
    float setting4TimesScale2; //0x150
    float unknown_0x154; //0x154
    u16 cycleShiftSetting; //0x158
    u16 cycleDuration; //0x15a min 2 = 2/60s for a full cycle
    float maxAngle; //0x15c setting converted to rad
    u16 setting4; //0x160
    u8 padding4[2];
    float period; //0x164 2pi/cycleDuration
}; //0x168

class Kinoko_ud : public Kinoko { //ObjectNum 0x1f5 = 501
    Kinoko_ud(const KMP::Holder<GOBJ>& gobjHolder); //80807950
    ~Kinoko_ud() override; //80807e1c vtable 808d5584
    const char* GetSubFileName() const override; //80807dfc
    void SetYScale() override; //0x124 80807df8
    void UpdateSpecific(); //0x150 80807a54

    u8 unknown_0x148[2];
    u16 cycleShiftSetting; //0x14a
    u16 curPauseFrames; //0x14c
    u16 cycleDuration; //0x14e
    u16 pauseDuration; //0x150
    u16 amplitude; //0x152

    float period; //0x158 2pi/cycleDuration
}; //0x15c

class Kinoko_nm : public ObjectExternKCL { //ObjectNum 0x1fa = 506 green mushrooms
public:
    ~Kinoko_nm() override; //80827a9c vtable 808d7248
    bool HasLod() override; //0x2c 80827a94
    const char* GetSubFileName() const override; //0x38 80827a74
    float GetPeriod() const override; //0x134 80827a68

    u16 textureSetting; //0x104;
    u8 padding4[2];
    Kinoko_kuki* stem; //0x108
}; //0x10c

}//namespace Objects
#endif