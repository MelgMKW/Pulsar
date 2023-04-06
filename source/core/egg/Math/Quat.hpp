#ifndef _EGGQUAT_
#define _EGGQUAT_
#include <types.hpp>
#include <core/egg/Math/Math.hpp>
#include <core/egg/Math/Vector.hpp>

namespace EGG {
struct Quatf : nw4r::math::QUAT {
    void Set(float x, float y, float z, float w); //80239dfc
    void SetAxisRotation(const EGG::Vector3f &axis, float angle); //8023a0a0
    void SetRPY(const EGG::Vector3f &angle); //80239e10 quat from euler
    void SetRPY(float alpha, float beta, float gamma); //80239f58 quat from euler
    void RotateVector(const EGG::Vector3f &angle, EGG::Vector3f &dest); //8023a2d0 rotates quat by vec and then converts it to a vec
    void RotateVectorConjugate(const EGG::Vector3f &angle, EGG::Vector3f &dest); //8023a404
    void MultiplyVector(const Quatf &quat, const EGG::Vector3f &vec, Quatf &dest); //8023a540 no clue why the syntax is so weird
    void SlerpTo(const Quatf &q2, Quatf &dest, float parameter); //8023a5c4 interpolates between two angles with percent
    void MakeVectorRotation(EGG::Vector3f &base, EGG::Vector3f &rotation); //8023a788
    float Norm(); //8023a138
    void Normalise(); //8023a168
    void Inverse(Quatf &dest); //8023a210
};
}//namespace EGG



#endif

