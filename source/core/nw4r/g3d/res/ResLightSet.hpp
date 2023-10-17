#ifndef _NW4R_G3D_RES_LIGHTSET_
#define _NW4R_G3D_RES_LIGHTSET_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {

class ResAnmScn;

struct ResLightSetData { //https://wiki.tockdom.com/wiki/SCN0_(File_Format)
    u32 size;
    s32 offsetToResAnmScnData;
    u32 name;
    u32 id;
    u32 refNumber;
    u32 ambLightName;
    u16 ambLightId;
    u8 numLight;
    u8 padding;
    u32 lightNames[8];
    u16 lightId[8];
};

class ResLightSet : public ResCommon<ResLightSetData> {
    bool Bind(const ResAnmScn scene); //80055840
};

}//namespace g3d
}//namespace nw4r


#endif