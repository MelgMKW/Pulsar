#ifndef _MEMLIST_
#define _MEMLIST_
#include <types.hpp>
namespace MEM {
struct Link {
    void* prevObj;
    void* nextObj;
}; //0x8

struct List {
    void* headObj;
    void* tailObj;
    u16 objCount;
    u16 offset;
}; //0xc

void InitList(List* list, u16 offset); //80199bf0
void* GetNthListObject(List* list, u16 idx); //8018cbdc
void AppendListObject(List* list, void* obj); //80199c08
void RemoveListObject(List* list, void* obj); //80199c78
void* GetNextListObject(List* list, void* obj); //80199ce4

} //namespace MEM

#endif