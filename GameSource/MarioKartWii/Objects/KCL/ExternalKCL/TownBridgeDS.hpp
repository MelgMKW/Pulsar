#ifndef _TOWNBRIDGEDS_
#define _TOWNBRIDGEDS_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ExternalKCL/ObjectExternKCL.hpp>

namespace Objects {
class TownBridgeDS : public ObjectExternKCL { //ObjectNum 0x1ff = 511
    enum State {
        TOWNBRIDGE_RISING,
        TOWNBRIDGE_FULLY_UP,
        TOWNBRIDGE_DESCENDING,
        TOWNBRIDGE_FULLY_DOWN
    };
    explicit TownBridgeDS(const KMP::Holder<GOBJ>& gobjHolder); //80809448
    ~TownBridgeDS() override; //8080ace0 vtable 808d5ae0
    void Update() override; //0x14 80809774
    u32 GetPropertiesBitfield() override; //0x2c 8080acd8
    void LoadAnimations() override; //0x5c 8080a8dc
    void LoadCollision() override; //0x60 808095b8

    bool AreItemsAllowed() override; //0x104 8080a8c8
    float vf_0x108() override; //0x108 8080a8bc
    void CalcOtherEntityDistance(CollisionInfo::ObjInfo* otherEntityObjInfo, const Vec3& otherEntityInitialPosition) override; //0x110 8080a0f0
    void UpdateOtherEntityPosWithRot(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos, Vec3& newEntityDir) override; //0x118 8080a4ac
    int vf_0x11c(CollisionInfo::ObjInfo* otherEntityObjInfo) override; //0x11c 8080a8b4
    const Mtx34& GetTransformationMatrix(u32 framesOffset)override; //0x12c 8080a964
    float GetPeriod() const override; //0x134 8080a8d0

    Vec3 initialRotation; //0x104
    bool unknown_0x110;
    u8 padding4[3];
    float inclinationAngle; //0x114 setting0
    u32 timeToRiseAndDescend; //0x118 setting1
    u32 timeToStopFullyUp; //0x11c setting2
    u32 timeToStopFullyDown; //0x120
    u32 totalPeriodTime; //0x124 2* timeToRise + timeToStopFullyUp + timeToStopFullyDown

    State state; //0x128
    Mtx34 transMtx2; //0x12c
    ObjectKCLController* kclController; //0x15c
    ObjectKCLController* kcl2Controller; //0x160
    ObjectKCLController* kcl3Controller; //0x164

}; //0x168

}//namespace Objects
#endif