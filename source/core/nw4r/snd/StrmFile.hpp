#ifndef _NW4R_SNDSTRMFILE_
#define _NW4R_SNDSTRMFILE_
#include <types.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class StrmFileReader {
public:
    struct RSTMHeader {
        char magic[4]; //RSTM
        u16 byteOrderMask; //FEFF
        u16 unknown_0x06;
        u32 length;
        u16 headerLength; //always 0x40
        u16 unknown_0x0e;
        u32 offsetToHEAD;
        u32 headLength;
        u32 offsetToADPC;
        u32 adpcLength;
        u32 offsetToDATA;
        u32 dataLength;
        u8 unknown_0x28[0x16];
        u8 speedUpByte; //artificial
        u8 volumeByte; //artifical
    }; //total size 0x40
    struct HEADSection {
        char magic[4]; //HEAD
        u32 length;
        u8 unknown_0x8[0x20 - 0x8]; //first is probably version, last is likely length of the subHeader
        u8 type; //soundtype but as a u8
        bool isLooped;
        u8 channelCount;
        u8 unknwon_0x23; //gets shifted and added to sample rate
        u16 sampleRate;
        u16 unknown_0x26;
        u32 loopStartSample; //0x28
        u32 samplesCount;
        u32 uncompressedFileSize; //in bytes
        u32 blocksCount;
        u32 blockSize;
        u32 unknown_0x3C[5];
        u32 bitsPerSample;
        u8 unknown_0x54[0x2c0 - 0x54];
    };//total size 0x2C0

    class StrmInfo { //-C for all offsets
    public:
        u32 type; //3 for strm, 800a4ec4, base on soundtype
        bool isLooped; //0x10
        u8 unknown_0x11[3]; //might be padding //
        u32 channelCount; //0x14
        u32 sampleRate; //44100Hz for example
        u16 unknown_0x1C[2]; //2nd might be padding
        u32 loopStartSample;
        u32 samplesCount;
        u32 uncompressedFileSize; //in bytes
        u32 blocksCount;
        u32 blockSize;
        u32 unknown_0x34[5];
        u32 bitsPerSample;
    }; //total size 0x3C

    StrmFileReader(); //800a4e90
    bool ReadStrmInfo(StrmInfo *info); //800a4ea0
    RSTMHeader *header;
    HEADSection *strmInfo;
};

class StrmFileLoader {
public:
    bool LoadFileHeader(void *buffer, u32 maxADPCoffset);
    bool ReadStrmInfo(StrmFileReader::StrmInfo *info); //800a5490
    DVDSoundArchive::DVDFileStream *stream;
    StrmFileReader fileReader;
}; //total size 0xC
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif

