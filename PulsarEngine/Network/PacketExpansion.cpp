#include <Network/PacketExpansion.hpp>

namespace Pulsar {
namespace Network {

static const u32 totalRACESize = sizeof(RKNet::RACEPacketHeader) + sizeof(PulRH1) + sizeof(PulRH2) + sizeof(PulSELECT) + 2 * sizeof(PulRACEDATA) + sizeof(PulUSER) + 2 * sizeof(PulITEM) + sizeof(PulEVENT);
class CustomRKNetController { //Exists to make received packets a pointer array so that the size can be variable
public:

    //static CustomRKNetController* Get() { return reinterpret_cast<CustomRKNetController*>(RKNet::Controller::sInstance); }
    virtual ~CustomRKNetController(); //8065741c vtable 808c097c

    u32 unkVtable;//unknown class vtable 808c0988
    OS::Mutex mutex; //0x8

    EGG::Heap* Heap; //0x20
    EGG::TaskThread* taskThread; //0x24
    RKNet::ConnectionState connectionState; //0x28 

    RKNet::ErrorParams errorParams; //0x2c

    u32 unknown_0x34;

    RKNet::ControllerSub subs[2]; //0x38
    RKNet::RoomType roomType; //0xe8
    u8 unknown_0xec[4];

    RKNet::SplitRACEPointers* splitToSendRACEPackets[2][12]; //0xf0 split pointers for the outgoing packets, double buffered, indexed by aid
    RKNet::SplitRACEPointers* splitReceivedRACEPackets[2][12]; //0x150 split pointers for the incoming packets, double buffered, indexed by aid
    RKNet::PacketHolder<void>* fullSendPackets[12]; //0x1b0 combined outgoing packets, indexed by aid
    u64 lastRACEToSendTimes[12]; //0x1e0 time when last sent to that aid
    u64 lastRACERecivedTimes[12]; //0x240 time when last received from that aid
    u64 RACEToSendTimesTaken[12]; //0x2a0 last send time minus the time of the send before it
    u64 RACEReceivedTimesTaken[12]; //0x300 last receive time minus the time of the receive before it
    u8 lastRACESendAid; //0x360 aid a packet was last sent to

    //MODIFICATIONS
    u8 defaultBuffer[0x25b0 - 0x361]; //0x361 1 per aid
    u32 toDisconnectAids; //0x25b0 for wiimmfi only?
    void* fullPulRecvPackets[12]; //0x25b4
    //END

    RKNet::StatusData localStatusData; //0x25e4 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
    RKNet::Friend friends[30]; //0x25ec
    bool friendsListIsChanged; //0x2754 true if unprocessed changes have happeend
    bool shutdownScheduled; //0x2755 will cause shutdown of wifi connection on next run of the main loop if true
    bool friendStatusUpdateScheduled; //0x2756 if true, the main loop will update all friend statuses on the next iteration
    bool nwc24Related; //0x2757
    bool hasprofanity; //0x2758 1 if name is bad
    u8 padding2[3];
    s32 badWordsNum; //0x275c number of bad strings in the profanity check
    u8 unknown_0x2760[4];
    s32 vr; //0x2764
    s32 br; //0x2768
    u32 lastSendBufferUsed[12]; //0x276c last full send buffer used for each aid, 0 or 1
    u32 lastReceivedBufferUsed[12][8]; //0x279c last Received buffer used for each packet per aid, 1 or 0
    s32 currentSub; //0x291c index of the current sub to use, 0 or 1
    u8 aidsBelongingToPlayerIds[12]; //0x2920 index is player id, value is aid
    u32 disconnectedAids; //0x292c 1 if disconnected, index 1 << aid
    u32 disconnectedPlayerIds; //0x2930 index 1 << playerId
    u8 unknown_0x2934[0x29c8 - 0x2934];

};
size_assert(CustomRKNetController, 0x29c8);

void* CreateSendAndRecvBuffers() {

    register RKNet::PacketHolder<void>* holder;
    register CustomRKNetController* controller;
    register u8 aid;
    asm(mr holder, r24;);
    asm(mr controller, r27;);
    asm(mr aid, r20;);

    controller->fullPulRecvPackets[aid] = new u8[totalRACESize];
    holder->bufferSize = totalRACESize;
    return new u8[totalRACESize];
}
kmCall(0x806570b4, CreateSendAndRecvBuffers);

/*
static const u32 sizeArray[8] = {
        sizeof(RKNet::RACEPacketHeader),
        sizeof(PulRH1),
        sizeof(PulRH2),
        sizeof(PulSELECT),
        2 * sizeof(PulRACEDATA),
        sizeof(PulUSER),
        2 * sizeof(PulITEM),
        sizeof(PulEVENT)
};
*/


kmWrite8(0x8089a19b, sizeof(PulRH1));
kmWrite8(0x8089a19f, sizeof(PulRH2));
kmWrite8(0x8089a1a3, sizeof(PulSELECT));
kmWrite8(0x8089a1a7, 2 * sizeof(PulRACEDATA));
kmWrite8(0x8089a1ab, sizeof(PulUSER));
kmWrite8(0x8089a1af, 2 * sizeof(PulITEM));
kmWrite8(0x8089a1b3, sizeof(PulEVENT));

void SetProperRecvBuffers(u8 aid, void* usualBuffer, u32 usualSize) {
    register CustomRKNetController* controller;
    asm(mr controller, r31;);
    memset(controller->fullPulRecvPackets[aid], 0, totalRACESize);
    DWC::SetRecvBuffer(aid, controller->fullPulRecvPackets[aid], totalRACESize);
}
kmWrite32(0x80658c78, 0x60000000); //prevent usual memset
kmCall(0x80658c90, SetProperRecvBuffers);

void ProperRecvBuffersClear() {
    const CustomRKNetController* controller = reinterpret_cast<CustomRKNetController*>(RKNet::Controller::sInstance);
    for(int aid = 0; aid < 12; ++aid) memset(controller->fullPulRecvPackets[aid], 0, totalRACESize);
}
kmCall(0x8065607c, ProperRecvBuffersClear);


void CheckPacket(CustomRKNetController* controller, RKNet::RACEPacketHeader& packet, u32 size, u32 sizeUnused, u32 aid) {
    using namespace RKNet;

    const u32 recvCRC = packet.crc32;
    packet.crc32 = 0;
    const u32 calcCRC = OS::CalcCRC32(&packet, size);
    packet.crc32 = recvCRC;
    bool disconnect = false;
    if(recvCRC != calcCRC) disconnect = true;
    else {
        u32* lastUsedBufferAid = &controller->lastReceivedBufferUsed[aid][0];
        SplitRACEPointers* recv = controller->splitReceivedRACEPackets[lastUsedBufferAid[0]][aid];
        PacketHolder<void>** holderRecv = &recv->packetHolders[0];
        const u8* sizes = &packet.sizes[0];

        for(int i = 0; i < 8; ++i) {
            const PacketHolder<void>* curHolder = holderRecv[i]; //starts at header etc...

            const u8 curSize = sizes[i]; //transmitted in packet
            if(curSize != 0) {
                if(curHolder->bufferSize < curSize) disconnect = true;
            }
        }
    }
    if(disconnect) controller->toDisconnectAids |= 1 << aid;
    else  reinterpret_cast<RKNet::Controller*>(controller)->ProcessRACEPacket(aid, packet, size);
}
kmBranch(0x80658608, CheckPacket);

bool DisconnectBadAids() {
    register CustomRKNetController* controller;
    asm(mr controller, r15;);

    int old = OS::DisableInterrupts();
    for(int aid = 0; aid < 12; ++aid) {
        if(controller->toDisconnectAids >> aid) DWC::CloseConnectionHard(aid);
    }
    controller->toDisconnectAids = 0;
    OS::RestoreInterrupts(old);

    return controller->shutdownScheduled;
}
kmCall(0x806579b4, DisconnectBadAids);
kmWrite32(0x806579b8, 0x2c030000);

//Various hardcoded size patches
kmWrite32(0x80661100, 0x418000d8); //bne -> blt for comparison against sizeof(SELECTPacket)
kmWrite32(0x8065adc8, 0x41800014); //bne -> blt for comparison against sizeof(ROOMPacket)
kmWrite32(0x80665244, 0x418000d0); //bne -> blt for comparison against sizeof(RACEHEADER1Packet)

ExpSELECTHandler* CreateRecvArr(ExpSELECTHandler* handler) { //wiimmfi hook prevents a more natural hook...
    register RKNet::OnlineMode mode;
    asm(mr mode, r31;);
    handler->mode = mode;
    handler->receivedPackets = new PulSELECT[12];
    return handler;
}
kmCall(0x8065fec0, CreateRecvArr);

void DeleteSELECT(ExpSELECTHandler* handler) {
    delete handler->receivedPackets;
    delete reinterpret_cast<RKNet::SELECTHandler*>(handler);
}
kmCall(0x8065ff84, DeleteSELECT);


u8 GetLastRecvSECTIONSize(u8 aid, u8 sectionIdx) {
    const CustomRKNetController* controller = reinterpret_cast<CustomRKNetController*>(RKNet::Controller::sInstance);
    RKNet::RACEPacketHeader* header = reinterpret_cast<RKNet::RACEPacketHeader*>(controller->fullPulRecvPackets[aid]);
    return header->sizes[sectionIdx];
}

}//namespace Network
}//namespace Pulsar