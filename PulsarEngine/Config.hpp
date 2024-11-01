#ifndef _PULSAR_CONFIG_
#define _PULSAR_CONFIG_

#include <kamek.hpp>
#include <IO/IO.hpp>
#include <Debug/Debug.hpp>
#include <Info.hpp>
#include <MarioKartWii/UI/Text/Text.hpp>
namespace Pulsar {


enum SectionIndexes {
    SECTION_INFO,
    SECTION_CUPS,
    SECTION_BMG
};

struct Variant {
    u8 slot;
    u8 musicSlot;
};
size_assert(Variant, 0x2);

struct Track {
    u8 slot;
    u8 musicSlot;
    u16 variantCount;
    u32 crc32;
};
size_assert(Track, 0x8);

enum PulsarId {
    PULSARID_NONE = 0xFFFFFFFF,
    PULSARID_FIRSTREG = 0,
    PULSARID_FIRSTCT = 0x100
};

enum PulsarCupId {
    PULSARCUPID_NONE = 0xFFFFFFFF,
    PULSARCUPID_FIRSTREG = 0,
    PULSARCUPID_FIRSTCT = 0x40
};

enum TTMode {
    TTMODE_150,
    TTMODE_200,
    TTMODE_150_FEATHER,
    TTMODE_200_FEATHER
};

/*
inline PulsarId operator+(PulsarId src, u32 rhs) {
    PulsarId ret = static_cast<PulsarId>(rhs + src);
    return ret;
}
*/

struct BinaryHeader {
    static const u32 CONFIGVERSION = 3;
    u32 magic;
    s32 version;
    s32 offsets[3];
    //s32 offsetToInfo; //from start of the header
    //s32 offsetToCups;
    //s32 offsetToBMG;
    char modFolderName[IOS::ipcMaxFileName + 1];
};

struct SectionHeader {
    u32 magic;
    u32 version;
    u32 size;
}; //0xc

struct InfoHolder {
    static const u32 magic = 'INFO';
    static const u32 index = SECTION_INFO;
    static const u32 curVersion = 1;
    SectionHeader header;
    Info info;
};

struct CupsHolder {
    static const u32 magic = 'CUPS';
    static const u32 index = SECTION_CUPS;
    static const u32 curVersion = 3;
    SectionHeader header;
    u16 ctsCupCount;
    u8 regsMode;
    u8 padding[1];
    u16 trophyCount[4];
    u32 totalVariantCount; //0x24
    Track tracks[1];
    Variant variants[1];
    //u16 alphabeticalIdx[1]; //slot 0's value = track index of the first track by alphabetical order
};

struct PulBMG {
    static const u32 index = SECTION_BMG;
    BMGHeader header;
};

struct ConfigFile {
    static u32 readBytes;
    void Destroy() {
        memset(this, 0, readBytes);
        delete(this);
    }
    static const char error[];
    static ConfigFile& LoadConfig();
    template <typename T>
    inline const T& GetSection() const {
        const T& section = *reinterpret_cast<const T*>(ut::AddU32ToPtr(this, this->header.offsets[T::index]));
        return section;
    }

    template <class T>
    static inline void CheckSection(const T& t) { if(t.header.magic != T::magic || t.header.version != T::curVersion) Debug::FatalError(error); }

    static const u32 magic = 'PULS';
    BinaryHeader header;
    //InfoHolder infoHolder;
    //CupsHolder cupsHolder;
    //BMGHeader rawBmg;
};

template<>
static inline void ConfigFile::CheckSection<PulBMG>(const PulBMG& bmg) {
    if(bmg.header.magic != 0x4D455347626D6731) Debug::FatalError(error);
}

} //namespace Pulsar

#endif