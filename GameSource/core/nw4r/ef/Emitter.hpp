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
    u32 emitFlags;
    float emitRatio;
    float emitRandom;
    u16 emitInterval;
    u16 emitEmitDiv;
    float emitIntervalRandom;
    float emitCount;
    u16 emitSpan; /* Emit time */
    float lODNear;
    float lODFar;
    float lODMinEmit;
    float params[6];
    u8 inherit;
    s8 inheritTranslate;
    s8 velInitVelocityRandom;
    s8 velMomentumRandom;
    float velPowerRadiationDir;
    float velPowerYAxis;
    float velPowerRandomDir;
    float velPowerNormalDir;
    float velDiffusionEmitterNormal;
    float velPowerSpecDir;
    float velDiffusionSpecDir;
    math::VEC3 velSpecDir;
    math::VEC3 translate;
    math::VEC3 scale;
    math::VEC3 rotate;
};

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

    EmitterParameter parameter;
    EvaluateStatus evalStatus;
    EmitterResource* resource;
    Effect* effectMgr;
    ActivityList activityList;
    bool isFirstEmission;
    u16 waitTime;
    u16 emitIntervalWait;
    u32 tick;
    u16 calcRemain;
    u16 randSeed;
    Random random;
    EmitterForm* form;
    Emitter* parent;
    Particle* referenceParticle;
    EmitterInheritSetting inheritSetting;
    nw4r::math::VEC3 globalPosition;
    nw4r::math::VEC3 prevGlobalPosition;
    bool txDirty;
    math::MTX34 globalMtx;
};


}//namespace ef
}//namespace nw4r
#endif