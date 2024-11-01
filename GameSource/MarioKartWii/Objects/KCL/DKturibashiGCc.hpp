#ifndef _DKTURIBASHIGCC_
#define _DKTURIBASHIGCC_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ObjectKCL.hpp>

namespace Objects {

class DKturibashiGCc : public ObjectKCL { //ObjectNum 0x202 = 514 rDKM bridge
    explicit DKturibashiGCc(const KMP::Holder<GOBJ>& gobj); //80805a4c
    ~DKturibashiGCc(); //80806514 vtable 808d52d8
    void OnStart() override; //0xC 80805ad8
    void Update() override; //0x14 80805c24
    u32 GetPropertiesBitfield() override; //0x2c 8080650c
    void LoadAnimations() override; //0x5c 808064fc
    void LoadCollision() override; //0x60 80806508
    void UpdateCollision() override; //0x74 80806504
    float GetCollisionDiameter() const override; //0xa0 808064e8

    void vf_0xb4() override; //0xb4 80806500

    bool vf_0xc0(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc0 808064a8
    bool vf_0xc4(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc4 808064b8
    bool vf_0xc8(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc8 808064c8
    bool vf_0xcc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xcc 808064d8


    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd0 80806498
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd4 8080649c
    bool IsColliding(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd8 808064a0
    bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xdc 808064a4

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe4 80806458
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe8 80806468
    bool vf_0xec(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xec 80806478
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xf0 80806488


    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf4 80806448
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf8 8080644c
    bool vf_0xfc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xfc 80806450
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x100 80806454


    bool AreItemsAllowed() override; //0x104 80806440
    float vf_0x108() override; //0x108 80806434
    void UpdateOtherEntityPos(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos) override; //0x110 808060d4
    void UpdateOtherEntityPosWithRot(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos, Vec3& newEntityDir) override; //0x118 80806268
    int vf_0x11c(CollisionInfo::ObjInfo* otherEntityObjInfo) override; //0x11c 8080642c


    bool IsCollidingImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); // 80807110
    float unknown_0xac;
    Vec3 collisionRelated;
    u32 boneJointsIdx[37]; //0xbc
}; //0x150

}//namespace Objects



#endif