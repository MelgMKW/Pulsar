#ifndef _RVL_ALLOCATOR_
#define _RVL_ALLOCATOR_
#include <types.hpp>
#include <core/rvl/mem/heap.h>

extern "C" {
    typedef struct MEMAllocator MEMAllocator;
    typedef void *(*MEMFuncAllocatorAlloc)(MEMAllocator *allocator, u32 size);
    typedef void  (*MEMFuncAllocatorFree) (MEMAllocator *allocator, void *block);

    struct MEMAllocatorFunc {
        MEMFuncAllocatorAlloc alloc;
        MEMFuncAllocatorFree free;
    };

    struct MEMAllocator {
        MEMAllocatorFunc const *func;
        void *heap;
        u32 heapParam1;
        u32 heapParam2;
    }; //0x10

    void MEMInitAllocatorForExpHeap(MEMAllocator *allocator, MEMHeapHandle heap, s32 alignment); //80199bb8
    void MEMInitAllocatorForUnitHeap(MEMAllocator *allocator, MEMHeapHandle heap); //80199bd4

} //extern "C"


#endif