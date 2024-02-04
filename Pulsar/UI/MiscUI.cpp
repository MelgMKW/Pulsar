#include <kamek.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceWifi.hpp>
#include <game/UI/Page/Other/Title.hpp>
#include <game/UI/Page/Other/Message.hpp>
#include <PulsarSystem.hpp>
#include <Debug/Debug.hpp>
#include <UI/UI.hpp>



namespace Pulsar {

namespace UI {
//No ghost saving on RKSYS
kmWrite32(0x8054913C, 0x60000000);
kmWrite32(0x80855f48, 0x48000148);

//BMG size patch (Diamond)
kmWrite32(0x8007B37C, 0x38000128);


//Credit to Kazuki for making the original ASM code, and Brawlbox for porting it to C++
void LaunchRiivolutionButton(SectionMgr* sectionMgr) {
    const SectionId id = sectionMgr->nextSectionId;
    if(id == SECTION_CHANNEL_FROM_MENU || id == SECTION_CHANNEL_FROM_CHECK_RANKINGS || id == SECTION_CHANNEL_FROM_DOWNLOADS) Debug::LaunchSoftware();
    else sectionMgr->LoadSection();
}
kmCall(0x80553a60, LaunchRiivolutionButton);

//Top left message when a race is about to start in a froom

void FixStartMessageFroom(CtrlRaceWifiStartMessage* startMsg, u32 bmgId, TextInfo* info) {
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    const SectionId id = sectionMgr->curSection->sectionId;
    if(id == SECTION_P1_WIFI_FRIEND_VS || id == SECTION_P1_WIFI_FRIEND_TEAMVS
        || id == SECTION_P2_WIFI_FRIEND_VS || id == SECTION_P2_WIFI_FRIEND_TEAMVS) {
        bmgId = BMG_GP_RACE;
        info->intToPass[0] = sectionMgr->sectionParams->currentRaceNumber + 1;
        info->intToPass[1] = System::sInstance->racesPerGP + 1;
    }
    startMsg->SetMsgId(bmgId, info);
}
kmCall(0x807f8b7c, FixStartMessageFroom);

void DisplayDate(CtrlMenuPressStart* start) {
    start->Load();
    start->SetMsgId(BMG_DATE);
}
kmCall(0x8063ac58, DisplayDate);

void CustomRoomDenyText(Pages::MessageBoxTransparent* msgBox, u32 bmgId, const TextInfo* info) {
    if(Pulsar::System::sInstance->isCustomDeny) bmgId = BMG_ROOM_DENY;
    msgBox->SetMessageWindowText(bmgId, info);
}
kmCall(0x805dd90c, CustomRoomDenyText);

}//namespace UI
}//namespace Pulsar