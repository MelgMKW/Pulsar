#ifndef _NW4R_EF_EMITTER_
#define _NW4R_EF_EMITTER_
#include <types.hpp>
#include <core/nw4r/ef/ActivityList.hpp>
#include <core/nw4r/ef/Common.hpp>
#include <core/nw4r/ef/ReferencedObject.hpp>
#include <core/nw4r/ef/res/ResEmitter.hpp>
#include <core/nw4r/ef/EmitterForm.hpp>
#include <core/nw4r/ef/Random.hpp>
#include <core/nw4r/ef/Particle.hpp>
#include <core/nw4r/ef/ParticleManager.hpp>

namespace nw4r {
namespace ef {

class Effect;

struct EmitterParameter {
    u32 comFlags;
    u32 emitFlags; //0x4
    float emitRatio; //0x8
    float emitRandom; //0xc
    u16 emitInterval; //0x10
    u16 emitEmitDiv; //0x12
    float emitIntervalRandom; //0x14
    float emitCount; //0x18
    u16 emitSpan; //0x1c Emit time
    float lODNear; //0x20
    float lODFar; //0x24
    float lODMinEmit; //0x28
    float params[6]; //0x2c
    u8 inherit; //0x44
    s8 inheritTranslate; //0x45
    s8 velInitVelocityRandom;
    s8 velMomentumRandom;
    float velPowerRadiationDir; //0x48
    float velPowerYAxis; //0x4c
    float velPowerRandomDir; //0x50 
    float velPowerNormalDir; //0x54
    float velDiffusionEmitterNormal; //0x58
    float velPowerSpecDir; //0x5c
    float velDiffusionSpecDir; //0x60
    math::VEC3 velSpecDir; //0x64
    math::VEC3 translate; //0x70
    math::VEC3 scale; //0x7c
    math::VEC3 rotate; //0x88
}; //0x94

//source of generated particles
class Emitter : public ReferencedObject {

public:
    Emitter(); //80027be0
    ~Emitter(); //80027c40

    void SendClosing() override; //80027d10 vtable 802722c0
    void DestroyFunc() override; //80027d20
    virtual bool Initialize(Effect* parent, EmitterResource* eh, u8 drawWeight); //80028260
    virtual Emitter* CreateEmitter(EmitterResource* res, EmitterInheritSetting* setting, Particle* particle,
        u16 calcRemain = 0, nw4r::math::VEC3* position = nullptr); // //800283d0 creates a child

    virtual void CalcEmitter(); //800292e0
    virtual void CalcParticle(); //800294a0 
    virtual void CalcEmission(); //80029530
    virtual void CalcBillboard(); //80029650

    bool Closing(ParticleManager* target); //80027e10
    const nw4r::math::MTX34* CalcGlobalMtx(math::MTX34* dest); //80029a60
    bool CreateEmitterTmp(EmitterResource* eh, EmitterInheritSetting* setting, Particle* pp,
        u16 calcRemain, math::VEC3* position = nullptr); //800286b0
    void Emission(ParticleManager* particleMgr, const math::MTX34* space); //80028e90
    u32 ForeachParticleManager(ForeachFunc foreachFunc, u32 param, bool includeWait, bool eachEmitter); //80029d30
    bool InitializeDatas(EmitterResource* res, Effect* ef); //80027f90
    static nw4r::math::MTX34* RestructMatrix(nw4r::math::MTX34* dest, nw4r::math::MTX34* orig, bool isInheritS, bool isInheritR, s8 inheritT,
        bool movePivot); //80029830
    u32 RetireParticleManagerAll(); //80027ec0
    u32 RetireParticleAll(); //80027c80
    void SetMtxDirty(); //80029bb0
    u16 GetNumParticleManager() const; //80029cc0
    ParticleManager* GetParticleManager(u16 idx); //80029cd0

    EmitterParameter parameter; //0x20
    EvaluateStatus evalStatus; //0xb4
    EmitterResource* resource; //0xb8
    Effect* effectMgr; //0xbc
    ActivityList activityList; //0xc0 list of particleManager
    bool isFirstEmission; //0xdc
    u16 waitTime; //0xde
    u16 emitIntervalWait; //0xe0
    u32 tick; //0xe4
    u16 calcRemain; //0xe8
    u16 randSeed; //0xea
    Random random; //0xef
    EmitterForm* form; //0xf0
    Emitter* parent; //0xf4
    Particle* referenceParticle; //0xf8
    EmitterInheritSetting inheritSetting; //0xfc
    bool mtxDirty; //0x106
    u8 padding;
    math::MTX34 globalMtx; //0x108
}; //0x138


}//namespace ef
}//namespace nw4r
#endif