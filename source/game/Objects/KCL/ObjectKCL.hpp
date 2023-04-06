#ifndef _OBJECT_KCL_
#define _OBJECT_KCL_
#include <kamek.hpp>
#include <game/Objects/Object.hpp>
#include <game/Visual/Model/CourseModel.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/

class ObjectKCL : public Object { //still an abstract class, used by objects that use a custom KCL, extended by a subclass for external KCLs
public:
    explicit ObjectKCL(KMP::GOBJHolder *gobjHolder); //8081a6d0
    ~ObjectKCL() override; //8067eb3c vtable 808d69d8
    void UpdateModel() override; //0x1c 8081a8d0
    void Init() override; //0x20 8081a79c
    float GetCollisionDiameter() const override; //0xa0 80682918
    u32 GetDrawType() const override; //0xb0 806807e0
    virtual void vf_0xb4() = 0; //0xb4
    virtual void InitCollision(); //0xb8 80682924
    virtual void RegisterEntity(float radius); //0xbc 8081a85c
    virtual void vf_0xc0() = 0; //0xc0
    virtual void vf_0xc4() = 0; //0xc4
    virtual void vf_0xc8() = 0; //0xc8
    virtual void vf_0xcc() = 0; //0xcc
    virtual bool ProcessLakituCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) = 0; //0xd0
    virtual void vf_0xd4() = 0; //0xd4
    virtual bool CheckCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) = 0; //0xd8
    virtual bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) = 0; //0xdc
    virtual void UpdateKCLHandler(float radius, Vec3 *position, KCLTypesBIT bitfield, u32 r6); //0xe0 80682914
    virtual void vf_0xe4() = 0; //0xe4
    virtual void vf_0xe8() = 0; //0xe8
    virtual void vf_0xec() = 0; //0xec
    virtual void vf_0xf0() = 0; //0xf0
    virtual void vf_0xf4() = 0; //0xf4
    virtual bool CheckOOBCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) = 0; //0xf8
    virtual void vf_0xfc() = 0; //0xfc
    virtual bool ProcessCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) = 0; //0x100
    virtual bool AreItemsAllowed(); //0x104 8068290c if false, items will disappear on the object
    virtual float vf_0x108(); //0x108 80682900
    virtual void vf_0x10c(); //0x10c 806828f8
    virtual void InitItemEntity(void *unkItemObjSub, Vec &itemPosition); //0x110 806828fc when an item entity is created on top of the object (item throw or backspam)
    virtual void UpdateItemEntity(void *unkItemObjSub, Vec &itemPosition); //0x114 806828f4 r4 contains base position?
    virtual void vf_0x118(); //0x118 806828f0
    virtual int vf_0x11c(); //0x11c 806828e8

}; //0xAC
size_assert(ObjectKCL, 0xAC);


#endif