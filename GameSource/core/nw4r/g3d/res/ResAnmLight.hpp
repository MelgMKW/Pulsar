#ifndef _NW4R_G3D_RES_ANMLIGHT_
#define _NW4R_G3D_RES_ANMLIGHT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace g3d {

class ResAnmScn;

struct ResAnmLightData {
    u32 size;
    s32 offsetToResAnmScnData;
    s32 name;
    u32 id;
    u32 refNumber;
    u32 specLightObjIdx;
    s32 offsetToResUserData;
    u32 flags;
    s32 offsetToEnableBool;
    s32 offsetToPosX;
    s32 offsetToPosY;
    s32 offsetToPosZ;
    s32 offsetToColor;
    s32 offsetToAimX; //Viewpoint position x
    s32 offsetToAimY; //Viewpoint position y
    s32 offsetToAimZ; //Viewpoint position z
    GX::DistAttnFn distFunc;
    s32 offsetToRefDistance;
    s32 offsetToRefBrightness;
    GX::SpotFn spotFunc;
    s32 offsetToCutoff;
    s32 offsetToSpecColor;
    s32 offsetToShininess;
};


class ResAnmLight : public ResCommon<ResAnmLightData> {};

}//namespace g3d
}//namespace nw4r


#endif