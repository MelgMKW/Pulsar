#ifndef _EGGSTREAMDECOMP_
#define _EGGSTREAMDECOMP_
#include <types.hpp>
#include <core/rvl/CX/Uncompression.hpp>

namespace EGG {
//non-official names
class StreamDecompLZ {
public:
    virtual void init(void* buffer, u32 lengthToDecompress); //80242498 vtable 802a3f78
    virtual s32 decomp(const void* src, u32 length); //802424c8
    virtual s32 getAlignment(); //802424f4
    virtual u32 getUncompressedSize(const void* src); //802424fc
    void* buffer; //0x4 will hold the decompressed file
    u32 lengthToDecompress; //0x8 of the compressed file
    CX::UncompContextLZ uncompContextLZ; //0xc
};
size_assert(StreamDecompLZ, 0x30);
}//namespace EGG

#endif