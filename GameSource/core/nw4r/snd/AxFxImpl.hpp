#ifndef _NW4R_SNDAXFXIMPL_
#define _NW4R_SNDAXFXIMPL_
#include <types.hpp>
#include <core/rvl/MEM/MEMheap.hpp>

namespace  nw4r {
namespace snd {
namespace detail {
class AxFxImpl {
public:
    bool CreateHeap(void* buffer, u32 size); //8008d120
    void DestroyHeap(); //8008d190
    void HookAlloc(void* (**alloc) (u32), void (**free) (void*)); //8008d1e0 will fill the ptrs
    u32 RestoreAlloc(void* (*alloc) (u32), void (*free) (void*)); //8008d240 sets the allocation functions
    static void* Alloc(u32 size); //8008d280
    static void  Free(void* buffer); //8008d2e0

    MEM::HeapHandle heapHandle;
    u32 allocCount;
    static AxFxImpl* cur; //803861B0
    static u32 totalAllocatedSize; //803861B4
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif