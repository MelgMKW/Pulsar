#ifndef _MEMUNITHEAP_
#define _MEMUNITHEAP_
#include <types.hpp>
#include <core/rvl/MEM/MEMheap.hpp>

namespace MEM {
//Heap of Unit Blocks of fixed size and alignment (specified at creation)
struct iUntHeapMBlockHead { //block header
    iUntHeapMBlockHead* next;
};

struct iUntMBlockList {
    iUntHeapMBlockHead* head;
};

struct iUntHeapHead { //right after normal Header
    iUntMBlockList freeList;
    u32 size;
};

HeapHandle CreateUnitHeapEx(void* startAddr, u32 heapSize, u32 blockSize, s32 alignment, u16 flag); //801998a4
void* DestroyUnitHeap(HeapHandle heap); //80199a00
void* AllocFromUnitHeap(HeapHandle heap); //80199a30
void FreeToUnitHeap(HeapHandle heap, void* block); //80199ac4
u32 CalcHeapSizeForUnitHeap(u32 blockSize, u32 blockCount, s32 alignment); //80199b34

} //namespace MEM


#endif
