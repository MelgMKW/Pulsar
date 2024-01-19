#ifndef _NW4R_MATH_TRIANGULAR_
#define _NW4R_MATH_TRIANGULAR_
#include <types.hpp>
#include <include/c_math.h>
#include <core/rvl/mtx/mtx.hpp>

namespace nw4r {
namespace math {

int SolveEquation2(float* root, float b, float c); //800867c0 ret = number of sols, root = solutions, must be at least float[2], a is assumed to be 1 in ax²+bx+c = 0
template <int pow>
inline float spow(float x) {
    return spow<pow - 1>(x) * x;
}

template <>
inline float spow<1>(float x) {
    return x;
}

}//namespace math
}//namespace nw4r

#endif
