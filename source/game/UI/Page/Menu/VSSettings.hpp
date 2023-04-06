#ifndef _VSSETTINGS_
#define _VSSETTINGS_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/UpDown.hpp>
#include <game/UI/Ctrl/RadioButton.hpp>

/*
Contributors:
-Melg
*/
//_sinit_ at 80853ca4
namespace Pages {
class VSSettings : public MenuInteractable { //ID 0x73
public:
    VSSettings(); //0x806284c8
    ~VSSettings() override; //80853b10 vtable 0x808da3c8
    void OnInit() override; //80852d90 0x28
    void OnDispose() override; //80853a8c 0x2C
    void OnActivate() override; //8085354c 0x30
    void AfterControlUpdate() override; //80853650
    int GetRuntimeTypeInfo() const override; //80853bd8 0x60 returns 809c4538
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //80853684 0x64
    int GetActivePlayerBitfield() const override; //80853aa4 0x68
    int GetPlayerBitfield() const; //80853a9c 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //80853b08 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //80853028 0x84
    UIControl *CreateControl(u32 controlId) override; //808530b8 0x88
    void SetButtonHandlers(PushButton *button) override; //80853aac 0x8C
    void OnButtonClick(PushButton *button, u32 hudSlotId); //80853654refers to back button
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //808536b0
    void OnBackPress(u32 hudSlotId); //808536b4
    void OnRadioClick(RadioButtonControl *control, u32 hudSlotId, u32 buttonId); //80853714
    void OnRadioChange(RadioButtonControl *control, u32 hudSlotId, u32 buttonId); //8085389c
    void OnUpDownChange(UpDownControl *control, u32 hudSlotId, u32 optionId); //80853998
    void OnUpDownClick(UpDownControl *control, u32 hudSlotId); //80853c74
    void OnUpDownSelect(UpDownControl *control, u32 hudSlotId); //80853c74
    void OnTextChange(TextUpDownValueControl::TextControl *control, u32 hudSlotId); //80853a10

    static Page *GetPageById(PageId id = PAGE_VS_SETTINGS); //80852c80
    static void TriggerRadioPtmf(PtmfHolder_3A<Page, void, RadioButtonControl *, u32, s32>, RadioButtonControl *control, u32 hudSlotId, u32 buttonId); //80853c14
    static void TriggerUpDown2APtmf(PtmfHolder_2A<Page, void, UpDownControl *, u32>, UpDownControl *control, u32 hudSlotId); //80853c74
    static void TriggerUpDown3APtmf(PtmfHolder_3A<Page, void, UpDownControl *, u32, u32>, UpDownControl *control, u32 hudSlotId, u32 optionId); //80853be4
    static void TriggerTextPtmf(PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl *, u32>, TextUpDownValueControl::TextControl *, u32 hudSlotId); //80853c44
    //onButtonClick 0x658 vtable 808bd18c 80853654
    //onButtonSelect 0x66C vtable 808bd18c virtual off 0x64
    //onButtonDeselect0x680 vtable 808bd18c 808536b0
    //onBackPress 0x694 vtable 808bd18c 808536b4
    //onStartPress 0x6A8 vtable 808bd18c virtual off 0x7C

    RadioButtonControl radioButtonControls[5]; //0x6c4
    UpDownControl upDownControl[1]; //0x13BC
    TextUpDownValueControl textUpDownValueControl[1]; //0x1984
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, s32> *radioButtonClickHandler; //0x1DF8
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, s32> *radioButtonChangeHandler;  //0x1DFC
    PtmfHolder_3A<Page, void, UpDownControl *, u32, u32> *upDownChangeHandler; //0x1E00 //when you scroll
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *upDownClickHandler; //0x1E04
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *upDownSelectHandler; //0x1E08
    PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl *, u32> *onTextChangeHandler; //0x1E0C
}; //0x1E10
size_assert(VSSettings, 0x1e10);
}//namespace Pages
#endif