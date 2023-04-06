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
    u32 version;
    s32 offsetToBRRES;
    s32 offsetToTexData;
    s32 offsetToName;
    u32 flag;
    u16 width;
    u16 height;
    union {
        GXTexFmt       fmt;
        GXCITexFmt     cifmt;
    };
    u32 mipmap_level;
    float min_lod;
    float max_lod;
    s32 offsetTooriginal_path;
    s32 offsetToResUserData;
};
class ResTex : public ResCommon<ResTexData> {
    void Init(); //80052ae0
    bool GetTexObjParam(void **image_ptr, u16 *width, u16 *height, GXTexFmt *format, float *min_lod, float *max_lod, bool *mipmap) const; //80052930
    bool GetTexObjCIParam(void **image_ptr, u16 *width, u16 *height, GXTexFmt *format, float *min_lod, float *max_lod, bool *mipmap) const; //800529f0
};
}//namespace g3d
}//namespace nw4r


#endif