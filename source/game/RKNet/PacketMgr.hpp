#ifndef _RKNETPACKETMGR_
#define _RKNETPACKETMGR_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/RKNet/EVENT.hpp>
#include <game/RKNet/ITEM.hpp>
#include <game/RKNet/RH1.hpp>
#include <game/RKNet/RACEDATA.hpp>
#include <game/RKNet/RH2.hpp>


namespace RKNet {




class PacketMgr {
public:
    static PacketMgr* sInstance; //809c1f50
    static PacketMgr* GetStaticInstance(); //80653208
    static void DestroyStaticInstance(); //80653284
    PacketMgr(); //80653df4
    ~PacketMgr(); //80653ecc
    void Reset(); //806532d8
    void Update(); //80653728

    void ExportRACEDATA(RACEDATAPacket& racedataPacket); //80653960
    RACEDATAPacket& GetRACEDATA(u8 playerId); //80653abc 
    void ExportRH2(RACEHEADER2Packet& rh2Packet); //80653c08
    RACEHEADER2Packet& GetRH2(u8 playerId); //80653cb8
    void ClearSentRACEDATA(); //80653d14
    void ClearSentRH2(); //80653d78

    void ProcessPlayerDC(u32 dcedAid); //80653ddc

    void UpdateAsRacer(); //80653f24
    void UpdateAsSpectator(); //80654150
    bool EveryoneIsConnected(); //80654038 Controller's IsConnectedToAnyone OR raceInfo stateflag of a player has 0x10 (dced)
    u32 GetPlayerRH1Timer(u32 playerId) const; //806544a8
    u16 GetPlayerLagFrames(u32 playerId) const; //80654568
    u32 GetMaxRH1Timer(u32 playerId) const; //806545dc
    void SetPlayerITEMItem(u8 playerId, ItemId itemId); //8065471c
    bool IsITEMItemNew() const; //80654734
    ItemId GetITEMStoredItem(u8 playerId) const; //80654740
    void AddEVENTEntry(ItemObjId itemObjId, EVENTAction action, void* data, u32 dataLength); //8065474c creator
    bool HasFreeEVENTEntries() const; //80654758
    int GetFreeEVENTEntriesCount() const; //80654764
    int GetEVENTFreeDataSpace() const; //80654810
    bool IsPlayerConnected(u32 playerId) const; //80654820
    bool IsPlayerLocal(u32 playerId) const; //806548a8
    u32 GetHudSlotId(u32 playerId) const; //80654918
    void UpdateRaceInfoConnectionStatus(); //80654984
    void ProcessLagFrames(); //80654b00
    void CreateAndExportRH1andUSER(); //80655164
    void CreateRH1AndExportRH1andUSERandRACEDATA(); //80654d08
    void ProcessReceived(); //806554a0
    void UpdateAidsBitfields(); //8065574c


    u8 unknown_0x0;
    bool isSomoneLagging;
    u8 unknown_0x2[2];
    u32 aidsWithSelectId;
    u32 aidsWithNewROOMorSELECT;
    u32 unknown_0xC;
    u16 localLagFrames;
    u16 countdownTime;
    RACEDATAPacket sendRACEDATABuffers[2]; //0x14
    EVENTPacket sendEVENTBuffer; //0x94
    u8 unknown_0x18c[4];
    u64 lastFriendUpdateTime;
    u32 playerRH1Timers[12];
}; //total size 0x1c8
size_assert(PacketMgr, 0x1c8);
}//namespace RKNet
#endif