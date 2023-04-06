#ifndef _NW4R_UTDVDLOCKEDFILESTREAM_
#define _NW4R_UTDVDLOCKEDFILESTREAM_
#include <types.hpp>
#include <core/nw4r/ut/DvdFileStream.hpp>

namespace nw4r {
namespace ut {
class DvdLockedFileStream : public DvdFileStream {
public:
    DvdLockedFileStream(u32 entryNum); //800b00d0 
    ~DvdLockedFileStream() override; //80274ca8
    volatile bool cancelFlag;
    u8 padding[3];
};
size_assert(DvdLockedFileStream, 0x7c);
}//namespace ut
}//namespace nw4r
#endif