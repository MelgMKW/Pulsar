#ifndef _NW4R_G3D_RES_ANMAMBLIGHT_
#define _NW4R_G3D_RES_ANMAMBLIGHT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>

namespace nw4r {
namespace g3d {

class ResAnmScn;


struct ResAnmAmbLightData { //https://wiki.tockdom.com/wiki/SCN0_(File_Format)
    u32 size; // Data size including the variable length part
    s32 offsetTResAnmScnData; // Offset to ResAnmScnData serving as the parent
    s32 name; // The name of this resource
    u32 id; // The ID of this resource
    u32 refNumber; // The ref_number for this resource
    u32 flags;
    s32 offsetToResColorAnmFramesData;
};


class ResAnmAmbLight : public ResCommon<ResAnmAmbLightData> {};

}//namespace g3d
}//namespace nw4r


#endif