#ifndef _NW4R_EF_LINKEDOBJECT_
#define _NW4R_EF_LINKEDOBJECT_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>

namespace nw4r {
namespace ef {
class LinkedObject {
public:
    ut::Link memoryLink;
    u32 id;
};
}//namespace ef
}//namespace nw4r
#endif