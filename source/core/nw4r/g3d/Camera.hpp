#ifndef _NW4R_G3D_CAMERA_
#define _NW4R_G3D_CAMERA_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace g3d {

struct CameraData {
    enum Flag {
        FLAG_CAMERA_LOOKAT = 0x00000001,
        FLAG_CAMERA_ROTATE = 0x00000002,
        FLAG_CAMERA_AIM = 0x00000004,
        MASK_CAMERA = 0x00000007,
        FLAG_CMTX_VALID = 0x00000008,

        FLAG_PROJ_FRUSTUM = 0x00000010,
        FLAG_PROJ_PERSP = 0x00000020,
        FLAG_PROJ_ORTHO = 0x00000040,
        MASK_PROJ = 0x00000070,
        FLAG_PMTX_VALID = 0x00000080,

        FLAG_VIEWPORT_JITTER_ABOVE = 0x00000100
    };

    //
    // Data member
    //

    math::MTX34 cameraMtx;
    math::MTX44 projMtx;
    u32  flags; //see enum
    math::VEC3 cameraPos;
    math::VEC3 cameraUp;
    math::VEC3 cameraTarget;
    math::VEC3 cameraRotate;
    float zRotation;

    GXProjectionType    projType;
    float projFovy; //viewing angle vertical
    float projAspect; //aspect ratio
    float projNear;
    float projFar;
    float projTop;
    float projBottom;
    float projLeft;
    float projRight;
    float lightScaleS;
    float lightScaleT;
    float lightTransS;
    float lightTransT;
    math::VEC2 viewportOrigin;
    math::VEC2 viewportSize;
    float  viewportNear;
    float  viewportFar;
    u32  scissorX;
    u32  scissorY;
    u32  scissorWidth;
    u32  scissorHeight;
    s32  scissorOffsetX;
    s32  scissorOffsetY;
};

class Camera : public ResCommon<CameraData> {
    enum PostureType {
        POSTURE_LOOKAT,
        POSTURE_ROTATE,
        POSTURE_AIM
    };

    struct PostureInfo {
        PostureType type;
        math::VEC3 cameraUp;
        math::VEC3 cameraTarget;
        math::VEC3 cameraRotate;
        float cameraTwist;
    };

    Camera(CameraData *data); //8006a0c0
    void GetCameraMtx(math::MTX34 *dest) const; //8006a760
    void GetEnvironmentTexMtx(math::MTX34 *dest) const; //8006a970
    void GetProjectionMtx(math::MTX44 *dest) const; //8006a7c0
    void GetProjectionTexMtx(math::MTX34 *dest) const; //8006a8a0
    void GetViewport(float *xOrigin, float *yOrigin, float *width, float *height, float *near, float *far) const; //8006a6f0
    void GXSetProjection() const; //8006aa80
    void SetScissor(u32 xOrigin, u32 yOrigin, u32 width, u32 height); //8006ab50
    void SetScissorBoxOffset(s32 xOffset, s32 yOffset); //8006ab80
    void SetViewport(float xOrigin, float yOrigin, float width, float height); //8006a9f0
    void Init(); //8006a0d0
    void Init(u16 efbWidth, u16 efbHeight, u16 xfbWidth, u16 xfbHeight, u16 viWidth, u16 viHeight); //8006a120
    void SetCameraMtxDirectly(const math::MTX34 &src); //8006a4d0
    void SetOrtho(float top, float bottom, float left, float right, float near, float far); //8006a560
    void SetPerspective(float fovy, float aspect, float near, float far); //8006a520
    void SetPosition(float x, float y, float z); //8006a240
    void SetPosition(const math::VEC3 &position); //8006a270
    void SetPosture(const PostureInfo &info); //8006a2b0
    void SetProjectionMtxDirectly(const math::MTX44 *dest); //8006a5a0
    void GXSetScissor() const; //8006a5f0
    void GXSetScissorBoxOffset() const; //8006a610
    void SetViewportZRange(float near, float far); //8006a6d0
};

}//namespace g3d   
}//namespace nw4r


#endif