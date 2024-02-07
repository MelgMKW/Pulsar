#ifndef _MULTITEAMSELECT_
#define _MULTITEAMSELECT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiKartSelect.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuMovie.hpp>


//_sinit_ at 8084d0dc
namespace Pages {
class MultiTeamSelect : public MenuInteractable { //ID 0x83
public:
    static const PageId id = PAGE_MULTIPLAYER_TEAM_SELECT;
    MultiTeamSelect(); //8062bb70
    ~MultiTeamSelect() override; //8084d050 vtable 808d9c60
    void OnInit() override; //0x28 8084bb34
    void OnActivate() override; //0x30 8084c444
    void BeforeEntranceAnimations() override; //0x38 8084c074
    void BeforeExitAnimations() override; //0x40 8084c11c
    void AfterControlUpdate() override; //0x4c 8084c714
    void OnResume() override; //0x54 8084cd30
    int GetRuntimeTypeInfo() const override; //0x60 8084d0d0
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  8084cc1c
    int GetActivePlayerBitfield() const override; //0x68 8084c004
    int GetPlayerBitfield() const override; //0x6c 8084c00c
    ManipulatorManager& GetManipulatorManager() override; //0x70 8084bffc
    void OnControlsInitialized() override; //0x80 8084c070
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8084c1c4
    UIControl* CreateControl(u32 controlId) override; //0x88 8084c314
    void SetButtonHandlers(PushButton& button) override; //0x8C 8084c014

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8084c718
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8084cc20
    void OnBackPress(u32 hudSlotId); //8084cc24
    static Page* GetPageById(PageId id = PAGE_MULTIPLAYER_TEAM_SELECT); //8084ba24
    static void AssignCPUTeams(); //8084ce1c
    static bool IsDifferentTeams(); //8084cff4 checks if at least one player populates each team
    //onButtonClick    vtable = 0x808bd204 function = 8084c718
    //onButtonSelect   vtable = 0x808bd204 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd204 function = 8084cc20
    //onBackPress      vtable = 0x808bd1f8 function = 8084cc24
    //onStartPress     vtable = 0x808bd1f8 offset   = 0x7c call is virtual Handler
    MultiKartBox** kartBoxes; //0x6c4
    DriverModelControl** driverModelControl; //0x6c8
}; //total size 0x6cc
size_assert(MultiTeamSelect, 0x6cc);
}//namespace Pages
#endif