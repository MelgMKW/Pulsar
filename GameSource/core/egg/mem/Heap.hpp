#ifndef _EGGHEAP_
#define _EGGHEAP_
#include <types.hpp>
#include <include/c_stdlib.h>
#include <core/rvl/MEM/MEMheap.hpp>
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
    static Heap* current; //80386ea0
    Heap(MEM::iHeapHead* rvlHeap); //802296e8
    virtual ~Heap(); //80229780 vtable 802a30c0
    virtual HeapType getHeapKind() const = 0;
    virtual void initAllocator(Allocator* allocator, s32 alignment) = 0;
    virtual void* alloc(u32 size, s32 alignment) = 0;
    virtual void free(void* block) = 0;
    virtual void destroy() = 0; //0x1c
    virtual u32 resizeForMBlock(void* buffer, u32 newSize) = 0;
    virtual u32 getAllocatableSize(s32 alignment) = 0;
    virtual u32 adjust() = 0;

    static void* alloc(u32 size, int align, Heap* heap = nullptr);
    template<class T>
    static inline T* alloc(u32 size, int align, Heap* heap = nullptr) { return static_cast<T*>(alloc(size, align, heap)); }

    static Heap* findHeap(MEM::iHeapHead* rvlHeap);
    Heap* findParentHeap();

    static Heap* findContainHeap(void* buffer);
    static void free(void* block, Heap* heap);
    void dispose(); //destroys disposers
    void dump();
    static void dumpAll();
    Heap* BecomeCurrentHeap() const; //returns old heap
    Heap* becomeCurrentHeapWithoutLocking();
private:
    nw4r::ut::Link parentLink;
    MEM::iHeapHead* rvlHeap; //0x10
    void* parentHeapMBlock; //0x14
    Heap* parentHeap; //0x18
    u16 dameFlag; //0x1C
    nw4r::ut::Link globalLink; //0x20
    nw4r::ut::List childList; //0x28
    const char* name; //0x34
}; //total size 0x38
}//namespace EGG

void* operator new(size_t size, int alignment);

void* operator new(size_t size, EGG::Heap* heap, int alignment);

inline void* operator new(size_t size, EGG::Heap* heap)
{
    return operator new(size, heap, 4);
}

inline void* operator new(size_t, void* ptr) { return ptr; }

void* operator new[](size_t size, int alignment);

void* operator new[](size_t size, EGG::Heap* heap, int alignment);

inline void* operator new[](size_t size, EGG::Heap* heap)
    {
        return operator new[](size, heap, 4);
    }

#endif