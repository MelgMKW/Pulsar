#ifndef _NW4R_UTFILESTREAM_
#define _NW4R_UTFILESTREAM_
#include <types.hpp>
#include <core/nw4r/ut/IOStream.hpp>
namespace nw4r {
namespace ut {
class FileStream : public IOStream {
public:
    class FilePosition {
    public:
        u32 size;
        u32 pos;
    };
    FileStream();
}; //total size 0x14
}//namespace ut
}//namespace nw4r
#endif