#ifndef _KMG_
#define _KMG_
#include <kamek.hpp>


typedef u16 ParameterTable[10][11]; //1st dimension is BattleStage idx, 2nd is playerCount
struct KMGHeader { //https://wiki.tockdom.com/wiki/KMG_(File_Format)
    char magic[4]; //RKMG
    u32 fileSize;
    u32 unknown_0x8;
    u32 maxHiddenScore; //0x4
    u16 entryCount;
    u16 headerSize;
};//total size 0x20

struct BalloonParameters {
    u16 ptsPerHit;
    u16 ptsPerPlayerKill; //unused, extra pts when "killing" = getting rid of the last balloon of a player
    u16 ptsWhenDying;
    u16 ptsWhenHit; //unused
    u16 ptsPerFriendHit; //unused, friendly fire
    u16 ptsWhenFriendHit;
    u16 unknownSeconds[3];
    u16 unknown_0x12;
}; //0x14

struct CoinParameters {
    u16 unknown[3];
    u16 unknownSeconds[3];
    u16 unknown_2;
    u16 minCoinLossOnOob;
    u16 minCoinLossOnHit;
    u16 coinLossPercent;
}; //0x14

struct KMG {
    KMGHeader header;
    ParameterTable balloonTimeLimit;
    ParameterTable unknown;
    BalloonParameters balloonParams;
    ParameterTable coinTimeLimit;
    ParameterTable unknown_2;
    ParameterTable coinStartCount;
    ParameterTable coinMaxCount;
    ParameterTable unknown_3;
    ParameterTable unknown_4;
    CoinParameters coinParams;
};

#endif