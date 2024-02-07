#ifndef _COMMONDISPPARAM_
#define _COMMONDISPPARAM_
#include <kamek.hpp>

struct ExhaustParticleSet {
    u32 type; //for particles; 0 = 2 pipes, 1 = left pipe, 2 = right pipe, other = no pipes
    Vec3 pos;
    Vec2 xyRot;
};

#endif