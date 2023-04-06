#include <Settings/UI/SettingsPanel.hpp>
#include <UI/BMG.hpp>

namespace PulsarUI {
void AddSettingsPage(Section *section, PageId id) {
    section->CreateAndInitPage(id);
    section->CreateAndInitPage(PAGE_VS_SETTINGS);
}
kmCall(0x8062fe24, AddSettingsPage);
kmCall(0x8062dbbc, AddSettingsPage);
kmCall(0x8062dd60, AddSettingsPage);
kmCall(0x8062df04, AddSettingsPage);
kmCall(0x8062e228, AddSettingsPage);
kmCall(0x8062e3cc, AddSettingsPage);

//buttonsPerRow/optionsPerScroller are sheet dependant
Page *CreateSettingsPage() {
    Section *section = SectionMgr::sInstance->curSection;
    SectionId id = section->sectionId;
    if ((id == SECTION_OPTIONS) || (id == SECTION_P1_WIFI) || (id == SECTION_P1_WIFI_GLOBE_DISCONNECT) || (id == SECTION_P1_WIFI_FROM_FIND_FRIEND)
        || (id == SECTION_P2_WIFI) || (id == SECTION_P2_WIFI_GLOBE_DISCONNECT)) {
        u8 buttonsPerRow[8] = { 2, 2, 2, 2, 4, 4, 4 ,4 };
        u8 optionsPerScroller[8] = { 4, 4, 4, 4, 4 , 4, 4, 4 };

        Page *settings = new(SettingsPanel)(4, 0, buttonsPerRow, optionsPerScroller, 1); //race settings
        section->Set(settings, PAGE_VS_TEAMS_VIEW);
        settings->Init(PAGE_VS_TEAMS_VIEW);

        buttonsPerRow[1] = 3;
        optionsPerScroller[0] = 7;
        settings = new(SettingsPanel)(2, 1, buttonsPerRow, optionsPerScroller, 2); //host settings
        section->Set(settings, PAGE_BATTLE_MODE_SELECT);
        settings->Init(PAGE_BATTLE_MODE_SELECT);
        optionsPerScroller[0] = 5;
        return new(SettingsPanel)(1, 1, buttonsPerRow, optionsPerScroller, 0); //menu settings
    }
    else {
        return new(Pages::VSSettings);
    }
}
kmCall(0x80623e1c, CreateSettingsPage);
kmWrite32(0x80623e10, 0x60000000); //nop the original new

//SETTINGS PANEL
SettingsPanel::SettingsPanel(u32 radioButtonsCount, u32 scrollerButtonsCount, const u8 buttonsPerRow[8], const u8 optionsPerScroller[8], u32 sheetId) {
    externControlCount = 3;
    internControlCount = radioButtonsCount + scrollerButtonsCount;
    hasBackButton = false;
    nextPageId = PAGE_NONE;
    SectionId id = SectionMgr::sInstance->curSection->sectionId;
    if (id == SECTION_OPTIONS) prevPageId = PAGE_OPTIONS;
    else if ((id == SECTION_P1_WIFI) || (id == SECTION_P1_WIFI_GLOBE_DISCONNECT) || (id == SECTION_P1_WIFI_FROM_FIND_FRIEND)
        || (id == SECTION_P2_WIFI) || (id == SECTION_P2_WIFI_GLOBE_DISCONNECT)) prevPageId = PAGE_WFC_MAIN;
    nextSection = SECTION_NONE;
    controlSources = 2;
    onMessageBoxClickHandler.ptmf = (&MenuInteractable::ChangeToPrevSection);
    //initThpPtmf.ptmf.vtableOffset = 0; //virtual func to be defined
    movieStartFrame = -1;
    extraControlNumber = 0;
    isLocked = false;
    controlCount = 0;

    onRadioButtonChangeHandler.subject = this;
    onRadioButtonChangeHandler.ptmf = static_cast<void (Page:: *)(RadioButtonControl *, u32, u32)>(&SettingsPanel::OnRadioButtonChange);

    onUpDownClickHandler.subject = this;
    onUpDownClickHandler.ptmf = static_cast<void (Page:: *)(UpDownControl *, u32)>(&SettingsPanel::OnUpDownClick);
    onUpDownSelectHandler.subject = this;
    onUpDownSelectHandler.ptmf = static_cast<void (Page:: *)(UpDownControl *, u32)>(&SettingsPanel::OnUpDownSelect);

    onTextChangeHandler.subject = this;
    onTextChangeHandler.ptmf = static_cast<void (Page:: *)(TextUpDownValueControl::TextControl *, u32)>(&SettingsPanel::OnTextChange);

    onButtonSelectHandler.subject = this;
    onButtonSelectHandler.ptmf = static_cast<void (MenuInteractable:: *)(PushButton *, u32)> (&SettingsPanel::OnExternalButtonSelect);
    onButtonDeselectHandler.subject = this;
    onButtonDeselectHandler.ptmf = static_cast<void (MenuInteractable:: *)(PushButton *, u32)> (&Pages::VSSettings::OnButtonDeselect);
    onBackPressHandler.subject = this;
    onBackPressHandler.ptmf = static_cast<void (MenuInteractable:: *)(u32)> (&SettingsPanel::OnBackPress);
    onStartPressHandler.subject = this;
    onStartPressHandler.ptmf = (&MenuInteractable::HandleStartPress);

    onButtonClickHandler.subject = this;
    onButtonClickHandler.ptmf = static_cast<void (MenuInteractable:: *)(PushButton *, u32)> (&SettingsPanel::OnSaveButtonClick);
    onRightButtonClickHandler.subject = this;
    onRightButtonClickHandler.ptmf = static_cast<void (MenuInteractable:: *)(PushButton *, u32)> (&SettingsPanel::OnRightButtonClick);
    onLeftButtonClickHandler.subject = this;
    onLeftButtonClickHandler.ptmf = static_cast<void (MenuInteractable:: *)(PushButton *, u32)> (&SettingsPanel::OnLeftButtonClick);

    sheetIdx = sheetId;
    titleBmg = BMG_SETTINGS_TITLE + this->sheetIdx + 1;

    this->controlsManipulatorManager.Init(1, false);
    this->SetManipulatorManager(&controlsManipulatorManager);
    this->controlsManipulatorManager.SetGlobalHandler(START_PRESS, (PtmfHolder_1A<Page, void, u32>*) & onStartPressHandler, false, false);
    this->controlsManipulatorManager.SetGlobalHandler(BACK_PRESS, (PtmfHolder_1A<Page, void, u32>*) & onBackPressHandler, false, false);
    activePlayerBitfield = 1;
    radioCount = radioButtonsCount;
    memcpy(this->buttonsPerRow, buttonsPerRow, 8);
    scrollersCount = scrollerButtonsCount;
    memcpy(this->optionsPerScroller, optionsPerScroller, 8);
};


SettingsPanel::~SettingsPanel() {
    delete[] radioButtonControls;
    delete[] upDownControls;
    delete[] textUpDownwID;
}


void SettingsPanel::OnInit() {

    radioButtonControls = new RadioButtonControl[this->radioCount];
    upDownControls = new UpDownControl[this->scrollersCount];
    textUpDownwID = new TextUpDownValueControlwID[this->scrollersCount];
    MenuInteractable::OnInit();
    this->SetTransitionSound(0, 0);
    //this->titleText->SetText(titleBmg);
    this->externControls[1]->SetMsgId(BMG_SETTINGS_PAGE + (this->sheetIdx + 1) % SETTINGSPAGECOUNT);
    this->externControls[2]->SetMsgId(BMG_SETTINGS_PAGE + (this->sheetIdx + 2) % SETTINGSPAGECOUNT);
};

UIControl *SettingsPanel::CreateExternalControl(u32 id) {
    PushButton *button = new(PushButton);
    char *variant;
    switch (id) {
    case(0):
        variant = "ButtonSAVE";
        break;
    case(1):
        variant = "ButtonRIGHT";
        break;
    case(2):
        variant = "ButtonLEFT";
        break;
    }
    this->AddControl(this->controlCount, button, 0);
    this->controlCount++;
    button->Load(Pulsar::buttonFolder, "Settings", variant, this->activePlayerBitfield, 0, false);
    return button;
    //has BMG 0x7D0 for OK
};

UIControl *SettingsPanel::CreateControl(u32 id) {
    Settings *data = Settings::GetInstance();
    if (id < this->radioCount) {
        RadioButtonControl *radioButtonControl = &this->radioButtonControls[id];
        this->AddControl(this->controlCount, radioButtonControl, 0);
        this->controlCount++;
        char *variant = "RadioRow0";

        const char *optionVariantsRow0[5] = { "Row0Option0", "Row0Option1", "Row0Option2", "Row0Option3", NULL };
        const char *optionVariantsRow1[5] = { "Row1Option0", "Row1Option1", "Row1Option2", "Row1Option3", NULL };
        const char *optionVariantsRow2[5] = { "Row2Option0", "Row0Option1", "Row2Option2", "Row2Option3", NULL };
        const char *optionVariantsRow3[5] = { "Row3Option0", "Row3Option1", "Row3Option2", "Row3Option3", NULL };
        const char **optionVariants = optionVariantsRow0;
        if (id == 1) {
            variant = "RadioRow1";
            optionVariants = optionVariantsRow1;
        }
        else if (id == 2) {
            variant = "RadioRow2";
            optionVariants = optionVariantsRow2;
        }
        else if (id == 3) {
            variant = "RadioRow3";
            optionVariants = optionVariantsRow3;
        }
        radioButtonControl->Load(this->buttonsPerRow[id], data->GetSettings()->pages[this->sheetIdx].radioSetting[id], Pulsar::controlFolder, "SettingsRadioBase", variant, "SettingsRadioOption", optionVariants, 1, 0, 0);
        radioButtonControl->SetOnChangeHandler(&this->onRadioButtonChangeHandler);
        radioButtonControl->id = id;
        u32 bmgCategory = BMG_RADIO_SETTINGS + (this->sheetIdx << 12);
        radioButtonControl->SetMsgId(id + bmgCategory);
        for (int i = 0; i < radioButtonControl->buttonsCount; i++) radioButtonControl->optionButtonsArray[i].SetMsgId((id + 1 << 4) + i + bmgCategory);
    }
    else if (id < (this->radioCount + this->scrollersCount)) {
        id -= this->radioCount;
        UpDownControl *upDownControl = &this->upDownControls[id];
        this->AddControl(this->controlCount, upDownControl, 0);
        this->controlCount++;

        char *variant = "UpDown0";
        if (id == 1) variant = "UpDown1";
        upDownControl->Load(this->optionsPerScroller[id], data->GetSettings()->pages[this->sheetIdx].scrollSetting[id], Pulsar::controlFolder, "SettingsUpDownBase", variant, "SettingsUpDownButtonR", "RightButton",
            "SettingsUpDownButtonL", "LeftButton", (UpDownDisplayedText *)&this->textUpDownwID[id], 1, 0, false, true, true);
        upDownControl->SetOnClickHandler(&this->onUpDownClickHandler);
        upDownControl->SetOnSelectHandler(&this->onUpDownSelectHandler);
        upDownControl->id = id;


        TextUpDownValueControlwID *valueControl = &this->textUpDownwID[id];

        valueControl->Load(Pulsar::controlFolder, "SettingsUpDownValue", "Value", "SettingsUpDownText", "Text");
        valueControl->SetOnTextChangeHandler(&this->onTextChangeHandler);
        valueControl->id = id;
        u32 bmgCategory = BMG_SCROLLER_SETTINGS + (this->sheetIdx << 12);
        upDownControl->SetMsgId(id + bmgCategory);
        valueControl->activeTextValueControl->SetMsgId((id + 1 << 4) + bmgCategory);

    }
    return NULL;
}

void SettingsPanel::SetButtonHandlers(PushButton *button) {
    PtmfHolder_2A<Page, void, PushButton *, u32> *onClickHandler = (PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onButtonClickHandler;
    if (button->buttonId == 1) onClickHandler = (PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onRightButtonClickHandler;
    else if (button->buttonId == 2) onClickHandler = (PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onLeftButtonClickHandler;

    button->SetOnClickHandler(onClickHandler, 0);
    button->SetOnSelectHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onButtonSelectHandler);
    button->SetOnDeselectHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onButtonDeselectHandler);
}

void SettingsPanel::OnActivate() {
    Settings::Binary::Page *page = &Settings::GetInstance()->GetSettings()->pages[this->sheetIdx];

    for (RadioButtonControl *radio = this->radioButtonControls; radio < &this->radioButtonControls[this->radioCount]; radio++) {
        u8 setting = page->radioSetting[radio->id];
        radio->chosenButtonId = setting;
        radio->selectedButtonId = setting;
    }
    for (UpDownControl *scroller = this->upDownControls; scroller < &this->upDownControls[this->scrollersCount]; scroller++) {
        scroller->curSelectedOption = page->scrollSetting[scroller->id];
    }
    MenuInteractable::OnActivate();
}

int SettingsPanel::GetRuntimeTypeInfo() const {
    return VSSettingsStaticAddr;
}

void SettingsPanel::OnExternalButtonSelect(PushButton *button, u32 r5) {
    u32 bmgId = 0;

    switch (button->buttonId) {
    case(0):
        bmgId = BMG_SETTINGS_BOTTOM;
        break;
    case(1):
        bmgId = BMG_SETTINGS_BOTTOM + 1 + (this->sheetIdx + 1) % SETTINGSPAGECOUNT;
        break;
    case(2):
        bmgId = BMG_SETTINGS_BOTTOM + 1 + (this->sheetIdx + 2) % SETTINGSPAGECOUNT;
    }
    this->bottomText->SetMsgId(bmgId, 0);
}

int SettingsPanel::GetActivePlayerBitfield() const {
    return this->activePlayerBitfield;
}

int SettingsPanel::GetPlayerBitfield() const {
    return this->playerBitfield;
}

ManipulatorManager *SettingsPanel::GetManipulatorManager() {
    return &this->controlsManipulatorManager;
}

void SettingsPanel::LoadPrevMenuAndSaveSettings(PushButton *button) {
    this->LoadPrevPage(button);
    Section *section = SectionMgr::sInstance->curSection;
    if (this->prevPageId == PAGE_OPTIONS) section->Get<ExpOptions>(PAGE_OPTIONS)->topSettingsPage = this->pageId;
    else if (this->prevPageId == PAGE_WFC_MAIN) section->Get<ExpWFCMain>(PAGE_WFC_MAIN)->topSettingsPage = this->pageId;
    else if (this->prevPageId == PAGE_FRIEND_ROOM) {
        section->Get<ExpFroom>(PAGE_WFC_MAIN)->topSettingsPage = this->pageId;
        this->nextPageId = PAGE_NONE; //FriendRoom's OnResume is important
    }
    SettingsPanel::SaveSettings();
}

//On Save Click/Back Press, is called and updates PulsarSettings
void SettingsPanel::SaveSettings() {
    Section *section = SectionMgr::sInstance->curSection;
    Settings *settings = Settings::GetInstance();
    for (int count = 0; count < SETTINGSPAGECOUNT; count++) {
        SettingsPanel *panel = section->Get<SettingsPanel>((PageId)(PAGE_VS_SETTINGS + count));
        Settings::Binary::Page *settingsPage = &settings->GetSettings()->pages[panel->sheetIdx];
        for (RadioButtonControl *radio = panel->radioButtonControls; radio < &panel->radioButtonControls[panel->radioCount]; radio++) {
            settingsPage->radioSetting[radio->id] = radio->chosenButtonId;
        }
        for (UpDownControl *scroller = panel->upDownControls; scroller < &panel->upDownControls[panel->scrollersCount]; scroller++) {
            settingsPage->scrollSetting[scroller->id] = scroller->curSelectedOption;
        }
    }
    settings->Update();
}


void SettingsPanel::OnBackPress(u32 hudSlotId) {
    PushButton *okButton = this->externControls[0];
    okButton->SelectFocus();
    this->LoadPrevMenuAndSaveSettings(okButton);
}

void SettingsPanel::OnSaveButtonClick(PushButton *button, u32 hudSlotId) {
    this->LoadPrevMenuAndSaveSettings(button);
}

void SettingsPanel::OnRightButtonClick(PushButton *button, u32 hudSlotId) {
    PageId id = (PageId)(0x73 + (this->sheetIdx + 1) % SETTINGSPAGECOUNT);
    this->LoadPrevPageById(id, button);
    SettingsPanel *nextPanel = SectionMgr::sInstance->curSection->Get<SettingsPanel>(id);
    nextPanel->externControls[0]->SelectInitialButton(0);
    nextPanel->bottomText->SetMsgId(BMG_SETTINGS_BOTTOM);
}

void SettingsPanel::OnLeftButtonClick(PushButton *button, u32 hudSlotId) {
    PageId id = (PageId)(0x73 + (this->sheetIdx + 2) % SETTINGSPAGECOUNT);
    this->LoadPrevPageById(id, button);
    SettingsPanel *nextPanel = SectionMgr::sInstance->curSection->Get<SettingsPanel>(id);
    nextPanel->externControls[0]->SelectInitialButton(0);
    nextPanel->bottomText->SetMsgId(BMG_SETTINGS_BOTTOM);
}

void SettingsPanel::OnRadioButtonChange(RadioButtonControl *radioButtonControl, u32 hudSlotId, u32 optionId) {
    this->bottomText->SetMsgId(BMG_RADIO_SETTINGS + (this->sheetIdx << 12) + (radioButtonControl->id + 1 << 8) + optionId);
}


void SettingsPanel::OnUpDownClick(UpDownControl *upDownControl, u32 hudSlotId) {
    PushButton *okButton = this->externControls[0];
    okButton->Select(0); //0 is the id
    //HandleOnRadioButtonSelect__19CustomSettingsPanelFP18RadioButtonControlUiUi = 0x8085389c do stuff with bmg IDs
    return;
}

void SettingsPanel::OnTextChange(TextUpDownValueControl::TextControl *text, u32 optionId) {
    TextUpDownValueControlwID *valueControl = (TextUpDownValueControlwID *)text->parentGroup->parentControl;

    u32 bmgId = BMG_SCROLLER_SETTINGS + (this->sheetIdx << 12) + optionId;
    text->SetMsgId(bmgId + (valueControl->id + 1 << 4));
    this->bottomText->SetMsgId(bmgId + (valueControl->id + 1 << 8));
    //TEXT HERE 80853a10
    return;
};

void SettingsPanel::OnUpDownSelect(UpDownControl *upDownControl, u32 hudSlotId) {
    u32 bmgId = BMG_SCROLLER_SETTINGS + (this->sheetIdx << 12) + (upDownControl->id + 1 << 8) + upDownControl->curSelectedOption;
    this->bottomText->SetMsgId(bmgId);
    return;
}

void TextUpDownValueControlwID::SetMessage(u32 optionId) {
    TextUpDownValueControl::TextControl *text = this->activeTextValueControl;
    u32 bmgId = BMG_SCROLLER_SETTINGS + (((PulsarUI::SettingsPanel *)this->parentGroup->parentPage)->sheetIdx << 12) + (this->id + 1 << 4) + optionId;
    text->SetMsgId(bmgId);
}
}//namespace PulsarUI





