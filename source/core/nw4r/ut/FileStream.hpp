#ifndef _NW4R_UTFILESTREAM_
#define _NW4R_UTFILESTREAM_
#include <types.hpp>
#include <core/nw4r/ut/IOStream.hpp>
namespace nw4r {
namespace ut {
class FileStream : public IOStream {
public:

    FileStream();
    virtual u32 GetSize() const = 0; //0x40
    virtual void Seek(s32 offset, u32 origin); //0x44
    virtual void Cancel(); //0x48 800afef0
    virtual bool CancelAsync(IOStreamCallback callback, void* arg); //0x4c 800aff00
    virtual bool CanSeek() const = 0; //0x50
    virtual bool CanCancel() const = 0; //0x54
    virtual u32 Tell() const = 0; //0x58

    class FilePosition {
    public:
        u32 Skip(s32 offset); //800aff10
        u32 Append(s32 offset); //800aff80
        void Seek(s32 offset, u32 origin); //800affd0
        u32 size;
        u32 pos;
    };

}; //total size 0x14
}//namespace ut
}//namespace nw4r
#endif