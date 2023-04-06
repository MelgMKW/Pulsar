#ifndef _EGGEXPHEAP_
#define _EGGEXPHEAP_
#include <types.hpp>
#include <core/rvl/mem/expHeap.h>
#include <core/egg/mem/Heap.hpp>

namespace EGG {
class GroupSizeHolder;

class ExpHeap : public Heap {
public:
    class GroupSizeHolder { //non-official naming
    public:
        GroupSizeHolder(); //80226dd0
        void Reset(); //80226e00
        void Add(u16 groupId, u32 size); //adds size to the entry of groupId
        u32 groupSize[0x100]; //in byte, the total size in bbytes of every block of a given groupId
    }; //0x400

    static ExpHeap *Create(int size, Heap *parent, u16 flags);
    ExpHeap(); //80226a1c
    virtual ~ExpHeap(); //0x8 802269a8 vtable 802a2ff8
    HeapType getHeapKind() const override; //C 80226efc
    void initAllocator(Allocator *allocator, s32 alignment) override; //0x10 80226dc0
    void *alloc(u32 size, s32 alignment) override; //0x14 80226c04
    void free(void *block) override; //0x18 80226c78
    void destroy() override; //0x1c 80226b94
    u32 resizeForMBlock(void *buffer, u32 newSize) override; //0x20 80226c80
    u32 getAllocatableSize(s32 alignment) override; //0x24 80226c90
    u32 adjust() override; //0x28 80226d4c

    u32 getTotalFreeSize(); //80226c88
    void SetGroupId(u16 groupId); //80226c98 

    void CalculateGroupSizes(GroupSizeHolder *groupSizeHolder); //80226cfc
    static void AddSizeToGroup(void *block, ExpHeap *heap, GroupSizeHolder *groupSizeHolder); //80226ca0, non-official
    //adds size to group's entry matching the block's group Id, used as a  MEMVisitor
};



}//namespace EGG

#endif