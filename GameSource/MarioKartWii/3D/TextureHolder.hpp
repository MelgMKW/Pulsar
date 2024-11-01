#ifndef _IMAGECONTAINER_
#define _IMAGECONTAINER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/3D/Texture.hpp>

class TextureHolder {
public:
    TextureHolder(u16 width, u16 height, GX::TexFmt gxTexFmt, EGG::Heap* heap = nullptr); //80563ce4 generally with w/h from GXRenderMode efb's w/h
    virtual ~TextureHolder(); //805641d8 vtable 808b4ac0
    void CopyFromEFB(u16 left, u16 top, bool mipmap, bool r7, bool r8); //80563db0

    EGG::LightTexture* texture; //0x4
    GX::TexObj texObj; //0x8
}; //0x28



#endif