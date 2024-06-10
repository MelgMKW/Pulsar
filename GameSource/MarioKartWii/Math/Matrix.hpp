#ifndef _GAME_MATRIX_
#define _GAME_MATRIX_
#include <core/egg/Math/Matrix.hpp>
#include <MarioKartWii/Math/Vector.hpp>

struct Mtx34 : EGG::Matrix34f {
    Vec3 GetColumnByIdx(u32 idx); //80537b80
};

typedef nw4r::math::MTX33 Mtx33;



#endif