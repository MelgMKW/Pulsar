#ifndef _WFCMAIN_
#define _WFCMAIN_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
/*
Contributors:
-Melg
*/
class FriendStatusButton : public PushButton {
    //no ctor, vtable 0x808bffc0
    ~FriendStatusButton() override; //8064b2fc
    u32 frames; //increments by 1 each frame, resets at 300
    u32 unknown_0x25C; //idk
}; //total size 0x25C

namespace Pages {
class WFCMain : public Page { //ID 0x8B
public:
    WFCMain(); //8064b640
    ~WFCMain() override; //vtable 0x808bff44 8064b850
    PageId GetNextPage() const override; //0x8064d688
    void OnInit() override; //0x8064b910 
    void OnActivate() override; //0x8064bc90
    int GetRuntimeTypeInfo() const override; //0x8064d690
    void OnButtonSelect(PushButton *pushButton, u32 hudSlotId); //8064bf4c
    PtmfHolder_2A<WFCMain, void, PushButton *, u32> onWorldwideClick; //0x44 vtable 808bffb4 8064bce8
    PtmfHolder_2A<WFCMain, void, PushButton *, u32> onContinentalClick; //0x58 vtable 808bffb4 8064bdc4
    PtmfHolder_2A<WFCMain, void, PushButton *, u32> onFriendsClick; //0x6C vtable 808bffb4 8064bea0
    PtmfHolder_2A<WFCMain, void, PushButton *, u32> onBackButtonPress; //0x80 vtable 808bffb4 8064bee4 ctrlmenubackbutton
    PtmfHolder_2A<WFCMain, void, PushButton *, u32> onButtonSelectHandler; //0x94 vtable 808bffb4 8064bf4c
    PtmfHolder_1A<WFCMain, void, u32> onBackPress; //0xA8 vtable 808bffa8 8064bfb8
    CtrlMenuPageTitleText ctrlMenuPageTitleText; //0xBC
    PushButton worldwideButton; //0x230
    PushButton continentalButton; //0x484
    FriendStatusButton friendsButton; //0x6D8
    CtrlMenuBackButton backButton; //0x934
    CtrlMenuInstructionText bottomText; //0xb98
    ControlsManipulatorManager manipulatorManager; //0xd0c
    PageId nextPageId; //when you press a button
};//total size 0xf34
size_assert(WFCMain, 0xf34);
}//namespace Pages
#endif