#ifndef _LOWBATTERY_
#define _LOWBATTERY_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/System/RecognizePad.hpp>

//_sinit_ at 805c3bb0
namespace Pages {

class BatteryMgr : public Page { //ID 0x55
public:
    BatteryMgr(); //805c35f8
    ~BatteryMgr() override; //805c363c vtable 808b7d5c
    PageId GetNextPage() const override; //0x10 805c3b6c
    int IsHomeMenuWorking() const override; //0x14 805bb254 returns 3 if homebutton is not allowed
    void OnInit() override; //0x28 805c36a4
    void OnActivate() override; //0x30 805c3700   
    void BeforeEntranceAnimations() override; //0x38 805c374c
    void AfterEntranceAnimations() override; //0x3c 805c3750
    void BeforeExitAnimations() override; //0x40 805c3754
    void AfterControlUpdate() override; //0x4c 805c3758
    int GetRuntimeTypeInfo() const override; //0x60 805c3b74
    ManipulatorManager manipulatorManager; //0x44
    PageId nextPage;
}; //total size 0x58
size_assert(BatteryMgr, 0x58);

class LowBattery : public Page { //ID 0x56
    LowBattery(); //805c37e0
    ~LowBattery() override; //805c3874 vtable 808b7cec
    void OnInit() override; //0x28 805c3900
    void OnActivate() override; //0x30 805c3a28 updates controller's battery field
    void BeforeEntranceAnimations() override; //0x38 805c3ad8
    void AfterExitAnimations() override; //0x44 805c3b1c
    void AfterControlUpdate() override; //0x4c 805c3a8c
    int GetRuntimeTypeInfo() const override; //0x60 805c3b60
    void OnClick(u32 hudSlotId); //805c3ac4
    PtmfHolder_1A<LowBattery, void, u32> onClickHandler; //0x44 805c3ac4
    PageManipulatorManager manipulatorManager; //0x58
    PadControl padControl; //0x19c
    RecognizePadWindow recognizePadWindow; //0x320
    BlackBackControlForMessage background; //0x494
    u32 unknown_0x608;
};
size_assert(LowBattery, 0x60c);

}//namespace pages

#endif