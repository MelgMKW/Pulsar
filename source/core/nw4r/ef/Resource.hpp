#ifndef _NW4R_EF_RESOURCE_
#define _NW4R_EF_RESOURCE_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/ef/LinkedObject.hpp>

namespace nw4r {
namespace ef {
struct EffectProject { //BREFF
    u32 headersize;
    ut::Link projectlink;
    u16 projectnameLen;
    u16 padding;
    u8 projectname[4];
};

struct TextureProject { //BREFT
    u32 headersize;
    ut::Link projectlink;
    u16 projectnameLen;
    u16 padding;
    u8 projectname[4];
};

class Resource {
public:
    EffectProject *Add(u8 *data);
    ut::List BREFFList;
    u32 emitterCount;
    ut::List BREFTList;
    u32 textureCount;
};

}//namespace ef
}//namespace nw4r
#endif    