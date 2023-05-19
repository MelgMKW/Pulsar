#ifndef _NW4R_SNDWAVEFILE_
#define _NW4R_SNDWAVEFILE_
#include <types.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>
#include <core/nw4r/snd/Util.hpp>
#include <core/nw4r/snd/Misc.hpp>


namespace nw4r {
namespace snd {
namespace detail {
struct WaveFile { //RWAV

    enum WaveFormat {
        FORMAT_PCM8 = 0,
        FORMAT_PCM16 = 1,
        FORMAT_ADPCM = 2
    };
    enum WaveDataLocationType {
        WAVE_DATA_LOCATION_OFFSET = 0,
        WAVE_DATA_LOCATION_ADDRESS = 1
    };

    struct WaveInfo {
        u8 format; // enum WaveFormat
        u8 loopFlag; // boolean
        u8 numChannels;
        u8 sampleRate24;
        u16 sampleRate;
        u8 dataLocationType; // enum WaveDataLocationType
        u8 padding;
        u32 loopStart;
        u32 loopEnd;
        u32 channelInfoTableOffset;
        u32 dataLocation;
        u32 reserved;
    };

    struct AdpcmParamSet {
        AdpcmParam adpcmParam;
        AdpcmLoopParam adpcmLoopParam;
    };

    struct WaveChannelInfo {
        u32 channelDataOffset;
        u32 adpcmOffset;
        u32 volumeFrontLeft;
        u32 volumeFrontRight;
        u32 volumeRearLeft;
        u32 volumeRearRight;
        u32 reserved;
    };

    struct InfoBlock { //INFO
        ut::BinaryBlockHeader blockHeader;
        WaveInfo waveInfo;
    };

    struct DataBlock { //DATA
        ut::BinaryBlockHeader blockHeader;
        union { //based on format
            s8 rawPCM8[1];
            s16 rawPCM16[1];
            u8 rawADPCM[1];
        };
    };

    struct FileHeader {
        ut::BinaryFileHeader fileHeader;
        u32 infoChunkOffset;
        u32 infoChunkSize;
        u32 dataChunkOffset;
        u32 dataChunkSize;
    };
};

class WaveFileReader {
public:
    WaveFileReader(const WaveFile::FileHeader* raw); //800ad1f0
    WaveFileReader(const WaveFile::WaveInfo* rawInfo); //800ad210
    bool ReadWaveInfo(WaveInfo* waveData, const void* waveDataOffsetOrigin) const; //800ad220
    const void* GetWaveDataAddress(const WaveFile::WaveChannelInfo* waveChannelInfo, const void* waveDataOffsetOrigin) const; //800ad430

    const WaveFile::WaveInfo* rawWaveInfo;
};

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif