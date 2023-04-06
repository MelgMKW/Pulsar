#ifndef _NW4R_SNDFRAMEHEAP_
#define _NW4R_SNDFRAMEHEAP_
#include <types.hpp>
#include <core/rvl/os/mutex.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/DisposeCallbackManager.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class FrameHeap {
    struct Block {
    public:
        ut::LinkListNode link;
        void *buffer;
        u32 size;
        void *callbackFunc;
        void *callbackArg;
    };
    class Section {
    public:
        ut::LinkListNode link;
        ut::LinkList<Block, offsetof(Block, link)> blockList;
    };
    int SaveState(); //80092500
    void LoadState(int level); //800925d0
    int GetCurrentLevel() const; //80092800
    void *Alloc(u32 size, void *callbackFunc, void *callbackArg); //80092450
    void *MEMiHeapHead;
    ut::LinkList<Section, offsetof(Section, link)> sectionlist;
};//total size 0x10
size_assert(FrameHeap, 0x10);
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif	
