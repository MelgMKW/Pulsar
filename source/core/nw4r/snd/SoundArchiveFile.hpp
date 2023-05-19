#ifndef _NW4R_SNDARCHIVEFILE_
#define _NW4R_SNDARCHIVEFILE_
#include <types.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>
#include <core/nw4r/snd/Util.hpp>
#include <core/rvl/nand.hpp>



//8009ed80 read bank info
namespace nw4r {
namespace snd {
class Sound3DParam;
namespace detail {

class SoundArchiveFile {//https://wiki.tockdom.com/wiki/BRSAR_(File_Format)
public:
    struct SeqSoundInfo {
        u32 dataOffset;
        SoundArchive::BankId bankId;
        u32 allocTrack;
        u8 channelPriority;
        u8 releasePriorityFix;
        u8 padding[2];
        u32 reserved;
    };

    struct StrmSoundInfo {
        u32 startPosition;
        u16 allocChannelCount;
        u16 allocTrackFlag;
        u32 reserved;
    };

    struct WaveSoundInfo { //for example title screen
        s32 subNo;
        u32 allocTrack;
        u8 channelPriority;
        u8 releasePriorityFix;
        u8 padding[2];
        u32 reserved;
    };

    typedef detail::Util::DataRef<void, SeqSoundInfo, StrmSoundInfo, WaveSoundInfo> SoundInfoRef;
    struct SoundCommonInfo {
        u32 stringId;
        u32 fileId;
        u32 playerId;
        detail::Util::DataRef<Sound3DParam> param3dRef;
        u8 volume;
        u8 playerPriority;
        u8 soundType;
        u8 remoteFilter;
        SoundInfoRef soundInfoRef;
        u32 userParam[2];
        u8 panMode;
        u8 panCurve;
        u8 actorPlayerId;
        u8 reserved;
    };

    struct BankInfo {
        u32 stringId;
        u32 fileId;
        u32 reserved;
    };

    struct PlayerInfo {
        u32 stringId;
        u8 playableSoundCount;
        u8 padding;
        u16 padding2;
        u32 heapSize;
        u32 reserved;
    };

    struct GroupItemInfo {
        u32 fileId;
        u32 offset;
        u32 size;
        u32 waveDataOffset;
        u32 waveDataSize;
        u32 reserved;
    };

    typedef detail::Util::Table< detail::Util::DataRef<SoundArchive::FilePos> > FilePosTable;
    struct FileInfo {
        u32 fileSize;
        u32 waveDataFileSize;
        s32 entryNum;
        detail::Util::DataRef<char> extFilePathRef;
        detail::Util::DataRef<FilePosTable> filePosTableRef;
    };

    struct SoundArchivePlayerInfo {
        u16 seqSoundCount;
        u16 seqTrackCount;
        u16 strmSoundCount;
        u16 strmTrackCount;
        u16 strmChannelCount;
        u16 waveSoundCount;
        u16 waveTrackCount;
        u16 padding;
        u32 reserved;
    };

    typedef detail::Util::Table<detail::Util::DataRef<GroupItemInfo> > GroupItemTable;

    struct GroupInfo {
        u32 stringId;
        s32 entryNum;
        detail::Util::DataRef<char> extFilePathRef;
        u32 offset;
        u32 size;
        u32 waveDataOffset;
        u32 waveDataSize;
        detail::Util::DataRef<GroupItemTable> itemTableRef;
    };

    typedef detail::Util::DataRef<SoundCommonInfo> SoundCommonInfoRef;
    typedef detail::Util::Table<SoundCommonInfoRef> SoundInfoTable;
    typedef detail::Util::Table<detail::Util::DataRef<BankInfo> > BankInfoTable;
    typedef detail::Util::Table<detail::Util::DataRef<PlayerInfo> > PlayerInfoTable;
    typedef detail::Util::Table<detail::Util::DataRef<FileInfo> > FileInfoTable;
    typedef detail::Util::Table<detail::Util::DataRef<GroupInfo> > GroupInfoTable;

    struct Info {
        detail::Util::DataRef<detail::Util::Table<SoundCommonInfoRef>> soundTableRef;
        detail::Util::DataRef<BankInfoTable> bankTableRef;
        detail::Util::DataRef<PlayerInfoTable> playerTableRef;
        detail::Util::DataRef<FileInfoTable> fileTableRef;
        detail::Util::DataRef<GroupInfoTable> groupTableRef;
        detail::Util::DataRef<SoundArchivePlayerInfo> soundArchivePlayerInfoRef;
    };

    struct Header {
        ut::BinaryFileHeader fileHeader;
        u32 offsetSYMB; //0x10
        u32 sizeSYMB; //0x14
        u32 offsetINFO; //0x18 
        u32 sizeINFO; //0x1c
        u32 offsetFILE; //0x20
        u32 sizeFILE; //0x24
    };
};

class SoundArchiveFileReader {
public:
    SoundArchiveFileReader(); //8009e690
    void Init(const void* soundArchiveData); //8009e6c0
    void SetStringChunk(const void* stringChunk, u32 stringChunkSize); //8009e770
    void SetInfoChunk(const void* infoChunk, u32 infoChunkSize); //8009e820

    SoundArchive::SoundType GetSoundType(SoundArchive::SoundId soundId) const; //8009e830
    bool ReadSoundInfo(SoundArchive::SoundId soundId, SoundArchive::SoundInfo* info) const; //8009e920
    bool ReadSound3DParam(SoundArchive::SoundId soundId, SoundArchive::Sound3DParam* param) const; //8009ea50
    bool ReadSeqSoundInfo(SoundArchive::SoundId soundId, SoundArchive::SeqSoundInfo* info) const; //8009eb60
    bool ReadStrmSoundInfo(SoundArchive::SoundId soundId, SoundArchive::StrmSoundInfo* info) const; //8009ec10
    bool ReadWaveSoundInfo(SoundArchive::SoundId soundId, SoundArchive::WaveSoundInfo* info) const; //8009ece0
    bool ReadBankInfo(SoundArchive::BankId bankId, SoundArchive::BankInfo* info) const; //8009ed80
    bool ReadPlayerInfo(SoundArchive::PlayerId playerId, SoundArchive::PlayerInfo* info) const; //8009ee30
    bool ReadGroupInfo(SoundArchive::GroupId groupId, SoundArchive::GroupInfo* info) const; //8009eef0
    bool ReadGroupItemInfo(SoundArchive::GroupId groupId, u32 index, SoundArchive::GroupItemInfo* info) const; //8009f000
    bool ReadSoundArchivePlayerInfo(SoundArchive::SoundArchivePlayerInfo* info) const; //8009f138
    u32 GetPlayerCount() const; //8009f1d0
    u32 GetGroupCount() const; //8009f210
    const char* GetGroupLabelString(SoundArchive::GroupId groupId) const; //8009f260
    const char* GetBankLabelString(SoundArchive::BankId bankId) const; //8009f340
    u32 GetSoundUserParam(SoundArchive::SoundId soundId) const; //8009f420
    u32 GetFileCount() const; //8009f4e0
    bool ReadFileInfo(SoundArchive::FileId fileId, SoundArchive::FileInfo* info) const; //8009f520
    bool ReadFilePos(SoundArchive::FileId fileId, u32 index, SoundArchive::FilePos* info) const; //8009f620
    u32 ConvertLabelStringToId(const void* stringTree, const char* str) const; //8009f740
    SoundArchiveFile::SoundInfoRef impl_GetSoundInfoOffset(); //8009f890

    SoundArchiveFile::Header header;
    SoundArchiveFile::Info* soundInfo; //0x28
    void* stringBase; //0x2c
    u8* stringTable; //0x30
    u8* soundStringTree; //0x34
    u8* playerStringTree;
    u8* groupStringTree;
    u8* bankStringTree;
}; //total size 0x44
size_assert(SoundArchiveFileReader, 0x44);
}

class NandSoundArchive : public SoundArchive {
public:
    NandSoundArchive(); //80097570
    ~NandSoundArchive() override; //800975c0 vtable 80274808
    detail::SoundArchiveFileReader fileReader; //0x108
    NAND::FileInfo fileInfo; //14c
    bool isOpen;
    u8 padding[3];
}; //total size 0x1DC
size_assert(NandSoundArchive, 0x1DC);

class MemorySoundArchive : public SoundArchive {
public:
    MemorySoundArchive(); //80095d80
    ~MemorySoundArchive() override; //80095dd0 vtable 802744d8
    bool Setup(const void* soundArchiveData); //80095e30
    const void* data;
    detail::SoundArchiveFileReader fileReader;
}; //total size 0x150
size_assert(MemorySoundArchive, 0x150);
}//namespace snd
}//namespace nw4r

#endif