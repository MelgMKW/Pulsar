#ifndef _RKNETRH1_
#define _RKNETRH1_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>


namespace RKNet {
struct RACEHEADER1Packet {
    u32 timer;
    u32 selectId; //0x4
    u16 team[2]; //0x8
    u16 lagFrames; //0xc
    u16 kartAndCharacter[2]; //0xe treated as a u16 ingame
    u16 countdownTime; //0x12
    u8 starRank[2];
    u8 trackId;         //0x16
    u8 unknown_0x17;
    u8 aidsBelongingToPlayer[12]; //0x18
    u8 engineClass; //0x24
    u8 unknown_0x25[3];
}; //0x28

struct RH1Data {
    u32 timer; //0
    KartId kartIds[2]; //0x4
    CharacterId charIds[2]; //0xc
    CourseId trackId; //0x14
    u32 team; //0x18
    u32 selectId; //0x1c
    u8 aidsBelongingToPlayer[12]; //0x20
    u8 engineClass; //0x2c
    u8 starRank[2]; //0x2d
    u8 padding;
}; //0x30

class RH1Handler {
public:
    static RH1Handler* sInstance; //809c2118
    static void GetStaticInstance(); //80663aa4
    static void DestroyStaticInstance(); //80663c38

    ~RH1Handler(); //80664d9c
    void Reset(); //80663c88
    void Reset(u8 hudSlotId); //8066410c

    bool HasValidCourse(); //806641b0
    KartId GetKart(u8 aid, u8 hudSlotId);
    CharacterId GetCharacter(u8 aid, u8 hudSlotId);
    u8 GetStarRank(u8 aid, u8 hudSlotId); //8066454c
    CourseId GetValidCourse(); //80664560 returns the first found "valid" track ie not random or 0x42/0x43
    u8 GetPlayerCount(); //806647d0
    u32 GetSELECTId(); //80664944 OBVIOUSLY WRONG
    u8 GetEngineClass(); //80664a3c
    u8* GetAidsBelongingToPlayer(); //80664b34
    void ImportNewPackets(); //806651b4
    void ExportDefaultPacket(u32 aid); //806653c8
    void ExportDefaultPacket2(u32 aid); //806653c80665480
    u8 unknown_0x0[0x20];
    RH1Data rh1Data[12]; //0x20
}; //total size 0x260
size_assert(RH1Handler, 0x260);

}//namespace RKNet
#endif