#ifndef _PULSARCUPSELECT_
#define _PULSARCUPSELECT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/CupSelect.hpp>
#include <MarioKartWii/UI/Ctrl/SheetSelect.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
namespace UI {
class ExpCupSelect : public Pages::CupSelect {
public:
    ExpCupSelect();
    ~ExpCupSelect() override {
        Settings::Mgr::GetInstance()->SetLastSelectedCup(CupsConfig::sInstance->lastSelectedCup);
        Settings::Mgr::GetInstance()->RequestSave();
    }
    static void UpdateCupData(PulsarCupId id, LayoutUIControl& control);
    void OnActivate() override;
    void AfterControlUpdate() override;
    UIControl* CreateControl(u32 controlId) override;
    void OnMoviesActivate(u32 r4) override;
    void OnStartPress(u32 hudSlotId) override;

private:
    void OnRightArrowSelect(SheetSelectControl& control, u32 hudSlotId);
    void OnLeftArrowSelect(SheetSelectControl& control, u32 hudSlotId);
    void OnArrowSelect(s32 direction);
    void OnBackPress(u32 hudSlotId);

    PtmfHolder_2A<ExpCupSelect, void, SheetSelectControl&, u32> onRightArrowSelectHandler;
    PtmfHolder_2A<ExpCupSelect, void, SheetSelectControl&, u32> onLeftArrowSelectHandler;
    SheetSelectControl arrows;
    LayoutUIControl randomControl;
    PulsarId randomizedId;
};

}//namespace UI
}//namespace Pulsar

#endif