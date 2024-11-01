#ifndef _SECTIONPARAMS_
#define _SECTIONPARAMS_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/MII/MiiGroup.hpp>

struct PlayerCombo {
    CharacterId selCharacter;
    KartId selKart;
    s8 rank; //as displayed on top of the player name
    u8 unknown_0x9[0xC - 0x9]; //padding most likely
}; //total size 0xC

struct OnlineParams { //+0x2d0 for params offsets
    void ResetRaceNumberAndCC(); //805e3b98
    void Reset(); //805e3ba8
    static u8 CalcRank(u8 wheelType, u8 starRank); //805e3d38
    void SetRankBMG(u8 playerId, u8 starRank); //805e3d48
    s32 currentRaceNumber; //0x0
    u32 engineClass; //0x4 none, 100, 150, mirror same as SELECT
    u8 friendIdx[12]; //0x8 0xff if not a friend or playerId == one of local playerIds
    Team team[12][2]; //0x14 aid, playerId
    u8 unknown_0x74[0x8c - 0x74];
    u32 rankBMG[12]; //0x8c
    u32 regionId[12]; //0xbc 0=NTSC-J, 1=NTSC-U, 2=PAL/EUR, 3=PAL/AUS, 4=Taiwan 5=South Korea F=None
};
size_assert(OnlineParams, 0xec);

struct TitleParams { //+0x4cc for params
    TitleParams(); //805e3dc8 inlined
    void Reset(); //805e3dfc and changes the next
    void ForceDemo(); //805e3fc
    bool isNextEventTitleTHP; //0
    u8 padding[3];
    GameType nextDemoType; //0x4
    GameMode nextDemoMode; //0x8 only works with vs and battle
    BattleType nextDemoBattleType;
    GameType prevDemoType; //0x10
    CourseId demoCourse; //0x14
    CourseId demoArena; //0x18
}; //0x1c

class SectionParams {
public:

    SectionParams(); //805e2f60
    ~SectionParams(); //805e2ff8

    void Reset(); //805e307c
    void ResetMiisGhostsAndSub(); //805e3224
    void ResetBattleParams(); //805e32ac
    void SetVStracks(CourseId initial); //805e346c does NOT randomize them, rather puts them in order
    static bool IsCourseUnlockedInOneCC(CourseId id); //805e372c
    static bool IsCupUnlockedInOneCC(u32 cupIdx); //805e37b0

    void RandomizeBattleArenas(); //805e32ec
    void SetBattleArenas(CourseId initial); //805e38fc does NOT randomize them, rather puts them in order
    static CourseId TrackIdxToCourseId(int idx); //805e3f68 not quite sure why we can't idxToCourseId[idx]
    static u32 CourseIdToTrackIdx(CourseId id); //805e3fa0
    static u32 CourseIdToCupIdx(CourseId id); //805e3ff8
    static u32 ArenaIdToCupIdx(CourseId id); //805e3ff8

    void ResetLicenseParams(); //805e40a8 character, kart, etc...
    static CourseId idxToCourseId[42]; //80895238

    void CopyMiisToRacedata(); //805e39d8
    void RandomizeVSTracks(); //805e32ec
    void ChangeLicense(); //805e40a8


    u8 unknown_0x0[0x60];
    u32 vsRaceNumber; //0x60
    u32 vsRaceCount;  //0x64
    u32 redWins; //0x68
    u32 blueWins; //0x6c
    Team lastBattleWinningTeam; //0x70
    u32 kartsDisplayType; //0x74 0 = only karts, 1 = only bikes, 2 = all
    CourseId vsTracks[32]; //0x78 offline
    u32 vsRaceLimit; //0xf8 based on unlocked cups
    CourseId battleArenas[10]; //0xfc offline
    u32 localPlayerCount; //0x124
    u32 category; //0x128, mainMenu's clicked buttonId, essentially indicated where in the game we are 
    CharacterId characters[4]; //0x12c 
    KartId karts[4]; //0x13c
    u32 lastSelectedCourse; //0x14c
    u32 lastSelectedArena; //0x150
    u8 unknown_0x154[0x10];
    u32 driftType[4]; //0x164
    u32 isOddLicense[4]; //0x174 https://decomp.me/scratch/ai0iE
    u8 unknown_0x184[4];
    MiiGroup playerMiis; //0x188
    PlayerCombo combos[2]; //0x220
    MiiGroup localPlayerMiis; //0x238
    OnlineParams onlineParams; //0x2d0
    u8 unknown_0x3bc[0x8]; //0x3bc
    GhostType ghostType; //0x3c4
    CourseId courseId; //0x3c8
    u32 licenseId; //0x3cc
    bool isNewTime; //0x3d0
    u8 unknown_0x3D1[3];
    u32 fastestLapId; //0x3d4 simply which lap is the fastest
    bool unknown_0x3D8; //0x3D8 unsure
    u8 unknown_0x3D9[0x4B4 - 0x3d9];
    s32 leaderboardPosition; //0x4B4
    u8 unknown_0x4B8[0x4c0 - 0x4B8];
    bool hasNewFriendChallenge; //0x4c0
    u8 unknown_0x4c1[0x4cc - 0x4c1];
    TitleParams titleParams; //0x4cc
    u8 licenseNum; //0x4e8
    u8 unknown_0x4e9[0x508 - 0x4E9];
    u32 friendIdxJoinedViaChannel; //0x508
    u8 unknown_0x50c[4];
}; //Total Size 0x510
size_assert(SectionParams, 0x510);

#endif