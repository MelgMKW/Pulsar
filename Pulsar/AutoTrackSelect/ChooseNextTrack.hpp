#ifndef _CHOOSENEXTTRACK_
#define _CHOOSENEXTTRACK_
#include <kamek.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Sound/RSARSounds.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <game/UI/Ctrl/CountDown.hpp>
namespace Pulsar {
namespace UI {

class RaceControlButtonInfo : public ControlButtonInfo { //needed because inputs are inverted online in mirror
public:
    void Update(const Input::ControllerHolder* controllerHolder) override;
};

class ChooseNextTrack : public Pages::RaceMenu { //use page 0x27
public:
    ChooseNextTrack();
    ~ChooseNextTrack() override {++SectionMgr::sInstance->sectionParams->currentRaceNumber;}
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

private:
    void UpdateButtonInfo(s32 direction);

public:
    const bool isBattle;
    const bool isHost;
    bool hasReceivedHostTrack[12]; //for the host to send confirmation once everyone has sent their confirmation
    bool hasSentInitialPacket; //only for host
    bool sendPacket;
    bool isReady;
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