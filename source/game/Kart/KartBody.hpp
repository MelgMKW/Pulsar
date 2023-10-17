#ifndef _KARTBODY_
#define _KARTBODY_

#include <kamek.hpp>
#include <game/Kart/KartPart.hpp>
#include <game/Kart/KartBRRESHandle.hpp>
#include <game/File/DispParams/BikePartsDisp.hpp>
#include <game/File/DispParams/KartPartsDisp.hpp>
#include <game/File/DispParams/DriverDisp.hpp>
#include <game/File/DispParams/KartDriverDisp.hpp>


namespace Kart {

class PhysicsHolder;

class Body : public Part { //tentative name
public:
    Body(const Values& kartValues, PhysicsHolder* physicsHolder); //8056c394 
    ~Body() override; //8056cd84 vtable 808b53c0
    void CreateModelDirectors(BRRESHandle& handle) override; //0x14 8056c410
    bool LoadModel(BRRESHandle& handle) override; //0x18 8056c3fc
    void vf_0x20(BRRESHandle& handle); //0x20 8056c9e8
    void PrepareAnm(u32 anmIdx, bool r5, bool r6); //8056ca48

    virtual void GetMatrix(Mtx34& dest) const; //0x44 8056c604
    virtual void UpdateWheelMatrix(Wheel& wheel, u32 wheelIdx); //0x48 8056c664
    virtual void Reset(); //0x4c 8056c4b4
    virtual void SetFloat_0x98(float f1); //0x50 8056e424
    virtual void SetHandleDistance(float distance); //0x54 8056e41c
    virtual void vf_0x58(); //0x58 8056c500
    virtual void SetDispParams(KartPartsDispParam* kartPartsDispParams, BikePartsDispParam* bikePartsDispParams) = 0; //0x5c
    virtual void vf_0x60(); //0x60 8056c874
    virtual void vf_0x64() = 0; //0x64

    void Init(KartPartsDispParam* kartPartsDispParams, BikePartsDispParam* bikePartsDispParams); //8056c458

    PhysicsHolder* kartPhysicsHolder; //0x90
    float unknown_0x94;
    float rightHandleDistance; //0x98
    float unknown_0x9c[2];
    u8 unknown_0xa4[0xa8 - 0xa4];
    Mtx34 unknown_0xa8;
    Mtx34 unknown_0xd8;
    u8 unknown_0x108[0x168 - 0x108];
    Mtx34 unknown_0x168;
    Mtx34 unknown_0x198;
    u8 unknown_0x1c8[0x230 - 0x1c8];
    float wheelForwardRotationSpeed; //from KartPartsDispParam/BikePartsDispParam
    float wheelBackwardRotationSpeed; //same


}; //Total size 0x240

class Arm : public Part { //arm_fr rr fl rl rl (forward/rear right/left)
public:
    ~Arm() override; //8056e4d4 vtable 808b5424
    bool LoadModel(BRRESHandle& handle) override; //0x18 8056c10c
    void UpdateMatrix() override; //0x1c 8056c124
    u8 unknown_0x90[4];
    u32 idx; //0x94
    bool unknown_0x98;
    u8 padding[3];
};
class BodyKart : public Body {
public:
    BodyKart(const Values& values, PhysicsHolder* physicsHolder); //8056ccc0
    ~BodyKart() override; //8056e494 vtable 808b5358
    void vf_0xC() override; //0xC 8056d118
    void Load() override; //0x10 8056ce04
    void UpdateMatrix() override; //0x1c 8056ce98
    void vf_0x24() override; //0x24 8056d230
    void ApplyStarColors() override; //0x28 8056d280
    void vf_0x2c() override; //0x2c 8056d2f8
    void vf_0x30() override; //0x30 8056d370
    void UpdateModelDrawPriority(u32 scnObjDrawOptionsIdx) override; //0x34 8056d3e8


    void SetDispParams(KartPartsDispParam* kartPartsDispParams, BikePartsDispParam* bikePartsDispParams) override; //0x5c 8056cdc4
    void vf_0x64() override; //0x64 8056d1ac

    Part** parts; //0x238 size wheelCount
    u16 wheelCount; //0x23c
    u8 padding[2];

}; //0x240

class BikeHandle : public Part {
public:
    ~BikeHandle() override; //8056d8f0 vtable 808b5314
    bool LoadModel(BRRESHandle& handle) override; //0x18 8056d4b0
    void UpdateMatrix() override; //0x1c 8056d4c0
};

class BikeSwingArm : public Part {
    ~BikeSwingArm() override; //8056d930 vtable 80e5157c
    bool LoadModel(BRRESHandle& handle) override; //0x18 8056d680
    void UpdateMatrix() override; //0x1c 8056d690
};

class BodyBike : public Body {
    BodyBike(const Values& kartValues, PhysicsHolder* physicsHolder); //8056d858
    ~BodyBike() override; //8056e2bc vtable 808b5268

    void vf_0xC() override; //8056dfc0
    void Load() override; //0x10 8056d998

    bool LoadModel(BRRESHandle& handle) override; //0x18 8056d984
    void UpdateMatrix() override; //0x1c 8056da88
    void vf_0x24() override; //0x24 8056e094
    void ApplyStarColors() override; //0x28 8056e0b4
    void vf_0x2c() override; //0x2c 8056e108
    void vf_0x30() override; //0x30 8056e15c
    void UpdateModelDrawPriority(u32 scnObjDrawOptionsIdx) override; //0x34 8056e1b0
    void GetMatrix(Mtx34& dest) const override; //0x44 8056dd54
    void UpdateWheelMatrix(Wheel& wheel, u32 wheelIdx) override; //0x48 8056de94

    void SetDispParams(KartPartsDispParam* kartPartsDispParams, BikePartsDispParam* bikePartsDispParams) override; //0x5c 8056d970
    void vf_0x60() override; //0x60 8056da0c
    void vf_0x64() override; //0x64 8056e034

    BikeHandle handle; //0x238
    u8 unknown_0x2c8[4];
    BikeSwingArm swingArm; //0x2cc
    u8 unknown_0x35c[4];

}; //0x360

class BodyQuacker : public BodyBike {
    BodyQuacker(const Values& kartValues, PhysicsHolder* physicsHolder); //8056e218
    ~BodyQuacker() override; //8056e42c vtable 808b5200

    void GetMatrix(Mtx34& dest) const override; //0x44 8056e2fc
    void UpdateMatrix() override; //0x48 8056e35c

};

}//namespace Kart

#endif