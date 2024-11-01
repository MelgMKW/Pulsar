#ifndef _EXPGHOSTSELECT_
#define _EXPGHOSTSELECT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/GhostSelect.hpp>
#include <UI/UI.hpp>
#include <UI/ToggleControls.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace UI {

//Extends GhostSelect by adding a ToggleButton to select ghosts and a BottomText
class ExpGhostSelect : public Pages::GhostSelect {
public:
    ExpGhostSelect();
    void OnInit() override;
    void OnActivate() override;
    void OnDeactivate() override;
    void ToggleSelectButton(bool isInvisible) {
        this->selectGhostButton.manipulator.inaccessible = isInvisible;
        this->selectGhostButton.isHidden = isInvisible;
    }

private:
    void OnChallengeGhostPress(PushButton& button, u32 hudSlotId);
    void OnWatchReplayPress(PushButton& button, u32 hudSlotId);
    void OnSelectGhostChange(ToggleButton& button, u32);
    void OnStartPress(u32);
    void OnRightArrowPress(SheetSelectControl& control, u32 hudSlotId);
    void OnLeftArrowPress(SheetSelectControl& control, u32 hudSlotId);
    void OnNewPage();
    void SetToggleBMG();
    void Reset();

    PtmfHolder_2A<ExpGhostSelect, void, ToggleButton&, u32> onSelectGhostChangeHandler;
    PtmfHolder_1A<ExpGhostSelect, void, u32> onStartPressHandler;
    CtrlMenuInstructionText bottomText;
    ToggleButton selectGhostButton;
    LayoutUIControl favGhost;
    s8 selectedGhostsPages[3];
    u8 selectedGhostsCount;
    s8 favGhostIndex;
};

const Text::Info GetCourseBottomText(PulsarId id, u32* bmgId);

}//namespace UI
}//namespace Pulsar

#endif