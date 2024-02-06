#ifndef _OBJECT_KCL_
#define _OBJECT_KCL_
#include <kamek.hpp>
#include <game/Objects/Object.hpp>
#include <game/KCL/KCLController.hpp>


/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/

class ObjectKCL : public Object { //still an abstract class, used by objects that use a custom KCL, extended by a subclass for external KCLs
public:
    explicit ObjectKCL(const KMP::Holder<GOBJ>& gobjHolder); //8081a6d0
    ObjectKCL(u16 objId, const Vec3& position, const Vec3& rotation, const Vec3& scale); //8081a714
    ObjectKCL(const char* name, const Vec3& position, const Vec3& rotation, const Vec3& scale, u32 r8); //8081a758
    ~ObjectKCL() override; //8067eb3c vtable 808d69d8
    void UpdateModel() override; //0x1c 8081a8d0
    void Init() override; //0x20 8081a79c
    float GetCollisionDiameter() const override; //0xa0 80682918
    u32 GetDrawType() const override; //0xb0 806807e0
    virtual void vf_0xb4() = 0; //0xb4
    virtual void InitCollision(); //0xb8 80682924
    virtual void RegisterEntity(float radius); //0xbc 8081a85c

    virtual bool vf_0xc0(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xc0
    virtual bool vf_0xc4(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xc4
    virtual bool vf_0xc8(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xc8
    virtual bool vf_0xcc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xcc

    virtual bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xd0
    virtual bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xd4
    virtual bool IsColliding(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xd8
    virtual bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xdc

    virtual void UpdateKCL(const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale, float radius); //0xe0 80682914


    //These 4 mostly call 0xf4-0x100 with initialTime = 0 and radius = 0
    virtual bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) = 0; //0xe4
    virtual bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) = 0; //0xe8
    virtual bool vf_0xec(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) = 0; //0xec
    virtual bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret) = 0; //0xf0

    virtual bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xf4
    virtual bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xf8
    virtual bool vf_0xfc(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0xfc
    virtual bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, u32 initialTime, float radius) = 0; //0x100 the one used for players

    virtual bool AreItemsAllowed(); //0x104 8068290c if false, items will disappear on the object
    virtual float vf_0x108(); //0x108 80682900
    virtual void SetObjInfoIsFilled(CollisionInfo::ObjInfo* objInfo) const; //0x10c 806828f8

    //when an item entity is created on top of the object (item throw or backspam) or when an object needs to follow this object's movement
    //this fills the object info by computing the distance btw this object and other, and the updating the entity's objInfo pos accordingly every frame
    virtual void CalcOtherEntityDistance(CollisionInfo::ObjInfo* otherEntityObjInfo, const Vec3& otherEntityInitialPosition); //0x110 806828fc 
    virtual void UpdateOtherEntityPos(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos); //0x114 806828f4 updates newEntityPos with objInfo's distance + this object's position
    virtual void UpdateOtherEntityPosWithRot(CollisionInfo::ObjInfo* otherEntityObjInfo, Vec3& newEntityPos, Vec3& newEntityDir); //0x118 806828f0
    virtual int vf_0x11c(CollisionInfo::ObjInfo* otherEntityObjInfo); //0x11c 806828e8

}; //0xAC
size_assert(ObjectKCL, 0xAC);


#endif