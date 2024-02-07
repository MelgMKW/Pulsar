#ifndef _NW4R_EF_EFFECTSYSTEM_
#define _NW4R_EF_EFFECTSYSTEM_
#include <types.hpp>
#include <core/nw4r/ef/MemoryManager.hpp>
#include <core/nw4r/ef/DrawOrder.hpp>
#include <core/nw4r/ef/DrawStrategy.hpp>
#include <core/nw4r/ef/EmitterForm.hpp>
#include <core/nw4r/ef/CreationQueue.hpp>
#include <core/nw4r/ef/Common.hpp>

namespace nw4r {
namespace ef {

class Effect;

extern DrawOrder basicDrawOrder; //the standard DrawOrder
extern DrawStrategyBuilder basicDrawStrategyBuilder; //the standard DrawStrategyBuilder
extern EmitFormBuilder basicEmitFormBuilder; //the standard EmitFormBuilder

//_sinit_ at 80027ab0
class EffectSystem {
public:
    typedef bool (*SortEffectOperatorLess)(const Effect* op1, const Effect* op2);

    static EffectSystem instance; //802ab4f8
    static EffectSystem* GetInstance(); //80027130

    //ctor inlined
    ~EffectSystem(); //800270a0
    bool Initialize(u32 maxGroupID); //80027140

    bool Closing(Effect* target); //800272a0
    Effect* CreateEffect(const char* name, u32 groupID = 0, u16 calcRemain = 0); //80027310
    Effect* CreateEffect(EmitterResource* res, u32 groupID = 0, u16 calcRemain = 0); //80027380
    u32 RetireEffectAll(u32 groupID); //800274b0
    u32 RetireEmitterAll(u32 groupID); //800275a0
    u32 RetireParticleAll(u32 groupID); //80027630
    void Calc(u32 groupID, CalcOption option = CALC_TYPE_NORMAL); //8022464c
    void Draw(const DrawInfo& drawInfo, u32 groupID); //800276c0
    void SetProcessCamera(const math::VEC3& position, const math::MTX34& matrix,
        float near, float far); //80027750
    void SortEffect(SortEffectOperatorLess less, u32 groupID); //80027830
    static bool SortEffectOperatorZ(const Effect* op1, const Effect* op2); //800279b0

    MemoryManagerBase* memoryManager;
    DrawOrderBase* drawOrderFunc;
    DrawStrategyBuilder* drawStrategyBuilder;
    EmitFormBuilder* emitFormBuilder;
    CreationQueue creationQueue;
    u32 maxGroupID;
    ActivityList* activityList;
    Random random;
    math::VEC3 processCameraPos;
    math::MTX34 processCameraMtx;
    float processCameraFar;
    float processCameraNear;
    bool xFFlushSafe;
    Emitter* tmpEmitter; // For Emitter::CreateEmitterTmp

};

}//namespace ef
}//namespace nw4r
#endif