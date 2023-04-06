#include <kamek.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <Pulsar.hpp>
#include <AutoTrackSelect/ExpFroomMessages.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <Settings/PlayerData.hpp>
#include <UI/BMG.hpp>

namespace PulsarUI {
bool ExpFroomMessages::isOnModeSelection = false;
PushButton *clickedButton = NULL;

void ExpFroomMessages::OnModeButtonClick(PushButton *button, u32 hudSlotId) {
    this->OnActivate();
}

void ExpFroomMessages::OnCourseButtonClick(PushButton *button, u32 hudSlotId) {
    Pulsar *pulsar = Pulsar::sInstance;
    pulsar->winningCourse = (CourseId)button->buttonId;
    Pages::FriendRoomMessages::OnModeButtonClick(clickedButton, hudSlotId);
}



kmWrite32(0x805dc47c, 0x7FE3FB78); //Get Page in r3
void OnStartButtonFroomMsgActivate(ExpFroomMessages *msg) {
    Pulsar *pulsar = Pulsar::sInstance;

    u32 msgCount = 4;
    if (!pulsar->CheckHAWConditions()) {
        msg->onModeButtonClickHandler.ptmf = &Pages::FriendRoomMessages::OnModeButtonClick;
    }
    else {
        if (msg->isOnModeSelection) {
            msg->isOnModeSelection = false;
            msgCount = pulsar->GetTotalTrackCount();
            msg->onModeButtonClickHandler.ptmf =
                static_cast<void (Pages::FriendRoomMessages:: *)(PushButton *, u32)>(&ExpFroomMessages::OnCourseButtonClick);

        }
        else {
            msg->isOnModeSelection = true;
            msg->onModeButtonClickHandler.ptmf =
                static_cast<void (Pages::FriendRoomMessages:: *)(PushButton *, u32)>(&ExpFroomMessages::OnModeButtonClick);
        }
    }
    msg->msgCount = msgCount;

}
kmCall(0x805dc480, OnStartButtonFroomMsgActivate);
//kmWrite32(0x805dc498, 0x60000000);
//kmWrite32(0x805dc4c0, 0x60000000);

kmWrite32(0x805dcb6c, 0x7EC4B378); //Get the loop idx in r4
u32 CorrectModeButtonsBMG(ROOMPacket *packet, u8 rowIdx) {
    ExpFroomMessages *messages = SectionMgr::sInstance->curSection->Get<ExpFroomMessages>(PAGE_FRIEND_ROOM_MESSAGES);
    Pulsar *pulsar = Pulsar::sInstance;
    if (pulsar->CheckHAWConditions() && !messages->isOnModeSelection)
    {
        return GetTrackBMG((CourseId)(messages->curPageIdx * 4 + rowIdx));
    }
    else return Pages::FriendRoomManager::GetMessageBmg(packet, 0);
}
kmCall(0x805dcb74, CorrectModeButtonsBMG);
}//namespace PulsarUI














