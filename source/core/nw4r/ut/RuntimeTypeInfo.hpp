#ifndef _NW4R_UT_RUNTIMETYPEINFO_
#define _NW4R_UT_RUNTIMETYPEINFO_
#include <types.hpp>
#include <core/nw4r/ut/Font.hpp>
#include <core/rvl/os/font.hpp>

namespace nw4r {
namespace ut {
namespace detail {
struct RuntimeTypeInfo { const RuntimeTypeInfo* parentTypeInfo; };
};


}//namespace ut
}//namespace nw4r
#endif