#ifndef _VSTEAMSVIEWPAGE_
#define _VSTEAMSVIEWPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuTeamConfirmTeam.hpp>


//_sinit_ at 808502b8
namespace Pages {
class VSTeamsView : public MenuInteractable { //ID 0x74
    VSTeamsView(); //806287e0
    ~VSTeamsView() override; //80850214 vtable 808d9f98
    void OnInit() override; //8084fdac 0x28
    void OnActivate() override; //8084fea8 0x30
    void AfterControlUpdate() override; //8084feac 0x4c
    int GetRuntimeTypeInfo() const override; //808502ac 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //8084ff80 0x64
    int GetActivePlayerBitfield() const override; //808501a8 0x68
    int GetPlayerBitfield() const; //808501a0 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //8085020c 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //8084fdb0 0x84
    UIControl *CreateControl(u32 controlId) override; //8084fe40 0x88
    void SetButtonHandlers(PushButton *button) override; //808501b0 0x8C
    void OnButtonClick(PushButton *button, u32 hudSlotId); //8084feb0
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8084ffb8
    void OnBackPress(u32 hudSlotId); //8084ffbc
    void AssignTeams(); //8084ffc8
    static Page *GetPageById(PageId id = PAGE_VS_TEAMS_VIEW); //8084fc9c
    //onButtonClick    vtable = 0x808bd174 function = 8084feb0
    //onButtonSelect   vtable = 0x808bd174 offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd174 function = 8084ffb8
    //onBackPress      vtable = 0x808bd168 function = 8084ffbc
    //onStartPress     vtable = 0x808bd168 offset = 0x7c call is virtual
    u32 readTeamPlayerCount;
    u32 blueTeamPlayerCount;
    CtrlMenuTeamConfirmTeam teams[2]; //0x6cc
}; //total size 0x1b2c
size_assert(VSTeamsView, 0x1b2c);
}//namespace Pages
#endif