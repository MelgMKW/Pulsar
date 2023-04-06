#ifndef _MEMUNITHEAP_
#define _MEMUNITHEAP_
#include <types.hpp>
#include <core/rvl/mem/heap.h>

extern "C" {

    //Heap of Unit Blocks of fixed size and alignment (specified at creation)
    struct MEMiUntHeapMBlockHead { //block header
        MEMiUntHeapMBlockHead *next;
    };

    struct MEMiUntMBlockList {
        MEMiUntHeapMBlockHead *head;
    };

    struct MEMiUntHeapHead { //right after normal MEMHeader
        MEMiUntMBlockList freeList;
        u32 size;
    };

    MEMHeapHandle MEMCreateUnitHeapEx(void *startAddr, u32 heapSize, u32 blockSize, s32 alignment, u16 flag); //801998a4
    void *MEMDestroyUnitHeap(MEMHeapHandle heap); //80199a00
    void *MEMAllocFromUnitHeap(MEMHeapHandle heap); //80199a30
    void MEMFreeToUnitHeap(MEMHeapHandle heap, void *block); //80199ac4
    u32 MEMCalcHeapSizeForUnitHeap(u32 blockSize, u32 blockCount, s32 alignment); //80199b34





} //extern C


#endif
