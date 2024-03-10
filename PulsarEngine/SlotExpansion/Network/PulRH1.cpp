#include <kamek.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKNet/RH1.hpp>
#include <SlotExpansion/Network/PulRH1.hpp>

#include <SlotExpansion/CupsConfig.hpp>

namespace Pulsar {
namespace Network {

//Fixes for spectating
u8 ExportRH1ToPulRH1(RKNet::PacketHolder& packetHolder, RKNet::RACEHEADER1Packet* rh1Packet, u32 len) {
    CustomRH1Packet* convPacket = reinterpret_cast<CustomRH1Packet*>(rh1Packet);
    if(!CupsConfig::IsRegsSituation()) {
        convPacket->starRankHud0 = rh1Packet->starRank[0];
        convPacket->starRankHud1 = rh1Packet->starRank[1];
        convPacket->trackId = static_cast<u16>(CupsConfig::sInstance->winningCourse);
    }
    packetHolder.Copy(convPacket, len);
    return convPacket->starRankHud0;
}
kmCall(0x80655458, ExportRH1ToPulRH1);
kmCall(0x806550e4, ExportRH1ToPulRH1);

CourseId ReturnCorrectId(const RKNet::RH1Handler& rh1Handler) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    for(int i = 0; i < 12; ++i) {
        const RKNet::RH1Data& cur = rh1Handler.rh1Data[i];
        const CourseId curTrack = cur.trackId;
        if(curTrack != 0xFFFFFFFF && (curTrack <= 0x42 || curTrack > 0xff) && cur.timer != 0) {
            if(CupsConfig::IsRegsSituation()) cupsConfig->winningCourse = CupsConfig::ConvertTrack_RealIdToPulsarId(cur.trackId);
            else cupsConfig->winningCourse = static_cast<PulsarId>(cur.trackId);
            return cupsConfig->GetCorrectTrackSlot();
        }
    }
    return COURSEID_NONE;
}
kmBranch(0x80664560, ReturnCorrectId);

const u8* GetRH1aidArray(const RKNet::RH1Handler& rh1) {
    for(int i = 0; i < 12; ++i) {
        const RKNet::RH1Data& cur = rh1.rh1Data[i];
        const CourseId curTrack = cur.trackId;
        if(curTrack != 0xFFFFFFFF && (curTrack <= 0x42 || curTrack > 0xff)) return &cur.aidsBelongingToPlayer[0];
    }
    return nullptr;
}
kmBranch(0x80664b34, GetRH1aidArray);


static bool IsThereAValidId() {
    const RKNet::RH1Handler* rh1 = RKNet::RH1Handler::sInstance;
    bool isValid = false;
    for(int i = 0; i < 12; ++i) {
        const RKNet::RH1Data& cur = rh1->rh1Data[i];
        const CourseId curTrack = cur.trackId;
        if(curTrack != 0xFFFFFFFF && (curTrack <= 0x42 || curTrack > 0xff)) {
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

static void ImportRH1ToPulRH1() {
    register CustomRH1Packet* packet;
    asm(mr packet, r28;);
    register RKNet::RH1Data* data;
    asm(addi data, r26, 0x20;);
    if(CupsConfig::IsRegsSituation()) {
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

