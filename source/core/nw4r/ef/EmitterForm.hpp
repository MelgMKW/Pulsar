#ifndef _NW4R_EF_EMITTERFORM_
#define _NW4R_EF_EMITTERFORM_
#include <types.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace ef {

class Emitter;
class ParticleManager;

enum EmitFormType {
    EMITFORMTYPE_DISC = 0,
    EMITFORMTYPE_LINE = 1,
    EMITFORMTYPE_CUBE = 5,
    EMITFORMTYPE_CYLINDER = 7,
    EMITFORMTYPE_SPHERE = 8,
    EMITFORMTYPE_POINT = 9,
    EMITFORMTYPE_TORUS = 10
};

class EmitterForm {
public:
    virtual void Emission(Emitter* emitter, ParticleManager* particleMgr, int count, u32 flags, float* params, u16 particleSLifetime,
        float particleLifetimesRandomness, const nw4r::math::MTX34* space) = 0;
};

class EmitFormBuilder {
public:
    virtual EmitterForm* Create(EmitFormType type);
};

}//namespace ef
}//namespace nw4r
#endif