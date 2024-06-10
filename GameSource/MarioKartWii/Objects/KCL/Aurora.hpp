#ifndef _AURORA_
#define _AURORA_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ObjectKCL.hpp>

namespace Objects {

class Aurora : public ObjectKCL { //ObjectNum 0x204 = 516
public:
    explicit Aurora(const KMP::Holder<GOBJ>& gobjHolder); //807fab58
    ~Aurora() override; //807fb690 vtable 808d42a8
    void OnStart() override; //0xC 807fabc4
    void Update() override; //0x14 807fac84
    u32 GetPropertiesBitfield() override; //0x2c 807fb688
    void LoadAnimations() override; //0x5c 807fb5f0

    void LoadCollision() override; //0x60 807fb684
    void UpdateCollision() override; //0x74 807fb680
    float GetCollisionDiameter() const override; //0xa0 807fb5dc
    void vf_0xb4() override; //0xb4 807fb67c

    bool vf_0xc0(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc0 807fb59c
    bool vf_0xc4(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc4 807fb5ac
    bool vf_0xc8(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc8 807fb5bc
    bool vf_0xcc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xcc 807fb5cc

    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd0 807fb58c
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd4 807fb590
    bool IsColliding(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd8 807fb594
    bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xdc 807fb598

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe4 807fb54c
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe8 807fb55c
    bool vf_0xec(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xec 807fb56c
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* result) override; //0xf0 807fb57c


    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius)  override; //0xf4 807fb53c
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf8 807fb540
    bool vf_0xfc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xfc 807fb544
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x100 807fb548

    bool AreItemsAllowed() override; //0x104 807fb534
    float vf_0x108() override; //0x108 807fb528
    void CalcOtherEntityDistance(CollisionInfo::ObjInfo* objInfo, const Vec& sourcePosition); //0x110 807fb33c
    void UpdateOtherEntityPosWithRot(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos, Vec3& newEntityDir) override; //0x118 807fb39c
    int vf_0x11c(CollisionInfo::ObjInfo* otherEntityObjInfo) override; //0x11c 807fb520


    bool IsCollidingNoTerrainInfoImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); //0xf4 807fb6d0
    bool IsCollidingAddEntryNoTerrainInfoImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); //0xf8 807fb8b0
    bool IsCollidingAddEntryImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); //807fbe6c

    u32 framesCounter; //0xac
    Vec3 minDistancesForCalcs; //0xb0
    u32 boneIndexes[37]; //0xc0 translates the given bones indexes, so changing the order changes the shape and visual pos of the wave

}; //0x154

}//namespace Objects



#endif