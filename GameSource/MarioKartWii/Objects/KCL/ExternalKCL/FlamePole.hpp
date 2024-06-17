#ifndef _FLAMEPOLE_
#define _FLAMEPOLE_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ExternalKCL/VolcanoPiece.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class FlamePoleEff : public ObjectCollidable {
public:
    ~FlamePoleEff() override; //80681828 vtable 808c1208
    void OnStart() override; //0xc 8067e404
    void Update() override; //0x14 8067e410
    u32 GetPropertiesBitfield() override; //0x2c 80681820
    const char* GetBRRESName() const override; //0x34 80681814
    void LoadAnimations() override; //0x5c 806817b4
    virtual void vf_0xec(); //8068180c

    ObjectEffect* rk_flamePole; //0xb0
    float unknown_0xb4[2];
    u8 unknown_0xbc[0x4];
}; //0xc0

class FlamePole : public ObjectExternKCL, public ObjectCycleManager { //ObjectNum 0x1fd = 509
    explicit FlamePole(const KMP::Holder<GOBJ>& gobjHolder); //8067e6f4
    ~FlamePole() override; //8067ebe0 vtable 808c1098
    void OnStart() override; //0xc 8067ec94
    void Update() override; //0x14 8067ef70
    u32 GetPropertiesBitfield() override; //0x2c 80681590
    void LoadAnimations() override; //0x5c 80681508
    void UpdateModelMatrix() override; //0x6c 8067f240
    float GetCollisionDiameter() const override; //0xa0 806814c4
    bool AreItemsAllowed() override; //0x104 806814bc
    float vf_0x108() override; //0x108 806814b0
    void CalcOtherEntityDistance(CollisionInfo::ObjInfo* otherEntityObjInfo, const Vec3& otherEntityInitialPosition) override; //0x110 8067fdf4
    void UpdateOtherEntityPosWithRot(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos, Vec3& newEntityDir) override; //0x118 8067fe1c
    int vf_0x11c(CollisionInfo::ObjInfo* otherEntityObjInfo) override; //0x11c 806814a4
    const Mtx34& GetTransformationMatrix(u32 framesOffset) const override; //0x12c 8067fbb8
    float GetYScale() const override; //0x130 8067fc50
    bool IsCollidingNoTriangleCheckImpl(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x148 8067fe88
    bool IsCollidingImpl(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x14c 80680218
    //ObjectCycleManager vtable 808c11e8 at 0x104
    //~FlamePole() override; //thunk 80681868

    u8 unknown_0x124[0x154 - 0x124]; //0x124
    float size; //0x154
    ObjectEffect* rk_flamePoleFoot; //0x158
    FlamePoleEff* eff; //0x15c
    u32 cycleTime; //0x160 setting1
    u32 startDelay; //0x164 setting2
    float sizeFactor; //0x168 setting3
    u8 unknown_0x164[0x1cc - 0x164];

}; //0x1cc

}//namespace Objects
#endif