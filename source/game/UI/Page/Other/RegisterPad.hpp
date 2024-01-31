#ifndef _X61PAGE_
#define _X61PAGE_
#include <kamek.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/System/RecognizePad.hpp>

//_sinit_ at 806056e4

class ConnectController : public LayoutUIControl {
public:
    ~ConnectController() override; //80603404 vtable 808ba868
    void InitSelf() override; //0x18 806035d8
    void OnUpdate() override; //0x1c 80603690
    int GetRuntimeTypeInfo() const override; //0x28 8060560c
    const char* GetClassName() const override; //0x2c 806033b8
    void Load(u32 hudSlotId); //8060345c
    u32 controllerID; //0x174 same as SectionPad's
};
size_assert(ConnectController, 0x178);

class EasyPairingController : public LayoutUIControl {
public:
    EasyPairingController(); //80604084
    ~EasyPairingController() override; //806040c0 vtable 808ba7b0
    void InitSelf() override; //0x18 806042a8
    void OnUpdate() override; //0x1c 806043b8
    int GetRuntimeTypeInfo() const override; //0x28 806055ec
    const char* GetClassName() const override; //0x2c 80604074
    void Load(u8 hudSlotId); //80604118
    u32 controllerID; //0x174 same as SectionPad's
    u8 hudSlotId; //0x178
    u8 padding[3];
};
size_assert(EasyPairingController, 0x17c);


namespace Pages {
class RegisteredPads : public Page { //ID 0x61 multiple register controllers
public:
    static const PageId id = PAGE_REGISTERED_PADS;
    RegisteredPads(); //80602f04
    ~RegisteredPads() override; //80602f68 vtable 808ba8a4
    PageId GetNextPage() const override; //0x10 80603308
    void OnInit() override; //0x28 80602fe8
    void OnActivate() override; //0x30 806030dc
    void BeforeEntranceAnimations() override; //0x38 80603250
    void AfterEntranceAnimations() override; //0x3c 80603254
    void AfterExitAnimations() override; //0x44 80603304
    void AfterControlUpdate() override; //0x4c 80603258
    int GetRuntimeTypeInfo() const override; //0x60 80605618
    void Register(u32 hudSlotId); //80603350
    PadControl padControls[4]; //0x44
    ManipulatorManager manipulatorManager; //0x654
    u32 localPlayerCount; //0x664
    bool canEnd; //0x668 when back is pressed on page 62 or when OK button
    u8 padding[3];
    u32 endAnimDirection; //0x66c
    float endAnimLength; //0x670
}; //total size 0x674
size_assert(RegisteredPads, 0x674);

class RegisterPad : public Page { //ID 0x62
public:
    static const PageId id = PAGE_REGISTER_PAD;
    RegisterPad(); //80603764
    ~RegisterPad() override; //806038e8 vtable 808ba7ec
    PageId GetNextPage() const override; //80603f10 
    int IsHomeMenuWorking() const override; //0x14 806055f8
    bool IsDVDEnabled() override; //0x18 80603f28 
    void OnInit() override; //0x28 806039a4
    void OnActivate() override; //0x30 80603b90
    void AfterControlUpdate() override; //0x4c 80603ba4
    int GetRuntimeTypeInfo() const override; //0x60 80605600

    void OnBackPress(u32 hudSlotId); //80603f70
    void OnStartPress(u32 hudSlotId); //80603fbc display the register wiimote page "press 1 and 2 simultaneously"

    PtmfHolder_1A<RegisterPad, void, u32> onBackPressHandler; //0x44 80603f70
    PtmfHolder_1A<RegisterPad, void, u32> onStartPress; //0x58 80603fbc
    PageManipulatorManager manipulatorManager; //0x6c
    CtrlMenuPageTitleText titleText; //0x1b0
    LayoutUIControl addWiiRemotesMsg; //0x324
    ConnectController connectControllers[4]; //0x498
    CtrlMenuInstructionText bottomText; //0xa78
    CtrlMenuDummyBack dummyBackButton; //0xbec
};
size_assert(RegisterPad, 0xd70);

class PairWiimotes : public Page {
public:
    static const PageId id = PAGE_PAIR_WII_REMOTES; //ID 0x63
    enum Status {
        STATUS_END, //for example when all 4 wiimotes are connected
    };
    PairWiimotes(); //80604584
    ~PairWiimotes() override; //80604638 vtable 808ba740
    void OnInit() override; //806046dc
    void OnActivate() override; //80604940
    void OnDeactivate() override; //0x34 806049e4
    void BeforeEntranceAnimations() override; //0x38 806049cc
    void AfterEntranceAnimations() override; //0x3c 806049c0
    void BeforeExitAnimations() override; //0x40 806049d8
    void AfterControlUpdate() override; //0x4c 80604a88
    int GetRuntimeTypeInfo() const override; //0x60 806055e0

    void SyncWiimotes(); //80604b00 also unsyncs based on status
    void OnBackAndStartPress(u32 hudSlotId); //80604c84

    PtmfHolder_1A<RegisterPad, void, u32> onBackAndStartPressHandler; //0x44 80604c84
    PageManipulatorManager manipulatorManager; //0x58
    LayoutUIControl bgWindow; //0x19c
    LayoutUIControl press12Msg; //0x310
    LayoutUIControl okMsg; //0x484
    EasyPairingController easyPairings[4]; //0x5f8
    Status status; //0xbe8
    float unknown_0xbec;
};
size_assert(PairWiimotes, 0xbf0);

class ConfirmPads : public Page {
public:
    static const PageId id = PAGE_CONFIRM_PAD;
    ConfirmPads(); //80604cd8
    ~ConfirmPads() override; //80604ea0 vtable 808ba6b8
    PageId GetNextPage() const override; //0x10 806055cc
    void OnInit() override; //0x28 80604f50
    void OnActivate() override; //0x30 80605198
    void OnDeactivate() override; //0x34 806051e4
    int GetRuntimeTypeInfo() const override; //0x60 806055d4

    void OnOkButtonClick(PushButton& button, u32 hudSlotId);     //80605204
    void OnChangeButtonClick(PushButton& button, u32 hudSlotId); //80605260
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId); //80605340
    void OnButtonSelect(PushButton& button, u32 hudSlotId);      //80605470
    void OnBackPress(u32 hudSlotId); //806054c4

    PtmfHolder_2A<ConfirmPads, void, PushButton&, u32> onOkButtonClickHandler; //0x44 80605204
    PtmfHolder_2A<ConfirmPads, void, PushButton&, u32> onChangeButtonClickHandler; //0x58 80605260
    PtmfHolder_2A<ConfirmPads, void, CtrlMenuBackButton&, u32> onBackButtonClickHandler; //0x6c 80605340
    PtmfHolder_2A<ConfirmPads, void, PushButton&, u32> onButtonSelectHandler; //0x80 80605470
    PtmfHolder_1A<ConfirmPads, void, u32> onBackPressHandler; //0x94 806054c4
    ControlsManipulatorManager manipulatorManager; //0xa8
    CtrlMenuPageTitleText titleText; //0x2cc
    PushButton okButton; //0x440
    PushButton changeButton; //0x694
    CtrlMenuBackButton backButton; //0x8e8
    CtrlMenuInstructionText bottomText; //0xb4c
    PageId nextPage; //0xcc0
};
size_assert(0xcc4, ConfirmPads);


}//namespace Pages
#endif