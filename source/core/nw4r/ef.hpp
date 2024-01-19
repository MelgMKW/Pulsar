#ifndef _NW4R_EF_
#define _NW4R_EF_
#include <types.hpp>
#include <core/nw4r/ef/ActivityList.hpp>
#include <core/nw4r/ef/Common.hpp>
#include <core/nw4r/ef/Copy.hpp>
#include <core/nw4r/ef/CreationQueue.hpp>
#include <core/nw4r/ef/DrawInfo.hpp>
#include <core/nw4r/ef/DrawOrder.hpp>
#include <core/nw4r/ef/DrawStrategy.hpp>
#include <core/nw4r/ef/Effect.hpp>
#include <core/nw4r/ef/EffectSystem.hpp>
#include <core/nw4r/ef/Emitter.hpp>
#include <core/nw4r/ef/EmitterForm.hpp>
#include <core/nw4r/ef/Handle.hpp>
#include <core/nw4r/ef/LinkedObject.hpp>
#include <core/nw4r/ef/MemoryManager.hpp>
#include <core/nw4r/ef/Particle.hpp>
#include <core/nw4r/ef/ParticleManager.hpp>
#include <core/nw4r/ef/Random.hpp>
#include <core/nw4r/ef/ReferencedObject.hpp>
#include <core/nw4r/ef/res/ResEmitter.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/ef/res/ResTexture.hpp>

namespace nw4r {
namespace ef {
void _PSSinCosRad(register float* ret, register float val); //80036f70
void PSSinCosRad(register float* sin, register float* cos, register float val); //80036ff0
}//namespace ef
}//namespace nw4r


#endif