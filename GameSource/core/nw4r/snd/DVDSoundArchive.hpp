#ifndef _NW4R_SNDDVDARCHIVE_
#define _NW4R_SNDDVDARCHIVE_
#include <types.hpp>
#include <core/nw4r/ut/DvdLockedFileStream.hpp>
#include <core/nw4r/snd/SoundArchiveFile.hpp>

namespace nw4r {
namespace snd {
class DVDSoundArchive : public SoundArchive {
public:
    class DVDFileStream : public ut::DvdLockedFileStream {
    public:
        //ctor inlined 8009132c
        ~DVDFileStream() override; //0xc 80091660 vtable 802742b0
        s32 Read(void* buf, u32 length) override; //0x14 800914b0
        u32 GetSize() const override; //0x40 80091620
        void Seek(s32 offset, u32 origin) override; //0x44 800914e0
        u32 Tell() const override; //0x58 80091630

        u32 offset; //70
        u32 size; //74
    }; //0x78

    DVDSoundArchive(); //80090fc0
    ~DVDSoundArchive() override; //80091010 vtable 80274318
    const void* detail_GetFileAddress(FileId fileId) const override; //0xc 80091650
    const void* detail_GetWaveDataFileAddress(FileId fileId) const override; //0x10 80091640
    int detail_GetRequiredStreamBufferSize() const override; //0x14 80091380
    ut::FileStream* OpenStream(void* buffer, int size, u32 begin, u32 length) const override; //0x18 80091210
    ut::FileStream* OpenExtStream(void* buffer, int size, const char* extFilePath, u32 begin, u32 length) const override; //0x1c 800912c0

    bool Open(const char* filePath); //80091090
    void Close(); //800911d0
    bool LoadHeader(void* buffer, u32 size); //80091390 INFO section
    bool LoadLabelStringData(void* buffer, u32 size); //80091420

    detail::SoundArchiveFileReader fileReader; //0x108
    DVDFileInfo fileInfo; //0x14c
    bool isOpen; //0x188
    u8 padding[3];
}; //total size 0x18c
size_assert(DVDSoundArchive, 0x18c);
}//namespace snd
}//namespace nw4r

#endif