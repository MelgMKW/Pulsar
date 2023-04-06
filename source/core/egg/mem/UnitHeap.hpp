#ifndef _EGGUNITHEAP_
#define _EGGUNITHEAP_
#include <types.hpp>
#include <core/rvl/mem/unitHeap.h>
#include <core/egg/mem/Heap.hpp>


namespace EGG {

//Heap of Unit Blocks of fixed size and alignment (specified at creation)
class UnitHeap : public Heap {
public:
    static UnitHeap *Create(int size, u32 blockSize, Heap *parent, s32 alignment, u16 flag); //802437c8
    static u32 calcHeapSize(u32 blockSize, u32 blockCount, s32 alignment); //802439d4

    virtual ~UnitHeap(); //0x8 80243754 vtable 802a3fd8
    HeapType getHeapKind() const override; //C 802439f8
    void initAllocator(Allocator *allocator, s32 alignment) override; //0x10 802439c4
    void *alloc(u32 size, s32 alignment) override; //0x14 80243984
    void free(void *block) override; //0x18 802439a4
    void destroy() override; //0x1c 80243914
    u32 resizeForMBlock(void *buffer, u32 newSize) override; //0x20 802439ac
    u32 getAllocatableSize(s32 alignment) override; //0x24 802439b4
    u32 adjust() override; //0x28 802439bc
};


}//namespace EGG

#endif