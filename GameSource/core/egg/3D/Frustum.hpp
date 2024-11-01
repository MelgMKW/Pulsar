#ifndef _EGG_FRUSTUM_
#define _EGG_FRUSTUM_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/Math/Matrix.hpp>

using namespace nw4r;
namespace EGG {

//Docs and matrix form using view volume: http://learnwebgl.brown37.net/08_projections/projections_perspective.html
//Matrix form using field of view: https://imgur.com/yl2fpo3

class Frustum {
public:
    Frustum(u32 type, Vector2f* aspectRatios, u32 r6, float near, float far); //r5 = width and height aspect ratio = width / height
    Frustum(const Frustum& other); //80227724
    void CopyToG3D_Perspective(g3d::Camera& camera); //802277fc
    void CopyToG3D_Orthographic(g3d::Camera& camera); //80227868

    void CalcMtxPerspective(math::MTX44& dest) const; //802278d0

    void GetPerspectiveParams(float* params); //80227b18 same offset as StateGX SetProjectionv


    void GetOrthographicParams(float* top, float* bottom, float* left, float* right); //80227cb4
    void GetOrthographicParams(math::MTX44* dest); //80227bd4

    void SetProjectionPerspectiveGX(); //802277a4
    void SetProjectionOrthographicGX(); //802277d0

    //bitfield specifies what to load from anm 1 = load fovy, 2 = load width, 4 = load near/far
    void LoadFromAnmScn(g3d::ResAnmScn& resAnmScn, int resAnmCamIdx, u32 bitField, float frame); //80227960

    /*
        top = near * tan(fovy/2) (t, b, r, l at near)
        bottom = -top
        right = top * aspect
        left = -right
    */
    bool GetViewToScreen(Vector3f* screenPos, const Vector3f& viewPos) const; //80227e18
    bool IsDirty() const; //8023ddc8

    u32 type; //0 ortho, 1 perspective
    u32 r6; //0x4
    float width; //0x8 also left
    float height; //0xc also top/orthoHeight
    float fovy; //0x10
    float tanFovy; //0x14 set to a constant for some reason but if loaded from AnmScn, is calculated
    float near; //0x18
    float far; //0x1c
    float unknown_0x20[3];
    u8 unknown_0x2c[0x34 - 0x2c];
    u16 bitfield; //0x34 1 = dirty
    u8 padding[2];
    virtual ~Frustum(); //0x38 8022018c vtable 802a3080
    virtual void LoadDirectly(); //80227ff4 without using nw4r::g3d::camera
    virtual void CopyToG3D(g3d::Camera& camera); //80228180 inlines either copytog3d
}; //0x3C
}//namespace EGG
#endif

