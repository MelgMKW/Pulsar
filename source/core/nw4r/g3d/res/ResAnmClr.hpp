#ifndef _NW4R_G3D_RES_ANMCLR_
#define _NW4R_G3D_RES_ANMCLR_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {

struct ResAnmClrInfoData { //"CLR Header"
    u16 frameCount;
    u16 entryCount;
    u32 isLooped;
    u32 offsetToFirstFrame;
};

struct ResAnmClrData { //https://wiki.tockdom.com/wiki/CLR0_(File_Format)
    ResBlockHeaderData  header;                 // Common header
    u32 version; //v5
    s32 offsetToBRRES;
    s32 offsetToClrDataDic;
    s32 offsetToResUserData;
    s32 offsetToname;                   // Source rcla file name (exclude extension)
    s32 toPath;
    ResAnmClrInfoData fileInfo;
    //data
};

class ResAnmClr : public ResCommon<ResAnmClrData> {};

}//namespace g3d
}//namespace nw4r


#endif