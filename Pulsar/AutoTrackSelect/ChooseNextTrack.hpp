#ifndef _CHOOSENEXTTRACK_
#define _CHOOSENEXTTRACK_
#include <kamek.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Sound/RSARSounds.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <game/RKNet/EVENT.hpp>
#include <game/UI/Ctrl/CountDown.hpp>
#include <game/Race/RaceInfo/RaceInfo.hpp>
#include <SlotExpansion/CupsDef.hpp>

namespace Pulsar {

namespace Network {

struct PulEVENT {
    PulEVENT(PulsarId id) : nextTrack(id) {}
    PulsarId nextTrack;
    u32 frames;
};

}//namespace Network

namespace UI {

class RaceControlButtonInfo : public ControlButtonInfo { //needed because inputs are inverted online in mirror
public:
    void Update(const Input::ControllerHolder* controllerHolder) override;
};

class ChooseNextTrack : public Pages::RaceMenu { //use page 0x27
public:
    enum Status {
        STATUS_HOST,
        STATUS_HOST_TRACK_SENT,
        STATUS_HOST_FINALSENT,

        STATUS_NOTRACK,
        STATUS_TRACKRECEIVED,
        STATUS_CONFIRMATIONSENT,
        STATUS_FINALHOSTRECEIVED,

        STATUS_NONE = -1
    };

    ChooseNextTrack();
    ~ChooseNextTrack() override { ++SectionMgr::sInstance->sectionParams->currentRaceNumber; }
    void OnActivate() override;
    void OnUpdate() override;
    //int GetRuntimeTypeInfo() const override;
    int GetMessageBMG() const override;
    u32 GetButtonCount() const override;
    const u32* GetVariantsIdxArray() const override;
    bool IsPausePage() const override;
    const char* GetButtonsBRCTRName() const override;
    void OnRightArrowSelect(SheetSelectControl& control, u32 hudSlotId);
    void OnLeftArrowSelect(SheetSelectControl& control, u32 hudSlotId);
    void OnButtonClick(PushButton& button, u32 hudSlotId); //0x8085a0f4

    bool IsHost() const { return this->status <= STATUS_HOST_FINALSENT; }
    bool IsReady() {
        if(this->status == STATUS_FINALHOSTRECEIVED) return true;
        else if(status == STATUS_HOST_FINALSENT) return true;
        {
            //++this->readyWait;
            //if(readyWait >= maxTimeDiff) return true;
        }
        return false;
    }

    void SendPacket(RKNet::EVENTAction action) {
        RKNet::EVENTHandler* event = RKNet::EVENTHandler::sInstance;
        if(!event->HasFreeEntries()) event->toSendEntries[23].state = RKNet::EVENTENTRYSTATE_FREE;
        Network::PulEVENT packet(CupsDef::sInstance->winningCourse);
        u32 frames = RaceInfo::sInstance->raceFrames;
        packet.frames = frames;
        //this->lastSentFrames = frames;
        event->AddEntry(static_cast<ItemObjId>(0x11), action, &packet, sizeof(Network::PulEVENT));
    }

    Status UpdateStatusHost() {
        if(this->status == STATUS_HOST) { this->status = STATUS_HOST_TRACK_SENT; }
        else {
            const RKNet::ControllerSub& sub = RKNet::Controller::sInstance->subs[RKNet::Controller::sInstance->currentSub];
            for(u8 aid = 0; aid < 12; aid++) {
                if(aid == sub.localAid || (1 << aid & sub.availableAids) == 0) continue;
                if(!this->hasReceivedHostTrack[aid]) return STATUS_NONE;
            }
            this->status = UI::ChooseNextTrack::STATUS_HOST_FINALSENT; //Final Confirmation
        }
        return this->status;
    }

    Status UpdateStatusNonHost() {
        if(this->status == STATUS_TRACKRECEIVED) {
            this->status = STATUS_CONFIRMATIONSENT;
            return this->status;
        }
        return STATUS_NONE;
    }

private:
    void UpdateButtonInfo(s32 direction);

public:
    const bool isBattle;
    Status status;
    //u32 lastSentFrames;

    //HOST VARIABLES
    //s32 maxTimeDiff;
    //s32 readyWait;
    bool hasReceivedHostTrack[12]; //for the host to send confirmation once everyone has sent their confirmation

private:
    PtmfHolder_2A<ChooseNextTrack, void, SheetSelectControl&, u32> onRightArrowSelectHandler;
    PtmfHolder_2A<ChooseNextTrack, void, SheetSelectControl&, u32> onLeftArrowSelectHandler;
    SheetSelectControlScaleFade arrows;
    CountDownTimerControl countdownControl;
    CountDown countdown;
    u32 curPageIdx;

    friend void AddArrowsToChooseNext(RaceMenu& page, u32 controlCount);

};
}//namespace UI
}//namespace Pulsar

#endif