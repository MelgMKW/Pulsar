#ifndef _RKGD_
#define _RKGD_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>

namespace RKSYS {
#pragma pack(push, 1)

struct RecordEntry {
    u32 finishTime;
    RFL::StoreData miiData;
}; //0x50

struct TrackRecords {
    RecordEntry cr;
    RecordEntry wr;
};

struct CompetitionRecordEntry {
    u32 finishTime;
    u32 unknown_0x4;
    RFL::StoreData miiData;
}; //0x54

struct CompetitionRecords {
    CompetitionRecordEntry cr;
    CompetitionRecordEntry wr;
};



struct RKGD { //+0x23308 to all offsets for rksys
    u32 magic; //RKGD
    u32 settings;
    /*
    0x1         0 GCN Rumble
    0x2         1 Flag display
    0x4         2 drift unknown
    0x8         3 message service
    0x10        4 data sharing
    0x20        5 mii display
    0x40        6 wall unknown
    0x80        7 unknown
    */
    u8 unknown_0x8[10][0x384];
    TrackRecords trackRecords[32]; //0x2330
    CompetitionRecords currentCompetition; //0x3730
    u32 unknown_0x37d8[2][5];
    u16 lastGhostRaceTime; //0x3800 d/m/y
    u16 regionId; //0x3802
}; //0x3804
size_assert(RKGD, 0x3804);
#pragma pack(pop)
}//namespace RKSYS

#endif