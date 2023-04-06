#ifndef _PULSARCUPSELECT_
#define _PULSARCUPSELECT_
#include <kamek.hpp>
#include <game/UI/Page/Menu/CupSelect.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>

namespace PulsarUI {
class ExpCupSelect : public Pages::CupSelect {
public:
    ExpCupSelect();
    static void UpdateCupData(u32 id, LayoutUIControl *control);
    void AfterControlUpdate() override;
    UIControl *CreateControl(u32 controlId) override;
    void OnMoviesActivate(u32 r4) override;
    void OnStartPress(u32 hudSlotId) override;

private:
    void OnRightArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId);
    void OnLeftArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId);
    void OnArrowSelect(s32 direction);
    void OnBackPress(u32 hudSlotId);

    PtmfHolder_2A<ExpCupSelect, void, SheetSelectControl::SheetSelectButton *, u32> onRightArrowSelectHandler;
    PtmfHolder_2A<ExpCupSelect, void, SheetSelectControl::SheetSelectButton *, u32> onLeftArrowSelectHandler;
    SheetSelectControl arrows;
    LayoutUIControl randomControl;
    CourseId randomizedId;

};

}//namespace PulsarUI

#endif