#ifndef _REGISTER_FRIEND_PAGE_
#define _REGISTER_FRIEND_PAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>
#include <MarioKartWii/UI/Ctrl/NumericEditBox.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>



//_sinit_ at 8061e87c
class FriendMatchingPlayer;
class RegisterFriend;

namespace Pages {
class RegisteringFriend : public Page { //ID 0xA5
public:
    RegisteringFriend(); //8061d214
    ~RegisteringFriend(); //8061d288 vtable 808bb740
    virtual PageId GetNextPage() const; //0x10 8061dc40
    virtual int IsHomeMenuWorking() const; //0x14 8061dc9c
    virtual void OnInit(); //0x28 8061d300
    virtual void OnActivate(); //0x30 8061d3a8
    virtual void BeforeEntranceAnimations(); //0x38 8061d4c8
    virtual void BeforeExitAnimations(); //0x40 8061d4cc
    virtual void AfterControlUpdate(); //0x4c 8061d4d0
    virtual void OnResume(); //0x54 8061d628
    virtual const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const; //0x60 8061e810

    CtrlMenuPageTitleText titleText; //0x44
    u32 status; //0x1b8
    ManipulatorManager manipulatorManager;
    Text::Info friendCodeIntPass; //0x1cc
    Text::Info textInfo2; //0x1cc
    u8 unknown_0x354[4];
    u64 friendCode; //0x358
    RegisterFriend* registerFriend; //0x360
    u8 unknown_0x364[4];

};
size_assert(RegisteringFriend, 0x368);

class RegisterFriend : public Page { //ID 0xA6
public:
    static const PageId id = PAGE_REGISTER_FRIEND;
    RegisterFriend(); //8061dcb8
    ~RegisterFriend(); //8061def0 vtable 808bb6ac
    virtual void OnInit(); //0x28 8061dfb4
    virtual void OnActivate(); //0x30 8061e270
    virtual const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const; //0x60 8061e804

    void OnDigitClick(PushButton& digit, u32 hudSlotId); //8061e348
    void OnBackSpaceClick(PushButton& backSpace, u32 hudSlotId); //8061e3b4
    void OnOkButtonClick(PushButton& okButton, u32 hudSlotId); //8061e400
    void OnBackButtonClick(CtrlMenuBackButton& backbutton, u32 hudSlotId); //8061e6ec
    void OnOkButtonSelect(PushButton& okButton, u32 hudSlotId); //8061e730
    void OnOkButtonDeselect(PushButton& okButton, u32 hudSlotId); //8061e76c
    void OnBackPress(u32 hudSlotId); //8061e77c

    PushButton numPad[10]; //0x44 10 digits
    PushButton backSpace; //0x178c
    PushButton okButton; //0x19e0
    NumericEditBox numericBox; //0x1c34 the box at the top of the numpad
    CtrlMenuBackButton backButton; //0x1ea8
    CtrlMenuInstructionText instructionText; //0x210c
    ControlsManipulatorManager manipulatorManager; //0x2280
    PtmfHolder_2A<RegisterFriend, void, PushButton&, u32> onDigitClickHandler; //0x24a4 8061e348
    PtmfHolder_2A<RegisterFriend, void, PushButton&, u32> onBackSpaceClickHandler; //0x24b8 8061e3b4
    PtmfHolder_2A<RegisterFriend, void, PushButton&, u32> onOkButtonClickHandler; //0x24cc 8061e400
    PtmfHolder_2A<RegisterFriend, void, CtrlMenuBackButton&, u32> onBackButtonClickHandler; //0x24e0 8061e6ec
    PtmfHolder_2A<RegisterFriend, void, PushButton&, u32> onOkSelectHandler; //0x24f4 8061e730
    PtmfHolder_2A<RegisterFriend, void, PushButton&, u32> onOkDeselectHandler; //0x2508 8061e76c
    PtmfHolder_1A<RegisterFriend, void, u32> onBackPressHandler; //0x251c 8061e77c
    u32 unknown_0x2530; //0x2530
};
size_assert(RegisterFriend, 0x2534);

}//namespace Pages
#endif