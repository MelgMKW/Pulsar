#ifndef _MEMLIST_
#define _MEMLIST_
#include <types.hpp>

extern "C" {
    struct MEMLink {
        void *prevObj;
        void *nextObj;
    }; //0x8

    struct MEMList {
        void *headObj;
        void *tailObj;
        u16 objCount;
        u16 offset;
    }; //0xc

    void MEMInitList(MEMList *list, u16 offset); //80199bf0
    void *MEMGetNthListObject(MEMList *list, u16 idx); //8018cbdc
    void MEMAppendListObject(MEMList *list, void *obj); //80199c08
    void MEMRemoveListObject(MEMList *list, void *obj); //80199c78
    void *MEMGetNextListObject(MEMList *list, void *obj); //80199ce4


}//extern "C" {

#endif