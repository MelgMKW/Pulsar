#ifndef _NW4R_SNDSTRMFILE_
#define _NW4R_SNDSTRMFILE_
#include <types.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>
#include <core/nw4r/snd/Misc.hpp>
#include <core/nw4r/snd/Util.hpp>

namespace nw4r {
namespace snd {
namespace detail {

struct StrmFile {
    struct alignas(0x20) Header {
        ut::BinaryFileHeader header; //RSTM, byte order 0xFEFF, version 0x0100, header 0x40, dataBlocks 2
        u32 offsetToHEAD; //0x10
        u32 headLength; //0x14
        u32 offsetToADPC; //0x18
        u32 adpcLength; //0x1c
        u32 offsetToDATA; //0x20
        u32 dataLength; //0x24
        //0x18 bytes of padding for alignment with HEAD
    };
    size_assert(Header, 0x28);

    struct StrmDataInfo { //+0x20 from HEAD start
        u8 format; //0x0 soundType
        bool isLooped; //0x1
        u8 channelCount; //0x2
        u8 sampleRate_0x3; //0x3
        u16 sampleRate; //0x4
        u16 offsetToBlockHeader; //0x6
        u32 loopStart; //0x8
        u32 loopEnd; //0xc
        u32 offsetToData; //0x10 called "uncompressed size (in bytes)" on brawlcrate
        u32 blocksCount; //0x14
        u32 blockSize; //0x18
        u32 blockSamples; //0x1c
        u32 lastBlockSize; //0x20
        u32 lastBlockSamples; //0x24
        u32 lastBlockPaddedSize; //0x28
        u32 adpcmSampleCount; //0x2c
        u32 adpcmSampleSize; //0x30 bits per sample
    };
    size_assert(StrmDataInfo, 0x34);

    struct TrackInfo {
        u8 channelCount;
        u8 channelIndexTable[0]; //channel count
    };

    struct TrackInfoEx {
        u8 volume;
        u8 pan;
        u8 padding[2];
        u32 reserved;
        u8 channelCount;
        u8 channelIndexTable[0]; //channel count
    };

    struct TrackTable {
        u8 trackCount;
        u8 trackDataType;
        u8 padding[2];
        Util::DataRef<TrackInfo, TrackInfoEx> refTrackHeader[0]; //0x4 size trackcount 
    };

    struct AdpcmParamSet {
        AdpcmParam adpcmParam;
        AdpcmLoopParam adpcmLoopParam;
    };

    struct ChannelInfo {
        Util::DataRef<AdpcmParamSet> refAdpcmInfo;
    };

    struct ChannelTable {
        u8 channelCount;
        u8 padding[3];
        Util::DataRef<ChannelInfo> refChannelHeader[0];
    };


    struct alignas(0x20) HeadBlock {
        ut::BinaryBlockHeader header; //HEAD, size 0x100
        Util::DataRef<StrmDataInfo> refStrmData; //0x8
        Util::DataRef<TrackTable> refTrackTable; //0x10
        Util::DataRef<ChannelTable> refChannelTable; //0x18
    };//total size 0x20
    size_assert(HeadBlock, 0x20);

    struct AdpcBlock {
        ut::BinaryBlockHeader blockHeader; //ADPC
    };

    struct DataBlock {
        ut::BinaryBlockHeader blockHeader; //DATA
        u32 dataOffset;
    };
};


class StrmFileReader {
public:
    struct StrmInfo { //-C for all offsets
        SampleFormat sampleFormat; //0x0 3 for strm, 800a4ec4, base on soundtype
        bool isLooped; //0x4
        u8 padding[3];
        u32 channelCount; //0x8
        u32 sampleRate; //0xc 44100Hz for example
        u16 blockHeaderOffset; //0x10
        u16 padding2;
        u32 loopStart; //0x14
        u32 loopEnd; //0x18
        u32 dataOffset; //0x1c
        u32 blocksCount; //0x20
        u32 blockSize; //0x24
        u32 blockSamples; //0x28
        u32 lastBlockSize; //0x2c
        u32 lastBlockSamples; //0x30
        u32 lastBlockPaddedSize; //0x34
        u32 adpcmSampleCount; //0x38
        u32 adpcmSampleSize; //0x3C bits per sample
    };
    size_assert(StrmInfo, 0x40);

    struct StrmTrackInfo {
        u8 volume;
        u8 pan;
        int channelCount;
        u8 channelIndexTable[32]; //only use as many as channelCount
    };

    StrmFileReader(); //800a4e90
    bool ReadStrmInfo(StrmInfo* info); //800a4ea0
    bool ReadStrmTrackInfo(StrmTrackInfo* trackInfo, int trackIndex) const; //800a4fb0
    const StrmFile::Header* header;
    const StrmFile::HeadBlock* headBlock;
};

class StrmFileLoader {
public:
    StrmFileLoader(ut::FileStream& fileStream); //inlined
    bool LoadFileHeader(void* buffer, u32 maxADPCoffset); //800a5270
    bool ReadStrmInfo(StrmFileReader::StrmInfo* info); //800a5490
    bool ReadStrmTrackInfo(StrmFileReader::StrmTrackInfo* trackInfo, int trackIndex) const; //800a54d0
    int GetChannelCount() const; //800a5440
    bool ReadAdpcmInfo(AdpcmParam* adpcmParam, AdpcmLoopParam* adpcmLoopParam, int channelIndex) const; //800a5510
    bool ReadAdpcBlockData(u16* yn1, u16* yn2, int blockIndex, int channelCount); //800a56a0
    ut::FileStream& stream;
    StrmFileReader fileReader;
}; //total size 0xC

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif

