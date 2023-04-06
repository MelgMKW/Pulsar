#ifndef _EGGALLOCATOR_
#define _EGGALLOCATOR_
#include <types.hpp>
#include <core/rvl/mem/allocator.h>

namespace EGG {
class Heap;
class Allocator : public MEMAllocator {
public:
    Allocator(Heap *heap, s32 alignment); //8020f62c
    virtual ~Allocator(); //8020f688 vtable 802a2668
    virtual void *alloc(u32 size); //8020f6c8
    virtual void free(void *block); //8020f6dc

private:
    Heap *heap;
    s32 alignment;
};
}//namespace EGG
#endif