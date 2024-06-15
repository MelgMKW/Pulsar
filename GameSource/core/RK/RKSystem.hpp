#ifndef _RKSYSTEM_
#define _RKSYSTEM_
#include <types.hpp>
#include <core/egg/System.hpp>


//_sinit_ at 800099cc
class RKSystem : public EGG::TSystem { //probably an intermediate class in btw
public:

    static RKSystem* GetStaticInstance(); //80008e84
    Heap* GetSystemHeap() override; //0xC 80008fac
    void Run() override; //0x34 8000951c
    void Initialize() override; //0x38 80009194

    void* WPADAlloc(u32  size); //80008e90
    u8 WPADFree(void* ptr); //80008eb0
    void Main(u32 r3, u32 r4); //80008ef0

    ExpHeap* kpadWorkHeap;
    Allocator* wpadAllocator; //0x5c
    ExpHeap* relLinkHeap;
    ExpHeap* heapSystem2;
    u8 frameClock;
    u8 unknown_0x68;
    bool drawFrame; //0x69
    u8 unknown_0x6b[0x74 - 0x6b];
}; //total size 0x74
size_assert(RKSystem, 0x74);
#endif