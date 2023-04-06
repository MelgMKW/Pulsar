#ifndef _NW4R_G3D_RES_ANMSHP_
#define _NW4R_G3D_RES_ANMSHP_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {


struct ResAnmShpInfoData { //"SHP0 header"
    u16 frameCount;
    u16 vertexCount;
    u32 isLooped;
};

struct ResAnmShpData { //https://wiki.tockdom.com/wiki/SHP0_(File_Format)
    ResBlockHeaderData header;
    u32 version; //v4    
    s32 offsetToBRRES;
    s32 offsetToShpDataDic;
    s32 offsetToVertexNameArray;
    s32 offsetToResUserData;
    s32 offsetToName;
    s32 offsetToPath;
    ResAnmShpInfoData fileInfo;
    //data
};

class ResAnmShp : public ResCommon<ResAnmShpData> {};

}//namespace g3d   
}//namespace nw4r


#endif