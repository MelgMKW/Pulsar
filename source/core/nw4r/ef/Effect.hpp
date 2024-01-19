#ifndef _NW4R_EF_EFFECT_
#define _NW4R_EF_EFFECT_
#include <types.hpp>
#include <core/nw4r/ef/LinkedObject.hpp>
#include <core/nw4r/ef/DrawInfo.hpp>
#include <core/nw4r/ef/Common.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/ef/res/ResEmitter.hpp>
#include <core/nw4r/ef/Emitter.hpp>
#include <core/nw4r/ef/EffectSystem.hpp>

namespace nw4r {
namespace ef {

//Manages one layer of emitters
class Effect : public ReferencedObject {
public:
    Effect(); //80026340
    ~Effect(); //800263b0

    typedef void (*FuncCBPrevEmission)(Emitter* emitter, ParticleManager* particleMgr, int* count, u32* flags, float(*params)[6],
        u16* aPtclLife, float* aPtclLifeRnd, math::MTX34* space);
    typedef void (*FuncCBPtclCalc)(ParticleManager* particleMgr, ut::List* utList, Particle* head);
    struct CallBack {
    public:
        FuncCBPrevEmission mPrevEmission;
        FuncCBPtclCalc mPrevPtclCalc;
        FuncCBPtclCalc mPostPtclCalc;
    };

    void SendClosing() override; //80026550 vtable 80272258
    void DestroyFunc() override; //80026560
    virtual bool Initialize(EffectSystem* manager, EmitterResource* eh, u16 calcRemain); //80026410
    virtual Emitter* CreateEmitter(ResEmitter emitter, u8 drawWeight, u16 calcRemain); //80026fa0
    virtual void Calc(CalcOption option = CALC_TYPE_NORMAL); //80026970
    virtual void Draw(const DrawInfo& drawInfo); //80026d60

    Emitter* CreateEmitter(EmitterResource* res, u8 drawWeight, u16 calcRemain); //80026680
    u32 ForeachEmitter(ForeachFunc foreachFunc, u32 param, bool includeWait); //80026e50
    u32 ForeachParticleManager(ForeachFunc foreachFunc, u32 param, bool includeWait); //80026dc0
    Emitter* GetRootEmitter() const; //80026d90
    u32 RetireEmitter(Emitter* target); //80026780
    u32 RetireEmitterAll(); //80026810
    u32 RetireParticleAll(); //800268e0
    void SetRootMtx(const math::MTX34& mtx); //80026f30

    EffectSystem* system;
    ActivityList activityList;
    u32 groupID;
    CallBack callBack;
    u32 flags;
}; //0xa0

}//namespace ef
}//namespace nw4r
#endif