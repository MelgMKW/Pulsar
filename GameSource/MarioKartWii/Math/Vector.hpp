#ifndef _GAME_VECTOR_
#define _GAME_VECTOR_

#include <core/egg/Math/Vector.hpp>
#include <core/egg/Math/Quat.hpp>


typedef EGG::Quatf Quat;
struct Mtx34;

struct Vec3 : EGG::Vector3f {
    Vec3() {}
    Vec3(float x, float y, float z): EGG::Vector3f(x, y, z) {}
    Vec3 operator-(); //805147d4 unary -, negates the vec
    static Vec3 RotateQuaternion(const Quat& rot, const Vec3& point); //805147fc
    Vec3 operator+(const Vec3& rhs); //80514838
    Vec3 operator-(const Vec3& rhs); //8051486c
    static Vec3 Cross(const Vec3& left, const Vec3& right); //80537830 probably part of another class
    static Vec3 MultiplyByScalar(float scalar, const Vec3& src); //80514810
    static Vec3 MultiplyByScalar2(float scalar, const Vec3& src); //80518ab8

    static Vec3 DivideByScalar(float scalar, const Vec3& src); //806a62a4
    static Vec3 EulerFromMatrix(const EGG::Matrix34f& src); //8067eaec
    void CalcYAxisRotMtx(Mtx34& dest) const; //806b3ca4 rotMtx with axis (x, 0, z), so xz rotation

};

struct Vec2 : EGG::Vector2f {
    Vec2() {}
    Vec2(float x, float z): EGG::Vector2f(x, z) {}
    Vec2 operator+(const Vec2& rhs) const; //80512040
    Vec2 operator-(const Vec2& rhs) const; //8051201c
};

struct Vec3ZeroInit { //Vec3 that is init to 0, 0, 0
    Vec3ZeroInit(); //805a1fb0
    ~Vec3ZeroInit(); //80513600
    Vec3 position;
};

#endif