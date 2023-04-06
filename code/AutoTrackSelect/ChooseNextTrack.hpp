#ifndef _CHOOSENEXTTRACK_
#define _CHOOSENEXTTRACK_
#include <kamek.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Page/RaceMenu/RaceMenu.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Sound/RSARSounds.hpp>
#include <game/Network/RKNetController.hpp>

namespace PulsarUI {
class ChooseNextTrack : public Pages::RaceMenu { //use page 0x27
public:
    ChooseNextTrack();
    void OnActivate() override;
    void OnUpdate() override;
    //int GetRuntimeTypeInfo() const override;
    int GetMessageBMG() const override;
    u32 GetButtonCount() const override;
    const u32 *GetVariantsIdxArray() const override;
    bool IsPausePage() const override;
    const char *GetButtonsBRCTRName() const override;
    void OnRightArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId);
    void OnLeftArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId);
    void UpdateButtonInfo(s32 direction);
    void OnButtonClick(PushButton *button, u32 hudSlotId); //0x8085a0f4

    PtmfHolder_2A<ChooseNextTrack, void, SheetSelectControl::SheetSelectButton *, u32> onRightArrowSelectHandler;
    PtmfHolder_2A<ChooseNextTrack, void, SheetSelectControl::SheetSelectButton *, u32> onLeftArrowSelectHandler;
    SheetSelectControlScaleFade arrows;
    u32 curPageIdx;
};
}//namespace PulsarUI

#endif