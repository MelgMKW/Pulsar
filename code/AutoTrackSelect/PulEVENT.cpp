#include <game/Race/RaceData.hpp>
#include <game/RKNet/EVENT.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <game/UI/Page/Other/WWRaceSupporting.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>
#include <AutoTrackSelect/PulEVENT.hpp>

namespace Pulsar {
namespace Network {

using namespace RKNet;
void CustomEVENT(SectionMgr* sectionMgr, SectionId id) {
    bool isReady = true;
    const Section* section = sectionMgr->curSection;
    const SectionParams* params = sectionMgr->sectionParams;
    UI::ChooseNextTrack* choosePage = section->Get<UI::ChooseNextTrack>(PAGE_GHOST_RACE_ENDMENU);
    if(choosePage != nullptr) {
        if(choosePage->isBattle && params->redWins < 2 && params->blueWins < 2
            || !choosePage->isBattle && sectionMgr->sectionParams->currentRaceNumber != System::sInstance->racesPerGP) {
            PulEVENT packet;
            packet.nextTrack = CupsDef::sInstance->winningCourse;
            EVENTAction action = EVENTACTION_NONE;
            bool sendPacket = choosePage->sendPacket;
            if(choosePage->isHost) {
                if(!choosePage->hasSentInitialPacket) choosePage->hasSentInitialPacket = true;
                else {
                    bool everyoneHasTrack = true;
                    const ControllerSub& sub = Controller::sInstance->subs[Controller::sInstance->currentSub];
                    for(u8 aid = 0; aid < 12; aid++) {
                        if(aid == sub.localAid || (1 << aid & sub.availableAids) == 0) continue;
                        if(!choosePage->hasReceivedHostTrack[aid]) {
                            everyoneHasTrack = false;
                            sendPacket = false;
                            break;
                        }
                    }
                    if(everyoneHasTrack) {
                        choosePage->isReady = true;
                        action = EVENTACTION_USE; //Final Confirmation
                    }
                }
            }
            isReady = choosePage->isReady;
            if(isReady) id = section->sectionId;
            if(sendPacket) {
                choosePage->sendPacket = false;
                EVENTHandler::sInstance->AddEntry((ItemObjId)0x11, action, &packet, 4);
            }
        }
    }
    if(isReady) {
        sectionMgr->SetNextSection(id, 0);
        register Pages::WWRaceEndWait* wait;
        asm volatile(mr wait, r31);
        wait->EndStateAnimated(0.0f, 0);
        sectionMgr->RequestSceneChange(0, 0xFF);
    }

}
kmCall(0x8064f5fc, CustomEVENT);
kmPatchExitPoint(CustomEVENT, 0x8064f648);

bool ProcessCustomEVENT(EVENTType* type, const void* packet, u8 aid) { //returns true if custom packet
    if((type->value & 0x1F) == 0x11) {
        SectionMgr* sectionMgr = SectionMgr::sInstance;
        UI::ChooseNextTrack* choosePage = sectionMgr->curSection->Get<UI::ChooseNextTrack>(PAGE_GHOST_RACE_ENDMENU);
        const PulEVENT* event = reinterpret_cast<const PulEVENT*>(packet);
        const ControllerSub& sub = Controller::sInstance->subs[Controller::sInstance->currentSub];
        if(aid == sub.hostAid) {
            if(type->value >> 5 == 0) {
                CupsDef* cups = CupsDef::sInstance;
                cups->winningCourse = event->nextTrack;
                cups->selectedCourse = cups->winningCourse;
                RaceData::sInstance->menusScenario.settings.courseId = cups->GetCorrectTrackSlot();
                choosePage->sendPacket = true; //confirmation to the host
            }
            else choosePage->isReady = true; //this is the host confirmation       
        }
        else {
            choosePage->hasReceivedHostTrack[aid] = true;
            choosePage->sendPacket = true; //confirmation packet will be sent as soon as everyone has received the host track
        }
        type->value = 0x10;
        return true;
    }
    return false;
}

asm void ProcessCustomEVENTWrapper() {
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

}//namespace Network
}//namespace Pulsar