#ifndef _MEMHEAP_
#define _MEMHEAP_
#include <types.hpp>
#include <core/rvl/MEM/MEMlist.hpp>
#include <core/rvl/os/OSmutex.hpp>
namespace MEM {
enum HeapType {
    HEAPTYPE_EXP,    //Expanded
    HEAPTYPE_FRAME,
    HEAPTYPE_UNIT,
    HEAPTYPE_UNKNOWN
};

struct iHeapHead { //header
    u32 magic;      //0x0 "EXPH" for example
    Link link;   //0x4
    List children; //0xc
    void* startAddr; //0x18
    void* endAddr; //0x1c
    OS::Mutex mutex; //0x20
    u32 attributes; //0x38 bitfield
}; //0x3c

typedef iHeapHead* HeapHandle;

void iInitHeapHead(iHeapHead* heap, u32 magic, void* startAddr, void* endAddr, u16 flag); //8019832c
void iFinalizeHeap(iHeapHead* heap); //801984ec
HeapHandle FindContainHeap(const void* ptr); //80198658
} //namespace MEM
#endif