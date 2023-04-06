#ifndef _TT_SPLITS_
#define _TT_SPLITS_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceTime.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceCount.hpp>

//_sinit_TTSplitsPAGE_cpp; //80856264
namespace Pages {
class TTSplits : public Page { //ID 0x2D
public:
    TTSplits(); //808556e4
    ~TTSplits() override; //80855864 vtable 808da5dc
    PageId GetNextPage() const override; //0x10 808561dc
    void OnInit() override; //0x28 80855924
    void BeforeEntranceAnimations() override; //0x38 80855b30
    void BeforeExitAnimations() override; //0x40 8085616c
    void AfterControlUpdate() override; //0x4c 80855adc
    int GetRuntimeTypeInfo() const override; //0x60 80856228
    void Unload(); //80855854 inlined
    static void TriggerAction(PtmfHolder_1A<TTSplits, void, u32> *triggeredHandler, u32 hudSlotId); //80856234
    CtrlRaceTime **ctrlRaceTimeArray; //size splitsRowCount
    u8 splitsRowCount; //0x48, lap count + 1 for total time
    u8 unknown_0x49[3]; //padding
    u32 maxActiveFrames; //0x4C set to 600, frames until timeout
    PtmfHolder_1A<TTSplits, void, u32> onClickHandler; //0x50 80855854 HandleClick
    PageManipulatorManager manipulatorManager; //0x64
    Timer timers[4]; //0x1A8 total time + up to 3 lap splits
    CtrlRaceCount ctrlRaceCount; //0x1D8 NEW RECORD
    LayoutUIControl savedGhostMessage; //0x370, live_message brctr
};
size_assert(TTSplits, 0x4e4);
}//namespace Pages
#endif