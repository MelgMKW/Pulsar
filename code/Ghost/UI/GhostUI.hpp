#include <kamek.hpp>
#include <game/UI/Page/Other/GhostManager.hpp>
#include <game/UI/Page/Other/GhostSelect.hpp>
#include <game/UI/Page/Menu/CourseSelect.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <UI/ToggleButton.hpp>

namespace PulsarUI {
//Extends GhostSelect by adding a ToggleButton to select ghosts and a BottomText
class ExpGhostSelect : public Pages::GhostSelect {
public:
    ExpGhostSelect();
    void OnInit() override;
    void OnActivate() override;

private:
    void OnChallengeGhostPress(PushButton *button, u32 hudSlotId);
    void OnWatchReplayPress(PushButton *button, u32 hudSlotId);
    void OnSelectGhostChange(ToggleButton *button);
    void OnRightArrowPress(SheetSelectControl *control, u32 hudSlotId);
    void OnLeftArrowPress(SheetSelectControl *control, u32 hudSlotId);
    void OnNewPage();
    void SetToggleBMG();
    void Reset();
    CtrlMenuInstructionText bottomText;
    ToggleButton selectGhostButton;
    PtmfHolder_1A<Page, void, ToggleButton *> onSelectGhostChangeHandler;
    s8 selectedGhostsPages[3];
    u8 selectedGhostsCount;
};

const TextInfo GetCourseBottomText(CourseId id);

}//namespace PulsarUI