#ifndef _NW4R_EF_TEXTURERESOURCE_
#define _NW4R_EF_TEXTURERESOURCE_
#include <types.hpp>
#include <core/nw4r/ef/res/Resource.hpp>

namespace nw4r {
namespace ef {

struct TextureData {
    char* name;
    u16 width;
    u16 height;
    u32 dataSize; // If changed, this will be corrupted when relocated. Cannot be changed or referenced.
    u8 format;
    u8 tlutFormat;
    u16 tlutEntries;
    u32 tlutSize; // If changed, this will be corrupted when relocated. Cannot be changed or referenced.
    u8 mipmap;
    u8 min_filt;
    u8 mag_filt;
    u8 reserved[1];
    float lod_bias;
    u8* texture;
    u8* tlut;
    u8 reserved2[28];
};

class ResTexture {
    TextureData* textureData;
};


}//namespace ef
}//namespace nw4r
#endif