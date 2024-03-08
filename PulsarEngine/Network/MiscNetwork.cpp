#include <kamek.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKNet/Select.hpp>
#include <MarioKartWii/System/random.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
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
static void DecideCC(CustomSELECTHandler& handler) {
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
static void SetTeams(CustomSELECTHandler* handler, u32& teams) {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub* sub = &controller->subs[0];
    if(sub->connectionUserDatas[0].playersAtConsole == 0) sub = &controller->subs[1];

    bool isValid = false;
    Team firstTeam = UI::TeamSelect::GetPlayerTeam(0); //guaranteed to exist since a room always has aid0
    if((handler->mode == RKNet::ONLINEMODE_PRIVATE_VS || handler->mode == RKNet::ONLINEMODE_PRIVATE_BATTLE)
        && UI::TeamSelect::isEnabled) {

        for(int aid = 0; aid < sub->playerCount; aid++) {
            if(sub->availableAids & (1 << aid)) {
                for(int player = 0; player < sub->connectionUserDatas[aid].playersAtConsole; player++) {
                    Team curSlotTeam = UI::TeamSelect::GetPlayerTeam(aid + 12 * player);
                    if(curSlotTeam != firstTeam) isValid = true;
                    teams = teams | (curSlotTeam & 1) << (aid * 2 + player);
                }
            }
        }
    }
    if(!isValid) reinterpret_cast<RKNet::SELECTHandler*>(handler)->DecidePrivateTeams(teams);
}
kmCall(0x806619d8, SetTeams);

}//namespace Network
}//namespace Pulsar