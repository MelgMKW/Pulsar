#ifndef _EGGVECTOR_
#define _EGGVECTOR_
#include <types.hpp>
#include <core/rvl/mtx/mtx.hpp>

namespace EGG {

struct Vector2f : nw4r::math::VEC2 {
    Vector2f() {}
    Vector2f(float x, float z): nw4r::math::VEC2(x, z) {};
    double NormalizeAndGetNorm(); //80243a00
    void Normalize(); //80243a78


};
struct Vector3f : nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(float x, float y, float z): nw4r::math::VEC3(x, y, z) {};
    double NormalizeAndGetNorm(); //80243adc
    void Normalize(); //80243b6c


};
}//namespace EGG






#endif

