#ifndef _BATTLESETTINGS_
#define _BATTLESETTINGS_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/UpDown.hpp>
#include <game/UI/Ctrl/RadioButton.hpp>

//_sinit_ at 8083cb44
namespace Pages {
class BattleSettings : public MenuInteractable { //ID 0x77
    BattleSettings(); //80629184
    ~BattleSettings() override; //8083c9b0 808d9188
    void OnInit() override; //8083bc5c 0x28
    void OnActivate() override; //8083c3a4 0x30
    void AfterControlUpdate() override; //8083c504 0x4c
    int GetRuntimeTypeInfo() const override; //8083ca78 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //8083c50c 0x64 
    int GetActivePlayerBitfield() const override; //8083c944 0x68
    int GetPlayerBitfield() const; //8083c93c 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //8083c9a8 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //8083bf50 0x84
    UIControl *CreateControl(u32 controlId) override; //8083bfe0 0x88
    void SetButtonHandlers(PushButton *button) override; //8083c94c 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //8083c508 refers to back button
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8083c538
    void OnBackPress(u32 hudSlotId); //8083c53c

    void OnRadioClick(RadioButtonControl *control, u32 hudSlotId, u32 buttonId); //8083c580
    void OnRadioChange(RadioButtonControl *control, u32 hudSlotId, u32 buttonId); //8083c6ec
    void OnUpDownChange(UpDownControl *control, u32 hudSlotId, u32 optionId); //8083c848
    void OnUpDownClick(UpDownControl *control, u32 hudSlotId); //8083c7cc
    void OnUpDownSelect(UpDownControl *control, u32 hudSlotId); //8083c838
    void OnTextChange(TextUpDownValueControl::TextControl *control, u32 hudSlotId); //8083c8c0

    static Page *GetPageById(PageId id = PAGE_BATTLE_SETTINGS); //8083bb4c
    static void TriggerRadioPtmf(PtmfHolder_3A<Page, void, RadioButtonControl *, u32, s32>, RadioButtonControl *control, u32 hudSlotId, u32 buttonId); //8083cab4
    static void TriggerUpDown2APtmf(PtmfHolder_2A<Page, void, UpDownControl *, u32>, UpDownControl *control, u32 hudSlotId); //8083cb14
    static void TriggerUpDown3APtmf(PtmfHolder_3A<Page, void, UpDownControl *, u32, u32>, UpDownControl *control, u32 hudSlotId, u32 optionId); //8083ca84
    static void TriggerTextPtmf(PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl *, u32>, TextUpDownValueControl::TextControl *, u32 hudSlotId); //8083cae4
    //onButtonClick 0x658 vtable 808bd18c 8083c508
    //onButtonSelect 0x66C vtable 808bd18c virtual off 0x64
    //onButtonDeselect0x680 vtable 808bd18c 8083c538
    //onBackPress 0x694 vtable 808bd18c 8083c53c
    //onStartPress 0x6A8 vtable 808bd18c virtual off 0x7C

    RadioButtonControl radioButtonControls[4]; //0x6c4
    UpDownControl upDownControl[1]; //0x1124
    TextUpDownValueControl textUpDownValueControl[1]; //0x16ec
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, s32> *radioButtonClickHandler; //0x1b60
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, s32> *radioButtonChangeHandler;  //0x1b64
    PtmfHolder_3A<Page, void, UpDownControl *, u32, u32> *upDownChangeHandler; //0x1b68 //when you scroll
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *upDownClickHandler; //0x1b6c
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *upDownSelectHandler; //0x1b70
    PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl *, u32> *onTextChangeHandler; //0x1b74
    //0x1b60





}; //0x1b78
size_assert(BattleSettings, 0x1b78);
}//namespace Pages
#endif