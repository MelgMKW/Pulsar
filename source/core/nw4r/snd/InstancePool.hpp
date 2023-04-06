#ifndef _NW4R_SNDINSTANCEPOOL_
#define _NW4R_SNDINSTANCEPOOL_

#include <types.hpp>
namespace nw4r {
namespace snd {
namespace detail {
struct PoolImpl {
    PoolImpl *next;
};
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif