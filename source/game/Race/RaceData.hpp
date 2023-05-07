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
    GAMETYPE_LOSS = 0xC
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

enum GPRank {
    GPRANK_3STARS,
    GPRANK_2STARS,
    GPRANK_1STAR,
    GPRANK_A,
    GPRANK_B,
    GPRANK_C,
    GPRANK_D,
    GPRANK_E
};

class RaceDataPlayer {
public:
    RaceDataPlayer(); //8052d96c

    virtual ~RaceDataPlayer(); //8052DC68 vtable 808b3294
    void Init(); //8052efd4
    GPRank ComputeGPRank(); //8052daf0 from hiddenScore

    void SetKartId(KartId kart); //8052e444
    void SetCharacterId(CharacterId character); //8052e42c
    void SetPlayerType(PlayerType type); //8052e44c
    void SetPrevFinishPos(u8 prevPos); //8052e658
    void SetMii(Mii* mii); //80530f30

    KartId GetKartId() const; //80530f28
    CharacterId GetCharacterId() const; //80530f20
    PlayerType GetPlayerType() const; //8052ed20
    Mii* GetMii() const; //80531068
    Team GetTeam() const; //8052dd18
    //u8 GetPrevFinishPos(); //8052e44c


    u8 unknown_0x4;
    s8 hudSlotId; //0x5
    s8 realControllerChannel; //id of the controller at the console for this player, -1 if not controlled by one
    u8 unknown_0x7; //possibly padding
    KartId kartId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles 0x8
    CharacterId characterId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters 0xC
    PlayerType playerType; //0x10
    Mii mii; //0x14
    Team team; //0xcc
    ControllerType controllerType; //0xd0 from Controller::GetType
    u8 unknown_0xd4[4];
    u16 previousScore; //0xd8
    u16 score; //0xda
    u8 unknown_0xdc[2]; //0xdc
    s16 gpHiddenScore; //0xde
    u8 unknown_0xe0;
    u8 prevFinishPos; //0xe1
    u8 unknown_0xe2[6];
    s16 rating; //vr or br, depending on mode
    u8 unknown_0xea[6];
}; //Total size 0xf0

struct RacedataSettings {
public:
    CourseId courseId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
    EngineClass engineClass; //0x4
    GameMode gamemode; //0x8
    GameType gametype; //0xc
    BattleType battleType; //0x10
    CpuMode cpuMode;
    ItemMode itemMode;
    u8 hudPlayerIds[4];
    u32 cupId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Cups
    u8 raceNumber; //resets at 100 for some reason
    u8 lapCount; //0x25
    u8 unknown_0x26;
    u8 unknown_0x27;
    u32 modeFlags; //bit flags:
    /*
        4 is competition?
        2 is teams enabled
        1 is mirror mode
        Others unknown
    */
    u32 selectId;
    u32 randomSeed; //for raceinfo
}; //Total size 0x34

class RacedataScenario {
public:
    explicit RacedataScenario(RKG& rkg); //8052dbc8, never used - racedata's constructor does it inline
    virtual ~RacedataScenario(); //805300f4 vtable 808b3288
    RacedataScenario& operator=(const RacedataScenario& rhs); //805305ac
    void Init(const RacedataScenario* prev); //8052fb90 prev can be Race if this is Menu
    void InitCompetitionSettings(); //8052fa0c
    void UpdateFromPrevRace(); //8052f1e0 prev positions + next GP race
    void ComputePlayerCounts(u8* playerCount, u8* screenCount, u8* localPlayerCount); //8052f788
    void InitScreens(u8 screenCount); //8052f4e8
    void InitGhostPlayer(u8 id, u8 realControllerId); //8052eef0
    void InitControllers(const RacedataScenario* prev); //8052ed28 prev used for TT replays
    void InitRNG(); //8052f924
    void UpdatePoints(); //8052e950

    GameType GetGameType() const; //8052ed18
    RaceDataPlayer* GetPlayer(u8 idx); //8052e434
    const RaceDataPlayer* GetPlayer(u8 idx) const; //8052dd20
    bool AreTeamsEnabled() const; //80530f0c
    bool BlueTeamHasMorePoints() const; //8052dca8
    void RegisterParamsToRKParameter(RKParameterFile& rkParamFile); //80531de4

    u8 playerCount; //0x4
    u8 screenCount; //0x5 equal to player count except for 3P where it's 4
    u8 localPlayerCount; //0x6
    u8 unknown_0x7;
    RaceDataPlayer players[12]; //0x8
    RacedataSettings settings; //0xb48 
    u8 mission[0x70]; //0xB7C 0x70 struct, see http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
    RKG* rkg; //0xBEC Scenario 0 points to the one you race, 1 points to one I'm not sure about, 2 points to null
}; //Total size 0xbf0


//ParameterFile size is 0x1c, Racedata's is /boot/menuset.prm
class EmptyRaceDataParent {
public:
    EmptyRaceDataParent() {};
    //this causes a 2nd vtable after RKParameterFile which is a copy of RKParameter file and would contain any new virtual function in RaceData
};

class RaceData: public EmptyRaceDataParent, public RKParameterFile {
public:
    static RaceData* sInstance; //0x809bd728 presumably private 
    static RaceData* GetStaticInstance(); //8052fe58
    static void DestroyStaticInstance(); //8052ffe8
    RaceData(); //8053015c inlined
    ~RaceData() override; //80530038 vtable 808b3268  for RKParemeterFile and 808b3260 for RaceData itself
    void vf_0x10() override; //80532078 just a blr
    void vf_0x14() override; //80532074 just a blr
    void vf_0x18() override; //80532070 just a blr

    static u8 GetPlayerCount(); //8052dd30
    void Init(); //8052dd40
    void InitRace(); //805302c4, Inits MenusScenario, then copies to Races "CopyMenuToInRace"
    void InitAwards(); //80530864
    void InitCredits(); //80531070
    void ResetScenarios(); //8052e454
    u8 UpdatePrevFromCur(); //80531ce4 return new race number

    u8 GetHudSlotId(u8 playerId) const; //80531f18
    u8 GetPlayerIdOfLocalPlayer(u8 hudSlotId) const;
    void SetGhost(RKG* rkg); //80531f2c
    void LoadNextGPTrack(); //80531f80
    bool IsTTReplay() const; //80532030

    RacedataScenario racesScenario; //0x20
    RacedataScenario menusScenario; //0xc10
    RacedataScenario unknown_scenario; //0x1800
    RKG ghosts[2]; //0x23f0 is the one you're racing, not sure what 1 is
};  //Total size 0x73f0
size_assert(RaceData, 0x73f0);

extern "C" {
    int GetTrackBMGId(CourseId id);
    int CharacterIDToWeightClass(CharacterId id); //0 light 1 medium 2 heavy
    char* CharacterIDToChar(CharacterId id); //80860acc
}
#endif