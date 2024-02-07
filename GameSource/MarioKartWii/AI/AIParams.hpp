#ifndef _AIPARAMS_
#define _AIPARAMS_
#include <kamek.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>

struct BinAIParamAction {
    float probRocketBoost;
    float probBurnout;
    float probStartDrift;
    float probGettingMT;
    float probTrick;
    float probWheelie;
    float unknown_0x18[2];
};




struct BinAIParamSpeed {
    float speedAdvantage;
    float speedBias;
    float baseSpeed;
};

struct CourseBinAIParamSpeed {
    BinAIParamSpeed speed;
    float parameter;
    float difficulty;
};

struct CommonBinAIParamSpeed { //https://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/kartAISpdParam.bin
    BinAIParamSpeed gpEntries[32][4]; //2nd row is CC
    BinAIParamSpeed vsEntries[4][32][3]; //CC, track slot, difficulty
};

struct CommonBinAIParamAction {
    BinAIParamAction actions[3][12]; //2nd row is playerId
};

namespace AI {
struct ParamAction {
    u8 probRocketBoost;
    u8 probBurnout;
    u8 probStartDrift;
    u8 probGettingMT;
    u8 probTrick;
    u8 probWheelie;
    u8 unknown_0x6[2];
}; //0x8

class Params {
public:
    typedef BinAIParamSpeed ParamSpeed;
    Params(u32 aiDifficulty); //8073ab68
    ParamSpeed* GetParamSpeed() const; //8073ac80
    ParamAction* GetParamAction(u8 playerIdx) const; //8073ac88
    static void LoadParamFile(ArchiveSource type, const char* path); //8073ac98
    void Load(); //8073aca8
    void LoadActions(CommonBinAIParamAction& rawActions, u32 difficulty); //8073b020
    virtual ~Params(); //8073abf8 vtable 808cb008
    ParamSpeed* speed;
    ParamAction* actions; //array of size 12
    u32 parameter;
    u32 difficulty;
}; //0x14

} //namespace AI

#endif