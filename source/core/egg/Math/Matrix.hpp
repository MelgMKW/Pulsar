#ifndef _EGGMATRIX_
#define _EGGMATRIX_
#include <types.hpp>
#include <core/egg/Math/Math.hpp>
#include <core/egg/Math/Vector.hpp>
#include <core/egg/Math/Quat.hpp>
namespace EGG {

//Everything is assumed to be in an euclidean space
/* Transformation Matrixes are used to map linearly a vector from one euclidean space to another
For example, a goomba defines an euclidean space centered on itself
https://cdn.discordapp.com/attachments/739985181389094975/1052953626462666782/image.png
this is how it looks, with rotation, scale and translation components in game*/

//_sinit_ at 8023040c
typedef struct Matrix34f : nw4r::math::MTX34 {
    Matrix34f() {};
    void CalcRPY(Vector3f &dest); //8022fb04
    void Set(float n00, float n01, float n02,
        float n03, float n10, float n11,
        float n12, float n13, float n20,
        float n21, float n22, float n23); //8022fbf0

    void InverseTo(Matrix34f &dest) const; //8022fabc
    void InverseTransposeTo(Matrix34f &dest) const; //8022fac0
    void MakeIdentity(); //8022fac4
    void MakeSRT(const Vector3f &scale, const Vector3f &rotation, const Vector3f &translation); //8022fc34
    void MakeRT(const Vector3f &rotation, const Vector3f &translation); //8022fe14
    void MakeR(const Vector3f &rotation); //8022ff98
    void MakeST(const Vector3f &scale, Vector3f &translation); //802300c8
    void MakeQT(const Quatf &quatf, const Vector3f &translation); //80230118
    void MakeQ(const Quatf &quatf); //802301d0
    void MakeS(const Vector3f &scale); //80230280
    void MakeQ2(const Quatf &quatf); //8023030c
    void SetAxisRotation(const Vector3f &axis, float angle); //802303bc
    Vector3f &MultVector(const Vector3f &factor); //802303f8
    void LoadPosMtx(u32 id); //8023040c
    void MultiplyTo(const Matrix34f &other, Matrix34f &dest); //80230410

};
}//namespace EGG



#endif

