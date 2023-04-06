#ifndef _EGGVECTOR_
#define _EGGVECTOR_
#include <types.hpp>
#include <core/rvl/mtx/mtx.hpp>

namespace EGG {

struct Vector2f : nw4r::math::VEC2 {
    double NormalizeAndGetNorm(); //80243a00
    void Normalize(); //80243a78


};
struct Vector3f : nw4r::math::VEC3 {
    double NormalizeAndGetNorm(); //80243adc
    void Normalize(); //80243b6c


};
}//namespace EGG






#endif

