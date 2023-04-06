#ifndef _NW4R_UTDVDFILESTREAM_
#define _NW4R_UTDVDFILESTREAM_
#include <types.hpp>
#include <core/nw4r/ut/FileStream.hpp>
#include <core/rvl/dvd/dvd.hpp>

namespace nw4r {
namespace ut {
class DvdFileStream : public FileStream {
public:
    class DvdFileStreamInfo {
        DVDFileInfo dvdInfo;
        DvdFileStream *stream;
    };
    DvdFileStream(u32 entryNum); //800b00d0 
    ~DvdFileStream() override; //80274c40
    void Seek(u32 begin, u32 r5);
    int Read(void *buffer, u32 size);
    FilePosition position; //14
    IOStreamCallback cancelCallback; //1c
    void *cancelArg; //20
    volatile bool isCancelling;
    u8 padding[3];
    DvdFileStreamInfo fileInfo; //28
    s32 priority; //68
    bool isBusy; //6c
    bool closeOnDestroyFlg;
    bool closeEnableFlg;
    bool isLocked;
    u32 offset; //70
    u32 size; //74
};
size_assert(DvdFileStream, 0x78);
}//namespace ut
}//namespace nw4r
#endif