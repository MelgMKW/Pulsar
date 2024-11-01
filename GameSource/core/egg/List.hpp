#ifndef _EGG_LIST_
#define _EGG_LIST_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>

namespace EGG {

class Link {
    Link(); //8022f710
    Link* next;
    Link* prev;
};
size_assert(Link, 0x8);

class List {
    List(); //8022f760
    explicit List(const List& listToCopy); //8022f7ec copy ctor
    virtual ~List(); //8022f720 vtable 802a31bc
    void Add(Link* link); //8022f77c
    void* GetFirst(); //8022f804
    Link* prev;
    Link* next;
}; //total size 0xC
size_assert(EGG::List, 0xC);
}//namespace EGG 
#endif