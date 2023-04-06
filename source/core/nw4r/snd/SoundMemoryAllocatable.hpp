#ifndef NW4R_SNDSOUNDMEMORYALLOCATABLE_
#define NW4R_SNDSOUNDMEMORYALLOCATABLE_

#include <types.hpp>

namespace nw4r {
namespace snd {

class SoundMemoryAllocatable {
public:
    virtual ~SoundMemoryAllocatable() {}
    virtual void *Alloc(u32 size) = 0;
};
}//namespace snd
}//namespace nw4r

#endif
