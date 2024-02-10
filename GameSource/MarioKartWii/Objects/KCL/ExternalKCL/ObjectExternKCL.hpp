#ifndef _OBJECT_EXTERNALKCL_
#define _OBJECT_EXTERNALKCL_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ObjectKCL.hpp>
#include <MarioKartWii/KCL/KCLController.hpp>

class ObjectKCLController {
public:
    explicit ObjectKCLController(KCL* raw); //807c4ce8
    ~ObjectKCLController(); //807c4d6c
    void Update(const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale, float radius); //807c4dc8

    bool CalcCollision(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807C58D4
    bool CalcCollisionNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807c551c
    bool CalcCollisionAddEntry(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807c6860
    bool CalcCollisionAddEntryNoTriangleCheck(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807c5a68
    bool CalcCollisionAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807c64c0
    bool CalcCollisionAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807c56f8
    bool CalcCollisionNoTerrainInfo(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, float radius); //807c62cc


    KCLController* controller;
    Mtx34 srMat;
    Mtx34 transfoMat;
    float yScale; //0x64
    float unknown_0x68[3];
}; //0x74
size_assert(ObjectKCLController, 0x74);

//ObjectNum 0x219 = 537 DemoCol, 0x217 = 535 M
class ObjectExternKCL : public ObjectKCL { //for objects whose KCL is provided by the szs and not in the game code
public:
    explicit ObjectExternKCL(const KMP::Holder<GOBJ>& gobjHolder); //8081a980
    ~ObjectExternKCL() override; //8067eafc vtable 808d6af8

    void LoadCollision() override; //0x60 8081aa58
    void UpdateCollision() override; //0x74 80681490
    Vec3& GetPosition() override; //0x9c 80681448
    float GetCollisionDiameter() const override; //0xa0 80687d70

    void vf_0xb4() override; //0xb4 8068147c
    void InitCollision() override; //0xb8 8081ab4c

    bool vf_0xc0(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc0 806810f8
    bool vf_0xc4(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc4 806811b0
    bool vf_0xc8(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xc8 80681268
    bool vf_0xcc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xcc 80681320

    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd0 80680df4
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd4 80680ef0
    bool IsColliding(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xd8 80680fec
    bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xdc 806810e8
    void UpdateKCL(const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale, float radius) override; //0xe0 806807e8

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe4 80680b14 
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xe8 80680bcc
    bool vf_0xec(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xec 80680c84
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) override; //0xf0 80680d3c

    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf4 806807f0
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xf8 806808fc
    bool vf_0xfc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0xfc 80680a08
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) override; //0x100 80680b04


    bool AreItemsAllowed() override; //0x104 80687d68
    float vf_0x108() override; //0x108 80687d5c
    void SetObjInfoIsFilled(CollisionInfo::ObjInfo* objInfo) const override; //0x10c 8068142c
    void CalcOtherEntityDistance(CollisionInfo::ObjInfo* otherEntityObjInfo, const Vec3& otherEntityInitialPosition) override; //0x110 807fea60
    void UpdateOtherEntityPos(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos) override; //0x114 806813d8
    void UpdateOtherEntityPosWithRot(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos, Vec3& newEntityDir) override; //0x118 80687d58
    int vf_0x11c(CollisionInfo::ObjInfo* otherEntityObjInfo) override; //0x11c 807fea58

    virtual void UpdateCollisionPosition(u32 r4); //0x120 8081ad6c
    virtual void SetYScale(); //0x124 8081af28 //something vertical scale
    virtual void UpdateDiffPosVector(const Vec3& src); //0x128 80681450
    virtual const Mtx34& GetTransformationMatrix() const; //0x12c 807feac0
    virtual float GetYScale() const; //0x130 80687db0
    virtual float GetPeriod() const; //0x134 8068143c
    virtual bool HasCurrentCollision(); //0x138 806808ec
    virtual bool IsSolidForLakitu(); //0x13c 806808f4
    virtual bool vf_0x140(); //0x140 806809f8
    virtual bool IsDriveable(); //0x144 80680a00
    virtual bool IsCollidingNoTriangleCheckImpl(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //0x148 8081afb4
    virtual bool IsCollidingImpl(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //0x14c 8081b16c

    ObjectKCLController* kclController; //0xAC
    Vec3 diffPrevCurPosition; //0xB0 Cur - Prev 
    u8 unknown_0xbc[0xFC - 0xbc];
    u32 timer; //0xFC resets when equal to raceinfo's global timer
    u8 unknown_0x100[4];
};
size_assert(ObjectExternKCL, 0x104);


#endif