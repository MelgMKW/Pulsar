#ifndef _NW4R_EF_PARTICLEMANAGER_
#define _NW4R_EF_PARTICLEMANAGER_
#include <types.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/ef/res/ResEmitter.hpp>
#include <core/nw4r/ef/ReferencedObject.hpp>
#include <core/nw4r/ef/Particle.hpp>
#include <core/nw4r/ef/ActivityList.hpp>
#include <core/nw4r/ef/DrawStrategy.hpp>

namespace nw4r {
namespace ef {

class Emitter;

class ParticleManager : public ReferencedObject {
public:
    enum ParticleManagerFlag {
        NW4R_EF_PMF_INHERITSCALE = 1 << 0,
        NW4R_EF_PMF_INHERITROTATE = 1 << 1,
        NW4R_EF_PMF_INHERITPIVOT = 1 << 2
    };
    struct ParticleModifier {
        struct SimpleLight {
            u8 type; //0x6c
            GX::Color ambient; //0x6d
            GX::Color diffuse; //0x71
            u8 padding[3];
            float radius; //0x78
            math::VEC3 position; //0x7c
        };
        math::VEC2 scale; //0x58
        math::VEC3 rotate; //0x60
        SimpleLight light; //0x6c
    }; //0x88

    void SendClosing() override; //0x8 80033490 vtable 80272500
    void DestroyFunc() override; //0xc 800334a0
    virtual bool Initialize(Emitter* parent, EmitterResource* resource); //0x10 800335f0
    virtual Particle* CreateParticle(u16 life, math::VEC3 position, math::VEC3 velocity, const math::MTX34* space,
        float momentum, const EmitterInheritSetting* setting, Particle* sourceParticle, u16 calcRemain = 0); //0x14 80033780
    virtual void Calc(); //0x18 800338b0
    virtual void Draw(const DrawInfo& drawInfo); //0x1c 80034f80

    void Modifier_SetSimpleLightAmbient(const GX::Color& ambient); //802238d0
    void Modifier_SetSimpleLightType(u8 type); //802238f4
    void Modifier_SetScale(math::VEC2& newScale); //80223a1c
    void Modifier_SetRotate(const math::VEC3& newRotate); //80223b50
    Emitter* managerEM; //0x20
    EmitterResource* resource; //0x24
    u32 flag; //0x28
    DrawStrategy* drawStrategy; //0x2c
    ut::Link drawOrderLink; //0x30
    ActivityList activityList; //0x38 list of Particle
    Particle* lastCalced; //0x54
    ParticleModifier modifier; //0x58
    u8 padding[2];
    s8 inheritTranslate; //0x8b
    u8 weight; //0x8c
    bool mtxDirty; //0x8d
    u8 padding2[2]; //0x8e
    math::MTX34 transMtx; //0x90
}; //0xc0

}//namespace ef
}//namespace nw4r
#endif