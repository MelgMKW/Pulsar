#ifndef _NW4R_G3D_RES_ANMSRT_
#define _NW4R_G3D_RES_ANMSRT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {


struct ResAnmTexSrtInfoData : TexSrtTypedef { //"SRT0 header"
    u16 frameCount;
    u16 materialCount;
    TexMatrixMode texMtxMode;
    u32 isLooped;
};

struct ResAnmTexSrtData { //https://wiki.tockdom.com/wiki/SRT0_(File_Format)
    ResBlockHeaderData header;
    u32 version;
    s32 offsetToBRRES;
    s32 offsetToTexSrtDataDic;
    s32 offsetToResUserData;
    s32 offsetToName;
    s32 offsetToPath;
    ResAnmTexSrtInfoData fileInfo;
    //data
};

class ResAnmTexSrt : public ResCommon<ResAnmTexSrtData>, public TexSrtTypedef {};

}//namespace g3d   
}//namespace nw4r


#endif