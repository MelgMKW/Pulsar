#ifndef _RKG_
#define _RKG_
#include <kamek.hpp>
#include <game/File/RawMii.hpp>

enum GhostType {
    GHOST_NONE = 0x0,
    BEST_TIME = 0x1,
    WORLD_RECORD = 0x2,
    CONTINENTAL_RECORD = 0x3,
    FLAG_GHOST = 0x4,
    SPECIAL_GHOST = 0x5, //no idea what this is
    GHOST_RACE = 0x6,
    FRIEND_GHOST = 0x24, //from 0x07 to 0x24
    EASY_STAFF_GHOST = 0x25,
    EXPERT_STAFF_GHOST = 0x26
};

struct RKGHeader {
    char magic[4]; //RKGD
    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;
    u32 courseId : 6;
    u32 unknown_1 : 2;
    u32 kartId : 6;
    u32 characterId : 6;
    u32 year : 7;
    u32 month : 4;
    u32 day : 5;
    u32 controllerType : 4;
    u32 unknown_2 : 4; //0xC
    bool compressed : 1;
    u32 unknown_3 : 2;
    GhostType ghostType : 7;
    bool driftType : 1;
    u32 unknown_4 : 1;
    u16 inputSectionLength; //uncompressed length 0xE
    u32 lapCount : 1;
    u8 lapSplits[0x20 - 0x11];
    u8 unknown_5[0x34 - 0x20];
    u8 countryCode;
    u8 stateCode;
    u16 locationCode;
    u32 unknown_0x6; //0x38
    RawMii miiData; //0x3C to 
    u16 miiCRC16;
}; //total size 0x88

struct RKGInputData {
    u16 faceButtonInputsCount;
    u16 directionInputsCount;
    u16 trickInputsCount;
    u16 unknown_0x6; //padding
    u8 unknown_0x8[0x2774 - 0x8]; //idk how to do that in c++
}; //total size 0x2774

struct CompressedRKG {
    RKGHeader header;
    u32 dataLength;
    char magic[4]; //Yaz1
};

class RKG {
public:
    void ClearBuffer(); //8051c088
    bool CheckHeader(); //8051c094 inlined checks magic, character, kart, year, day, month
    bool CheckValidity(); //8051c120
    void DecompressTo(RKG *copyBuffer);
    bool CompressTo(RKG *copyBuffer);
    int GetLength(RKG *src); //8051d388 only if valid
    RKGHeader header;
    RKGInputData data;
    u32 uncompressedCRC32;
};//total size 0x2800

#endif