#include <kamek.hpp>
#include <game/Network/RKNetRoom.hpp>
#include <game/Network/RKNetController.hpp>
#include <Pulsar.hpp>
#include <Settings/PlayerData.hpp>

//Implements the ability for a host to send a message, allowing for custom host settings

//ROOMPacket bits arrangement: 0-4 GPraces
u8 racesPerGP = 0;

void ConvertROOMPacketToData(u16 param) {
    u8 raceCount;
    switch (param) {
    case(0x800):
        raceCount = 7;
        break;
    case(0x1000):
        raceCount = 11;
        break;
    case(0x1800):
        raceCount = 23;
        break;
    case(0x2000):
        raceCount = 31;
        break;
    case(0x2800):
        raceCount = 63;
        break;
    case(0x3000):
        raceCount = 1;
        break;
    default:
        raceCount = 3;
    }
    racesPerGP = raceCount;
    Pulsar::sInstance->hasHAW = (param & 0x4000) >> 14;
}

//Adds the settings (for now, only GP races) to the free bits of the packet
void SetAllToSendPackets(RKNetROOMHandler *roomHandler, u32 packetArg) {
    ROOMPacketReg packetReg = { packetArg };
    RKNetController *controller = RKNetController::sInstance;
    u8 localAid = controller->subs[controller->currentSub].localAid;
    if (packetReg.packet.messageType == 1 && localAid == controller->subs[controller->currentSub].hostAid) {
        PulsarSettings::Binarya *settings = PulsarSettings::GetInstance()->GetSettings();
        u8 gpParam = settings->pages[OPT_HOST_SETTINGS].scrollSetting[OPT_SCROLL_GP_RACES];
        packetReg.packet.message |= gpParam << 11;
        u8 hostParam = Pulsar::sInstance->CheckHAWConditions();
        packetReg.packet.message |= hostParam << 14;
        ConvertROOMPacketToData(packetReg.packet.message & 0xF800);
    }
    for (int i = 0; i < 12; i++) if (i != localAid) roomHandler->toSendPackets[i] = packetReg.packet;
};
kmBranch(0x8065ae70, SetAllToSendPackets);

//Non-hosts extract the setting, store it and then return the packet without these bits
ROOMPacket GetParamFromPacket(u32 packetArg, u8 aid) {
    ROOMPacketReg packetReg = { packetArg };
    if (packetReg.packet.messageType == 1) {
        RKNetController *controller = RKNetController::sInstance;
        if (controller->subs[controller->currentSub].hostAid != aid) packetReg.packet.messageType = 0;
        else ConvertROOMPacketToData(packetReg.packet.message & 0xF800);
        packetReg.packet.message &= 0x7FF;
    }
    return packetReg.packet;
}
kmBranch(0x8065af70, GetParamFromPacket);

//Implements that setting
asm void GetRaceCount() {
    ASM(
        lis r5, racesPerGP@ha;
    lbz r0, racesPerGP@l(r5);
    blr;
    )
}
kmCall(0x806460B8, GetRaceCount);
kmCall(0x8064f51c, GetRaceCount);