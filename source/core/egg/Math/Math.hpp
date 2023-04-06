#ifndef _EGGMATH_
#define _EGGMATH_
#include <types.hpp>
#include <core/nw4r/math/math.hpp>

namespace EGG {
namespace Math {
//Everything is assumed to be in an euclidean space
float Sqrt(float value); //8022f80c
float FrSqrt(float value); //8022f85c
//angles in rad
float Sin(float angle); //8022f860
float Cos(float angle); //8022f86c in rad
float Tan(float angle); //8022f878

float Asin(float value); //8022f89c
float Acos(float value); //8022f8c0
float Atan2(float x, float y); //8022f8e4
}//namespace Math

}//namespace EGG

#endif