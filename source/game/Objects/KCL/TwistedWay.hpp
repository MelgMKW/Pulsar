#ifndef _TWISTEDWAY_
#define _TWISTEDWAY_
#include <kamek.hpp>
#include <game/Objects/KCL/ObjectKCL.hpp>

//Goomba, just as an example
namespace Objects {

class TwistedWay : public ObjectKCL { //0x1fe = 510
    explicit TwistedWay(GOBJ *gobj); //80813bd4
    ~TwistedWay(); //80814918 vtable 808d62f8
    void OnStart() override; //0xC 80813c40
    void Update() override; //0x14 80813cfc
    bool HasLod() override; //0x2c 80814910
    void LoadAnimations() override; //0x5c 80814900
    void LoadCollision() override; //0x60 8081490c
    void UpdateCollision() override; //0x74 80814908
    float GetCollisionDiameter() const override; //0xa0 808148f8

    void vf_0xb4() override; //0xb4 80814904 just a blr

    void vf_0xc0() override; //0xc0 808148b8
    void vf_0xc4() override; //0xc4 808148c8
    void vf_0xc8() override; //0xc8 808148d8
    void vf_0xcc() override; //0xcc 808148e8
    bool ProcessLakituCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xd0 808148a8
    void vf_0xd4() override; //0xd4 808148ac
    bool CheckCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xd8 808148b0
    bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override;
    //0xdc 808148b4 same as coursemodel update collision essentially

    void vf_0xe4() override; //0xe4 80814868
    void vf_0xe8() override; //0xe8 80814878
    void vf_0xec() override; //0xec 80814888
    void vf_0xf0() override; //0xf0 80814898
    void vf_0xf4() override; //0xf4 80814858
    bool CheckOOBCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xf8 8081485c
    void vf_0xfc() override; //0xfc 80814860
    bool ProcessCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0x100 80814864
    bool AreItemsAllowed() override; //0x104 80814850
    float vf_0x108() override; //0x108 80814844
    void InitItemEntity(void *unkItemObjSub, Vec &itemPosition) override; //0x110 80814428
    void vf_0x118() override; //0x118 808145d8
    int vf_0x11c() override; //0x11c 8081483c

    void ProcessCollisionImpl(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //80815d64
    u32 someFrameCount; //0xac init at 1000
    float unknown_0xb0[4];
    u8 unknown_0xc0[0x10c - 0xc0];
}; //0x10c

}//namespace Objects



#endif