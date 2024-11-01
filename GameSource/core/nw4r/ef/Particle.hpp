#ifndef _NW4R_EF_PARTICLE_
#define _NW4R_EF_PARTICLE_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/nw4r/math.hpp>
#include <core/nw4r/ef/res/ResTexture.hpp>
#include <core/nw4r/ef/res/ResEmitter.hpp>
#include <core/nw4r/ef/Common.hpp>
#include <core/nw4r/ef/ReferencedObject.hpp>

namespace nw4r {
namespace ef {

class Emitter;
class ParticleManager;

class ParticleParameter {
public:
    void Initialize(ParticleParameterDesc* ppd, ParticleManager* pm); //800324b0
    GX::Color color[2][2];
    math::VEC2 size; //0x10
    math::VEC2 scale; //0x18
    math::VEC3 rotate; //0x20

    nw4r::math::VEC2 textureScale[3]; //0x2c
    float textureRotate[3]; //0x44
    nw4r::math::VEC2 textureTranslate[3]; //0x50
    TextureData* texture[3]; //0x68
    u16 textureWrap; //0x74
    u8 textureReverse; //0x76
    u8 alphaCmpRef0;
    u8 alphaCmpRef1; //0x78
    s8 alphaFlickRnd; //0x79
    u8 rotateOffset[3]; //0x7a
    u8 collisionStatus; //0x7d
    u8 padding[2];

    nw4r::math::VEC3 velocity; //0x80
    nw4r::math::VEC3 position; //0x8c
    nw4r::math::VEC3 prevPosition; //0x98
    float momentum; //0xa4
};

class Particle : public ReferencedObject {
public:

    Particle(); //80032440
    ~Particle(); //80032450
    void SendClosing() override; //80032490 vtable 802724e8
    void DestroyFunc() override; //800324a0
    virtual bool Initialize(u16 life, nw4r::math::VEC3 position, nw4r::math::VEC3 velocity, ParticleManager* particleMgr,
        const nw4r::math::MTX34* space, float omentum, const EmitterInheritSetting* setting, Particle* sourceParticle); //800327d0

    ParticleParameter parameter; //0x20
    ParticleManager* particleManager; //0xc8


    math::VEC3 prevAxis; //0xcc

    EvaluateStatus evalStatus; //0xd8

    u16 tick; //0xdc
    u16 randSeed;
    u16 life; //0xe0
    u16 calcRemain;

}; //0xe4

}//namespace ef
}//namespace nw4r
#endif