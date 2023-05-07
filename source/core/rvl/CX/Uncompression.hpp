#ifndef _CXUNCOMPRESSION_
#define _CXUNCOMPRESSION_
#include "types.hpp"

namespace CX {

u32 GetUncompressedSize(const void *src); //8015c2e0

//Stream
struct UncompContextLZ { //LZ77
    void* destBuffer;
    s32 remainingSize;
    u8 unknown_0x8[0x24 - 0x8];
};
size_assert(UncompContextLZ, 0x24);
void InitUncompContextLZ(UncompContextLZ* context, void* dest); //8015bef0
s32 ReadUncompLZ(UncompContextLZ* context, const void* src, u32 length); //8015bf24
}

#endif