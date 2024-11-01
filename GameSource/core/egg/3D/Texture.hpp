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
    CpuTexture(u16 width, u16 height, GX::TexFmt gxTexFmt); //80218098
    CpuTexture(GX::TexObj* texObj); //802180d0
    u16 width;
    u16 height;
    u8 flags;
    u8 gxTexFmt; //0x5
    GX::TexWrapMode wrap_s;
    GX::TexWrapMode wrap_t; //0x7
    GX::TexFilter min_filt;
    GX::TexFilter max_filt;
    u8 unknown_0xA[2];
    void* image_ptr; //0xC
    virtual ~CpuTexture(); //80218178 vtable 802a2b10
    virtual void Configure(); //80218b98
    virtual void InitTexObj(GX::TexObj* obj); //802181e8
};

//this is NOT loaded directly into GX (using GXLoadTexObj), instead, once the TexObj is initialized (using the image_ptr buffer), it is used to replace MDL0's materials (g3d::ResMat) TexObj, 
//which are the ones loaded into memory
//best example is WLscreenGC, whose wl_screen1 mat uses a black texture whose TexObj is replaced by one whose image_ptr is an EFB copy (hence acting as a replay screen)
class CapTexture : public CpuTexture {
public:
    ~CapTexture() override; //80214e10 vtable 802a29f0
    void Configure() override; //80214bd0
    void CopyFromEFB(u16 left, u16 top, bool mipmap, GX::TexFmt format); //80214c74
    u8 unknown_0x14[0x28 - 0x14];
};


}//namespace EGG

#endif