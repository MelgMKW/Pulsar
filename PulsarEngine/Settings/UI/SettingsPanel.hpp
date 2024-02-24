#ifndef _PUL_SETTINGSPAGE_
#define _PUL_SETTINGSPAGE_
#include <kamek.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Page/Menu/VSSettings.hpp>
#include <Settings/UI/ExpOptionsPage.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#include <Settings/UI/ExpSinglePlayer.hpp>

/*SettingsPanel which has (currently) 3 pages for menu, race and host settings
Inspired by VSRaceSettings but does not extend it as I wanted a custom amount of radioControls/scrollers depending on the page
*/
extern u32 VSSettingsStaticAddr;

namespace Pulsar {
namespace UI {
/*
class TextUpDownValueControlwID: public TextUpDownValueControl {
public:
    TextUpDownValueControlwID() {};
    void SetMessage(u32 optionId) override; //this is needed because usually the bottom message does not vary while scrolling
    u32 id; //the onScroll handler doesn't pass the ID
};
*/

class SettingsPanel : public Pages::MenuInteractable {
public:
    static int pageCount;
    static const PageId firstId = PAGE_GP_INTERFACE;
    static const int maxPageCount = 5;
    static u8 radioButtonCount[maxPageCount];
    static u8 scrollerCount[maxPageCount];
    static u8 buttonsPerPagePerRow[maxPageCount][8];
    static u8 optionsPerPagePerScroller[maxPageCount][8];

    static inline void CreatePanels(Section* section);
    SettingsPanel(u32 sheetIdx); //max 8 radios and 8 scrollers per instance
    ~SettingsPanel() override;
    void OnInit() override; //To be defined
    void OnActivate() override; //TO BE DEFINED
    int GetRuntimeTypeInfo() const override; //80853bd8
    void OnExternalButtonSelect(PushButton& button, u32 r5) override;
    int GetActivePlayerBitfield() const override;
    int GetPlayerBitfield() const override;
    ManipulatorManager& GetManipulatorManager() override; //offset 0x70
    UIControl* CreateExternalControl(u32 id) override; //0x84
    UIControl* CreateControl(u32 id) override; //0x88
    void SetButtonHandlers(PushButton& pushButton) override; //80853aac 0x8C
    void OnBackPress(u32 hudSlotId);

private:
    static void SaveSettings(bool writeFile);
    void OnSaveButtonClick(PushButton& button, u32 hudSlotId);
    void OnRightButtonClick(PushButton& button, u32 hudSlotId);
    void OnLeftButtonClick(PushButton& button, u32 hudSlotId);
    void OnButtonClick(PushButton& button, u32 direction);
    void OnRadioButtonChange(RadioButtonControl& radioButtonControl, u32 r5, u32 optionId);

    void OnUpDownClick(UpDownControl& upDownControl, u32 hudSlotId);
    void OnUpDownSelect(UpDownControl& upDownControl, u32 hudSlotId);

    void OnTextChange(TextUpDownValueControl::TextControl& text, u32 optionId);
    void LoadPrevMenuAndSaveSettings(PushButton& button);
    int GetNextIdx(s32 direction); //1 for right, -1 for left
    u32 GetTextId(const TextUpDownValueControl::TextControl& text) const {
        TextUpDownValueControl* valueControl = static_cast<TextUpDownValueControl*>(text.parentGroup->parentControl);
        return static_cast<int>(reinterpret_cast<u32>(valueControl) - reinterpret_cast<u32>(&this->textUpDown[0])) / sizeof(TextUpDownValueControl);
    }

    RadioButtonControl* radioButtonControls; //0x6C4
    PtmfHolder_3A<SettingsPanel, void, RadioButtonControl&, u32, u32> onRadioButtonChangeHandler; //0x6c8
    u32 radioCount; //0x6dc
    UpDownControl* upDownControls; //0x6e8
    TextUpDownValueControl* textUpDown; //0x6ec
    PtmfHolder_2A<SettingsPanel, void, UpDownControl&, u32> onUpDownClickHandler; //0x6f0
    PtmfHolder_2A<SettingsPanel, void, UpDownControl&, u32> onUpDownSelectHandler; //0x704
    PtmfHolder_2A<SettingsPanel, void, TextUpDownValueControl::TextControl&, u32> onTextChangeHandler; //0x718 when you scroll
    u32 scrollersCount; //0x72c
    PtmfHolder_2A<MenuInteractable, void, PushButton&, u32> onRightButtonClickHandler; //0x738
    PtmfHolder_2A<MenuInteractable, void, PushButton&, u32> onLeftButtonClickHandler; //0x74c
public:
    u32 sheetIdx; //0x750
};
}//namespace UI
}//namespace Pulsar
#endif