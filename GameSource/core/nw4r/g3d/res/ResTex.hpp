#ifndef _NW4R_G3D_RESTEX_
#define _NW4R_G3D_RESTEX_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace g3d {
struct ResTexData { //https://wiki.tockdom.com/wiki/TEX0_(File_Format)
    ResBlockHeaderData header;
    u32 version; //0x8
    s32 offsetToBRRES; //0xc
    s32 offsetToTexData; //0x10
    s32 offsetToName; //0x14
    u32 flag; //0x18
    u16 width; //0x1c
    u16 height; //0x1e
    union {
        GX::TexFmt       fmt;
        GX::CITexFmt     cifmt;
    };
    u32 mipmap_level;
    float min_lod;
    float max_lod;
    s32 offsetTooriginal_path;
    s32 offsetToResUserData;
};
class ResTex : public ResCommon<ResTexData> {
    void Init(); //80052ae0
    bool GetTexObjParam(void** image_ptr, u16* width, u16* height, GX::TexFmt* format, float* min_lod, float* max_lod, bool* mipmap) const; //80052930
    bool GetTexObjCIParam(void** image_ptr, u16* width, u16* height, GX::TexFmt* format, float* min_lod, float* max_lod, bool* mipmap) const; //800529f0
};
}//namespace g3d
}//namespace nw4r


#endif