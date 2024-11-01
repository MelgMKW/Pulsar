#ifndef _SETTINGS_BINARY_
#define _SETTINGS_BINARY_
#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <Config.hpp>

namespace Pulsar {
namespace Settings {

enum SectionIndexes {
    SECTION_PAGES,
    SECTION_MISC,
    SECTION_TROPHIES,
    SECTION_GP
};

struct TrackTrophy {
    u32 crc32;
    bool hastrophy[4];
}; //0x8


struct Page {
    union {
        struct {
            u8 radioSetting[6];
            u8 scrollSetting[6];
        };
        u8 settings[12];
    };
};

struct PagesHolder {
    static const u32 pageMagic = 'PAGE';
    static const u32 version = 1;
    static const u32 index = SECTION_PAGES;
    Pulsar::SectionHeader header;
    u32 pulsarPageCount;
    u32 userPageCount;
    Page pages[1]; //0x14
};

struct MiscParams {
    static const u32 miscMagic = 'MISC';
    static const u32 version = 1;
    static const u32 index = SECTION_MISC;
    Pulsar::SectionHeader header;
    u32 reserved[20]; //0xc
    PulsarCupId lastSelectedCup; //0x5c
    u32 trackCount; //0x60
};

struct TrophiesHolder {
    static const u32 tropMagic = 'TROP';
    static const u32 version = 1;
    static const u32 index = SECTION_TROPHIES;
    Pulsar::SectionHeader header;
    u16 trophyCount[4];
    TrackTrophy trophies[1];
};

struct GPCupStatus {
    u8 gpCCStatus[4]; //one per CC
};
struct GPSection {
    static const u32 gpMagic = 'GP\0\0';
    static const u32 version = 1;
    static const u32 index = SECTION_GP;

    //2 bits for trophy
    //4 bits for rank, 0 to 7
    //3 2 1 a b c d e

    Pulsar::SectionHeader header;
    GPCupStatus gpStatus[1]; //one per cup
};

struct BinaryHeader {
    u32 magic;
    u32 version;
    u32 fileSize;
    u32 sectionCount;
    u32 offsets[1]; //0x10
    //u32 offsetToPages;
    //u32 offsetToMisc;
    //u32 offsetToTrophies;
    //u32 offsetToGP;
};

/*OLD VERSIONS*/
struct BinaryHeaderV1 {
    u32 magic;
    u32 version;
    u32 fileSize;
    u32 offsetToPages;
    u32 offsetToMisc;
    u32 offsetToTrophies;
    u32 offsetToGP;
};

struct PagesHolderV1 {
    static const u32 pageMagic = 'PAGE';
    static const u32 version = 1;
    static const u32 index = SECTION_PAGES;
    Pulsar::SectionHeader header;
    u32 pageCount;
    Page pages[1];
};

class alignas(0x20) Binary {
    static const u32 binMagic = 'PULP';
    static const u32 sectionCount = 4;
    static const u32 curVersion = 4;

    Binary(u32 pulsarPageCount, u32 userPageCount, u32 trackCount);

    template<typename T>
    inline T& GetSection() {
        return *reinterpret_cast<T*>(ut::AddU32ToPtr(this, this->header.offsets[T::index]));
    }
    template<typename T>
    inline const T& GetSection() const {
        return *reinterpret_cast<const T*>(ut::AddU32ToPtr(this, this->header.offsets[T::index]));
    }
    template <class T>
    bool CheckSection(const T& t) { if(t.header.magic != T::magic) return false; return true; }

    BinaryHeader header;
    PagesHolder pages;
    //MiscParams misc;
    //TrophiesHolder trophies;
    friend class Mgr;
};

}//namespace Settings
}//namespace Pulsar

/*CHANGELOG:
-V1 is defunct and was never used

-V2:
*now uses an offset array with each section having its own index
*each section has its size included
*GP section has been added

-V3:
*Pages section now supports user pages

*/


#endif