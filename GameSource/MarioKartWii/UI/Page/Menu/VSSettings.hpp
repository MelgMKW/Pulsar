#ifndef _VSSETTINGS_
#define _VSSETTINGS_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Ctrl/UpDown.hpp>
#include <MarioKartWii/UI/Ctrl/RadioButton.hpp>

/*
Contributors:
-Melg
*/
//_sinit_ at 80853ca4
namespace Pages {
class VSSettings : public MenuInteractable { //ID 0x73
public:
    static const PageId id = PAGE_VS_SETTINGS;
    VSSettings(); //806284c8
    ~VSSettings() override; //80853b10 vtable 808da3c8
    void OnInit() override; //0x28 80852d90
    void OnDispose() override; //0x2C 80853a8c
    void OnActivate() override; //0x30 8085354c
    void AfterControlUpdate() override; //80853650
    int GetRuntimeTypeInfo() const override; //0x60 returns 809c4538 80853bd8
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64 80853684
    int GetActivePlayerBitfield() const override; //0x68 80853aa4
    int GetPlayerBitfield() const override; //0x6C 80853a9c
    ManipulatorManager& GetManipulatorManager() override; //0x70 80853b08
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 80853028
    UIControl* CreateControl(u32 controlId) override; //0x88 808530b8
    void SetButtonHandlers(PushButton& button) override; //0x8C 80853aac
    void OnButtonClick(PushButton& button, u32 hudSlotId); //80853654 refers to back button
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //808536b0
    void OnBackPress(u32 hudSlotId); //808536b4
    void OnRadioClick(RadioButtonControl& control, u32 hudSlotId, u32 buttonId); //80853714
    void OnRadioChange(RadioButtonControl& control, u32 hudSlotId, u32 buttonId); //8085389c
    void OnUpDownChange(UpDownControl& control, u32 hudSlotId, u32 optionId); //80853998
    void OnUpDownClick(UpDownControl& control, u32 hudSlotId); //80853c74
    void OnUpDownSelect(UpDownControl& control, u32 hudSlotId); //80853c74
    void OnTextChange(TextUpDownValueControl::TextControl* control, u32 hudSlotId); //80853a10

    static Page* GetPageById(PageId id = PAGE_VS_SETTINGS); //80852c80
    static void TriggerRadioPtmf(PtmfHolder_3A<Page, void, RadioButtonControl&, u32, s32>, RadioButtonControl* control, u32 hudSlotId, u32 buttonId); //80853c14
    static void TriggerUpDown2APtmf(PtmfHolder_2A<Page, void, UpDownControl&, u32>, UpDownControl* control, u32 hudSlotId); //80853c74
    static void TriggerUpDown3APtmf(PtmfHolder_3A<Page, void, UpDownControl&, u32, u32>, UpDownControl* control, u32 hudSlotId, u32 optionId); //80853be4
    static void TriggerTextPtmf(PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl&, u32>, TextUpDownValueControl::TextControl&, u32 hudSlotId); //80853c44

    //onButtonClick    vtable = 0x808bd06c function = 80853654
    //onButtonSelect   vtable = 0x808bd06c offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd06c function = 808536b0
    //onBackPress      vtable = 0x808bd060 function = 808536b4
    //onStartPress     vtable = 0x808bd060 offset   = 0x7c call is virtual

    RadioButtonControl radioButtonControls[5]; //0x6c4
    UpDownControl upDownControl[1]; //0x13BC
    TextUpDownValueControl textUpDownValueControl[1]; //0x1984
    PtmfHolder_3A<Page, void, RadioButtonControl&, u32, s32>* radioButtonClickHandler; //0x1DF8
    PtmfHolder_3A<Page, void, RadioButtonControl&, u32, s32>* radioButtonChangeHandler;  //0x1DFC
    PtmfHolder_3A<Page, void, UpDownControl&, u32, u32>* upDownChangeHandler; //0x1E00 //when you scroll
    PtmfHolder_2A<Page, void, UpDownControl&, u32>* upDownClickHandler; //0x1E04
    PtmfHolder_2A<Page, void, UpDownControl&, u32>* upDownSelectHandler; //0x1E08
    PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl&, u32>* onTextChangeHandler; //0x1E0C
}; //0x1E10
size_assert(VSSettings, 0x1e10);
}//namespace Pages
#endif