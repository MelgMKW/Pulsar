#include <Settings/UI/SettingsPanel.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace UI {

u8 SettingsPanel::radioButtonCount[SettingsPanel::pageCount] ={ 1, 4, 2 };
u8 SettingsPanel::scrollerCount[SettingsPanel::pageCount] ={ 1, 0, 1 };

u8 SettingsPanel::buttonsPerPagePerRow[SettingsPanel::pageCount][8] = //first row is SettingsType, 2nd is rowIdx of radio
{
    { 2, 0, 0, 0, 0, 0, 0, 0 },
    { 2, 2, 2, 2, 0, 0, 0, 0 },
    { 2, 4, 0, 0, 0, 0, 0, 0 },
};

u8 SettingsPanel::optionsPerPagePerScroller[SettingsPanel::pageCount][8] =
{
    { 5, 7, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

inline void SettingsPanel::CreatePanels(Section* section) {
    for(int i = 0; i < pageCount; ++i) { //menu->race->host
        Page* settings = new(SettingsPanel)(i);
        section->Set(settings, static_cast<PageId>(PAGE_VS_SETTINGS + i));
        settings->Init(static_cast<PageId>(PAGE_VS_SETTINGS + i));
    }
}

void AddSettingsPage(Section* section, PageId id) {
    section->CreateAndInitPage(id);
    SettingsPanel::CreatePanels(section);
}
kmCall(0x8062fe24, AddSettingsPage);
kmCall(0x8062dbbc, AddSettingsPage);
kmCall(0x8062dd60, AddSettingsPage);
kmCall(0x8062df04, AddSettingsPage);
kmCall(0x8062e228, AddSettingsPage);
kmCall(0x8062e3cc, AddSettingsPage);


//SETTINGS PANEL
SettingsPanel::SettingsPanel(u32 sheetId) :
    radioCount(radioButtonCount[sheetId]), scrollersCount(scrollerCount[sheetId]), sheetIdx(sheetId)
{
    externControlCount = 3;
    internControlCount = radioCount + scrollersCount;
    hasBackButton = false;
    nextPageId = PAGE_NONE;
    titleBmg = BMG_SETTINGS_TITLE + this->sheetIdx + 1;
    activePlayerBitfield = 1;
    movieStartFrame = -1;
    extraControlNumber = 0;
    isLocked = false;
    controlCount = 0;
    nextSection = SECTION_NONE;
    controlSources = 2;

    SectionId id = SectionMgr::sInstance->curSection->sectionId;
    if(id == SECTION_OPTIONS) prevPageId = PAGE_OPTIONS;
    else if((id == SECTION_P1_WIFI) || (id == SECTION_P1_WIFI_GLOBE_DISCONNECT) || (id == SECTION_P1_WIFI_FROM_FIND_FRIEND)
        || (id == SECTION_P2_WIFI) || (id == SECTION_P2_WIFI_GLOBE_DISCONNECT)) prevPageId = PAGE_WFC_MAIN;

    onMessageBoxClickHandler.ptmf = &Menu::ChangeToPrevSection;

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
    delete[] radioButtonControls;
    delete[] upDownControls;
    delete[] textUpDown;
}

void SettingsPanel::OnInit() {
    radioButtonControls = new RadioButtonControl[this->radioCount];
    upDownControls = new UpDownControl[this->scrollersCount];
    textUpDown = new TextUpDownValueControl[this->scrollersCount];
    MenuInteractable::OnInit();
    this->SetTransitionSound(0, 0);
    this->externControls[1]->SetMsgId(BMG_SETTINGS_PAGE + this->GetNextIdx(1));
    this->externControls[2]->SetMsgId(BMG_SETTINGS_PAGE + this->GetNextIdx(2));
};

UIControl* SettingsPanel::CreateExternalControl(u32 id) {
    PushButton* button = new(PushButton);
    const char* variant = "SAVE";
    if(id == 1) variant = "RIGHT";
    else if(id == 2) variant = "LEFT";
    this->AddControl(this->controlCount++, *button, 0);
    button->Load(UI::buttonFolder, "Settings", variant, this->activePlayerBitfield, 0, false);
    return button;
};

UIControl* SettingsPanel::CreateControl(u32 id) {
    if(id < this->radioCount) {
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
        radioButtonControl.Load(buttonsPerPagePerRow[this->sheetIdx][id], Settings::GetSettingValue(static_cast<SettingsType>(this->sheetIdx), id),
            UI::controlFolder, "RadioBase", variant, "RadioOption", optionVariants, 1, 0, 0);
        radioButtonControl.SetOnChangeHandler(this->onRadioButtonChangeHandler);
        radioButtonControl.id = id;
        u32 bmgCategory = BMG_RADIO_SETTINGS + (this->sheetIdx << 12);
        radioButtonControl.SetMsgId(id + bmgCategory);
        for(int i = 0; i < radioButtonControl.buttonsCount; ++i) {
            radioButtonControl.optionButtonsArray[i].SetMsgId((id + 1 << 4) + i + bmgCategory);
        }
    }
    else if(id < (this->radioCount + this->scrollersCount)) {
        id -= this->radioCount;
        UpDownControl& upDownControl = this->upDownControls[id];
        this->AddControl(this->controlCount, upDownControl, 0);
        ++this->controlCount;

        char variant[12];
        snprintf(variant, 12, "UpDown%d", id);

        upDownControl.Load(optionsPerPagePerScroller[this->sheetIdx][id], Settings::GetSettingValue(static_cast<SettingsType>(this->sheetIdx), id + 6),
            UI::controlFolder, "UpDownBase", variant, "UpDownR", "Right", "UpDownL",
            "Left", &this->textUpDown[id], 1, 0, false, true, true);
        upDownControl.SetOnClickHandler(this->onUpDownClickHandler);
        upDownControl.SetOnSelectHandler(this->onUpDownSelectHandler);
        upDownControl.id = id;

        TextUpDownValueControl& valueControl = this->textUpDown[id];
        valueControl.Load(UI::controlFolder, "UpDownValue", "Value", "UpDownText", "Text");
        valueControl.SetOnTextChangeHandler(this->onTextChangeHandler);
        u32 bmgCategory = BMG_SCROLLER_SETTINGS + (this->sheetIdx << 12);
        upDownControl.SetMsgId(id + bmgCategory);
        valueControl.activeTextValueControl->SetMsgId((id + 1 << 4) + bmgCategory);
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
    for(RadioButtonControl* radio = this->radioButtonControls; radio < &this->radioButtonControls[this->radioCount]; radio++) {
        const u8 setting = Settings::GetSettingValue(static_cast<SettingsType>(this->sheetIdx), radio->id);
        radio->chosenButtonId = setting;
        radio->selectedButtonId = setting;
    }
    for(UpDownControl* scroller = this->upDownControls; scroller < &this->upDownControls[this->scrollersCount]; scroller++) {
        scroller->curSelectedOption = Settings::GetSettingValue(static_cast<SettingsType>(this->sheetIdx), scroller->id + 6);
    }
    MenuInteractable::OnActivate();
}

int SettingsPanel::GetRuntimeTypeInfo() const {
    return VSSettingsStaticAddr;
}

void SettingsPanel::OnExternalButtonSelect(PushButton& button, u32 r5) {
    u32 bmgId = BMG_SETTINGS_BOTTOM;
    const u32 id = button.buttonId;
    if(id == 1) bmgId += 1 + this->GetNextIdx(1);
    else if(id == 2) bmgId += 1 + this->GetNextIdx(2);
    this->bottomText->SetMsgId(bmgId);
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
    if(this->prevPageId == PAGE_OPTIONS) section->Get<ExpOptions>(PAGE_OPTIONS)->topSettingsPage = this->pageId;
    else if(this->prevPageId == PAGE_WFC_MAIN) section->Get<ExpWFCMain>(PAGE_WFC_MAIN)->topSettingsPage = this->pageId;
    else if(this->prevPageId == PAGE_FRIEND_ROOM) {
        section->Get<ExpFroom>(PAGE_WFC_MAIN)->topSettingsPage = this->pageId;
        this->nextPageId = PAGE_NONE; //FriendRoom's OnResume is important
    }
    SettingsPanel::SaveSettings();
}

//On Save Click/Back Press, is called and updates PulsarSettings
void SettingsPanel::SaveSettings() {
    const Section* section = SectionMgr::sInstance->curSection;
    Settings* settings = Settings::sInstance;
    for(int count = 0; count < pageCount; count++) {
        SettingsPanel* panel = section->Get<SettingsPanel>((PageId)(PAGE_VS_SETTINGS + count));
        for(const RadioButtonControl* radio = panel->radioButtonControls; radio < &panel->radioButtonControls[panel->radioCount]; radio++) {
            settings->SetSettingValue(static_cast<SettingsType>(panel->sheetIdx), radio->id, radio->chosenButtonId);
        }
        for(const UpDownControl* scroller = panel->upDownControls; scroller < &panel->upDownControls[panel->scrollersCount]; scroller++) {
            settings->SetSettingValue(static_cast<SettingsType>(panel->sheetIdx), scroller->id + 6, scroller->curSelectedOption);
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
    this->OnButtonClick(button, 2);
}

void SettingsPanel::OnButtonClick(PushButton& button, u32 direction) {
    const PageId id = (PageId)(PAGE_VS_SETTINGS + this->GetNextIdx(direction));
    SettingsPanel* nextPanel = SectionMgr::sInstance->curSection->Get<SettingsPanel>(id);
    this->LoadPrevPageById(id, button);
    nextPanel->externControls[0]->SelectInitialButton(0);
    nextPanel->bottomText->SetMsgId(BMG_SETTINGS_BOTTOM);
}

void SettingsPanel::OnRadioButtonChange(RadioButtonControl& radioButtonControl, u32 hudSlotId, u32 optionId) {
    this->bottomText->SetMsgId(BMG_RADIO_SETTINGS + (this->sheetIdx << 12) + (radioButtonControl.id + 1 << 8) + optionId);
}

void SettingsPanel::OnUpDownClick(UpDownControl& upDownControl, u32 hudSlotId) {
    PushButton& okButton = *this->externControls[0];
    okButton.Select(0);
}

void SettingsPanel::OnTextChange(TextUpDownValueControl::TextControl& text, u32 optionId) {
    const u32 bmgId = BMG_SCROLLER_SETTINGS + (this->sheetIdx << 12) + optionId;
    u32 id = this->GetTextId(text);
    this->bottomText->SetMsgId(bmgId + (id + 1 << 8));
    text.SetMsgId(bmgId + (id + 1 << 4));
};

void SettingsPanel::OnUpDownSelect(UpDownControl& upDownControl, u32 hudSlotId) {
    const u32 bmgId = BMG_SCROLLER_SETTINGS + (this->sheetIdx << 12) + (upDownControl.id + 1 << 8) + upDownControl.curSelectedOption;
    this->bottomText->SetMsgId(bmgId);
}

int SettingsPanel::GetNextIdx(u32 direction) {
    return (this->sheetIdx + direction) % pageCount;
}

/*
void TextUpDownValueControl::SetMessage(u32 optionId) {
    TextUpDownValueControl::TextControl* text = this->activeTextValueControl;
    u32 id = this->GetTextId(text);
    const u32 bmgId = BMG_SCROLLER_SETTINGS +
        (this->parentGroup->GetParentPage<UI::SettingsPanel>()->sheetIdx << 12) + (this->id + 1 << 4) + optionId;
    text->SetMsgId(bmgId);
}
*/


}//namespace UI
}//namespace Pulsar





