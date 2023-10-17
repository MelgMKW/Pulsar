#ifndef _NW4R_EF_CREATIONQUEUE_
#define _NW4R_EF_CREATIONQUEUE_
#include <types.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/ef/res/ResEmitter.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace ef {
class Particle;

class CreationQueue {
public:
    enum CreationType {
        TYPE_PARTICLE,
        TYPE_EMITTER
    };
    struct CreationQueueData {
        u8 type;
        u8 flags;
        u16 calcRemain;
        EmitterInheritSetting inheritSetting;
        Particle* referenceParticle;
        EmitterResource* emitterResource;
        math::VEC3 position;
        math::VEC3 velocity;
    };

    CreationQueue(); //80037be0
    void Execute(); //80037ef0
    void AddParticleCreation(const EmitterInheritSetting* setting, Particle* caller, EmitterResource* eh, u16 calcRemain,
        const nw4r::math::VEC3* position = nullptr, const nw4r::math::VEC3* velocity = nullptr); //80037d70
    void AddEmitterCreation(const EmitterInheritSetting* setting, Particle* caller, EmitterResource* eh, u16 calcRemain,
        const nw4r::math::VEC3* position = nullptr, const nw4r::math::VEC3* velocity = nullptr); //80037bf0

    int itemCount;
    CreationQueueData queueData[1024];

public:

};

}//namespace ef
}//namespace nw4r
#endif