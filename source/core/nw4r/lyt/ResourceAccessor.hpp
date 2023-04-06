#ifndef _NW4R_LYTRESOURCEACCESSOR_
#define _NW4R_LYTRESOURCEACCESSOR_
#include <types.hpp>
#include <core/nw4r/ut/Font.hpp>

namespace nw4r {
namespace lyt {
typedef u32 ResType;
class ResourceAccessor {
    ResourceAccessor(); //80083cf0
    virtual ~ResourceAccessor(); //80083cb0 vtable 80273808
    virtual void *GetResource(ResType type, const char *fileName, u32 *size = 0) = 0;
    virtual ut::Font *GetFont(const char *name); //80083d00
};
}//namespace lyt
}//namespace nw4r
#endif