#include <kamek.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/Audio/RaceMgr.hpp>
#include <PulsarSystem.hpp>
#include <AutoTrackSelect/ExpFroomMessages.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <Settings/Settings.hpp>
#include <UI/UI.hpp>

#include <PulsarSystem.hpp>

namespace Pulsar {
namespace UI {
bool ExpFroomMessages::isOnModeSelection = false;
u32 ExpFroomMessages::clickedButtonIdx = 0;

void ExpFroomMessages::OnModeButtonClick(PushButton& button, u32 hudSlotId) {
    this->clickedButtonIdx = button.buttonId;
    this->OnActivate();
}

void ExpFroomMessages::OnCourseButtonClick(PushButton& button, u32 hudSlotId) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    u32 clickedIdx = clickedButtonIdx;
    u32 id = button.buttonId;
    PulsarId pulsarId = static_cast<PulsarId>(id);
    if(clickedIdx < 2) {
        if(id == this->msgCount - 1) {
            pulsarId = cupsConfig->RandomizeTrack();
        }
        else {
            PulsarCupId cupId =  static_cast<PulsarCupId>(cupsConfig->ConvertTrack_IdxToPulsarId(id) / 4);
            pulsarId = cupsConfig->ConvertTrack_PulsarCupToTrack(cupId, id % 4);
            //pulsarId = cupsConfig->ConvertTrack_IdxToPulsarId(id); //vs or teamvs
        }
    }
    else pulsarId = static_cast<PulsarId>(pulsarId + 0x20U); //Battle
    cupsConfig->winningCourse = pulsarId;
    PushButton& clickedButton = this->messages[0].buttons[clickedIdx];
    clickedButton.buttonId = clickedIdx;
    Pages::FriendRoomMessages::OnModeButtonClick(clickedButton, 0); //hudslot is unused
}

//kmWrite32(0x805dc47c, 0x7FE3FB78); //Get Page in r3
static void OnStartButtonFroomMsgActivate() {
    register ExpFroomMessages* msg;
    asm(mr msg, r31;);

    if(!Info::IsHAW(true)) {
        msg->onModeButtonClickHandler.ptmf = &Pages::FriendRoomMessages::OnModeButtonClick;
        msg->msgCount = 4;
    }
    else {
        for(int i = 0; i < 4; ++i) msg->messages[0].buttons[i].HandleDeselect(0, -1);
        if(msg->isOnModeSelection) {
            msg->isOnModeSelection = false;
            if(msg->clickedButtonIdx >= 2) msg->msgCount = 10;
            else msg->msgCount = CupsConfig::sInstance->GetEffectiveTrackCount() + 1;
            msg->onModeButtonClickHandler.ptmf = &ExpFroomMessages::OnCourseButtonClick;

        }
        else {
            msg->isOnModeSelection = true;
            msg->msgCount = 4;
            msg->onModeButtonClickHandler.ptmf = &ExpFroomMessages::OnModeButtonClick;
        }
    }
}
kmCall(0x805dc480, OnStartButtonFroomMsgActivate);
//kmWrite32(0x805dc498, 0x60000000);
//kmWrite32(0x805dc4c0, 0x60000000);

static void OnBackPress(ExpFroomMessages& msg) {
    if(Info::IsHAW(true) && msg.location == 1) {
        if(!msg.isOnModeSelection) {
            msg.isEnding = false;
            msg.OnActivate();
        }
        else msg.isOnModeSelection = false;
    }
}
kmBranch(0x805dd32c, OnBackPress);

static void OnBackButtonClick() {
    OnBackPress(*SectionMgr::sInstance->curSection->Get<ExpFroomMessages>());
}
kmBranch(0x805dd314, OnBackButtonClick);


//kmWrite32(0x805dcb6c, 0x7EC4B378); //Get the loop idx in r4
u32 CorrectModeButtonsBMG(const RKNet::ROOMPacket& packet) {
    register u32 rowIdx;
    asm(mr rowIdx, r22;);
    register const ExpFroomMessages* messages;
    asm(mr messages, r19;);
    if(Info::IsHAW(true) && !messages->isOnModeSelection) {
        if(messages->clickedButtonIdx >= 2 && messages->clickedButtonIdx < 4) {
            return BMG_BATTLE + messages->curPageIdx * 4 + rowIdx;
        }
        else {
            if(rowIdx + messages->curPageIdx * 4 == messages->msgCount - 1) {
                return BMG_RANDOM_TRACK;
            }
            else {
                CupsConfig* cupsConfig = CupsConfig::sInstance;
                bool hasRegs = cupsConfig->HasRegs();
                u32 idx = messages->curPageIdx;
                if(!hasRegs) idx += 8;
                return GetTrackBMGId(cupsConfig->ConvertTrack_PulsarCupToTrack(CupsConfig::ConvertCup_IdxToPulsarId(idx), rowIdx)); //FIX HERE
            }
        }
    }
    else return Pages::FriendRoomManager::GetMessageBmg(packet, 0);
}
kmCall(0x805dcb74, CorrectModeButtonsBMG);
}//namespace UI
}//namespace Pulsar
