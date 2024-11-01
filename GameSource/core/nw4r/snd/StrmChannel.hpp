#ifndef _NW4R_SNDSTRMCHANNEL_
#define _NW4R_SNDSTRMCHANNEL_
#include <types.hpp>
namespace nw4r {
namespace snd {
namespace detail {
class StrmBufferPool {
public:
    void* Alloc(); //800a4d20
    void Free(void* p); //800a4e10
    void* buffer; //0
    u32 bufferSize; //4
    u32 blockSize; //8
    int blockCount; //c
    int allocCount; //10
    u8 allocFlags[4]; //14
}; //total size 0x18
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif

