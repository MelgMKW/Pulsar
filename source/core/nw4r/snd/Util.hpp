#ifndef _NW4R_SNDUTIL_
#define _NW4R_SNDUTIL_
#include <types.hpp>

namespace nw4r {
namespace snd {
namespace detail {
namespace Util {
template< typename T, typename T1 = void, typename T2 = void, typename T3 = void >
struct DataRef {
    u8 refType;
    u8 dataType;
    u16 reserved;
    u32 value;
};
static u16 CalcRandom();

}//namespace Util
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif