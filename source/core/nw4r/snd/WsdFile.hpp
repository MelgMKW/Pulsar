#ifndef _NW4R_SNDWSDFILE_
#define _NW4R_SNDWSDFILE_
#include <types.hpp>

#include <core/nw4r/snd/BasicPlayer.hpp>
#include <core/nw4r/snd/Util.hpp>
#include <core/nw4r/snd/Misc.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>

namespace nw4r {
namespace snd {
namespace detail {
struct WaveSoundInfo {
    float pitch;
    u8 pan;
    u8 surroundPan;
    u8 fxSendA;
    u8 fxSendB;
    u8 fxSendC;
    u8 ainSend;
}; //0xc

struct WaveSoundNoteInfo {
    s32 waveIndex;
    u8 attack;
    u8 hold;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 originalKey;
    u8 pan;
    u8 surroundPan;
    u8 volume;
    float pitch;
}; //0x14

//Links which RWAV files inside a RWAR to use; how to functionally use the file: https://imgur.com/0FDMOoZ
struct WsdFile { //RWSD https ://wiki.tockdom.com/wiki/BRWSD_(File_Format)
    struct NoteInfo {
        s32 waveIndex;
        u8 attack;
        u8 decay;
        u8 sustain;
        u8 release;
        u8 hold;
        u8 padding[3];
        u8 originalKey;
        u8 volume;
        u8 pan;
        u8 surroundPan;
        float pitch;
        Util::DataRef<void> lfoTableRef;
        Util::DataRef<void> graphEnvTablevRef;
        Util::DataRef<void> randomizerTableRef;
        u32 reserved;
    };

    struct TrackInfo {
        struct NoteEvent {
            float position;
            float length;
            u32 noteIndex;
            u32 reserved;
        };
        typedef Util::Table< Util::DataRef<NoteEvent> > NoteEventTable;

        Util::DataRef< NoteEventTable > noteEventTableRef;
    };

    struct WsdInfo {
        float pitch;
        u8 pan;
        u8 surroundPan;
        u8 fxSendA;
        u8 fxSendB;
        u8 fxSendC;
        u8 ainSend;
        u8 padding[2];
        Util::DataRef<void> graphEnvTablevRef;
        Util::DataRef<void> randomizerTableRef;
        u32 reserved;
    };

    typedef Util::Table<Util::DataRef<NoteInfo> > NoteTable;
    typedef Util::Table<Util::DataRef<TrackInfo> > TrackTable;

    struct Wsd {
        Util::DataRef<WsdInfo> refWsdInfo;
        Util::DataRef<TrackTable> refTrackTable;
        Util::DataRef<NoteTable> refNoteTable;
    };

    struct DataBlock { //DATA
        ut::BinaryBlockHeader blockHeader;
        u32 wsdCount;
        Util::DataRef<Wsd> refWsd[0];
    };

    struct WaveBlock { //WAVE, code is present but not used in kwii?
        ut::BinaryBlockHeader blockHeader;
        u32 waveCount;
        u32 offsetTable[0];
    };

    struct Header { //RWSD
        ut::BinaryFileHeader fileHeader;
        u32 dataBlockOffset;
        u32 dataBlockSize;
        u32 waveBlockOffset;
        u32 waveBlockSize;
    };
};

class WsdFileReader {
public:
    WsdFileReader(const void* rawWsd); //800ad9b0
    bool ReadWaveSoundInfo(WaveSoundInfo* noteInfo, int index) const; //800ada40
    bool ReadWaveSoundNoteInfo(WaveSoundNoteInfo* noteInfo, int index, int noteIndex) const; //800adb60
    bool ReadWaveInfo(int waveIndex, WaveInfo* waveData, const void* waveDataOffsetOrigin) const; //800adc80
    const WsdFile::Header* header;
    const WsdFile::DataBlock* dataBlock;
    const WsdFile::WaveBlock* waveBlock;
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif