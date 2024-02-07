#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/GhostManager.hpp>
#include <MarioKartWii/UI/Page/Other/GhostSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/CourseSelect.hpp>
#include <MarioKartWii/UI/Ctrl/SheetSelect.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <UI/ToggleButton.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace UI {

//Extends GhostSelect by adding a ToggleButton to select ghosts and a BottomText
class ExpGhostSelect : public Pages::GhostSelect {
public:
    ExpGhostSelect();
    void OnInit() override;
    void OnActivate() override;
    void ToggleSelectButton(bool isInvisible) {
        this->selectGhostButton.manipulator.inaccessible = isInvisible;
        this->selectGhostButton.isHidden = isInvisible;
    }

private:
    void OnChallengeGhostPress(PushButton& button, u32 hudSlotId);
    void OnWatchReplayPress(PushButton& button, u32 hudSlotId);
    void OnSelectGhostChange(ToggleButton& button, u32);
    void OnRightArrowPress(SheetSelectControl& control, u32 hudSlotId);
    void OnLeftArrowPress(SheetSelectControl& control, u32 hudSlotId);
    void OnNewPage();
    void SetToggleBMG();
    void Reset();

    CtrlMenuInstructionText bottomText;
    ToggleButton selectGhostButton;
    PtmfHolder_2A<ExpGhostSelect, void, ToggleButton&, u32> onSelectGhostChangeHandler;
    s8 selectedGhostsPages[3];
    u8 selectedGhostsCount;
};

const TextInfo GetCourseBottomText(PulsarId id, u32* bmgId);

}//namespace UI
}//namespace Pulsar