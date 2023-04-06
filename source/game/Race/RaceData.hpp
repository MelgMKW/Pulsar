/*
Racedata is the class that holds the information to set up a race, such as the gamemode and the characters each player chose
Contributors:
    Seeky (main documentation)
    TheLordScruffy (main documentation)
    WhatIsLoaf (ghost player type)
    riidefi (ParameterFile)
    CLF78 (local player count)
References:
    http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
    https://github.com/riidefi/mkw/blob/master/source/game/host_system/ParameterFile.hpp
*/

#ifndef _RACEDATA_
#define _RACEDATA_
#include <kamek.hpp>
#include <core/RK/ParameterFile.hpp>
#include <game/Visual/Mii.hpp>
#include <game/System/Identifiers.hpp>
#define CHARACTERCOUNT 27
#define KARTCOUNT 36

enum PlayerType {
    PLAYER_REAL_LOCAL,
    PLAYER_CPU,
    PLAYER_UNKNOWN2,
    PLAYER_GHOST,
    PLAYER_REAL_ONLINE,
    PLAYER_NONE
};

enum Team {
    TEAM_RED,
    TEAM_BLUE
};

enum BattleType {
    BATTLE_BALLOON,
    BATTLE_COIN
};

enum CpuMode {
    CPU_EASY,
    CPU_NORMAL,
    CPU_HARD,
    CPU_NONE
};

enum GameMode {
    MODE_GRAND_PRIX,
    MODE_VS_RACE,
    MODE_TIME_TRIAL,
    MODE_BATTLE,
    MODE_MISSION_TOURNAMENT,
    MODE_GHOST_RACE,
    MODE_6,
    MODE_PRIVATE_VS,
    MODE_PUBLIC_VS,
    MODE_PUBLIC_BATTLE,
    MODE_PRIVATE_BATTLE,
    MODE_AWARD,
    MODE_CREDITS
};

enum GameType {
    GAMETYPE_TIME_ATTACK = 0x0,
    GAMETYPE_REPLAY = 0x1,
    GAMETYPE_CPU_RACE = 0x5,
    GAMETYPE_ONLINE_SPECTATOR = 0x6,
    GAMETYPE_GP_WIN = 0x7,
    GAMETYPE_VS_WIN = 0x8,
    GAMETYPE_TEAMVS_WIN = 0x9,
    GAMETYPE_BATTLE_WIN = 0xA,
    GAMETYPE_LOSS = 0xC,
};

enum EngineClass {
    CC_50,
    CC_100,
    CC_150,
    CC_BATTLE //Note: Battle mode actually sets it to 50cc (which is ignored by code), but setting it to this in other modes results in Battle CC
};

enum ItemMode {
    ITEMS_BALANCED,
    ITEMS_FRANTIC,
    ITEMS_STRATEGIC,
    ITEMS_NONE
};

struct RacedataSettings {
public:
    CourseId courseId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
    EngineClass engineClass;
    GameMode gamemode;
    GameType gametype;
    BattleType battleType;
    CpuMode cpuMode;
    ItemMode itemMode;
    u8 hudPlayerIds[4];
    u32 cupId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Cups
    u8 raceNumber; //resets at 100 for some reason
    u8 lapCount;
    u8 unknown_0x26;
    u8 unknown_0x27;
    u32 modeFlags; //bit flags:
    /*
        2 is teams enabled
        1 is mirror mode
        Others unknown
    */
    u32 unknown_0x2c;
    u32 unknown_0x30;
}; //Total size 0x34

class RacedataPlayer {
public:
    RacedataPlayer(); //8052d96c
    virtual ~RacedataPlayer(); //8052DC68 vtable 808b3294
    u32 ComputeGPRank(); //8052daf0
    u8 unknown_0x4;
    s8 localPlayerNum;
    s8 realControllerId; //id of the controller at the console for this player, -1 if not controlled by one
    u8 unknown_0x7; //possibly padding
    KartId kartId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles 0x8
    CharacterId characterId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters 0xC
    PlayerType playerType; //0x10
    Mii mii; //0x14
    Team team;
    u8 unknown_0xd0[8];
    u16 previousScore;
    u16 score;
    u8 unknown_0xdc[2];
    s16 gpRankScore;
    u8 unknown_0xe0;
    u8 prevFinishPos;
    u8 unknown_0xe2[6];
    s16 rating; //vr or br, depending on mode
    u8 unknown_0xea[6];
}; //Total size 0xf0

class RacedataScenario {
public:
    explicit RacedataScenario(RKG *rkg); //8052dbc8, never used - racedata's constructor does it inline
    virtual ~RacedataScenario(); //805300f4 vtable 808b3288
    u8 playerCount; //0x4
    u8 screenCount; //0x5 equal to player count except for 3P where it's 4
    u8 localPlayerCount; //0x6
    u8 unknown_0x7;
    RacedataPlayer players[12]; //0x8
    RacedataSettings settings; //0xb48 
    u8 mission[0x70]; //0xB7C 0x70 struct, see http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
    RKG *rkg; //0xBEC Scenario 0 points to the one you race, 1 points to one I'm not sure about, 2 points to null
}; //Total size 0xbf0


//ParameterFile size is 0x1c, Racedata's is /boot/menuset.prm
class EmptyRaceDataParent {
public:
    EmptyRaceDataParent() {};
    //this causes a 2nd vtable after RKParameterFile which is a copy of RKParameter file and would contain any new virtual function in RaceData
};

class RaceData : public EmptyRaceDataParent, public RKParameterFile {
public:
    static RaceData *sInstance; //0x809bd728 presumably private 
    static RaceData *GetStaticInstance(); //8052fe58
    static void DestroyStaticInstance(); //8052ffe8
    RaceData(); //8053015c inlined
    ~RaceData() override; //80530038 vtable 808b3268  for RKParemeterFile and 808b3260 for RaceData itself
    void vf_0x10() override; //80532078 just a blr
    void vf_0x14() override; //80532074 just a blr
    void vf_0x18() override; //80532070 just a blr

    u8 GetLocalPlayerNum(u8 id); //80531f18
    u8 GetHudSlotBytId(u8 id);
    RacedataScenario racesScenario; //0x20
    RacedataScenario menusScenario; //0xc10
    RacedataScenario unknown_scenario; //0x1800
    RKG ghosts[2]; //0x23f0 is the one you're racing, not sure what 1 is
};  //Total size 0x73f0
size_assert(RaceData, 0x73f0);

extern "C" {
    int GetTrackBMGId(CourseId id);
    int CharacterIDToWeightClass(CharacterId id); //0 light 1 medium 2 heavy
    char *CharacterIDToChar(CharacterId id); //80860acc
}
#endif