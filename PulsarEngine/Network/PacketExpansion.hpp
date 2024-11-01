#ifndef _PUL_NETWORK_EXPANSION_
#define _PUL_NETWORK_EXPANSION_

#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKNet/SELECT.hpp>
#include <MarioKartWii/RKNet/EVENT.hpp>
#include <MarioKartWii/RKNet/ROOM.hpp>
#include <MarioKartWii/RKNet/ITEM.hpp>
#include <MarioKartWii/RKNet/RACEDATA.hpp>
#include <MarioKartWii/RKNet/RH1.hpp>
#include <MarioKartWii/RKNet/RH2.hpp>
#include <MarioKartWii/RKNet/USER.hpp>

/*
Each section has its own way of transmitting the extra data for now:
-SELECT and ROOM use BeforeSend/AfterReception hooks, located at the Export/Import functions of the respective Handlers
-RH1 is done on the fly
*/

namespace Pulsar {
namespace Network {

#pragma pack(push, 1)
struct PulPlayerData { //SELECT struct
    u16 pulCourseVote; //0x0 swapped with rank
    u16 sumPoints; //0x2
    u8 character; //0x4
    u8 kart; //0x5
    u8 prevRaceRank; //0x6 swapped with coursevote
    u8 starRank; //0x8 1st bit of 2nd p is also used to specify customPacket
}; //total size 0x8
size_assert(PulPlayerData, 0x8);


struct PulRH1 : public RKNet::RACEHEADER1Packet {

    //Pulsar data
    u16 pulsarTrackId; //current
    u8 variantIdx;

    //HAW Vote
    u8 chooseNextStatus;
    bool hasTrack;
    u16 nextTrack; //PulsarId

    //KOStats
    u16 timeInDanger;
    u8 almostKOdCounter;
    u8 finalPercentageSum; //to be divided by racecount at the end of the GP

};
struct PulRH2 : public      RKNet::RACEHEADER2Packet {};
struct PulROOM : public     RKNet::ROOMPacket {

    //Generic ROOM settings
    u32 hostSystemContext; //System's context but with just gamemodes taken from the settings
    u8 raceCount;
};

enum SELECTComboStatus {
    SELECT_COMBO_DISABLED,
    SELECT_COMBO_ENABLED,
    SELECT_COMBO_SELECTING,
    SELECT_COMBO_SELECTED,
    SELECT_COMBO_WAITING_FOR_START,

    SELECT_COMBO_HOST_START,

};

struct PulSELECT : public RKNet::SELECTPacket {

    u16 pulVote; //0x38 no need for 2, they're guaranteed to be the same
    u16 pulWinningTrack; //0x3a
    u8 variantIdx; //0x3c

    /*Sole reason these are here and not in ROOM is for easy additions of these gamemodes to public rooms (regionals) since ROOM does not exist there*/
    //OTT Settings
    u8 allowChangeComboStatus;

    //KOSettings
    u8 koPerRace;
    u8 racesPerKO;
    bool alwaysFinal;
};

struct PulRACEDATA : public RKNet::RACEDATAPacket {};
struct PulUSER : public     RKNet::USERPacket {};
struct PulITEM : public     RKNet::ITEMPacket {};
struct PulEVENT : public    RKNet::EVENTPacket {}; //NOT RECOMMENDED as this has variable length
#pragma pack(pop)

static_assert(sizeof(PulROOM) < sizeof(PulSELECT), "ROOM SELECT");

class ExpSELECTHandler {
public:

    static ExpSELECTHandler& Get() { return *reinterpret_cast<ExpSELECTHandler*>(RKNet::SELECTHandler::sInstance); };
    static void DecideTrack(ExpSELECTHandler& self);
    RKNet::OnlineMode  mode; //from page 0x90 OnInit SectionId Switch
    u32 unknown_0x4;
    PulSELECT toSendPacket; //0x8
    PulSELECT* receivedPackets; //sizeof(PulSELECT) + 0x8

    u8 padding[0x2e0 - (sizeof(PulSELECT) + 0x8 + 4)];

    u8 lastSentToAid; //0x2e0
    u8 unknown_0x2e4[7];
    u64 lastSentTime; //0x2e8
    u64 lastReceivedTimes[12]; //0x2f0
    u64 unknown_0x350[12]; //0x350
    u32 unknown_0x3b0[12]; //0x3b0
    u32 hasNewSELECT; //0x3e0 bitflag
    u32 hasNewRACEHEADER_1; //0x3e4 bitflag
    u32 aidsWithAccurateRaceSettings; //0x3e8
    u32 aidsWithAccurateAidPidMap; //0x3ec
    u32 aidsThatHaveVoted; //0x3f0
    u8 unknown_0x3F4[4];
};

u8 GetLastRecvSECTIONSize(u8 aid, u8 sectionIdx);

}//namespace Network
}//namespace Pulsar

#endif