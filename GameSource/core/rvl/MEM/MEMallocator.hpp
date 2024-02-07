#ifndef _RVL_ALLOCATOR_
#define _RVL_ALLOCATOR_
#include <types.hpp>
#include <core/rvl/MEM/MEMheap.hpp>

namespace MEM {

struct Allocator;
typedef void* (*FuncAllocatorAlloc)(Allocator* allocator, u32 size);
typedef void  (*FuncAllocatorFree) (Allocator* allocator, void* block);

struct AllocatorFunc {
    FuncAllocatorAlloc alloc;
    FuncAllocatorFree free;
};

struct Allocator {
    AllocatorFunc const* func;
    void* heap;
    u32 heapParam1;
    u32 heapParam2;
}; //0x10

void InitAllocatorForExpHeap(Allocator* allocator, HeapHandle heap, s32 alignment); //80199bb8
void InitAllocatorForUnitHeap(Allocator* allocator, HeapHandle heap); //80199bd4

} //namespace MEM


#endif