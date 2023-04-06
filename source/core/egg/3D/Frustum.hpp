#ifndef _EGG_FRUSTUM_
#define _EGG_FRUSTUM_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/Math/Matrix.hpp>

using namespace nw4r;
namespace EGG {
//_sinit_ at 800a17b4
class Frustum { //unsure where to put it
public:
    Frustum(u32 type, Vector2f *r5, u32 r6); //0 ortho, 1 perspective 
    void CopyToG3D_Perspective(const Matrix34f *projMatrix); //802277fc
    //Non-official names:
    void GetOrthoCoords(float *top, float *bottom, float *left, float *right); //80227cb4
    void LoadOrthoIntoCamera(g3d::Camera *camera); //80227868

    u32 type;
    u32 r6;
    Vector2f r5;
    float fovy; //0x10
    u8 unknown_0x14[4];
    float neat; //0x18
    float far; //0x1c
    u8 unknown_0x20[0x38 - 0x20];
    virtual ~Frustum(); //0x38 8022018c vtable 802a3080
    virtual void LoadDirectly(); //80227ff4 without using nw4r::g3d::camera
    virtual void LoadIntoCamera(g3d::CameraData *data); //80228180
}; //0x3C
}//namespace EGG
#endif

