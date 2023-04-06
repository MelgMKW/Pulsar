#ifndef _NW4R_SNDARCHIVEFILE_
#define _NW4R_SNDARCHIVEFILE_
#include <types.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>
#include <core/rvl/nand.hpp>

//8009ed80 read bank info
namespace nw4r {
namespace snd {
namespace detail {
class SoundArchiveFileReader { //https://wiki.tockdom.com/wiki/BRSAR_(File_Format)
public:
    SoundArchiveFileReader(); //8009e690
    bool ReadSoundInfo(u32 id, SoundArchive::SoundInfo *soundInfo); //8009e920
    bool ReadStrmInfo(u32 id, SoundArchive::StrmSoundInfo *soundInfo); //8009ec10
    u32 ConvertLabelStringToId(u8 *stringTree, const char *string) const; //8009f740
    SoundArchive::SoundType GetSoundType(u32 soundId); //8009e830
    char magic[4]; //RSAR
    u16 byteOrderMark; //0x4 0xFEFF for big endian
    u16 version; //0x6 01 04 for revo_kart
    u32 length; //0x8
    u16 headerLength; //0xc
    u16 sectionCount; //0xe
    u32 offsetSYMB; //0x10
    u32 sizeSYMB; //0x14
    u32 offsetINFO; //0x18 
    u32 sizeINFO; //0x1c
    u32 offsetFILE; //0x20
    u32 sizeFILE; //0x24
    UnkType *soundInfo; //0x28
    void *stringBase; //0x2c
    u8 *stringTable; //0x30
    u8 *soundStringTree; //0x34
    u8 *playerStringTree;
    u8 *groupStringTree;
    u8 *bankStringTree;
}; //total size 0x44
size_assert(SoundArchiveFileReader, 0x44);
}

class NandSoundArchive : public SoundArchive {
public:
    NandSoundArchive(); //80097570
    ~NandSoundArchive() override; //800975c0 vtable 80274808
    detail::SoundArchiveFileReader fileReader; //0x108
    NANDFileInfo fileInfo; //14c
    bool isOpen;
    u8 padding[3];
}; //total size 0x1DC
size_assert(NandSoundArchive, 0x1DC);

class MemorySoundArchive : public SoundArchive {
public:
    MemorySoundArchive(); //80095d80
    ~MemorySoundArchive() override; //80095dd0 vtable 802744d8
    bool Setup(const void *soundArchiveData); //80095e30
    const void *data;
    detail::SoundArchiveFileReader fileReader;
}; //total size 0x150
size_assert(MemorySoundArchive, 0x150);
}//namespace snd
}//namespace nw4r

#endif