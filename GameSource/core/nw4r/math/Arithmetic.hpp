#ifndef _NW4R_MATH_ARITHMETIC_
#define _NW4R_MATH_ARITHMETIC_
#include <types.hpp>
#include <include/c_math.h>
#include <core/rvl/mtx/mtx.hpp>

namespace nw4r {
namespace math {

extern const float F_PI; //803878F8


namespace detail {
float FExp(float);
float FLog(float);
}//namespace detail

inline float FExp(float value) { return detail::FExp(value); }
inline float FLog(float value) { return (value > 0.0f) ? detail::FLog(value) : NAN; }
float FrSqrt(float);

}//namespace math
}//namespace nw4r

#endif
