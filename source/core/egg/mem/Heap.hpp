#ifndef _EGGHEAP_
#define _EGGHEAP_
#include <types.hpp>
#include <core/rvl/mem/heap.h>
#include <core/nw4r/ut/List.hpp>
#include <core/egg/mem/Allocator.hpp>
#include <core/egg/mem/Disposer.hpp>

namespace EGG {
enum HeapType {
    HEAP_TYPE_NONE,
    HEAP_TYPE_EXP,
    HEAP_TYPE_FRAME,
    HEAP_TYPE_UNIT
};

class Heap : public Disposer {
public:
    Heap(/*MEMiHeapHead*/ void *rvlHeap); //802296e8
    virtual ~Heap(); //80229780 vtable 802a30c0
    virtual HeapType getHeapKind() const = 0;
    virtual void initAllocator(Allocator *allocator, s32 alignment) = 0;
    virtual void *alloc(u32 size, s32 alignment) = 0;
    virtual void free(void *block) = 0;
    virtual void destroy() = 0; //0x1c
    virtual u32 resizeForMBlock(void *buffer, u32 newSize) = 0;
    virtual u32 getAllocatableSize(s32 alignment) = 0;
    virtual u32 adjust() = 0;

    static void *alloc(u32 size, int align, Heap *heap);
    static Heap *findHeap(/*MEMiHeapHead*/ void *rvlHeap);
    Heap *findParentHeap();

    static Heap *findContainHeap(void *buffer);
    static void free(void *block, Heap *heap);
    void dispose(); //destroys disposers
    void dump();
    static void dumpAll();
    Heap *BecomeCurrentHeap(); //returns old heap
    Heap *becomeCurrentHeapWithoutLocking();
private:
    nw4r::ut::Link parentLink;
    MEMiHeapHead *rvlHeap; //0x10
    void *parentHeapMBlock; //0x14
    Heap *parentHeap; //0x18
    u16 dameFlag; //0x1C
    nw4r::ut::Link globalLink; //0x20
    nw4r::ut::List childList; //0x28
    const char *name; //0x34
}; //total size 0x38
}//namespace EGG

#ifdef __INTELLISENSE__
inline void *operator new(unsigned long long size, EGG::Heap *heap)
{
    return EGG::Heap::alloc(size, 0x4, heap);
}
inline void *operator new[](unsigned long long size, EGG::Heap *heap)
{
    return EGG::Heap::alloc(size, 0x4, heap);
}
inline void *operator new(unsigned long long size, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, 0);
}
inline void *operator new[](unsigned long long size, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, 0);
}
inline void *operator new(unsigned long long size, EGG::Heap *heap, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, heap);
}
inline void *operator new[](unsigned long long size, EGG::Heap *heap, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, heap);
}
inline void *operator new(unsigned long long, void *ptr) { return ptr; }
#else
inline void *operator new(size_t size, EGG::Heap *heap)
{
    return EGG::Heap::alloc(size, 0x4, heap);
}
inline void *operator new[](size_t size, EGG::Heap *heap)
{
    return EGG::Heap::alloc(size, 0x4, heap);
}
inline void *operator new(size_t size, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, 0);
}
inline void *operator new[](size_t size, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, 0);
}
inline void *operator new(size_t size, EGG::Heap *heap, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, heap);
}
inline void *operator new[](size_t size, EGG::Heap *heap, u32 alignment)
{
    return EGG::Heap::alloc(size, alignment, heap);
}
inline void *operator new(size_t, void *ptr) { return ptr; }
#endif
#endif