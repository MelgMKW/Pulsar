#ifndef _PUL_SETTINGSPAGE_
#define _PUL_SETTINGSPAGE_
#include <kamek.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Page/Menu/VSSettings.hpp>
#include <Settings/PlayerData.hpp>
#include <Settings/UI/ExpOptionsPage.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#define SETTINGSPAGECOUNT 3

/*SettingsPanel which has (currently) 3 pages for menu, race and host settings
Inspired by VSRaceSettings but does not extend it as I wanted a custom amount of radioControls/scrollers depending on the page
*/
extern u32 VSSettingsStaticAddr;

namespace PulsarUI {
class TextUpDownValueControlwID : public TextUpDownValueControl {
public:
    TextUpDownValueControlwID() {};
    void SetMessage(u32 optionId) override; //this is needed because usually the bottom message does not vary while scrolling
    u32 id; //the onScroll handler doesn't pass the ID
};

class SettingsPanel : public Pages::MenuInteractable {
public:
    SettingsPanel(u32 radioCount, u32 scrollersCount, const u8 buttonsPerRow[8], const u8 optionsPerScroller[8], u32 sheetIdx); //max 8 radios and 8 scrollers per instance
    ~SettingsPanel() override;
    void OnInit() override; //To be defined
    void OnActivate() override; //TO BE DEFINED
    int GetRuntimeTypeInfo() const override; //80853bd8
    void OnExternalButtonSelect(PushButton *button, u32 r5) override;
    int GetActivePlayerBitfield() const override;
    int GetPlayerBitfield() const override;
    ManipulatorManager *GetManipulatorManager() override;; //offset 0x70
    UIControl *CreateExternalControl(u32 id) override; //0x84
    UIControl *CreateControl(u32 id) override; //0x88
    void SetButtonHandlers(PushButton *pushButton) override; //80853aac 0x8C
private:
    static void SaveSettings();
    void OnBackPress(u32 hudSlotId);
    void OnSaveButtonClick(PushButton *pushButton, u32 hudSlotId);
    void OnRightButtonClick(PushButton *button, u32 hudSlotId);
    void OnLeftButtonClick(PushButton *button, u32 hudSlotId);

    void OnRadioButtonChange(RadioButtonControl *radioButtonControl, u32 r5, u32 optionId);

    void OnUpDownClick(UpDownControl *upDownControl, u32 hudSlotId);
    void OnUpDownSelect(UpDownControl *upDownControl, u32 hudSlotId);

    void OnTextChange(TextUpDownValueControl::TextControl *text, u32 optionId);
    void LoadPrevMenuAndSaveSettings(PushButton *button);

    //0x658 vtable 808bd18c 80853654
    //0x66C vtable 808bd18c virtual off 0x64
    //0x680 vtable 808bd18c 808536b0
    //0x694 vtable 808bd18c 808536b4
    //0x6A8 vtable 808bd18c virtual off 0x7C


    RadioButtonControl *radioButtonControls; //0x6C4
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> onRadioButtonChangeHandler;
    u32 radioCount;
    u8 buttonsPerRow[8];
    UpDownControl *upDownControls;
    TextUpDownValueControlwID *textUpDownwID; //0x1984
    PtmfHolder_2A<Page, void, UpDownControl *, u32> onUpDownClickHandler; //0x1E04
    PtmfHolder_2A<Page, void, UpDownControl *, u32> onUpDownSelectHandler; //0x1E08
    PtmfHolder_2A<Page, void, TextUpDownValueControl::TextControl *, u32> onTextChangeHandler; //when you scroll
    u32 scrollersCount;
    u8 optionsPerScroller[8];
    PtmfHolder_2A<MenuInteractable, void, PushButton *, u32> onRightButtonClickHandler;
    PtmfHolder_2A<MenuInteractable, void, PushButton *, u32> onLeftButtonClickHandler;
public:
    u32 sheetIdx;
};
}//namespace PulsarUI
#endif