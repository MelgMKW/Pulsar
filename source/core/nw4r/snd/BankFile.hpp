#ifndef _NW4R_SNDBANKFILE_
#define _NW4R_SNDBANKFILE_
#include <types.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>
#include <core/nw4r/snd/Util.hpp>
#include <core/nw4r/snd/Misc.hpp>

namespace  nw4r {
namespace snd {
namespace detail {

enum WaveDataLocationType {
    WAVE_DATA_LOCATION_INDEX = 0,
    WAVE_DATA_LOCATION_ADDRESS = 1,
    WAVE_DATA_LOCATION_CALLBACK = 2
};

enum NoteOffType {
    NOTE_OFF_TYPE_RELEASE = 0,
    NOTE_OFF_TYPE_IGNORE = 1
};

struct BankFile { //https://wiki.tockdom.com/wiki/BRBNK_(File_Format) RBNK 
    struct RangeTable;
    struct IndexTable;

    struct InstParam {
        s32 waveIndex;
        u8 attack; //0x4
        u8 decay; //0x5
        u8 sustain; //0x6
        u8 release; //0x7
        u8 hold; //0x8
        u8 waveDataLocationType; //0x9 see enum
        u8 noteOffType; //0xa see enum
        u8 alternateAssign; //0xb
        u8 originalKey; //0xc
        u8 volume; //0xd
        u8 pan; //0xe
        u8 padding2; //0xf
        float pitch; //0x10
        Util::DataRef<void> lfoTableRef; //0x14
        Util::DataRef<void> graphEnvTablevRef; //0x1c
        Util::DataRef<void> randomizerTableRef; //0x24
        u32 reserved; //0x28
    };

    struct RangeTable {
        u8 tableSize;
        u8 key[0];
    };

    typedef Util::DataRef<void, InstParam, RangeTable, IndexTable> InstrumentRef;
    struct IndexTable {
        u8 min;
        u8 max;
        u16 reserved;
        InstrumentRef ref[0];
    };

    struct DataBlock {
        ut::BinaryBlockHeader blockHeader;
        Util::Table<InstrumentRef> instTable;
    };

    struct Header {
        ut::BinaryFileHeader fileHeader;
        u32 dataBlockOffset;
        u32 dataBlockSize;
        u32 waveBlockOffset;
        u32 waveBlockSize;
    };
};

struct InstInfo {

    struct WaveDataLocation {
        WaveDataLocationType type;
        s32 index;
    };

    WaveDataLocation waveDataLocation;
    u8 attack;
    u8 hold;
    u8 decay;
    u8 sustain;
    u8 release;
    NoteOffType noteOffType;
    u8 alternateAssign;
    u8 originalKey;
    u8 pan;
    u8 volume;
    float tune;
};

class BankFileReader {
public:
    BankFileReader(const void* bankData);
    const BankFile::InstParam* GetInstParam(int prgNumber, int key, int velocity) const; //8008d630
    bool ReadInstInfo(InstInfo* instInfo, int prgNo, int key, int velocity) const; //8008d740
    const BankFile::InstrumentRef* GetReferenceToSubRegion(const BankFile::InstrumentRef* ref, int splitKey) const; //8008d8e0
    bool ReadWaveInfo(WaveInfo* waveParam, const InstInfo::WaveDataLocation& waveDataLocation,
        const void* rawWavArchive, const WaveInfo** waveInfoAddress) const; //8008da00
};
}//namespace detail

}//namespace snd
}//namespace nw4r
#endif