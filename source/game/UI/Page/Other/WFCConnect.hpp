#ifndef _WFCCONNECTPAGEaa&_
#define _WFCCONNECTPAGEaa&_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>

namespace Pages {
//_sinit_ at 0x8064944c
class WFCConnect : public Page { //ID 0x84
public:
    static const PageId id = PAGE_WFC_CONNECT;
    enum Status {};
    WFCConnect(); //806467d4
    ~WFCConnect() override; //80646850 vtable 808bfaa4
    PageId GetNextPage() const override; //0x10 806478c4
    int IsHomeMenuWorking() const override; //0x14 80647998
    void OnInit() override; //0x28 806468b8
    void OnActivate() override; //0x30 80646924
    void OnDeactivate() override; //0x34 80646e00
    void BeforeEntranceAnimations() override; //0x38 80646dd4
    void AfterEntranceAnimations() override; //0x3c 80646dd8
    void BeforeExitAnimations() override; //0x40 80646df8
    void AfterExitAnimations() override; //0x44 80646dfc
    void AfterControlUpdate() override; //0x4c 80646eb0
    void OnResume() override; //0x54 806474e8
    int GetRuntimeTypeInfo() const override; //0x60 806492f0

    void SetText(); //806479dc title, globe etc...
    static u32 GetTitleBMGId(); //80647cec
    void OnDisconnect(); //80647db8 unused?
    PtmfHolder_0A<WFCConnect, void> onDisconnectHandler; //0x44 80647db8
    Status status; //0x58
    ManipulatorManager manipulatorManager; //0x5c
    u8 unknown_0x6c[2];
    bool isConnected;
    u8 padding;
};
size_assert(WFCConnect, 0x70);

class WFCDataStatement : public Page { //ID 0x85 https://imgur.com/Qy2s24P
public:
    static const PageId id = PAGE_WFC_DATA_STATEMENT;
    WFCDataStatement(); //80647ecc
    ~WFCDataStatement() override; //80647fe4 vtable 808bfa28
    void OnInit() override; //0x28 80648084
    void OnActivate() override; //0x30 80648220
    int GetRuntimeTypeInfo() const override; //0x60 806492e4

    void OnButtonClick(PushButton& button, u32 hudSlotId); //80648404
    void OnBackPress(); //80648480
    void SetType(u32 type);
    PtmfHolder_2A<WFCDataStatement, void, PushButton&, u32> onButtonClickHandler; //0x44 80648404
    PtmfHolder_1A<WFCDataStatement, void, u32> onBackPressHandler; //0x58 80648480
    ControlsManipulatorManager manipulatorManager; //0x6c
    CtrlMenuPageTitleText titleText; //0x290
    MessageWindowControl explanationBox; //0x404
    PushButton nextButton; //0x578
    CtrlMenuBackButton backButton; //0x7cc
    u32 type; //0xa30 0: no back button, message bmg id 7401 (when you play) 1: back button, message bmg id 7408 (mii privacy)
    u8 unknown_0xa34[4];
};
size_assert(WFCDataStatement, 0xa38);

class WFCAllowData : public Page { // ID 0x86 https://imgur.com/o7Gyanj
public:
    static const PageId id = PAGE_WFC_DATA_ALLOW;
    WFCAllowData(); //806484a8
    ~WFCAllowData() override; //80648610 vtable 808bf994
    void OnInit() override; //0x28 806486bc
    void OnActivate() override; //0x30 806488b4
    void OnResume() override; //0x54 80648a24
    int GetRuntimeTypeInfo() const override; //0x60 806492d8

    void OnButtonClick(PushButton& button, u32 hudSlotId); //80648afc
    void OnBackButtonClick(CtrlMenuBackButton& backButton, u32 hudSlotId); //80648afc

    PtmfHolder_2A<WFCAllowData, void, PushButton&, u32> onButtonClickHandler; //0x44 80648afc
    PtmfHolder_2A<WFCAllowData, void, CtrlMenuBackButton&, u32> onBackButtonClickHandler; //0x44 80648c9c
    PtmfHolder_1A<WFCAllowData, void, u32> onBackPressHandler; //0x58 80648cb4
    ControlsManipulatorManager manipulatorManager; //0x80
    CtrlMenuPageTitleText titleText; //0x2a4
    MessageWindowControl explanationBox; //0x418
    PushButton nextButton; //0x58c
    PushButton nextButton; //0x7e0
    CtrlMenuBackButton backButton; //0xa34
    u32 unknown_0xc98;

};
size_assert(WFCAllowData, 0xc9c);

class WFCDisconnect : public Page { //ID 0x87, fills YesNo PopUp with "Disconnect from Nintendo WFC"
public:
    static const PageId id = PAGE_WFC_DISCONNECT;
    WFCDisconnect(); //80648de8
    ~WFCDisconnect() override; //80648e64 vtable 808bf924
    void OnInit() override; //80648ecc
    void OnActivate() override; //0x30 80648f28
    void OnDeactivate() override; //0x34 8064912c sets DisconnectMgr's status
    void BeforeEntranceAnimations() override; //0x38 80649124
    void BeforeExitAnimations() override; //0x40 80649128
    void OnResume() override; //0x54 806491dc
    int GetRuntimeTypeInfo() const override; //0x60 806492cc

    void OnYesNoYesClick(PushButton& button, u32 buttonId); //806491ec

    u8 unknown_0x44[4];
    ManipulatorManager manipulatorManager; //0x48
    PtmfHolder_2A<WFCConnect, void, PushButton&, u32> onYesNoYesClickHandler; //0x58 806491ec "Schedule Disconnection"
};
size_assert(WFCDisconnect, 0x6c);


}//namespace Pages
#endif