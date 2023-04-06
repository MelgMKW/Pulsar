#ifndef _SECTIONMGR98_
#define _SECTIONMGR98_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/Visual/Mii.hpp>

struct PlayerCombo {
    CharacterId selCharacter;
    KartId selKart;
    s8 starRank;
    u8 unknown_0x9[0xC - 0x9]; //passing most likely
}; //total size 0xC

class SectionMgr98 {
public:
    SectionMgr98(); //805e2f60
    ~SectionMgr98(); //805e2ff8
    void RandomizeVSTracks(); //805e32ec
    u8 unknown_0x0[0x60];
    u32 raceNumber; //0x60
    u32 vsRaceCount;  //0x64
    u8 unknown_0x68[0x78 - 0x68];
    CourseId vsTracks[32]; //0x78
    u32 vsRaceLimit; //0xf8 based on unlocked cups
    u8 unknown_0xfc[0x124 - 0xfc];
    u32 localPlayerCount; //0x124
    u32 category; //0x128, mainMenu's clicked buttonId, essentially indicated where in the game we are 
    CharacterId characters[4];
    KartId karts[4];
    u32 lastSelectedCourse; //0x14c
    u32 lastSelectedStage; //0x150
    u8 unknown_0x154[0x188 - 0x154];
    MiiGroup playerMiis; //0x188
    PlayerCombo combos[2]; //0x220
    MiiGroup localPlayerMiis; //0x238
    u32 currentRaceNumber; //0x2D0
    u8 unknown_0x2D4[0x3C4 - 0x2D4];
    GhostType ghostType;
    CourseId courseId; //0x3c8
    u32 licenseId;
    bool isNewTime; //0x3d0
    u8 unknown_0x3D1[3];
    u32 fastestLapId; //0x3d4 simply which lap is the fastest
    bool unknown_0x3D8; //0x3D8 unsure
    u8 unknown_0x3D9[0x4B4 - 0x3d9];
    s32 leaderboardPosition; //0x4B4
    u8 unknown_0x4B8[0x4E8 - 0x4B8];
    u8 licenseNum;
    u8 unknown_0x4e9[0x510 - 0x4E9];
}; //Total Size 0x510
size_assert(SectionMgr98, 0x510);

#endif