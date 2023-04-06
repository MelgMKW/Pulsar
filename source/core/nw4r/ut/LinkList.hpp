#ifndef _NW4R_UTLINKLIST_
#define _NW4R_UTLINKLIST_
#include <types.hpp>

namespace nw4r {
namespace ut {

class LinkListNode {
public:
    LinkListNode *next;
    LinkListNode *prev;
}; // Total size 0x8


template <class T, s32 offset>
class LinkList {
public:
    T *GetFirst() { return (T *)((char *)initialNode.next - offset); }; //not at all official but I only need this
    int count;
    LinkListNode initialNode;
}; // Total size 0xc

}//namespace ut
}//namespace nw4r
#endif