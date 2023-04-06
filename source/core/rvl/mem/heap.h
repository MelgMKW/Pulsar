#ifndef _MEMHEAP_
#define _MEMHEAP_
#include <types.hpp>
#include <core/rvl/mem/list.h>
#include <core/rvl/os/mutex.hpp>

extern "C" {
    enum MEMHeapType {
        MEMHEAPTYPE_EXP,    //Expanded
        MEMHEAPTYPE_FRAME,
        MEMHEAPTYPE_UNIT,
        MEMHEAPTYPE_UNKNOWN
    };

    struct MEMiHeapHead { //header
        u32 magic;      //0x0 "EXPH" for example
        MEMLink link;   //0x4
        MEMList children; //0xc
        void *startAddr; //0x18
        void *endAddr; //0x1c
        OSMutex mutex; //0x20
        u32 attributes; //0x38 bitfield
    }; //0x3c

    typedef MEMiHeapHead *MEMHeapHandle;

    void MEMiInitHeapHead(MEMiHeapHead *heap, u32 magic, void *startAddr, void *endAddr, u16 flag); //8019832c
    void MEMiFinalizeHeap(MEMiHeapHead *heap); //801984ec
    MEMHeapHandle MEMFindContainHeap(const void *ptr); //80198658

}//extern "C" {

#endif