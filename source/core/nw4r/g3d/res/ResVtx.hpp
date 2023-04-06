#ifndef _NW4R_G3D_RESVTX_
#define _NW4R_G3D_RESVTX_
#include <types.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/gx/GXEnum.hpp>

//https://wiki.tockdom.com/wiki/MDL0_(File_Format)#Section_8_-_Materials
namespace nw4r {
namespace g3d {
struct ResVtxPosData {
    u32 size;
    s32 offsetToResMdlData;
    s32 offsetToVtxPosArray;
    s32 offsetToName;
    u32 idx;
    GXCompCnt  cmpcnt;
    GXCompType tp;
    u8 frac;
    u8 stride;
    u16 count;
    math::VEC3 min;
    math::VEC3 max;
    //padding to align vertex data
    //vertex data
};

struct ResVtxNrmData {
    u32 size;
    s32 offsetToResMdlData;
    s32 offsetToVtxNrmArray;
    s32 offsetToName;
    u32 idx;
    GXCompCnt cmpcnt;
    GXCompType tp;
    u8 frac;
    u8 stride;
    u16 numNrm;
    //padding to align vertex data
    //normal data
};

struct ResVtxClrData
{
    u32 size;
    s32 offsetToResMdlData;
    s32 offsetToVtxClrArray;
    s32 offsetToName;
    u32        id;
    GXCompCnt  cmpcnt;
    GXCompType tp;
    u8         stride;
    u8         dummy_;
    u16        numClr;
    //padding to align vertex data
    //color data
};


}//namespace g3d   
}//namespace nw4r


#endif