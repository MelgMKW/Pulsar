#ifndef _NW4R_G3D_RES_ANMCAMERA_
#define _NW4R_G3D_RES_ANMCAMERA_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace g3d {

class ResAnmScn;

struct ResAnmCameraData {
    u32 size;
    s32 offsetToResAnmScnData;
    s32 name;
    u32 id;
    u32 refNumber;
    GX::ProjectionType projType;
    u32 flags;
    s32 offsetToResUserData;
    s32 offsetToPosX;
    s32 offsetToPosY;
    s32 offsetToPosZ;
    s32 offsetToAspect;
    s32 offsetToNear;
    s32 offsetToFar;
    s32 offsetToRotX;
    s32 offsetToRotY;
    s32 offsetToRotZ;
    s32 offsetToAimX;
    s32 offsetToAimY;
    s32 offsetToAimZ;
    s32 offsetToTwist;
    s32 offsetToPerspFovy;
    s32 offsetToOrthoHeight;
};

struct CameraAnmResult {
    u32 flags;
    GX::ProjectionType projType; //0x4
    math::VEC3 pos; //0x8 pos: Camera position
    float aspect; //0x14 aspect: aspect ratio width/height
    float near; //0x18 near: Distance to the near clipping plane
    float far; //0x1c far: Distance to the far clipping plane

    union {
        struct {
            Vec rot; //rot: Rotation angle around the xyz axis of the camera (in degrees)
        } rotate;
        struct {
            Vec aim; //0x20
            float twist; //0x2c twist: Rotation angle around the line of sight axis of the camera (in degrees)
        } aim;
    };
    union {
        float fovy; //0x30 fovy: Vertical direction field of view
        float orthoHeight;
    };
};

class ResAnmCamera : public ResCommon<ResAnmCameraData> {
    void GetAnmResult(CameraAnmResult* result, float frame) const; //80055fd0
};

}//namespace g3d
}//namespace nw4r


#endif