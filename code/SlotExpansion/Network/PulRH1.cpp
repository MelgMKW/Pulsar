#include <kamek.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <game/RKNet/RH1.hpp>
#include <SlotExpansion/Network/PulRH1.hpp>

#include <SlotExpansion/CupsDef.hpp>

namespace Pulsar {
namespace Network {

//Fixes for spectating
u8 ExportRH1ToPulRH1(RKNet::PacketHolder& packetHolder, RKNet::RACEHEADER1Packet* rh1Packet, u32 len) {
    CustomRH1Packet* convPacket = reinterpret_cast<CustomRH1Packet*>(rh1Packet);
    if(!CupsDef::IsRegsSituation()) {
        convPacket->starRankHud0 = rh1Packet->starRank[0];
        convPacket->starRankHud1 = rh1Packet->starRank[1];
        convPacket->trackId = static_cast<u16>(CupsDef::sInstance->winningCourse);
    }
    packetHolder.Copy(convPacket, len);
    return convPacket->starRankHud0;
}
kmCall(0x80655458, ExportRH1ToPulRH1);
kmCall(0x806550e4, ExportRH1ToPulRH1);

CourseId ReturnCorrectId(const RKNet::RH1Handler& rh1Handler) {
    CupsDef* system = CupsDef::sInstance;
    for(int i = 0; i < 12; ++i) {
        const RKNet::RH1Data& curRH1 = rh1Handler.rh1Data[i];
        if((curRH1.trackId <= 0x42 || curRH1.trackId > 0xff) && curRH1.timer != 0) {
            if(CupsDef::IsRegsSituation()) system->winningCourse = CupsDef::ConvertTrack_RealIdToPulsarId(curRH1.trackId);
            else system->winningCourse = static_cast<PulsarId>(curRH1.trackId);
            return system->GetCorrectTrackSlot();
        }
    }
    return COURSEID_NONE;
}
kmBranch(0x80664560, ReturnCorrectId);

const u8* GetRH1aidArray(const RKNet::RH1Handler& rh1) {
    for(int i = 0; i < 12; ++i) {
        const RKNet::RH1Data& cur = rh1.rh1Data[i];
        const CourseId curTrack = cur.trackId;
        if(curTrack <= 0x42 || curTrack > 0xff) return &cur.aidsBelongingToPlayer[0];
    }
    return nullptr;
}
kmBranch(0x80664b34, GetRH1aidArray);


bool IsThereAValidId() {
    const RKNet::RH1Handler* rh1 = RKNet::RH1Handler::sInstance;
    bool isValid = false;
    for(int i = 0; i < 12; ++i) {
        const RKNet::RH1Data* cur = &rh1->rh1Data[i];
        if(cur->trackId <= 0x42 && cur->timer != 0) {
            isValid = true;
            break;
        }
    }
    return isValid;
}
kmCall(0x806643a4, IsThereAValidId);
kmCall(0x80664080, IsThereAValidId);
kmWrite32(0x80664084, 0x2C030000); //change comparison from r0 to r3

kmWrite32(0x806652b4, 0x60000000); //nop track store
kmWrite32(0x80665308, 0x60000000); //nop star rank store

void ImportRH1ToPulRH1() {
    register CustomRH1Packet* packet;
    asm volatile(mr packet, r28;);
    register RKNet::RH1Data* data;
    asm volatile(addi data, r26, 0x20;);
    if(CupsDef::IsRegsSituation()) {
        RKNet::RACEHEADER1Packet* normal = reinterpret_cast<RKNet::RACEHEADER1Packet*>(packet);
        data->trackId = static_cast<CourseId>(normal->trackId);
        data->starRank[0] = normal->starRank[0];
        data->starRank[1] = normal->starRank[1];
    }
    else {
        data->trackId = static_cast<CourseId>(packet->trackId);
        data->starRank[0] = packet->starRankHud0;
        data->starRank[1] = packet->starRankHud1;
    }
}
kmCall(0x806652ec, ImportRH1ToPulRH1);

}//namespace Network
}//namespace Pulsar

