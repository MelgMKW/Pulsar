#include <kamek.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <game/RKNet/Select.hpp>
#include <game/System/random.hpp>
#include <game/Race/RaceData.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <Settings/Settings.hpp>
#include <SlotExpansion/Network/PulSELECT.hpp>
#include <Info.hpp>
#include <UI/TeamSelect/TeamSelect.hpp>

namespace Pulsar {
namespace Network {
//No disconnect for being idle (Bully)
kmWrite32(0x80521408, 0x38000000);
kmWrite32(0x8053EF6C, 0x38000000);
kmWrite32(0x8053F0B4, 0x38000000);
kmWrite32(0x8053F124, 0x38000000);

//Overwrites CC rules -> 10% 100, 65% 150, 25% mirror and/or in frooms, overwritten by host setting
void DecideCC(CustomSELECTHandler& handler) {
    if(CupsConfig::IsRegsSituation()) reinterpret_cast<RKNet::SELECTHandler&>(handler).DecideEngineClass();
    else {
        const u8 ccSetting = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_HOST, SETTINGHOST_RADIO_CC);
        RKNet::Controller* controller = RKNet::Controller::sInstance;
        const RKNet::RoomType roomType = controller->roomType;
        u8 ccClass = 1; //1 100, 2 150, 3 mirror
        if(roomType == RKNet::ROOMTYPE_VS_REGIONAL
            || roomType == RKNet::ROOMTYPE_FROOM_HOST && ccSetting == HOSTSETTING_CC_NORMAL) {
            Random random;
            const u32 result = random.NextLimited(100); //25
            u32 prob100 = Info::GetProb100(); //100
            u32 prob150 = Info::GetProb150(); //00
            if(result < 100 - (prob100 + prob150)) ccClass = 3;
            else if(result < 100 - prob100) ccClass = 2;
        }
        else if(ccSetting == HOSTSETTING_CC_150) ccClass = 2;
        else if(ccSetting == HOSTSETTING_CC_MIRROR) ccClass = 3;
        handler.toSendPacket.engineClass = ccClass;
    }

}
kmCall(0x80661404, DecideCC);

//Sets Team using the TeamSelectPage if it has been enabled by the host; verifies the validity of the teams
void SetTeams(CustomSELECTHandler* handler, u32& teams) {
    const RKNet::Controller* controller = RKNet::Controller::sInstance; //check if this only called for the host
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    bool isValid = false;
    Team firstTeam = UI::TeamSelect::GetPlayerTeam(0);
    if((handler->mode == RKNet::ONLINEMODE_PRIVATE_VS || handler->mode == RKNet::ONLINEMODE_PRIVATE_BATTLE)
        && UI::TeamSelect::isEnabled) {
        const u32 availableAids = sub.availableAids;
        u32 counter = 0;
        for(int aid = 0; aid < sub.playerCount; aid++) {
            if((1 << aid & availableAids) == 0) continue;
            Team curSlotTeam = UI::TeamSelect::GetPlayerTeam(counter);
            counter++;
            if(curSlotTeam != firstTeam) isValid = true;
            teams = teams | (curSlotTeam & 1) << aid;
        }
    }
    if(!isValid) reinterpret_cast<RKNet::SELECTHandler*>(handler)->DecidePrivateTeams(teams);
};
kmCall(0x806619d8, SetTeams);
}//namespace Network
}//namespace Pulsar