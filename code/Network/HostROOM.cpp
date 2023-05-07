#include <kamek.hpp>
#include <game/RKNet/ROOM.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <Settings/UI/SettingsPanel.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
namespace Network {

//Implements the ability for a host to send a message, allowing for custom host settings

//ROOMPacket bits arrangement: 0-4 GPraces
//u8 racesPerGP = 0;

void ConvertROOMPacketToData(u16 param) {
    u8 raceCount;
    switch(param & 0x3800) {
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
    System *system = System::sInstance;
    system->racesPerGP = raceCount;
    system->hasHAW = (param & 0x4000) >> 14;
}

//Adds the settings to the free bits of the packet, only called for the host
void SetAllToSendPackets(RKNet::ROOMHandler& roomHandler, u32 packetArg) {
    RKNet::ROOMPacketReg packetReg ={ packetArg };
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const u8 localAid = controller->subs[controller->currentSub].localAid;
    if(packetReg.packet.messageType == 1 && localAid == controller->subs[controller->currentSub].hostAid) {
        const u8 gpParam = Settings::GetSettingValue(SETTINGSTYPE_HOST, SETTINGHOST_SCROLL_GP_RACES);
        packetReg.packet.message |= gpParam << 11;
        const u8 hostParam = Info::IsHAW(true);
        packetReg.packet.message |= hostParam << 14;
        ConvertROOMPacketToData(packetReg.packet.message & 0xF800);
    }
    for(int i = 0; i < 12; ++i) if(i != localAid) roomHandler.toSendPackets[i] = packetReg.packet;
}
kmBranch(0x8065ae70, SetAllToSendPackets);
//kmCall(0x805dce34, SetAllToSendPackets);
//kmCall(0x805dcd2c, SetAllToSendPackets);
//kmCall(0x805d9fe8, SetAllToSendPackets);

//Non-hosts extract the setting, store it and then return the packet without these bits
RKNet::ROOMPacket GetParamFromPacket(u32 packetArg, u8 aid) {
    RKNet::ROOMPacketReg packetReg ={ packetArg };
    if(packetReg.packet.messageType == 1) {
        const RKNet::Controller* controller = RKNet::Controller::sInstance;
        if(controller->subs[controller->currentSub].hostAid != aid) packetReg.packet.messageType = 0;
        else ConvertROOMPacketToData(packetReg.packet.message & 0xF800);
        packetReg.packet.message &= 0x7FF;
        Page* topPage = SectionMgr::sInstance->curSection->GetTopLayerPage();
        PageId topId = topPage->pageId;
        if(topId == PAGE_VS_SETTINGS || topId == PAGE_VS_TEAMS_VIEW || topId == PAGE_BATTLE_MODE_SELECT){
            UI::SettingsPanel *panel = static_cast<UI::SettingsPanel*>(topPage);
            panel->OnBackPress(0);
        }
    }
    return packetReg.packet;
}
kmBranch(0x8065af70, GetParamFromPacket);

//Implements that setting
kmCall(0x806460B8, System::GetRaceCount);
kmCall(0x8064f51c, System::GetRaceCount);
}//namespace Network
}//namespace Pulsar