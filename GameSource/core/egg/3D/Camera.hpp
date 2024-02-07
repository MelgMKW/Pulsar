#ifndef _EGG_CAMERA_
#define _EGG_CAMERA_
#include <types.hpp>
#include <core/egg/Math/Matrix.hpp>

namespace EGG {
class RotCamera {
public:
    RotCamera(); //80214a8c
};



class BaseCamera {
public:
    virtual Matrix34f& GetViewMatrix() = 0; //0x8
    virtual const Matrix34f& GetViewMatrix() const = 0; //0xc
    virtual void UpdateMatrix(); //0x10 8021460c
    virtual void DoUpdateMatrix() = 0; //0x14
    virtual void LoadMatrix() = 0; //0x18
    virtual void LoadOldMatrix() = 0; //0x1c
    virtual Vector3f GetPosition() = 0; //0x20
    virtual void Draw(EGG::BaseCamera* camera); //0x24 8021461c
    virtual void DoDraw() = 0; //0x28
    virtual Matrix34f& GetViewMatrixOld() = 0; //0x2c

    Vector3f GetLookVector(); //8021466c
    Vector3f GetRightVector(); //802146c0
    Vector3f GetUpVector(); //80214714
};

class LookAtCamera : public BaseCamera {
public:
    Matrix34f& GetViewMatrix() override; //0x8 80214bac vtable 802a29c0
    const Matrix34f& GetViewMatrix() const override; //0xc 80214ba4
    void DoUpdateMatrix() override; //0x14 80214770
    void LoadMatrix() override; //0x18 802149b8
    void LoadOldMatrix() override; //0x1c 80214a04
    Vector3f GetPosition() override; //0x20 80214bb4
    void DoDraw() override; //0x28 802149b4
    Matrix34f& GetViewMatrixOld() override; //0x2c 80214768

    Matrix34f viewMatrix; //0x4
    Matrix34f viewMatrixOld; //0x34    
    Vector3f position; //0x64
    Vector3f targetPosition; //0x70
    Vector3f targetDir; //0x7c

}; //0x88

//Orthographic camera, objects' size stays constant regardless of distance, makes for a great 2D representation
class OrthoCamera : public LookAtCamera {
public:
    OrthoCamera(); //80214a08
    void DoUpdateMatrix() override; //0x14 80214b14 vtable 802a2990
    float unknown_0x88[2];
}; //0x90
}//namespace EGG
#endif