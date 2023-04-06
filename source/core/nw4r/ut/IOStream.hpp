#ifndef _NW4R_UTIOSTREAM_
#define _NW4R_UTIOSTREAM_
#include <types.hpp>

namespace nw4r {
namespace ut {
class IOStream {
public:
    typedef void (*IOStreamCallback)(s32 result, IOStream *stream, void *arg);
    virtual ~IOStream();
    bool isAvailable; //4
    u8 padding[3];
    u32 asyncResult; //8
    IOStreamCallback callBack; //c
    void *arg; //10
};
size_assert(IOStream, 0x14);
}//namespace ut
}//namespace nw4r

#endif