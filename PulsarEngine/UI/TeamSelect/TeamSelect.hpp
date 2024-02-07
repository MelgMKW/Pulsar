#ifndef _TEAMSELECT_
#define _TEAMSELECT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Page/Menu/MiiSelect.hpp>
#include <UI/ToggleButton.hpp>


//Custom Page that allows the host (and only the host) to arrange teams as they see fit. This also has a ToggleButton to disable it if wanted
namespace Pulsar {
namespace UI {


class TeamSelect : public Pages::MenuInteractable {
public:
    TeamSelect();
    void OnInit() override;
    void BeforeEntranceAnimations() override;
    void BeforeControlUpdate() override;
    int GetActivePlayerBitfield() const override;
    int GetPlayerBitfield() const override;
    ManipulatorManager& GetManipulatorManager() override;; //offset 0x70
    UIControl* CreateExternalControl(u32 id) override; //0x84
    UIControl* CreateControl(u32 id) override; //0x88
    void SetButtonHandlers(PushButton& button) override; //80853aac 0x8C
    static inline Team GetPlayerTeam(u8 teamsArrayIdx) { return static_cast<Team>(teams[teamsArrayIdx]); }

private:
    void OnArrowClick(PushButton& button, u32 hudSlotId);
    void OnArrowSelect(PushButton& button, u32 hudSlotId);
    void OnArrowDeselect(PushButton& button, u32 hudSlotId) {};
    void OnButtonClick(PushButton& button, u32 hudSlotId);
    void OnButtonSelect(PushButton& button, u32 hudSlotId) {};
    void OnButtonDeselect(PushButton& button, u32 hudSlotId) {};
    void OnBackPress(u32 hudSlotId);
    void OnToggleButtonClick(ToggleButton& button, u32);
    void SetColours(u32 idx, u8 team);
    static u8 CalcTeamsArrayIdx(u32 teamsArrayIdx);
    static u32 CalcIdx(u8 teamsArrayIdx);
    static void RotateArrow(PushButton& button, u8 team);
    static void RotateArrowPane(PushButton& button, const char* pane, u8 team);

    PtmfHolder_2A<TeamSelect, void, PushButton&, u32> onArrowClickHandler;
    PtmfHolder_2A<TeamSelect, void, PushButton&, u32> onArrowSelectHandler;
    PtmfHolder_2A<TeamSelect, void, PushButton&, u32> onArrowDeselectHandler;
    PtmfHolder_2A<TeamSelect, void, ToggleButton&, u32> onToggleButtonClick;
    PushButton arrows[12];
    LayoutUIControl miis[12];
    MiiName name;
    MiiGroup* miiGroup; //take friendroom's
    u8 arrowMiiIdx[12];
    ToggleButton toggle;
    static const char* miiBg;
    static const char* border;
    static u8 teams[24];

public:
    static bool isEnabled;



};
}//namespace UI
}//namespace Pulsar
#endif