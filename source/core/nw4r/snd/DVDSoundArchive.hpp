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
        DVDFileStream(); //inlined 8009132c
        virtual void func_vtable(); //802742b0
    };

    DVDSoundArchive(); //80090fc0
    virtual ~DVDSoundArchive(); //80091010 vtable 80274318
    virtual const void *Detail_GetFileAddress(u32 fileId); //80091650
    virtual const void *Detail_GetWaveDataFileAddress(u32 fileId); //80091640
    virtual int Detail_GetRequiredStreamBufferSize() const; //80091380
    virtual ut::FileStream *OpenStream(void *buffer, int size, u32 begin, u32 length) const; //80091210
    virtual ut::FileStream *OpenExtStream(void *buffer, int size, const char *extFilePath, u32 begin, u32 length) const; //800912c0
    bool LoadHeader(void *buffer, u32 size); //80091390 INFO section
    bool Open(const char *filePath);
    bool Open(s32 entryNum);
    DVDFileStream *OpenExtStream(DVDFileStream *dvdFileStream, u32 size, const char *path, u32 begin, u32 length);
    detail::SoundArchiveFileReader fileReader; //0x108
    DVDFileInfo fileInfo; //0x14c
    bool isOpen; //0x188
    u8 unknown_0x189[3];

}; //total size 0x18c
size_assert(DVDSoundArchive, 0x18c);
}//namespace snd
}//namespace nw4r

#endif