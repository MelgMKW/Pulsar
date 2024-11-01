#ifndef _EGG_EFFECT_
#define _EGG_EFFECT_
#include <types.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/nw4r/ef.hpp>
#include <core/nw4r/ut/Color.hpp>
#include <core/egg/Math/Matrix.hpp>

namespace EGG {

class ExpParticleManager;


/*Effect logic terminology:
-Fade = retires emitters, but current particles will be drawn until their life ends, then replaces the handle's effect by a dummy
-FollowFade = retires emitters, but current particles will be drawn until their life ends, AND DOES NOT replace the handle's effect by a dummy, so Create isn'"t needed"
-Kill = retires emitters AND particles then replaces the handle's effect by a dummy
-Create = assigns the correct ef:Effect to the handle by using EffectManager::CreateEffect; needed after fade and/or kill


*/
using namespace nw4r;
class Effect {
public:
    Effect(const char* effectName, int creatorIdx); //80222ccc
    virtual ~Effect(); //80222d50 vtable 802a2dc8 reset at 0x84
    virtual void Create(); //0xc 80222d90
    virtual void Fade(); //0x10 80222e60
    virtual void FollowFade(); //0x14 80222eb0
    virtual void Kill(); //0x18 80222ef4
    virtual void SetDisableCalc(bool disable); //0x1c 80222f50
    virtual void SetDisableDraw(bool disable); //0x20 80222fc0
    virtual void SetDisableCalcDraw(bool disable); //0x24 80223030
    virtual void SetLife(u16 life); //0x28 802230cc
    virtual void SetEmitRatio(float ratio); //0x2c 8022318c
    virtual void SetEmitInterval(u16 interval); //0x30 80223220
    virtual void SetEmitEmitDiv(u16 emitDiv); //0x34 802232b4
    virtual void SetPowerRadiationDir(float dir); //0x38 80223348
    virtual void SetPowerSpecDir(float dir); //0x3c 802233dc
    virtual void SetPowerSpecDirAddBase(float dir); //0x40 80223470 adds the dir to the EmitterResource value
    virtual void SetSpecDir(const Vector3f& dir); //0x44 80223528
    virtual void SetSpecDirAddBase(const Vector3f& dir); //0x48 80223620
    virtual void SetVelocity(const Vector3f& velocity); //0x4c 802237d0
    virtual void SetColor(u8 r, u8 g, u8 b, u8 a); //0x50 80223834
    virtual void SetParticleSize(const Vector2f& size); //0x54 802238fc
    virtual void SetParticleScale(const Vector2f& scale); //0x58 802239bc
    virtual void SetExpParticleManagerRotate(const Vector3f& rot); //0x5c 80223a30
    virtual void SetParticleRotate(const Vector3f& rot); //0x60 80223af0
    virtual void SetLocalScale(const Vector3f& locScale); //0x64 80223b6c
    virtual void SetDynamicsScale(const Vector3f& scale, const Vector2f*); //068 80223c18
    virtual void SetScale(float scale); //0x6c 80223d14
    virtual void SetScale(const Vector3f& scale); //0x70 80223d30
    virtual void SetPos(const Vector3f& pos); //0x74 80223d58
    virtual void SetMtx(const Matrix34f& mtx); //0x78 80223d80
    virtual void SetAnimStop(u32 index, bool enable); //0x7c 80223d9c
    virtual void Update(); //0x80 80223f58
    virtual void Reset(); //0x84 802242dc

    u16 GetEmitterPtclLife() const; //802240b8
    float GetEmissionRatio() const; //80224158
    bool LoadEmitter(bool r4); //returns true if properly loaded 802241f8
    static void SetParticleLightType(ExpParticleManager* particleManager, u8 type); //802238f4
    static void SetParticleAmbientColor(ExpParticleManager* particleManager, nw4r::ut::Color& color); //802238d0

    char name[0x20]; //0x4
    int creatorIdx; //0x24
    u32 bitfield;
    Vector3f scale; //0x2c
    Vector3f position; //0x38
    Mtx matrix; //0x44
    ef::Handle<ef::Effect> effectHandle; //0x74 nw4r::ef::effect
}; //total size 0x7c
size_assert(Effect, 0x7c);
}//namespace EGG
#endif