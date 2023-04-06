#ifndef _NW4R_G3D_RES_ANMCHR_
#define _NW4R_G3D_RES_ANMCHR_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {
struct ChrAnmResult {
    enum Flag {};
    u32 flags;
    math::VEC3 ratio;
    math::VEC3 rotation;
    math::MTX34 rotTranslation;
};

struct ResAnmChrInfoData { //"CHR0 header"
    enum ScalingRule {
        SCALINGRULE_STANDARD = 0,
        SCALINGRULE_SOFTIMAGE = 1,
        SCALINGRULE_MAYA = 2
    };
    u16 frameCount; //0x20
    u16 nodeCount; //0x22
    u32 isLooped; //0x24
    ScalingRule scalingRule;
};

struct ResAnmChrData { //https://wiki.tockdom.com/wiki/CHR0_(File_Format)
    ResBlockHeaderData header;
    u32 version; //0x8
    s32 offsetToBRRES; //0xc
    s32 toChrDataDic;  //0x10
    s32 offsetToResUserData; //0x14
    s32 offsetToName; //0x18
    s32 offsetToPath; //0x1c
    ResAnmChrInfoData fileInfo; //0x20
    //data
};

class ResAnmChr : public ResCommon<ResAnmChrData> {};

}//namespace g3d
}//namespace nw4r


#endif