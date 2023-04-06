#ifndef _OBJECT_EXTERNALKCL_
#define _OBJECT_EXTERNALKCL_
#include <kamek.hpp>
#include <game/Objects/KCL/ObjectKCL.hpp>
#include <game/Collision/KCLHandler.hpp>

class ObjectKCLHandler {
public:
    explicit ObjectKCLHandler(KCL *raw); //807c4ce8
    KCLHandler *handler;
    Mtx34 mat_0x4;
    Mtx34 mat_0x34;
    float yScale; //0x64
    float unknown_0x68[3];
}; //0x74
size_assert(ObjectKCLHandler, 0x74);

class ObjectExternKCL : public ObjectKCL { //for objects whose KCL is provided by the szs and not in the game code
    explicit ObjectExternKCL(KMP::GOBJHolder *gobjHolder); //8081a980
    ~ObjectExternKCL() override; //8067eafc vtable 808d6af8

    void LoadCollision() override; //0x60 8081aa58
    void UpdateCollision() override; //0x74 80681490
    Vec3 *GetPosition() const override; //0x9c 80681448
    float GetCollisionDiameter() const override; //0xa0 80687d70

    void vf_0xb4() override; //0xb4 8068147c
    void InitCollision() override; //0xb8 8081ab4c

    void vf_0xc0() override; //0xc0 806810f8
    void vf_0xc4() override; //0xc4 806811b0
    void vf_0xc8() override; //0xc8 80681268
    void vf_0xcc() override; //0xcc 80681320
    bool ProcessLakituCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xd0 80680df4
    void vf_0xd4() override; //0xd4 80680ef0
    bool CheckCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xd8 80680fec
    bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xdc 806810e8
    void UpdateKCLHandler(float radius, Vec3 *position, KCLTypesBIT bitfield, u32 r6) override; //0xe0 806807e8

    void vf_0xe4() override; //0xe4 80680b14 
    void vf_0xe8() override; //0xe8 80680bcc
    void vf_0xec() override; //0xec 80680c84
    void vf_0xf0() override; //0xf0 80680d3c
    void vf_0xf4() override; //0xf4 806807f0
    bool CheckOOBCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xf8 806808fc
    void vf_0xfc() override; //0xfc 80680a08

    bool ProcessCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0x100 80680b04
    bool AreItemsAllowed() override; //0x104 80687d68
    float vf_0x108() override; //0x108 80687d5c
    void vf_0x10c() override; //0x10c 8068142c
    void InitItemEntity(void *unkItemObjSub, Vec &itemPosition) override; //0x110 807fea60  sets initial position
    void UpdateItemEntity(void *unkItemObjSub, Vec &itemPosition) override; //0x114 806813d8
    void vf_0x118() override; //0x118 80687d58
    int vf_0x11c() override; //0x11c 807fea58

    virtual void UpdateCollisionPosition(u32 r4); //0x120 8081ad6c
    virtual void SetYScale(); //0x124 8081af28 //something vertical scale
    virtual void UpdateDiffPosVector(const Vec3 &src); //0x128 80681450
    virtual Mtx34 *GetTransformationMatrix() const; //0x12c 807feac0
    virtual float GetYScale() const; //0x130 80687db0
    virtual float GetPeriod() const; //0x134 8068143c
    virtual bool vf_0x138(); //0x138 806808ec
    virtual bool IsSolidForLakitu(); //0x13c 806808f4
    virtual bool vf_0x140(); //0x140 806809f8
    virtual bool IsDriveable(); //0x144 80680a00
    virtual bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //0x148 8081afb4
    virtual bool ProcessCollisionImpl(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //0x14c 8081b16c

    ObjectKCLHandler *kclHandler; //0xAC
    Vec3 diffPrevCurPosition; //0xB0 Cur - Prev 
    u8 unknown_0xbc[0xFC - 0xbc];
    u32 timer; //0xFC resets when equal to raceinfo's global timer
    u8 unknown_0x100[4];
};
size_assert(ObjectExternKCL, 0x104);


#endif