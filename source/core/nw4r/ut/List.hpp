#ifndef _NW4R_UTLIST_
#define _NW4R_UTLIST_
#include <types.hpp>
namespace nw4r {
namespace ut {


struct Link {
    void *prev, *next;
}; // Total size 0x8

struct List {
    Link *head;
    Link *tail;
    u16 count;  //0x8
    u16 offset; //0xA
}; // Total size 0xc

void List_Init(List *list, u16 offset);
void List_Append(List *list, void *newObj);
void List_Insert(List *list, void *insertBefore, void *newObj);
void List_Remove(List *list, void *obj);
void *List_GetNext(const List *list, void *obj);
void *List_GetPrev(const List *list, void *obj);
void *List_GetNth(const List *list, u16 idx);
}//namespace ut
}//namespace nw4r
#endif