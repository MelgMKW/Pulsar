#ifndef _VOLCANOPIECE_
#define _VOLCANOPIECE_
#include <kamek.hpp>
#include <game/Objects/KCL/ExternalKCL/ObjectExternKCL.hpp>

namespace Objects {
class VolcanoPiece : public ObjectExternKCL { //ObjectNum 0x1fc = 508
    explicit VolcanoPiece(const KMP::Holder<GOBJ>& gobjHolder); //80817de8
    ~VolcanoPiece() override; //80803da8 vtable 808d670c
    void Update() override; //0x14 80819400
    u32 GetPropertiesBitfield() override; //0x2c 80805974
    const char* GetSubFileName() const override; //0x38 80803f6c
    void LoadCollision() override; //0x60 80817f6c
    bool vf_0xc0(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc0 80805404
    bool vf_0xc4(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc4 8080554c
    bool vf_0xc8(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc8 80805694
    bool vf_0xcc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xcc 808057dc


    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd0 80804f68
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd4 808050ec
    bool IsColliding(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd8 80805270
    bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xdc 808053f4

    void UpdateKCL(const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale, float radius) override; //0xe0 808044c0

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe4 80804a48
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe8 80804b90
    bool vf_0xec(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xec 80804cd8
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xf0 80804e20

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf4 808045ac
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf8 80804730
    bool vf_0xfc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xfc 808048b4
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x100 80804a38


    void UpdateCollisionPosition(u32 r4) override; //0x120 80818334
    void SetYScale() override; //0x124 80818674
    void UpdateDiffPosVector(const Vec3& src) override; //0x128 80805924
    const Mtx34& GetTransformationMatrix() const override; //0x12c 8080595c
    bool IsCollidingNoTriangleCheckImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x148 808199a8
    bool IsCollidingImpl(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x14c 80819da0
    virtual void UpdateTransformationMtxImpl(); //0x150 808187b4            
    virtual void Init_eAnm(); //0x154 808193fc just a blr as no _e mdl0      
    virtual void SetCollisionType(u32 type); //0x158 808045a8 just a blr as this is for _b.kcl

    char kclName[10]; //0x104, using setting 1
    Vec3 position2; //0x114
    Vec3 rotation2; //0x120
    float unknown_0x12c;
    u32 framesUntilShake; //0x130 using setting corresponding to engine class
    u32 framesUntilShakingStops; //0x134 (until shake + time it shakes) * 60 (from setting using engine class)
    u32 framesUntilFalling; //0x138 UntilShakingStops + FramesBtwShakingAndFalling (setting 8)
    Mtx34 transformationMtx2; //0x13c
    ObjectKCLController* b_kclHandler; //0x16c
    ObjectKCLController* c_kclHandler; //0x170
}; //0x174

}//namespace Objects
#endif