#ifndef _YESNO_
#define _YESNO_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>

//_sinit_ at 806531dc
namespace Pages {
class YesNo : public Page {
public:
    static const PageId id = PAGE_YESNO_FULL; //ID 0x53
    YesNo(); //80652300 inlined
    ~YesNo() override; //806523a4 vtable 808c08e8
    void OnInit() override; //0x28 80652430
    void OnActivate() override; //0x30 806524c4
    void AfterControlUpdate() override; //0x4c 80652564
    int GetRuntimeTypeInfo() const override; //0x60 806531a0
    virtual void Reset(); //0x64 806525a0

    void SetMessageBoxMsg(u32 bmgId, Text::Info* text); //806525fc
    void PrepareButton(u32 buttonId, u32 bmgId, Text::Info* text, u32 endAnimDir,
        const PtmfHolder_2A<Page, void, u32, PushButton&> onClickPtmf); //80652604
    void OnButtonClick(PushButton& button, u32 hudSlotId); //80652678
    void SelectInitialButton(); //80652700

    static void TriggerPtmf(PtmfHolder_2A<YesNo, void, PushButton&, u32>& handler, PushButton& button, u32 hudSlotId); //806531ac


    PtmfHolder_2A<Page, void, u32, PushButton&>* onButtonClickObj[2]; //0x44 called by OnButtonClick, 1st arg is buttonId
    u32 unknown_0x44[2];
    ControlsManipulatorManager controlsManipulatorManager; //0x4c
    u32 clickedButtonId; //0x270
    u32 endAnimDir[2]; //0x274 animDir this page should end when a given button is clicked
    u32 initialButtonIdx; //0x27c
    PtmfHolder_2A<YesNo, void, PushButton&, u32> onClickHandler; //80652678
    PushButton buttons[2]; //0x294
    MessageWindowControl voteForNextCourse; //0x73c
    u32 localPlayerBitfield; //0x8b0
    u8 unknown_0x8b4;
    u8 padding[3];
}; //total size 0x8b8
size_assert(YesNo, 0x8b8);

class YesNoPopUp : public YesNo { //ID 0x4e for example Choose/Random online cup select
public:
    class Container : public LayoutUIControl {
    public:
        Container(); //80652be0
        ~Container() override; //80652c1c
        void SetPositionAnim(PositionAndScale& positionAndScale, float curFrame) override; //0x20 80652d44
        int GetRuntimeTypeInfo() const override; //0x28 80653194
        const char* GetClassName() const override; //0x2c 80652bd0
        void Load(const char* folderName, const char* ctrName, const char* variant); //80652c74
    };
    YesNoPopUp(); //80652774
    ~YesNoPopUp() override; //8065284c vtable 808c0840
    void OnInit() override; //0x28 806528fc
    void BeforeEntranceAnimations() override; //0x38 80652b48
    void AfterExitAnimations() override; //0x44 80652b8c
    int GetRuntimeTypeInfo() const override; //0x60 80653188
    void Reset() override; //80652ce8
    BlackBackControlForMessage blackMsgBoxBg; //0x8b8
    Container container; //0xa2c
}; //total size 0xba0
size_assert(YesNoPopUp, 0xba0);

class YesNoFull : public YesNo { //ID 0x53 not displayed on top of another page, takes the whole space
public:
    YesNoFull(); //80652d7c
    ~YesNoFull() override; //80652e4c vtable 808c07d8
    void OnInit() override; //80652ef0
    void BeforeEntranceAnimations() override; //0x38 80653144
    void AfterExitAnimations() override; //0x44 80653160
    int GetRuntimeTypeInfo() const override; //0x60 8065317c
    void Reset() override; //806530d0
    void SetTitleMsg(u32 bmgId, Text::Info* textInfo = nullptr); //8065313c
    CtrlMenuPageTitleText titleText; //0x8b8
};
size_assert(YesNoFull, 0xa2c);

}//namespace Pages
#endif