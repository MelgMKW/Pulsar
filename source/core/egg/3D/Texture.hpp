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
    CpuTexture(u16 width, u16 height); //80218098
    CpuTexture(GXTexObj texObj); //802180d0
    u16 width;
    u16 height;
    u8 unknown_0x4;
    GXTexFmt format;
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

class MatTexture: public CpuTexture {
public:
    u8 unknown_0x14[0x28 - 0x14];
};


}//namespace EGG

#endif