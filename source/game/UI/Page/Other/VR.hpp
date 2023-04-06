#ifndef _VRPAGE_
#define _VRPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/CountDown.hpp>

/*
Contributors:
-Melg
*/
namespace Pages {
class VR : public Page { //ID 0x91
public:
    VR(); //8064a3f4 vtable 0x808bfd0c
    ~VR() override; //0x8064a4e0
    void OnInit() override; //0x28 8064a58c
    void OnActivate() override; //0x30 8064a84c
    void AfterControlUpdate() override; //0x4C 8064aac4
    int GetRuntimeTypeInfo() const override; //8064aea8 returns 809C1ee8
    void FillVRControl(u32 r4, u32 index, u32 team, u8 type, bool isLocalPlayer, u8 aid); //8064ab08
    void OnButtonClick(PushButton *button, u32 hudSlotId); //8064ae6c
    //r4 related to teams, some sort of index+side thing type: 1 = WW 2 = battle WW 0 = others
    PtmfHolder_2A<Page, void, PushButton *, u32> onButtonClickHandler; //808bfd70 8064ae6c
    ControlsManipulatorManager manipulatorManager;
    CtrlMenuPageTitleText ctrlMenuBackButton;
    CtrlMenuInstructionText ctrlMenuBottomMessage;
    PushButton okButton; //0x564
    LayoutUIControl vrControls[12]; //7b8
    CountDown *timer; //from page 0x90
}; //total size 0x192c
size_assert(VR, 0x192c);
}//namespace Pages
#endif