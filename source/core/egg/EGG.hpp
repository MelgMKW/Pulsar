#ifndef _EGG_
#define _EGG_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/egg/Archive.hpp>
#include <core/egg/Audio.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/DvdRipper.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/Thread.hpp>

namespace EGG {
class List {
    List(); //8022f760
    explicit List(List *listToCopy); //8022f7ec
    virtual ~List(); //8022f720 vtable 802a31bc
    void Add(nw4r::ut::LinkListNode *node);

    nw4r::ut::LinkListNode *head;
    u8 unknown_0x8[4]; //count maybe?
}; //total size 0xC
size_assert(EGG::List, 0xC);
}//namespace EGG 
#endif