#ifndef _NW4R_G3D_RES_ANMCLR_
#define _NW4R_G3D_RES_ANMCLR_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/math.hpp>

namespace nw4r {
namespace g3d {

struct ClrAnmResult {
    u32 bRgbaExist;
    u32 rgba[11];
    u32 rgbaMask[11];
};

struct ResAnmClrAnmData {
    u32 rgbaMask;
    u32 offsetToColor;
};

struct ResAnmClrMatData {
    s32 offsetToName;
    u32 flags;
    ResAnmClrAnmData anms[1];
};

struct ResAnmClrInfoData { //"CLR Header"
    u16 frameCount; //0x0
    u16 entryCount; //0x2
    u32 isLooped; //0x4
    u32 offsetToFirstFrame;
};

struct ResAnmClrData { //https://wiki.tockdom.com/wiki/CLR0_(File_Format)
    ResBlockHeaderData  header; //Common header
    u32 version; //0x8 v5 sometimes v4
    s32 offsetToBRRES; //0xC negative
    s32 offsetToClrDataDic; //0x10
    s32 offsetToResUserData; //0x14
    s32 offsetToname; //0x18
    s32 toPath; //0x1c
    ResAnmClrInfoData fileInfo; //0x20
    //data
};

class ResAnmClr : public ResCommon<ResAnmClrData> {};

}//namespace g3d
}//namespace nw4r


#endif