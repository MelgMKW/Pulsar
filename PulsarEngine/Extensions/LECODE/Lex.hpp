
#ifndef _LECODE_LEX_
#define _LECODE_LEX_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartMovement.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>

namespace LECODE {
//https://wiki.tockdom.com/wiki/LEX_(File_Format)
struct LEXHeader {
    static const u32 goodMagic = 'LE-X';
    u32 magic;
    u16 majorVersion; //0x4
    u16 minorVersion;
    u32 size; //0x8
    u32 offsetToFirstSection; //0xc
};

struct LEXSectionHeader {
    u32 magic;
    u32 dataSize;
    //char data[];
};

struct SET1 : LEXSectionHeader {
    static const u32 magic = 'SET1';
    Vec3 itemPosFactor;
    bool hasStartingItem;
    u8 padding;
    u16 onlineTime;
};

struct CANN : public LEXSectionHeader {
    static const u32 magic = 'CANN';
    u32 cannonTypesLength;
    Kart::Movement::CannonParams params[1];
};

struct HIPT {
    struct List {
        u8 contextCondition; //1 offline only, 2 online only, 3 both
        s8 lap; //positive = the lap this applies to, negative = the lap starting from the top lap this applies to, so -1 = last lap, 99 = all laps
        u8 cpFrom; //inclusive
        u8 cpTo;
        bool showTracker;
    };
    static const u32 magic = 'HIPT';
    List list[1];
};

struct RITP {
    static const u32 magic = 'RITP';
};

class LexMgr {
    inline void Reset();
public:
    static const KMPHeader* LoadLEXAndKMP(u32, const char* kmpString);
    LEXHeader* lex;
    SET1* set1;
    HIPT::List* hiptList;
    u32 hiptLength;
    Kart::Movement::CannonParams* cann;
};

}//namespace LECODE
#endif