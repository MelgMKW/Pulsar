#ifndef _NW4R_G3D_RES_ANMFOG_
#define _NW4R_G3D_RES_ANMFOG_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace g3d {

class ResAnmScn;

struct ResAnmFogData {
    u32 size;
    s32 offsetToResAnmScnData;
    s32 name;
    u32 id;
    u32 refNumber;
    u32 flags;
    GX::FogType type;
    s32 offsetToStartz;
    s32 offsetToEndz;
    s32 offsetTocolor;
};


class ResAnmFog : public ResCommon<ResAnmFogData> {};

}//namespace g3d
}//namespace nw4r


#endif