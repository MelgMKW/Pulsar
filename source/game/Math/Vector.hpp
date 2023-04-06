#ifndef _GAME_VECTOR_
#define _GAME_VECTOR_

#include <core/egg/Math/Vector.hpp>
#include <core/egg/Math/Quat.hpp>


typedef EGG::Quatf Quat;

struct Vec3 : EGG::Vector3f {
    Vec3 operator-(); //805147d4 unary -, negates the vec
    Vec3 RotateQuaternion(const Quat &quat, const Vec3 &angle); //805147fc
    Vec3 operator+(const Vec3 &rhs); //80514838
    Vec3 operator-(const Vec3 &rhs); //8051486c
    Vec3 Cross(const Vec3 &left, const Vec3 &right); //80537830 probably part of another class
    Vec3 MultiplyByScalar(float scalar, const Vec &src); //80514810
    Vec3 DivideByScalar(float scalar, const Vec3 &src); //806a62a4
    Vec EulerFromMatrix(const EGG::Matrix34f &src); //8067eaec

};

struct Vec2 : EGG::Vector2f {
    Vec2 operator+(const Vec2 &rhs); //80512040
    Vec2 operator-(const Vec2 &rhs); //8051201c
};

struct Vec3ZeroInit { //Vec3 that is init to 0, 0, 0
    Vec3ZeroInit(); //805a1fb0
    ~Vec3ZeroInit(); //80513600
    Vec3 position;
};

#endif