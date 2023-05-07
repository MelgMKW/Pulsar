#ifndef _VSTEAMSVIEWPAGE_
#define _VSTEAMSVIEWPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuTeamConfirmTeam.hpp>


//_sinit_ at 808502b8
namespace Pages {
class VSTeamsView: public MenuInteractable { //ID 0x74
    VSTeamsView(); //806287e0
    ~VSTeamsView() override; //80850214 vtable 808d9f98
    void OnInit() override; //0x28 8084fdac
    void OnActivate() override; //0x30 8084fea8
    void AfterControlUpdate() override; //0x4c 8084feac
    int GetRuntimeTypeInfo() const override; //0x60 808502ac
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64 8084ff80
    int GetActivePlayerBitfield() const override; //0x68 808501a8
    int GetPlayerBitfield() const override; //0x6C 808501a0
    ManipulatorManager& GetManipulatorManager() override; //0x70 8085020c
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8084fdb0
    UIControl* CreateControl(u32 controlId) override; //0x88 8084fe40
    void SetButtonHandlers(PushButton& button) override; //0x8C 808501b0
    void OnButtonClick(PushButton& button, u32 hudSlotId); //8084feb0
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8084ffb8
    void OnBackPress(u32 hudSlotId); //8084ffbc
    void AssignTeams(); //8084ffc8
    static Page* GetPageById(PageId id = PAGE_VS_TEAMS_VIEW); //8084fc9c
    //onButtonClick    vtable = 0x808bd174 function = 8084feb0
    //onButtonSelect   vtable = 0x808bd174 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd174 function = 8084ffb8
    //onBackPress      vtable = 0x808bd168 function = 8084ffbc
    //onStartPress     vtable = 0x808bd168 offset   = 0x7c call is virtual
    u32 readTeamPlayerCount;
    u32 blueTeamPlayerCount;
    CtrlMenuTeamConfirmTeam teams[2]; //0x6cc
}; //total size 0x1b2c
size_assert(VSTeamsView, 0x1b2c);
}//namespace Pages
#endif