#include <Settings/UI/SettingsPanel.hpp>
#include <Settings/Settings.hpp>
#include <Settings/UI/ExpOptionsPage.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace Pulsar {
namespace UI {

//SETTINGS PANEL
SettingsPanel::SettingsPanel()
{
    bmgOffset = 0;
    sheetIdx = 0;
    catIdx = 0;
    externControlCount = 3;
    internControlCount = Settings::Params::maxRadioCount + Settings::Params::maxScrollerCount;
    hasBackButton = false;
    nextPageId = static_cast<PageId>(id);
    //titleBmg = BMG_SETTINGS_TITLE;
    activePlayerBitfield = 1;
    movieStartFrame = -1;
    extraControlNumber = 0;
    isLocked = false;
    controlCount = 0;
    nextSection = SECTION_NONE;
    controlSources = 2;

    SectionId id = SectionMgr::sInstance->curSection->sectionId;
    if(id == SECTION_OPTIONS) prevPageId = PAGE_OPTIONS;
    else if((id == SECTION_P1_WIFI) || (id == SECTION_P1_WIFI_FROM_FROOM_RACE) || (id == SECTION_P1_WIFI_FROM_FIND_FRIEND)
        || (id == SECTION_P2_WIFI) || (id == SECTION_P2_WIFI_FROM_FROOM_RACE)) prevPageId = PAGE_WFC_MAIN;
    else if(id >= SECTION_LICENSE_SETTINGS_MENU && id <= SECTION_SINGLE_P_LIST_RACE_GHOST) prevPageId = PAGE_SINGLE_PLAYER_MENU;

    onMessageBoxClickHandler.ptmf = &Menu::ChangeToPrevSection;

    onRadioButtonClickHandler.subject = this;
    onRadioButtonClickHandler.ptmf = &SettingsPanel::OnRadioButtonClick;
    onRadioButtonChangeHandler.subject = this;
    onRadioButtonChangeHandler.ptmf = &SettingsPanel::OnRadioButtonChange;

    onUpDownClickHandler.subject = this;
    onUpDownClickHandler.ptmf = &SettingsPanel::OnUpDownClick;
    onUpDownSelectHandler.subject = this;
    onUpDownSelectHandler.ptmf = &SettingsPanel::OnUpDownSelect;

    onTextChangeHandler.subject = this;
    onTextChangeHandler.ptmf = &SettingsPanel::OnTextChange;

    onButtonSelectHandler.subject = this;
    onButtonSelectHandler.ptmf = &SettingsPanel::OnExternalButtonSelect;
    onButtonDeselectHandler.subject = this;
    onButtonDeselectHandler.ptmf = &Pages::VSSettings::OnButtonDeselect;
    onBackPressHandler.subject = this;
    onBackPressHandler.ptmf = &SettingsPanel::OnBackPress;
    onStartPressHandler.subject = this;
    onStartPressHandler.ptmf = &MenuInteractable::HandleStartPress;

    onButtonClickHandler.subject = this;
    onButtonClickHandler.ptmf = &SettingsPanel::OnSaveButtonClick;
    onRightButtonClickHandler.subject = this;
    onRightButtonClickHandler.ptmf = &SettingsPanel::OnRightButtonClick;
    onLeftButtonClickHandler.subject = this;
    onLeftButtonClickHandler.ptmf = &SettingsPanel::OnLeftButtonClick;

    this->controlsManipulatorManager.Init(1, false);
    this->SetManipulatorManager(controlsManipulatorManager);
    this->controlsManipulatorManager.SetGlobalHandler(START_PRESS, onStartPressHandler, false, false);
    this->controlsManipulatorManager.SetGlobalHandler(BACK_PRESS, onBackPressHandler, false, false);
};

SettingsPanel::~SettingsPanel() {
    Settings::Mgr* mgr = Settings::Mgr::sInstance;
    mgr->SetLastSelectedCup(CupsConfig::sInstance->lastSelectedCup);
    mgr->RequestSave();
    //delete[] radioButtonControls;
    //delete[] upDownControls;
    //delete[] textUpDown;
}

void SettingsPanel::OnInit() {
    //radioButtonControls = new RadioButtonControl[this->radioCount];
    //upDownControls = new UpDownControl[this->scrollersCount];
    //textUpDown = new TextUpDownValueControl[this->scrollersCount];

    const Settings::Mgr& settings = Settings::Mgr::Get();
    for(int i = 0; i < Settings::Params::pageCount; ++i) {
        for(int radioIdx = 0; radioIdx < Settings::Params::radioCount[i]; ++radioIdx) {
            this->radioSettings[i][radioIdx] = settings.GetSettingValue(static_cast<Settings::Type>(i), radioIdx);
        }
        for(int scrollerIdx = 0; scrollerIdx < Settings::Params::scrollerCount[i]; ++scrollerIdx) {
            this->scrollerSettings[i][scrollerIdx] = settings.GetSettingValue(static_cast<Settings::Type>(i), scrollerIdx + 6);
        }
    }
    MenuInteractable::OnInit();
    this->SetTransitionSound(0, 0);
};

UIControl* SettingsPanel::CreateExternalControl(u32 id) {
    const char* variant = "SAVE";
    if(id == 1) variant = "RIGHT";
    else if(id == 2) variant = "LEFT";
    PushButton* button = new(PushButton);
    this->AddControl(this->controlCount++, *button, 0);
    button->Load(UI::buttonFolder, "Settings", variant, this->activePlayerBitfield, 0, false);
    return button;
};

UIControl* SettingsPanel::CreateControl(u32 id) {
    const Settings::Mgr& settings = Settings::Mgr::Get();
    if(id < Settings::Params::maxRadioCount) {
        RadioButtonControl& radioButtonControl = this->radioButtonControls[id];
        this->AddControl(this->controlCount++, radioButtonControl, 0);

        char variant[12];
        char option0Variant[12];
        char option1Variant[12];
        char option2Variant[12];
        char option3Variant[12];
        snprintf(variant, 12, "Row%d", id);
        snprintf(option0Variant, 12, "%sOption%d", variant, 0);
        snprintf(option1Variant, 12, "%sOption%d", variant, 1);
        snprintf(option2Variant, 12, "%sOption%d", variant, 2);
        snprintf(option3Variant, 12, "%sOption%d", variant, 3);

        const char* optionVariants[5] ={ option0Variant, option1Variant, option2Variant, option3Variant, nullptr };
        radioButtonControl.Load(4, 0, UI::controlFolder, "RadioBase", variant, "RadioOption", optionVariants, 1, 0, 0);
        radioButtonControl.SetOnClickHandler(this->onRadioButtonClickHandler);
        radioButtonControl.SetOnChangeHandler(this->onRadioButtonChangeHandler);
        radioButtonControl.id = id;

    }
    else if(id < (Settings::Params::maxRadioCount + Settings::Params::maxScrollerCount)) {
        id -= Settings::Params::maxRadioCount;
        UpDownControl& upDownControl = this->upDownControls[id];
        this->AddControl(this->controlCount, upDownControl, 0);
        ++this->controlCount;

        char variant[12];
        snprintf(variant, 12, "UpDown%d", id);

        upDownControl.Load(7, 0, UI::controlFolder, "UpDownBase", variant, "UpDownR", "Right", "UpDownL",
            "Left", &this->textUpDown[id], 1, 0, false, true, true);
        upDownControl.SetOnClickHandler(this->onUpDownClickHandler);
        upDownControl.SetOnSelectHandler(this->onUpDownSelectHandler);
        upDownControl.id = id;

        TextUpDownValueControl& valueControl = this->textUpDown[id];
        valueControl.Load(UI::controlFolder, "UpDownValue", "Value", "UpDownText", "Text");
        valueControl.SetOnTextChangeHandler(this->onTextChangeHandler);

    }
    return nullptr;
}

void SettingsPanel::SetButtonHandlers(PushButton& button) {
    PtmfHolder_2A<MenuInteractable, void, PushButton&, u32>* onClickHandler = &this->onButtonClickHandler;
    if(button.buttonId == 1) onClickHandler = &this->onRightButtonClickHandler;
    else if(button.buttonId == 2) onClickHandler = &this->onLeftButtonClickHandler;
    button.SetOnClickHandler(*onClickHandler, 0);
    button.SetOnSelectHandler(this->onButtonSelectHandler);
    button.SetOnDeselectHandler(this->onButtonDeselectHandler);
}

void SettingsPanel::OnActivate() {
    this->titleBmg = this->bmgOffset + BMG_SETTINGS_TITLE + this->catIdx;
    this->externControls[0]->SelectInitial(0);
    this->bottomText->SetMessage(BMG_SETTINGS_BOTTOM); //no need for any offset here as this is the default "save" bottom msg

    this->externControls[1]->SetMessage(BMG_SETTINGS_PAGE + this->GetNextBMGOffset(1));
    this->externControls[2]->SetMessage(BMG_SETTINGS_PAGE + this->GetNextBMGOffset(-1));
    for(int i = 0; i < Settings::Params::maxRadioCount; ++i) {
        RadioButtonControl& radio = this->radioButtonControls[i];
        bool isDisabled = false;
        if(i >= Settings::Params::radioCount[this->sheetIdx]) isDisabled = true;
        radio.isHidden = isDisabled;
        radio.manipulator.inaccessible = isDisabled;

        if(!isDisabled) {
            radio.buttonsCount = Settings::Params::buttonsPerPagePerRow[this->sheetIdx][radio.id];
            const u8 setting = this->radioSettings[this->sheetIdx][radio.id];
            radio.chosenButtonId = setting;
            radio.selectedButtonId = setting;
            u32 bmgCategory = this->bmgOffset + BMG_RADIO_SETTINGS + (this->catIdx << 12);
            radio.SetMessage(radio.id + bmgCategory);

            for(int j = 0; j < 4; ++j) {
                bool isHidden = false;
                if(j >= Settings::Params::buttonsPerPagePerRow[this->sheetIdx][radio.id]) isHidden = true;
                radio.optionButtonsArray[j].isHidden = isHidden;
                if(!isHidden) radio.optionButtonsArray[j].SetMessage((radio.id + 1 << 4) + j + bmgCategory);
            }
        }
    }
    for(int i = 0; i < Settings::Params::maxScrollerCount; ++i) {
        UpDownControl& scroller = this->upDownControls[i];
        TextUpDownValueControl& valueControl = this->textUpDown[i];
        bool isDisabled = false;
        if(i >= Settings::Params::scrollerCount[this->sheetIdx]) isDisabled = true;
        scroller.isHidden = isDisabled;
        scroller.manipulator.inaccessible = isDisabled;
        scroller.optionsCount = Settings::Params::optionsPerPagePerScroller[this->sheetIdx][i];
        valueControl.isHidden = isDisabled;
        if(!isDisabled) {
            scroller.curSelectedOption = this->scrollerSettings[this->sheetIdx][i];
            u32 bmgCategory = this->bmgOffset + BMG_SCROLLER_SETTINGS + (this->catIdx << 12);
            scroller.SetMessage(scroller.id + bmgCategory);
            valueControl.activeTextValueControl->SetMessage((scroller.id + 1 << 4) + bmgCategory);
        }



    }
    MenuInteractable::OnActivate();
}

const ut::detail::RuntimeTypeInfo* SettingsPanel::GetRuntimeTypeInfo() const {
    return Pages::VSSettings::typeInfo;
}

void SettingsPanel::OnExternalButtonSelect(PushButton& button, u32 r5) {
    u32 bmgId = BMG_SETTINGS_BOTTOM; //default "save"
    const u32 id = button.buttonId;

    if(id == 1) bmgId += 1 + this->GetNextBMGOffset(1);
    else if(id == 2)  bmgId += 1 + this->GetNextBMGOffset(-1);
    this->bottomText->SetMessage(bmgId);
}

int SettingsPanel::GetActivePlayerBitfield() const {
    return this->activePlayerBitfield;
}

int SettingsPanel::GetPlayerBitfield() const {
    return this->playerBitfield;
}

ManipulatorManager& SettingsPanel::GetManipulatorManager() {
    return this->controlsManipulatorManager;
}

void SettingsPanel::LoadPrevMenuAndSaveSettings(PushButton& button) {
    this->LoadPrevPage(button);
    const Section* section = SectionMgr::sInstance->curSection;
    /*if(this->prevPageId == PAGE_OPTIONS) section->Get<ExpOptions>()->topSettingsPage = static_cast<PulPageId>(this->pageId);*/
    if(this->prevPageId == PAGE_WFC_MAIN) section->Get<ExpWFCMain>()->topSettingsPage = static_cast<PulPageId>(this->pageId);
    else if(this->prevPageId == PAGE_FRIEND_ROOM) {
        section->Get<ExpFroom>()->topSettingsPage = static_cast<PulPageId>(this->pageId);
        this->nextPageId = PAGE_NONE; //FriendRoom's OnResume is important
    }
    //else if(this->prevPageId == PAGE_SINGLE_PLAYER_MENU) ExpSinglePlayer::topSettingsPage = static_cast<PulPageId>(this->pageId);
    this->SaveSettings(true);
}

//On Save Click/Back Press, is called and updates PulsarSettings
void SettingsPanel::SaveSettings(bool writeFile) {
    const ExpSection* section = ExpSection::GetSection();
    Settings::Mgr* settings = Settings::Mgr::sInstance;

    for(int count = 0; count < Settings::Params::pageCount; ++count) {

        const bool isPulsarPage = count < Settings::Params::pulsarPageCount;
        for(int i = 0; i < Settings::Params::radioCount[count]; ++i) {
            const u8 value = this->radioSettings[count][i];
            if(isPulsarPage) settings->SetSettingValue(static_cast<Settings::Type>(count), i, value);
            else settings->SetUserSettingValue(static_cast<Settings::UserType>(count - Settings::Params::pulsarPageCount), i, value);
        }
        for(int i = 0; i < Settings::Params::scrollerCount[count]; ++i) {
            const u8 value = this->scrollerSettings[count][i];
            if(isPulsarPage) settings->SetSettingValue(static_cast<Settings::Type>(count), i + Settings::Params::maxRadioCount, value);
            else settings->SetUserSettingValue(static_cast<Settings::UserType>(count - Settings::Params::pulsarPageCount), i + Settings::Params::maxRadioCount, value);
        }
    }
    settings->Update();
}

void SettingsPanel::OnBackPress(u32 hudSlotId) {
    PushButton& okButton = *this->externControls[0];
    okButton.SelectFocus();
    this->LoadPrevMenuAndSaveSettings(okButton);
}

void SettingsPanel::OnSaveButtonClick(PushButton& button, u32 hudSlotId) {
    this->LoadPrevMenuAndSaveSettings(button);
}

void SettingsPanel::OnRightButtonClick(PushButton& button, u32 hudSlotId) {
    this->OnButtonClick(button, 1);
}

void SettingsPanel::OnLeftButtonClick(PushButton& button, u32 hudSlotId) {
    this->OnButtonClick(button, -1);
}

void SettingsPanel::OnButtonClick(PushButton& button, u32 direction) {
    this->nextPageId = this->pageId;
    const int nextIdx = this->GetNextSheetIdx(direction);
    this->sheetIdx = nextIdx;
    if(nextIdx < Settings::Params::pulsarPageCount) {
        this->catIdx = nextIdx;
        this->bmgOffset = 0;
    }
    else {
        this->catIdx = nextIdx - Settings::Params::pulsarPageCount; //5 becomes 0 if pulsarPageCount is 5
        this->bmgOffset = BMG_USERSETTINGSOFFSET;
    }

    this->EndStateAnimated(0, button.GetAnimationFrameSize());
    this->SaveSettings(false);
}

void SettingsPanel::OnRadioButtonClick(RadioButtonControl& radioButtonControl, u32 hudSlotId, u32 optionId) {
    this->radioSettings[this->sheetIdx][radioButtonControl.id] = optionId;
}

void SettingsPanel::OnRadioButtonChange(RadioButtonControl& radioButtonControl, u32 hudSlotId, u32 optionId) {
    this->bottomText->SetMessage(this->bmgOffset + BMG_RADIO_SETTINGS + (this->catIdx << 12) + (radioButtonControl.id + 1 << 8) + optionId);
}

void SettingsPanel::OnUpDownClick(UpDownControl& upDownControl, u32 hudSlotId) {
    PushButton& okButton = *this->externControls[0];
    okButton.Select(0);
}

void SettingsPanel::OnTextChange(TextUpDownValueControl::TextControl& text, u32 optionId) {

    const u32 bmgId = this->bmgOffset + BMG_SCROLLER_SETTINGS + (this->catIdx << 12) + optionId;
    u32 id = this->GetTextId(text);
    this->scrollerSettings[this->sheetIdx][id] = optionId;

    text.SetMessage(bmgId + (id + 1 << 4));
    if(!this->externControls[0]->IsSelected()) {
        this->bottomText->SetMessage(bmgId + (id + 1 << 8));
    }
};

void SettingsPanel::OnUpDownSelect(UpDownControl& upDownControl, u32 hudSlotId) {
    const u32 bmgId = this->bmgOffset + BMG_SCROLLER_SETTINGS + (this->catIdx << 12) + (upDownControl.id + 1 << 8) + upDownControl.curSelectedOption;
    this->bottomText->SetMessage(bmgId);
}

int SettingsPanel::GetNextSheetIdx(s32 direction) {
    return (this->sheetIdx + direction + Settings::Params::pageCount) % Settings::Params::pageCount;
}

int SettingsPanel::GetNextBMGOffset(s32 direction) {
    const u32 nextIdx = this->GetNextSheetIdx(direction);
    if(nextIdx < Settings::Params::pulsarPageCount) return nextIdx;
    else return BMG_USERSETTINGSOFFSET + nextIdx - Settings::Params::pulsarPageCount;
}

}//namespace UI
}//namespace Pulsar




