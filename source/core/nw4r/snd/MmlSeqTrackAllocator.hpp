
#ifndef _NW4R_SNDMMLALLOCATORL_
#define _NW4R_SNDMMLALLOCATORL_
#include <types.hpp>
#include <core/nw4r/snd/InstancePool.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class MmlSeqTrackAllocator {
    virtual void func_vtable();
    UnkType *ptr;
    PoolImpl trackPool;
}; //total size 0xC	
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif
