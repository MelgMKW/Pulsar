#ifndef _NW4R_UTDVDLOCKEDFILESTREAM_
#define _NW4R_UTDVDLOCKEDFILESTREAM_
#include <types.hpp>
#include <core/nw4r/ut/DvdFileStream.hpp>

namespace nw4r {
namespace ut {
class DvdLockedFileStream : public DvdFileStream {
public:
    explicit DvdLockedFileStream(s32 entryNum); //800b06b0
    explicit DvdLockedFileStream(const DVDFileInfo* openedFile, bool closeEnable = true); //800b0740

    void* GetRuntimeTypeInfo() const override; //80091610 vtable 80274ca8
    ~DvdLockedFileStream() override; //0xc 800b07d0
    void Close() override; //0x10 800b0830
    s32 Read(void* buf, u32 length) override; //0x14 800b0870
    bool ReadAsync(void* buffer, u32 length, IOStreamCallback callback, void* cbArg) override; //0x18 80091600
    bool CanAsync() const override; //0x28 800915e0
    void Cancel() override; //0x48 800b0a30
    bool CancelAsync(IOStreamCallback callback, void* arg) override; //0x4c 800b0600
    s32 Peek(void* buffer, u32 length) override; //0x5c 800b0950
    bool PeekAsync(void* buffer, u32 length, IOStreamCallback callback, void* cbArg) override; //0x60 800915f0

    bool cancelFlag; //0x70
    u8 padding3[3];

    static OS::Mutex mutex; //802f12e8

};
size_assert(DvdLockedFileStream, 0x74);
}//namespace ut
}//namespace nw4r
#endif