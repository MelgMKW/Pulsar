#ifndef _AIRBLOCK_
#define _AIRBLOCK_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ObjectKCL.hpp>

namespace Objects {

class Airblock : public ObjectKCL { //ObjectNum 0x1 = 1
public:
    explicit Airblock(const KMP::Holder<GOBJ>& gobjHolder); //807f9388
    Airblock(const Vec3& position, const Vec3& rotation, const Vec3& scale); //807f9424
    ~Airblock() override; //807f9910 vtable 808d4178
    void OnStart() override; //0xC 807f94cc
    void Update() override; //0x14 807f9904
    u32 GetPropertiesBitfield() override; //0x2c 807f9908
    void LoadCollision() override; //0x60 807f9584
    void UpdateCollision() override; //0x74 807f96a4
    float GetCollisionDiameter() const override; //0xa0 807f983c
    void vf_0xb4() override; //0xb0 807f9770

    bool vf_0xc0(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc0 807f98c4
    bool vf_0xc4(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc4 807f98d4
    bool vf_0xc8(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc8 807f98e4
    bool vf_0xcc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xcc 807f98f4

    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd0 807f98b4
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd4 807f98b8
    bool IsColliding(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd8 807f98bc
    bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xdc 807f98c0

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe4 807f9874
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe8 807f9884
    bool vf_0xec(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xec 807f9894
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xf0 807f98a4


    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius)  override; //0xf4 807f9864
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf8 807f9868
    bool vf_0xfc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xfc 807f986c
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x100 807f9870

    bool IsCollidingNoTerrainInfoImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); // 807f9950
    bool IsCollidingAddEntryNoTerrainInfoImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); // 807f9c14
    bool IsCollidingAddEntryImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius); // 807fa51c

    u8 unknown_0xAC[0xb4 - 0xac];
    u32 unknown_0xb4[4];
    bool isSetting1Equal1; //0xc4
    u8 padding4[3];
    u32 unknown_0xC8[3];
}; //0xd4

}//namespace Objects



#endif