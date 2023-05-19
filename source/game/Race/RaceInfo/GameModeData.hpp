
#ifndef _GAMEMODEDATA_
#define _GAMEMODEDATA_
#include <kamek.hpp>
#include <game/File/KRT.hpp>
#include <game/System/Timer.hpp>
#include <game/KMP/KMPController.hpp>
#include <game/RKNet/RH2.hpp>

class RaceInfo;
class GMData { //Abstract
public:
    virtual bool CanRaceEnd() = 0;
    virtual void UpdateLocalPlayers(); //0xc 80535de8
    virtual void Update(); //0x10 80535e84 
    virtual void HandlePositionTracking(); //0x14 805336d8
    virtual const KMP::JGPTHolder* GetRespawnPoint(u8 playerId); //0x18 80535ef4
    virtual void Init(); //0x1c 8053308c
    virtual void vf_0x20(); //0x20 80533be8
    virtual void vf_0x24(); //0x24 80533c34
    virtual void vf_0x28(); //0x28 805371a4
    RaceInfo* raceinfo;
}; //Total size 0x8

class GMDataGP: public GMData {
    GMDataGP(RaceInfo* raceinfo); //80532124 inlined
    bool CanRaceEnd() override; //0x8 80535f28 vtable 808b344c
    void Update() override; //0x10 80535fe4
    KRT* rawKRT; //0x8 ranktimeGP.krt
}; //0xc

class GMDataVS: public GMData {
    bool CanRaceEnd() override; //0x8 80536054 vtable 808b3420
}; //0x8

class GMDataTT: public GMData { //also used 
    bool CanRaceEnd() override; //0x8 80536054 vtable 808b3478
}; //0x8

class GMDataBattle: public GMData {
    void HandlePositionTracking() override; //0x14 80538418
    KMP::JGPTHolder* GetRespawnPoint(u8 playerId) override; //0x18 805391e4
    void Init() override; //0x1c 80538fec
    virtual void OnItemCollision(u8 playerIdSubject, u8 playerIdUser) = 0; //0x2c user = who used the item who collided
    virtual void OnKartCollision(u8 playerIdCollided, u8 playerIdCollider) = 0; //0x30
    virtual void OnOOBCollision(u8 playerId) = 0; //0x34
    virtual void OnObjectCollision(u8 playerId) = 0; //0x38
    virtual void vf_0x3c(); //0x3c 8053d8b8
    virtual u16 GetKMGSeconds1() = 0; //0x40
    virtual u16 GetKMGSeconds2() = 0; //0x44
    virtual u16 GetKMGSeconds3() = 0; //0x48
    u32 unknown_0x8;
    u16 curRespawnPoint; //0xc
    u8 unknown_0xa[2];
    u16 curRespawnRangeScale; //0xe
    u8 unknown_0x10[0x38 - 0x10];
}; //0x38

class GMDataBalloonBattle: public GMDataBattle {
    bool CanRaceEnd() override; //0x8 80539770 vtable 808b36e4
    void Update() override; //0x10 80539574  
    void OnItemCollision(u8 playerIdSubject, u8 playerIdUser) override; //0x2c 80538770 handles balloon loss
    void OnKartCollision(u8 playerIdCollided, u8 playerIdCollider) override; //0x30 80538994 handles balloon steal
    void OnOOBCollision(u8 playerId) override; //0x34 80538bc0
    void OnObjectCollision(u8 playerId) override; //0x38 80538ce0
    u16 GetKMGSeconds1() override; //0x40 8053d954
    u16 GetKMGSeconds2() override; //0x44 8053d938
    u16 GetKMGSeconds3() override; //0x48 8053d91c
}; //0x38

class GMDataCoinBattle: public GMDataBattle {
    bool CanRaceEnd() override; //0x8 80539a84 vtable 808b3698
    void Update() override; //0x10 80539824 
    void OnItemCollision(u8 playerIdxSubject, u8 playerIdxUser) override; //0x2c 80539a90 handles coin loss
    void OnKartCollision(u8 playerIdCollided, u8 playerIdCollider) override; //0x30 80539b30 handles coin steal
    void OnOOBCollision(u8 playerId) override; //0x34 80539be8
    void OnObjectCollision(u8 playerId) override; //0x38 8053d8bc
    u16 GetKMGSeconds1() override; //0x40 8053d8f8
    u16 GetKMGSeconds2() override; //0x44 8053d8dc
    u16 GetKMGSeconds3() override; //0x48 8053d8c0
}; //0x38

class GMDataOnlineVSPlayer {
public:
    GMDataOnlineVSPlayer(); //80532488
    ~GMDataOnlineVSPlayer(); //805324ac
    Timer raceFinishTime;
    u8 unknown_0xc[0x14 - 0xc];
}; //Total size 0x14

class RH2Packer { //808b33c0, 808b3390, 808b33a8, 808b3378, 808b3360, 808b33f0
    virtual ~RH2Packer();
    virtual void Pack(RKNet::RACEHEADER2Packet* packet, u32 r5);
    virtual int Unpack(RKNet::RACEHEADER2Packet* packet, u32 r5);
    virtual int GetParamSize();
}; //0x8

class RH2IntPacker: public RH2Packer {
public:
    ~RH2IntPacker() override;
    void Pack(RKNet::RACEHEADER2Packet* packet, u32 r5) override;
    int Unpack(RKNet::RACEHEADER2Packet* packet, u32 r5) override;
    int GetParamSize() override;
    int param;
};




class GMDataOnlineVS: public GMData {
public:
    bool CanRaceEnd() override; //0x8 8053fa10 vtable 808b3928
    void UpdateLocalPlayers() override; //0xc 8053fb98
    void Update() override; //0x10 8053f2a4
    void HandlePositionTracking() override; //0x14 8053f4a0
    void Init() override; //0x1c 8053e370
    void vf_0x24() override; //0x24 8053fb38
    GMDataOnlineVSPlayer players[12];
    RKNet::RACEHEADER2Packet rh2Packet; //0xf8
    u8 unknown_0x120[0xc];
    RH2Packer packers[9]; //one for each RH2 value? hold the RH2 values as well as a packing parameter (the size of the value?)
}; //Total size 0x174

class GMDataOnlineBalloonBattle: public GMDataBattle {
public:
    GMDataOnlineBalloonBattle(RaceInfo* raceinfo); //80539f88
    bool CanRaceEnd() override; //0x8 8053d914 vtable 808b3570
    void Update() override; //0x10 8053bbf4
    void Init() override; //0x1c 80539c3c
    void vf_0x28() override; //0x28 8053d3a0
    void OnItemCollision(u8 playerIdSubject, u8 playerIdUser) override; //0x2c 8053b4cc
    void OnKartCollision(u8 playerIdCollided, u8 playerIdCollider) override; //0x30 8053b584 handles balloon steal
    void OnOOBCollision(u8 playerId) override; //0x34 8053b63c
    void OnObjectCollision(u8 playerId) override; //0x38 8053b7a4
    void vf_0x3c() override; //0x3c 8053b6e8
    u16 GetKMGSeconds1() override; //0x40 805391dc
    u16 GetKMGSeconds2() override; //0x44 80538f50
    u16 GetKMGSeconds3() override; //0x48 80538f58
    u8 unknown_0x38[0x108 - 0x38]; //bunch of ptrs
    Timer timer; //0x108
    u8 unknown_0x114[0x170 - 0x114];
};//0x170

class GMDataOnlineCoinBattle: public GMDataCoinBattle {
public:
    void Update() override; //0x10 8053d428 vtable 808b3524
}; //0x38

typedef GMDataTT GMDataAwards;
typedef GMDataTT GMDataCredits;
#endif