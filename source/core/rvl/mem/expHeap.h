#ifndef _MEMEXPHEAP_
#define _MEMEXPHEAP_
#include <types.hpp>
#include <core/rvl/mem/heap.h>

extern "C" {
    struct MEMiExpHeapMBlockHead { //block of memory you allocate
        u16 magic; //UD, FR
        u16 attribute; //0x2
        u32 blockSize; //0x4
        MEMiExpHeapMBlockHead *prevBlock; //0x8
        MEMiExpHeapMBlockHead *nextBlock; //0xc
    }; //0x10

    struct MEMiExpMBlockList {
        MEMiExpHeapMBlockHead *head;
        MEMiExpHeapMBlockHead *tail;
    }; //0x8

    struct MEMiExpHeapHead { //right after normal MEMHeader
        MEMiExpMBlockList freeBlocks; //0x0, 3c from start
        MEMiExpMBlockList usedBlocks; //0x8, 44
        u16 groupID; //0x10, 4c
        u16 feature; //0x12, 4e
    };  //0x14, 0x50 total

    // Callback function type called for every memory block
    typedef void (*MEMHeapVisitor)(void *block, MEMHeapHandle heap, u32 userParam);

    MEMHeapHandle MEMCreateExpHeapEx(void *startAddr, u32 size, u16 flag); //80198ca8 Creates an expanded heap
    void *MEMDestroyExpHeap(MEMHeapHandle heap); //80198d58 Destroys the expanded heap
    void *MEMAllocFromExpHeapEx(MEMHeapHandle heap, u32 size, s32 alignment); //80198d88 Allocates a block from the expanded heap
    u32 MEMResizeForMBlockExpHeap(MEMHeapHandle heap, void *block, u32 size); //80198e38 resize func for ExpHeaps
    void MEMFreeToExpHeap(MEMHeapHandle heap, void *block); //80199038 Returns the block to the expanded heap
    u32 MEMGetTotalFreeSizeForExpHeap(MEMHeapHandle heap); //80199104 Gets the total size of the available regions of the expanded heap
    u32 MEMGetAllocatableSizeForExpHeapEx(MEMHeapHandle heap, s32 alignment); //80199180 Returns the maximum allocatable size from the expanded heap


    u16 MEMSetGroupIDForExpHeap(MEMHeapHandle heap, u16 groupId); //80199258
    void MEMVisitAllocatedForExpHeap(MEMHeapHandle heap, MEMHeapVisitor visitor, u32 userParam); //801992a8
    /*
    The visitor function is called for all the memory block of the heap. The userParam is passed to the function.
    The order of the blocks called by the visitor function is the order in which they were allocated.
    */

    u32 MEMGetSizeForMBlockExpHeap(const void *block); //80199344 Gets the size of the block that was allocated from the expanded heap.
    u16 MEMGetGroupIDForMBlockExpHeap(const void *block); //8019934c
    u32 MEMAdjustExpHeap(MEMHeapHandle heap); //80199358
    /*
    Deallocates the expanded heap's available region and reduces the memory region that is available for use by the expanded heap.
    = Removes the last free block
    There must not be memory blocks allocated from the back of heap memory.
    Returns the new size after reduction
    */

} //extern C


#endif
