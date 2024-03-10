#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/RKNet/EVENT.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Page/Other/WWRaceSupporting.hpp>
#include <PulsarSystem.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>

namespace Pulsar {
namespace Network {

using namespace RKNet;

static inline u32 ShouldSendPacketHost(UI::ChooseNextTrack* choosePage) {
    if(choosePage->status == UI::ChooseNextTrack::STATUS_HOST) {
        choosePage->status = UI::ChooseNextTrack::STATUS_HOST_TRACK_SENT;
        return EVENTACTION_NONE;
    }
    else {
        const ControllerSub& sub = Controller::sInstance->subs[Controller::sInstance->currentSub];
        for(u8 aid = 0; aid < 12; aid++) {
            if(aid == sub.localAid || (1 << aid & sub.availableAids) == 0) continue;
            if(!choosePage->hasReceivedHostTrack[aid]) return -1;
        }
        choosePage->status = UI::ChooseNextTrack::STATUS_HOST_FINALSENT;
        return EVENTACTION_USE; //Final Confirmation
    }
}

static inline u32 ShouldSendPacketOther(UI::ChooseNextTrack* choosePage) {
    if(choosePage->status == UI::ChooseNextTrack::STATUS_TRACKRECEIVED) {
        choosePage->status = UI::ChooseNextTrack::STATUS_CONFIRMATIONSENT;
        return EVENTACTION_SHOOT;
    }
    return -1;
}

static void CustomEVENT(SectionMgr* sectionMgr, SectionId id) {

    const Section* section = sectionMgr->curSection;
    const SectionParams* params = sectionMgr->sectionParams;
    UI::ChooseNextTrack* choosePage = section->Get<UI::ChooseNextTrack>(PAGE_GHOST_RACE_ENDMENU);

    if(choosePage != nullptr) {
        if(choosePage->IsReady()) id = section->sectionId;
        else if(choosePage->isBattle && params->redWins < 2 && params->blueWins < 2
            || !choosePage->isBattle && sectionMgr->sectionParams->currentRaceNumber != System::sInstance->racesPerGP) {

            UI::ChooseNextTrack::Status next;
            if(choosePage->IsHost()) next = choosePage->UpdateStatusHost();
            else next = choosePage->UpdateStatusNonHost();

            if(next != UI::ChooseNextTrack::STATUS_NONE) choosePage->SendPacket(static_cast<EVENTAction>(next));
            return;
        }
    }
    sectionMgr->SetNextSection(id, 0);
    register Pages::WWRaceEndWait* wait;
    asm(mr wait, r31);
    wait->EndStateAnimated(0.0f, 0);
    sectionMgr->RequestSceneChange(0, 0xFF);

}
kmCall(0x8064f5fc, CustomEVENT);
kmPatchExitPoint(CustomEVENT, 0x8064f648);

static bool ProcessCustomEVENT(EVENTType* type, const void* packet, u8 aid) { //returns true if custom packet
    if((type->value & 0x1F) == 0x11) {
        SectionMgr* sectionMgr = SectionMgr::sInstance;
        UI::ChooseNextTrack* choosePage = sectionMgr->curSection->Get<UI::ChooseNextTrack>(PAGE_GHOST_RACE_ENDMENU);
        const PulEVENT* event = reinterpret_cast<const PulEVENT*>(packet);
        const ControllerSub& sub = Controller::sInstance->subs[Controller::sInstance->currentSub];
        if(aid == sub.hostAid) { //can only trigger for non-hosts
            if((type->value >> 5) == UI::ChooseNextTrack::STATUS_HOST_TRACK_SENT && choosePage->status == UI::ChooseNextTrack::STATUS_NOTRACK) {
                CupsConfig* cupsConfig = CupsConfig::sInstance;
                cupsConfig->winningCourse = event->nextTrack;
                //cupsConfig->selectedCourse = cupsConfig->winningCourse;
                RaceData::sInstance->menusScenario.settings.courseId = cupsConfig->GetCorrectTrackSlot();
                choosePage->status = UI::ChooseNextTrack::STATUS_TRACKRECEIVED; //confirmation to the host
            }
            else if((type->value >> 5) == UI::ChooseNextTrack::STATUS_HOST_FINALSENT) {
                choosePage->status = UI::ChooseNextTrack::STATUS_FINALHOSTRECEIVED; //this is the host confirmation  
            }
        }
        else if(choosePage->IsHost()) {
            //s32 diff = event->frames - choosePage->lastSentFrames;
            //choosePage->maxTimeDiff = nw4r::ut::Max(choosePage->maxTimeDiff, diff);
            choosePage->hasReceivedHostTrack[aid] = true; //confirmation packet will be sent when everyone has track
        }
        type->value = 0x10;
        return true;
    }
    return false;
}

asmFunc ProcessCustomEVENTWrapper() {
    ASM(
        nofralloc;
    mflr r26;
    mr r3, r24;
    mr r4, r23;
    mr r5, r28;
    bl ProcessCustomEVENT; //returns true if custom
    add r24, r24, r3;
    mulli r3, r3, sizeof(PulEVENT);
    add r23, r23, r3;
    lbz r0, 0 (r24);
    mtlr r26;
    li r26, 0;
    blr;
    )
}
kmCall(0x8065bda0, ProcessCustomEVENTWrapper);

//80655574 timeout 600 frames since last RH1 can lead to a dc :
//if(rh1[aid].timer - playerRH1Timers[0] > 600)


}//namespace Network
}//namespace Pulsar