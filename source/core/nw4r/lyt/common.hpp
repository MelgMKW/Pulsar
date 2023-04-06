#ifndef _NW4R_LYTCOMMON_
#define _NW4R_LYTCOMMON_
#include <types.hpp>
#include <core/nw4r/lyt/resources.hpp>

class ResourceAccessor;

namespace nw4r {
namespace lyt {
struct ResBlockSet {
    const res::TextureList *pTextureList;
    const res::FontList *pFontList;
    const res::MaterialList *materialList;
    ResourceAccessor *pResAccessor;
};
namespace detail {
class TexCoordAry {
public:
    TexCoordAry(); //80084370
    void Free(); //80084390
    void Reserve(u8 count); //800843e0
    void SetSize(u8 count); //80084480
    void Copy(const void *source, u8 count); //80084570

    u8 reservedSize, usedSize;
    void *data;
};  // Total size 0x8
}//namespace detail
}//namespace lyt
}//namespace nw4r
#endif