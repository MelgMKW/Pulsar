#ifndef _NW4R_UTIOSTREAM_
#define _NW4R_UTIOSTREAM_
#include <types.hpp>

namespace nw4r {
namespace ut {
class IOStream {
public:
    typedef void (*IOStreamCallback)(s32 result, IOStream* stream, void* arg);
    virtual void* GetRuntimeTypeInfo() const; //0x8 
    virtual ~IOStream(); //0xc
    virtual void Close() = 0; //0x10
    virtual s32 Read(void* buf, u32 length); //0x14
    virtual bool ReadAsync(void* buffer, u32 length, IOStreamCallback callback, void* cbArg); //0x18 800afea0
    virtual s32 Write(const void* buffer, u32 length); //0x1c 800afeb0
    virtual bool WriteAsync(const void* buffer, u32 length, IOStreamCallback callback, void* cbArg); //0x20 800afec0
    virtual bool IsBusy() const; //0x24 800afed0
    virtual bool CanAsync() const = 0; //0x28
    virtual bool CanRead() const = 0; //0x2c
    virtual bool CanWrite() const = 0; //0x30
    virtual u32 GetOffsetAlign() const; //0x34
    virtual u32 GetSizeAlign() const; //0x38
    virtual u32 GetBufferAlign() const; //0x3c

    bool isAvailable; //4
    u8 padding[3];
    s32 asyncResult; //8
    IOStreamCallback callBack; //c
    void* cbArg; //10
};
size_assert(IOStream, 0x14);
}//namespace ut
}//namespace nw4r

#endif