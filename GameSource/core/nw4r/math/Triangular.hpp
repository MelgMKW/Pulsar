#ifndef _NW4R_MATH_TRIANGULAR_
#define _NW4R_MATH_TRIANGULAR_
#include <types.hpp>
#include <include/c_math.h>
#include <core/rvl/mtx/mtx.hpp>

namespace nw4r {
namespace math {

extern const float F_PI; //803878F8
float SinFIdx(float fidx);
float CosFIdx(float fidx);
void SinCosFIdx(float* sin, float* cos, float fidx);
float Atan2FIdx(float y, float x);
u16 Atan2Idx(float y, float x);


}//namespace math
}//namespace nw4r

#endif
