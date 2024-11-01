#ifndef _CHOOSENEXTTRACK_
#define _CHOOSENEXTTRACK_
#include <kamek.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Ctrl/SheetSelect.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>
#include <UI/UI.hpp>


namespace Pulsar {
namespace UI {

class RaceControlButtonInfo : public ControlButtonInfo { //needed because inputs are inverted online in mirror
public:
    void Update(const Input::ControllerHolder* controllerHolder) override;
};

class ChooseNextTrack : public Pages::RaceMenu { //use page 0x27
public:
    static const PageId fakeId = PAGE_GHOST_RACE_ENDMENU; //never exists in an online race, and RaceMenu uses this id to know what/how to init and activate the page
    static const PulPageId id = PULPAGE_CHOOSENEXT;
    enum Status {
        STATUS_NOTRACK,
        STATUS_TRACK,
        STATUS_HOST_START,
        STATUS_RH1_READY,
        STATUS_NONE = -1
    };
    static const u32 maxButtonCount = 5;

    ChooseNextTrack();
    ~ChooseNextTrack() override { ++SectionMgr::sInstance->sectionParams->onlineParams.currentRaceNumber; }
    void OnActivate() override;
    void OnUpdate() override;
    //const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override;
    int GetMessageBMG() const override;
    u32 GetButtonCount() const override;
    const u32* GetVariantsIdxArray() const override;
    bool IsPausePage() const override;
    const char* GetButtonsBRCTRName() const override;

private:
    void OnRightArrowSelect(SheetSelectControl& control, u32 hudSlotId);
    void OnLeftArrowSelect(SheetSelectControl& control, u32 hudSlotId);
    void OnButtonClick(PushButton& button, u32 hudSlotId); //8055a0f4

public:
    SectionId ProcessHAW(SectionId defaultId);
    PageId GetPageAfterWifiResults(PageId defaultId) const;


private:
    void UpdateButtonInfo(s32 direction);
    void UpdateRH1();
public:
    const bool isBattle;
    Status status;
    bool isHost;
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