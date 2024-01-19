#ifndef _EGG_TEXTURE_
#define _EGG_TEXTURE_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/egg/Math/Vector.hpp>

namespace EGG {
//https://wiki.tockdom.com/wiki/BLIGHT_(File_Format)
//https://wiki.tockdom.com/wiki/BLMAP_(File_Format)

class CpuTexture {
public:
    CpuTexture(); //8021805c
    CpuTexture(u16 width, u16 height, GXTexFmt gxTexFmt); //80218098
    CpuTexture(GXTexObj texObj); //802180d0
    u16 width;
    u16 height;
    u8 unknown_0x4;
    u8 gxTexFmt; //0x5
    GXTexWrapMode wrap_s;
    GXTexWrapMode wrap_t; //0x7
    GXTexFilter min_filt;
    GXTexFilter max_filt;
    u8 unknown_0xA[2];
    void* image_ptr; //0xC
    virtual ~CpuTexture(); //80218178 vtable 802a2b10
    virtual void Configure(); //80218b98
    virtual void InitTexObj(GXTexObj* obj); //802181e8
};

class MatTexture : public CpuTexture {
public:
    ~MatTexture() override; //80214e10 vtable 802a29f0
    void Configure() override; //80214bd0
    void CopyFromEFB(u16 left, u16 top, bool mipmap, GXTexFmt format); //80214c74
    u8 unknown_0x14[0x28 - 0x14];
};


}//namespace EGG

#endif