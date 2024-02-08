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
        DvdFileStream* stream;
    };
    explicit DvdFileStream(s32 entryNum); //800b00d0
    explicit DvdFileStream(const DVDFileInfo* openedFile, bool closeEnable = true); //800b0190

    void* GetRuntimeTypeInfo() const override; //800b0690 vtable 80274c40
    ~DvdFileStream() override; //0xc 800b02c0
    void Close() override; //0x10 800b0340
    s32 Read(void* buf, u32 length) override; //0x14 800b0390
    bool ReadAsync(void* buffer, u32 length, IOStreamCallback callback, void* cbArg) override; //0x18 800b0390
    bool IsBusy() const override; //0x24 800915d0
    bool CanAsync() const override; //0x28 800b0660
    bool CanRead() const override; //0x2c 800915b0
    bool CanWrite() const override; //0x30 800915a0

    u32 GetOffsetAlign() const override; //0x34 80091580
    u32 GetSizeAlign() const override; //0x38 80091570
    u32 GetBufferAlign() const override; //0x3c 80091560


    u32  GetSize()  const override; //0x40 800b0670
    void Seek(s32 offset, u32 origin) override; //0x44 800b05e0
    void Cancel() override; //0x48 800b05f0
    bool CancelAsync(IOStreamCallback callback, void* arg) override; //0x4c 800b0600
    bool CanSeek() const override; //0x50 800915c0
    bool CanCancel() const override; //0x54 80091590
    u32  Tell() const override; //0x58 800b0680

    virtual s32 Peek(void* buffer, u32 length); //0x5c 800b0520
    virtual bool PeekAsync(void* buffer, u32 length, IOStreamCallback callback, void* cbArg); //0x60 800b0560

    static void DvdAsyncCallback_(s32 result, DVDFileInfo* fileInfo); //800b0070
    static void DvdCBAsyncCallback_(s32 result, DVDCommandBlock* block); //800b00a0


    FilePosition position; //14
    IOStreamCallback cancelCallback; //1c
    void* cancelArg; //20
    bool isCancelling;
    u8 padding[3];
    DvdFileStreamInfo fileInfo; //28
    s32 priority; //68
    bool isBusy; //6c
    bool closeOnDestroyFlag;  //0x6e
    bool closeEnableFlag; //0x6e
};
size_assert(DvdFileStream, 0x70);
}//namespace ut
}//namespace nw4r
#endif