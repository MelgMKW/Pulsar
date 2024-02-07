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
    GX::Color color[2][2];
    math::VEC2 size;
    math::VEC2 scale;
    math::VEC3 rotate;

    nw4r::math::VEC2 textureScale[3];
    float textureRotate[3];
    nw4r::math::VEC2 textureTranslate[3];
    TextureData* texture[3];
    u16 textureWrap;
    u8 textureReverse;
    u8 alphaCmpRef0;
    u8 alphaCmpRef1;
    s8 alphaFlickRnd;
    u8 rotateOffset[3];
    u8 collisionStatus;
    // padding 2byte

    nw4r::math::VEC3 velocity;
    nw4r::math::VEC3 position;
    nw4r::math::VEC3 prevPosition; // Previous position (updated during calc)
    float omentum;

    void Initialize(ParticleParameterDesc* ppd, ParticleManager* pm);
};

class Particle : public ReferencedObject {
public:

    Particle();
    ~Particle();
    void SendClosing() override;
    void DestroyFunc() override;
    virtual bool Initialize(u16 life, nw4r::math::VEC3 position, nw4r::math::VEC3 velocity, ParticleManager* particleMgr,
        const nw4r::math::MTX34* space, float omentum, const EmitterInheritSetting* setting, Particle* sourceParticle);

    ParticleParameter parameter;
    ParticleManager* particleManager;


    math::VEC3 prevAxis;

    EvaluateStatus evalStatus;

    u16 tick;
    u16 randSeed;
    u16 life; /* Lifetime */
    u16 calcRemain;


};

}//namespace ef
}//namespace nw4r
#endif