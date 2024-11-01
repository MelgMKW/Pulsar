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
#include <MarioKartWii/Mii/Mii.hpp>
#include <MarioKartWii/File/RKG.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/System/Rating.hpp>

class RacedataPlayer {
public:
    RacedataPlayer(); //8052d96c

    virtual ~RacedataPlayer(); //8052DC68 vtable 808b3294
    void RegisterPlayerParams(RKParameterFile& paramFile); //8052da50 inlined in Racedata::init
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
    void ResetScores(); //8052e640
    //u8 GetPrevFinishPos(); //8052e44c


    u8 unknown_0x4;
    s8 hudSlotId; //0x5
    s8 realControllerChannel; //id of the controller at the console for this player, -1 if not controlled by one
    u8 unknown_0x7; //possibly padding
    KartId kartId; //0x8 http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles
    CharacterId characterId; //0xC http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters
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
    u8 finishPos; //0xe2
    u8 unknown_0xe3;
    Rating rating; //0xe4 vr or br, depending on mode
    u8 unknown_0xec[4];
}; //Total size 0xf0
size_assert(RacedataPlayer, 0xf0);

struct RacedataSettings { //0xb68 for race scenario, 0x1758 for menu
public:
    CourseId courseId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
    EngineClass engineClass; //0x4
    GameMode gamemode; //0x8
    GameType gametype; //0xc
    BattleType battleType; //0x10
    CpuMode cpuMode; //0x14
    ItemMode itemMode; //0x18
    u8 hudPlayerIds[4]; //0x1c
    u32 cupId; //http://wiki.tockdom.com/wiki/List_of_Identifiers#Cups
    u8 raceNumber; //0x24 resets at 100 for some reason
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
    u32 randomSeed; //0x30 for raceinfo
}; //Total size 0x34

class RacedataScenario {
public:
    explicit RacedataScenario(RKG& rkg); //8052dbc8, never used - racedata's constructor does it inline
    virtual ~RacedataScenario(); //805300f4 vtable 808b3288
    RacedataScenario& operator=(const RacedataScenario& rhs); //805305ac
    void Init(const RacedataScenario* prev); //8052fb90 prev can be Race if this is Menu
    void InitCompetitionSettings(); //8052fa0c
    void UpdateFromPrevRace(); //8052f1e0 prev positions + next GP race
    void ComputePlayerCounts(u8* playerCount, u8* screenCount, u8* localPlayerCount) const; //8052f788
    void InitScreens(u8 screenCount); //8052f4e8
    void InitGhostPlayer(u8 id, u8 realControllerId); //8052eef0
    void InitControllers(const RacedataScenario* prev); //8052ed28 prev used for TT replays
    void InitRNG(); //8052f924
    void UpdatePoints(); //8052e950

    GameType GetGameType() const; //8052ed18
    RacedataPlayer* GetPlayer(u8 idx); //8052e434
    const RacedataPlayer* GetPlayer(u8 idx) const; //8052dd20
    bool AreTeamsEnabled() const; //80530f0c
    bool BlueTeamHasMorePoints() const; //8052dca8
    void RegisterParamsToRKParameter(RKParameterFile& rkParamFile); //80531de4

    u8 playerCount; //0x4
    u8 screenCount; //0x5 equal to player count except for 3P where it's 4
    u8 localPlayerCount; //0x6
    u8 unknown_0x7;
    RacedataPlayer players[12]; //0x8
    RacedataSettings settings; //0xb48 
    u8 mission[0x70]; //0xB7C 0x70 struct, see http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
    RKG* rkg; //0xBEC Scenario 0 points to the one you race, 1 points to one I'm not sure about, 2 points to null
}; //Total size 0xbf0
size_assert(RacedataScenario, 0xbf0);

//ParameterFile size is 0x1c, Racedata's is /boot/menuset.prm
class EmptyRacedataParent {
public:
    EmptyRacedataParent() {};
    //this causes a 2nd vtable after RKParameterFile which is a copy of RKParameter file and would contain any new virtual function in Racedata
};

class Racedata : public EmptyRacedataParent, public RKParameterFile {
public:
    static Racedata* sInstance; //809bd728 presumably private 
    static Racedata* CreateInstance(); //8052fe58
    static void DestroyInstance(); //8052ffe8
    Racedata(); //8053015c inlined
    ~Racedata() override; //80530038 vtable 808b3268  for RKParemeterFile and 808b3260 for Racedata itself
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
    u32 GetPlayerIdOfLocalPlayer(u8 hudSloftId) const; //80531f70
    void SetGhost(const RKG& rkg); //80531f2c
    void LoadNextGPTrack(); //80531f80
    bool IsTTReplay() const; //80532030

    RacedataScenario racesScenario; //0x20
    RacedataScenario menusScenario; //0xc10
    RacedataScenario awardScenario; //0x1800
    RKG ghosts[2]; //0x23f0 is the one you're racing, not sure what 1 is

    static const u8 pointsRoom[12][12]; //80890030 12-sized array per room size, so add 12 * (size - 1) to the ptr to get to the wanted roomsize
};  //Total size 0x73f0
size_assert(Racedata, 0x73f0);




#endif