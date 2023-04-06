#ifndef _VOLCANOPIECE_
#define _VOLCANOPIECE_
#include <kamek.hpp>
#include <game/Objects/KCL/ExternalKCL/ObjectExternKCL.hpp>

namespace Objects {
class VolcanoPiece : public ObjectExternKCL { //0x1fc = 508
    explicit VolcanoPiece(KMP::GOBJHolder *gobjHolder); //80817de8
    ~VolcanoPiece() override; //80803da8 vtable 808d670c
    void Update() override; //0x14 80819400
    bool HasLod() override; //0x2c 80805974
    char *GetSubFileName() const override; //0x38 80803f6c
    void LoadCollision() override; //0x60 80817f6c
    void vf_0xc0() override; //0xc0 80805404
    void vf_0xc4() override; //0xc4 8080554c
    void vf_0xc8() override; //0xc8 80805694
    void vf_0xcc() override; //0xcc 808057dc
    bool ProcessLakituCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xd0 80804f68
    void vf_0xd4() override; //0xd4 808050ec
    bool CheckCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xd8 80805270
    bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xdc 808053f4

    void UpdateKCLHandler(float radius, Vec3 *position, KCLTypesBIT bitfield, u32 r6) override; //0xe0 808044c0
    void vf_0xe4() override; //0xe4 80804a48
    void vf_0xe8() override; //0xe8 80804b90
    void vf_0xec() override; //0xec 80804cd8
    void vf_0xf0() override; //0xf0 80804e20
    void vf_0xf4() override; //0xf4 808045ac
    bool CheckOOBCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0xf8 80804730
    void vf_0xfc() override; //0xfc 808048b4
    bool ProcessCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0x100 80804a38
    void UpdateCollisionPosition(u32 r4) override; //0x120 80818334
    void SetYScale() override; //0x124 80818674
    void UpdateDiffPosVector(const Vec3 &src) override; //0x128 80805924
    Mtx34 *UpdateTransformationMtx() const override; //0x12c 8080595c
    bool ProcessEntityCollisionImpl(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0x148 808199a8
    bool ProcessCollisionImpl(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime) override; //0x14c 80819da0
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
    ObjectKCLHandler *b_kclHandler; //0x16c
    ObjectKCLHandler *c_kclHandler; //0x170
}; //0x174

}//namespace Objects
#endif