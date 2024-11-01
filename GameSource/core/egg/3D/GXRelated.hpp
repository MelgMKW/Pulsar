#ifndef _EGG_GXRELATED_
#define _EGG_GXRELATED_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {

class GraphicsFifo {
public:
    static GraphicsFifo* Create(u32 size, EGG::Heap* heap); //80229540
    static GraphicsFifo* sInstance; //80386E90
    GraphicsFifo(u32 size, EGG::Heap* heap); //80229640
    virtual ~GraphicsFifo(); //802295a8 vtable 802a30b0

    GX::FifoObj* fifoObj; //0x4
    void* rawBuffer;
    u32 bufferSize; //0xC 32-bits aligned
}; //0x10


}//namespace EGG
#endif