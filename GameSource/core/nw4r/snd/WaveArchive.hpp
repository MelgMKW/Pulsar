#ifndef _NW4R_SNDWAVEARCHIVE_
#define _NW4R_SNDWAVEARCHIVE_
#include <types.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>
#include <core/nw4r/snd/Util.hpp>
#include <core/nw4r/snd/WaveFile.hpp>
#include <core/nw4r/snd/Misc.hpp>


namespace nw4r {
namespace snd {
namespace detail { //ASSOCIATED WITH BANK FILES and/or wsd files like title screen
struct WaveArchive { //RWAR, composed of RWAV files, as many as fileTable has items

    struct TableItem {
        Util::DataRef<WaveFile::FileHeader> waveFileRef;
        u32 waveFileSize;
    };

    struct TableBlock { //TABL
        ut::BinaryBlockHeader blockHeader;
        Util::Table<TableItem> fileTable;
    };

    struct DataBlock { //DATA, has the RWAVs
        ut::BinaryBlockHeader blockHeader;
        u8 data[1];
    };

    struct FileHeader {
        ut::BinaryFileHeader fileHeader;
        u32 tableChunkOffset;
        u32 tableChunkSize;
        u32 dataChunkOffset;
        u32 dataChunkSize;
    };
};

class WaveArchiveReader {
public:
    WaveArchiveReader(const void* rawArchive); //800ad0e0
    const WaveFile::FileHeader* WaveArchiveReader::GetWaveFile(int index) const; //800ad160
    const WaveArchive::TableBlock* rawTbleBlock;
    const WaveArchive::DataBlock* rawDataBlock;
};


}//namespace detail
}//namespace snd
}//namespace nw4r
#endif