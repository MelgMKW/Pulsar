#ifndef _EGG_EFFECT_
#define _EGG_EFFECT_
#include <types.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/nw4r/ef.hpp>
#include <core/egg/Math/Matrix.hpp>

namespace EGG {
class Effect {
public:
    Effect(const char *effectName, u32 r5); //0x80222ccc
    virtual ~Effect(); //0x80222d50 vtable 802a2dc8 reset at 0x84
    virtual void Create(); //0xc 80222d90 they're all actually virtual but oh well
    virtual void Fade(); //0x10 80222e60
    virtual void FollowFade(); //0x14 80222eb0
    virtual void Kill(); //0x18 80222ef4
    virtual void SetDisableCalc(bool disable); //0x1c 80222f50
    virtual void SetDisableDraw(bool disable); //0x20 80222fc0
    virtual void SetDisableCalcDraw(bool disable); //0x24 80223030
    virtual void SetLife(u16 life); //0x28 802230cc
    virtual void SetEmitRatio(float ratio); //0x2c 8022318c
    virtual void vf_0x30(); //0x30 80223220
    virtual void SetEmitEmitDiv(u16 emitDiv); //0x34 802232b4
    virtual void SetPowerRadiationDir(float dir); //0x38 80223348
    virtual void SetPowerSpecDir(float dir); //0x3c 802233dc
    virtual void vf_0x40(); //0x40 80223470
    virtual void SetSpecDir(const Vector3f &dir); //0x44 80223528
    virtual void vf_0x48(); //0x48 80223620
    virtual void vf_0x4c(); //0x4c 802237d0
    virtual void SetColor(u8 r, u8 g, u8 b, u8 a); //0x50 80223834
    virtual void vf_0x54(); //0x54 802238fc
    virtual void SetParticleScale(Vector2f &scale); //0x58 802239bc
    virtual void vf_0x5c(); //0x5c 80223a30
    virtual void SetParticleRotate(const Vector3f &rot); //0x60 80223af0
    virtual void SetLocalScale(const Vector3f &locScale); //0x64 80223b6c
    virtual void SetDynamicsScale(const Vector3f &scale, const Vector2f *); //068 80223c18
    virtual void SetScale(float scale); //0x6c 80223d14
    virtual void SetScale(const Vector3f &scale); //0x70 80223d30
    virtual void SetPos(const Vector3f &pos); //0x74 80223d58
    virtual void SetMtx(const Matrix34f &mtx); //0x78 80223d80
    virtual void vf_0x7c(); //0x7c 80223d9c
    virtual void Update(); //0x80 80223f58
    virtual void Reset(); //0x84 802242dc

    bool LoadEmitter(bool r4); //returns true if properly loaded 802241f8
    char name[0x20];
    u32 r5Arg_0x24;
    u32 unknown_0x28;
    Vector3f vec_0x2C; //position?
    Vector3f vec_0x38; //rotation?
    Mtx mtx_0x44;
    nw4r::ef::HandleBase handleBase; //0x74
}; //total size 0x7c
size_assert(EGG::Effect, 0x7c);
}//namespace EGG
#endif