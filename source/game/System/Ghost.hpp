#ifndef _GHOST_
#define _GHOST_

#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <game/File/RKG.hpp>
#include <game/System/identifiers.hpp>
#include <game/System/Timer.hpp>

enum GhostGroupType {
    GROUP_SAVED,
    GROUP_DOWNLOADED,
    GROUP_EASY_STAFF,
    GROUP_EXPERT_STAFF,
    GROUP_GHOST_RACE,
    GROUP_COMPETITION,
    GROUP_NONE = 0xFF
};



class GhostData {
public:
    GhostData(); //8051c270
    explicit GhostData(RKG *rkg); //8051c398
    ~GhostData(); //8051cf90
    void Init(RKG *src); //8051c790
    bool ReadRKG(RKG *src); //8051c530
    void Fill(u32 playerId); //8051cb1c fills based on racedata
    bool CreateRKG(RKG *dest); //8051ca80
    bool CreateRKGWithoutInputs(RKG *dest); //8051ca0c this assumes RKG is already filled with inputs?
    void FillHeader(RKG *dest); //8051c7f4
    void Reset(); //8051c4a0

    bool isValid; //0x0
    u8 padding;
    wchar_t userData[11]; //emulating wide chars
    RawMii miiData; //0x4A
    u8 lapCount;
    u8 unknown_0x65[3];
    Timer lapTimes[5]; //0x68
    Timer finishTime; //0xA4
    CharacterId characterId; //0xB0
    KartId kartId; //0xB4
    CourseId courseId; //0xB8
    ControllerId controllerId; //0xBC
    u8 year; //0xC0
    u8 month; //0xC1
    u8 day; //0xC2
    u8 unknown_0xC3;
    GhostType type; //0xC4
    bool isDriftAuto; //0xC8
    u8 unknown_0xc9[3];
    u32 nationality; //0xCC
    u32 inputSize; //0xD0
    void *inputs; //0xD4
}; //total size 0xd8

class GhostGroup {
public:
    GhostGroup(EGG::Heap *heap, u32 type); //0x8051ce94 vtable 808b2d38
    virtual ~GhostGroup(); //8051cff8
    void DisableGhostData(u16 id); //8051d064 set isValid to false
    GhostData *GetGhostData(u16 id); //8051d084 only if valid
    bool ReadRKG(u16 id, RKG *src); //8051d0bc

    u16 count; //depends on type
    u8 unknown_0x6[2];
    GhostGroupType ghostType;  //saved 0, downloaded 1, easy 2, expert 3, ghost race 4, competition 5
    GhostData *files; //0xC size count
    bool *hasLoaded; //0x10 size count
}; //total size 0x14

#endif