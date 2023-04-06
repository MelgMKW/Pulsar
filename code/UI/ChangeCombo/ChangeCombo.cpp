#include <Pulsar.hpp>
#include <UI/ChangeCombo/ChangeCombo.hpp>

u8 kartsSortedByWeight[3][12] = {
    {STANDARD_KART_S, BABY_BOOSTER, MINI_BEAST, CHEEP_CHARGER, RALLY_ROMPER, BLUE_FALCON, STANDARD_BIKE_S, BULLET_BIKE, BIT_BIKE, QUACKER, MAGIKRUISER, JET_BUBBLE},
    {STANDARD_KART_M, CLASSIC_DRAGSTER, WILD_WING, SUPER_BLOOPER, ROYAL_RACER, SPRINTER, STANDARD_BIKE_M, MACH_BIKE, BON_BON, RAPIDE, NITROCYCLE, DOLPHIN_DASHER},
    {STANDARD_KART_L,  OFFROADER, FLAME_FLYER, PIRANHA_PROWLER, JETSETTER, HONEYCOUPE, STANDARD_BIKE_L, BOWSER_BIKE, WARIO_BIKE, SHOOTING_STAR, SPEAR, PHANTOM},
};

namespace PulsarUI {
kmWrite32(0x806508d4, 0x60000000); //Add VR screen outside of 1st race in frooms
kmWrite32(0x806240e0, 0x60000000); //nop the new
Pages::VR *AddComboPages() {
    SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;

    if (sectionId == SECTION_P1_WIFI_VS_VOTING || sectionId == SECTION_P1_WIFI_FROOM_VS_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_TEAMVS_VOTING || sectionId == SECTION_P1_WIFI_BATTLE_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_BALLOON_VOTING || sectionId == SECTION_P1_WIFI_FROOM_COIN_VOTING) {
        return new(ExpVR);
    }
    return new(Pages::VR);
}
kmCall(0x806240ec, AddComboPages);


ExpVR::ExpVR(): comboButtonState(0) {
    this->onRandomComboClick.subject = this;
    this->onRandomComboClick.ptmf = &ExpVR::RandomizeCombo;
    this->onChangeComboClick.subject = this;
    this->onChangeComboClick.ptmf = &ExpVR::ChangeCombo;
}

void TempKillInitControl(Pages::VR *page, u32 controlCount) {
    SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if (sectionId == SECTION_P1_WIFI_VS_VOTING || sectionId == SECTION_P1_WIFI_FROOM_VS_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_TEAMVS_VOTING || sectionId == SECTION_P1_WIFI_BATTLE_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_BALLOON_VOTING || sectionId == SECTION_P1_WIFI_FROOM_COIN_VOTING) return;
    page->InitControlGroup(controlCount);
}
kmCall(0x8064a61c, TempKillInitControl);
//kmWrite32(0x8064a61c, 0x60000000); //nop initControlGroup

void ExpVR::OnInit() {
    this->InitControlGroup(0x11);
    VR::OnInit();

    PushButton *button = &this->randomComboButton;
    this->AddControl(0xF, button, 0);
    button->Load(Pulsar::buttonFolder, "WifiMemberButtons", "ButtonRandom", 1, 0, false);
    button->SetOnClickHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onRandomComboClick, 0);

    button = &this->changeComboButton;
    this->AddControl(0x10, button, 0);
    button->Load(Pulsar::buttonFolder, "WifiMemberButtons", "ButtonChange", 1, 0, false);
    button->SetOnClickHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onChangeComboClick, 0);
    button->manipulator.SetAction(START_PRESS, &button->onClickHandlerObj, 0);

    Section *section = SectionMgr::sInstance->curSection;

    Pages::CountDownTimer *countdownPage = section->Get<Pages::CountDownTimer>(PAGE_COUNTDOWN);
    CountDown *timer = &countdownPage->countdown;

    Pages::CharacterSelect *charPage = section->Get<Pages::CharacterSelect>(PAGE_CHARACTER_SELECT);
    charPage->timer = timer;
    charPage->ctrlMenuCharSelect.timer = timer;

    Pages::KartSelect *kartPage = section->Get<Pages::KartSelect>(PAGE_KART_SELECT);
    if (kartPage != NULL) kartPage->timer = timer;

    Pages::BattleKartSelect *kartBattlePage = section->Get<Pages::BattleKartSelect>(PAGE_BATTLE_KART_SELECT);
    if (kartBattlePage != NULL) kartBattlePage->timer = timer;

    Pages::MultiKartSelect *multiKartPage = section->Get<Pages::MultiKartSelect>(PAGE_MULTIPLAYER_KART_SELECT);
    if (multiKartPage != NULL) multiKartPage->timer = timer;

    Pages::DriftSelect *driftPage = section->Get<Pages::DriftSelect>(PAGE_DRIFT_SELECT);
    if (driftPage != NULL) driftPage->timer = timer;

    Pages::MultiDriftSelect *multiDriftPage = section->Get<Pages::MultiDriftSelect>(PAGE_MULTIPLAYER_DRIFT_SELECT);
    if (multiDriftPage != NULL) multiDriftPage->timer = timer;
}

void UseCorrectOKButtonBRCTR(PushButton *okButton, const char *folderName, const char *ctrName, const char *variant, u32 localPlayerCount, u32 r8, bool inaccessible) {
    SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if (sectionId == SECTION_P1_WIFI_VS_VOTING || sectionId == SECTION_P1_WIFI_FROOM_VS_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_TEAMVS_VOTING || sectionId == SECTION_P1_WIFI_BATTLE_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_BALLOON_VOTING || sectionId == SECTION_P1_WIFI_FROOM_COIN_VOTING) {
        ctrName = "WifiMemberButtons";
    }
    okButton->Load(folderName, ctrName, variant, localPlayerCount, r8, inaccessible);
}
kmCall(0x8064a6e8, UseCorrectOKButtonBRCTR);

void ExpVR::RandomizeCombo(PushButton *randomComboButton, u32 hudSlotId) {
    Random random;


    SectionMgr *menu = SectionMgr::sInstance;
    SectionMgr98 *sectionMgr98 = menu->sectionMgr98;
    for (int hudId = 0; hudId < sectionMgr98->localPlayerCount; hudId++) {
        CharacterId character = (CharacterId)random.NextLimited(24);
        u32 randomizedKartPos = random.NextLimited(12);
        KartId kart = (KartId)(kartsSortedByWeight[CharacterIDToWeightClass(character)][randomizedKartPos]);

        sectionMgr98->characters[hudId] = character;
        sectionMgr98->karts[hudId] = kart;
        sectionMgr98->combos[hudId].selCharacter = character;
        sectionMgr98->combos[hudId].selKart = kart;

        Section *section = menu->curSection;
        ExpCharacterSelect *charSelect = section->Get<ExpCharacterSelect>(PAGE_CHARACTER_SELECT); //guaranteed to exist on this page
        for (int i = 0; i < 24; i++) {
            if (buttonIdToCharacterId[i] == character) {
                charSelect->randomizedCharId = i;
                charSelect->rolledCharId = i;
                charSelect->rouletteCounter = 0x50;
                charSelect->ctrlMenuCharSelect.selectedCharacter = character;
                break;
            }
        }

        ExpBattleKartSelect *battleKartSelect = section->Get<ExpBattleKartSelect>(PAGE_BATTLE_KART_SELECT);
        if (battleKartSelect != NULL) battleKartSelect->selectedKart = random.NextLimited(2);

        ExpKartSelect *kartSelect = section->Get<ExpKartSelect>(PAGE_KART_SELECT);
        if (kartSelect != NULL) {
            kartSelect->rouletteCounter = 0x50;
            kartSelect->randomizedKartPos = randomizedKartPos;
            kartSelect->rolledKartPos = randomizedKartPos;
        }

        ExpMultiKartSelect *multiKartSelect = section->Get<ExpMultiKartSelect>(PAGE_MULTIPLAYER_KART_SELECT);
        if (multiKartSelect != NULL) {
            multiKartSelect->rouletteCounter = 0x50;
            multiKartSelect->rolledKartPos[0] = randomizedKartPos;
            u32 options = 12;
            SectionId sectionId = section->sectionId;
            if (sectionId == SECTION_P2_WIFI_BATTLE_VOTING || sectionId == SECTION_P2_WIFI_FROOM_BALLOON_VOTING || sectionId == SECTION_P2_WIFI_FROOM_COIN_VOTING) {
                options = 2;
            }
            multiKartSelect->rolledKartPos[1] = random.NextLimited(options);
        }
    }
    this->comboButtonState = 1;
    this->EndStateAnimated(randomComboButton->GetAnimationFrameSize(), 0);
}

void ExpVR::ChangeCombo(PushButton *changeComboButton, u32 hudSlotId) {
    this->comboButtonState = 2;
    this->EndStateAnimated(changeComboButton->GetAnimationFrameSize(), 0);
}

void AddChangeComboPages(Section *section, PageId id) {
    section->CreateAndInitPage(id);
    section->CreateAndInitPage(PAGE_CHARACTER_SELECT);
    switch (section->sectionId) {
    case(SECTION_P1_WIFI_VS_VOTING):
    case(SECTION_P1_WIFI_FROOM_VS_VOTING):
    case(SECTION_P1_WIFI_FROOM_TEAMVS_VOTING):
        section->CreateAndInitPage(PAGE_KART_SELECT);
        section->CreateAndInitPage(PAGE_DRIFT_SELECT);
        break;
    case(SECTION_P1_WIFI_BATTLE_VOTING):
    case(SECTION_P1_WIFI_FROOM_BALLOON_VOTING):
    case(SECTION_P1_WIFI_FROOM_COIN_VOTING):
        section->CreateAndInitPage(PAGE_BATTLE_KART_SELECT);
        section->CreateAndInitPage(PAGE_DRIFT_SELECT);
        break;
    case(SECTION_P2_WIFI_VS_VOTING):
    case(SECTION_P2_WIFI_FROOM_VS_VOTING):
    case(SECTION_P2_WIFI_FROOM_TEAMVS_VOTING):
    case(SECTION_P2_WIFI_BATTLE_VOTING):
    case(SECTION_P2_WIFI_FROOM_BALLOON_VOTING):
    case(SECTION_P2_WIFI_FROOM_COIN_VOTING):
        section->CreateAndInitPage(PAGE_MULTIPLAYER_KART_SELECT);
        section->CreateAndInitPage(PAGE_MULTIPLAYER_DRIFT_SELECT);
        break;
    }

}
//P1
kmCall(0x8062e09c, AddChangeComboPages); //0x58 can't do this more efficiently because supporting page 0x7F breaks kart images
kmCall(0x8062e7e0, AddChangeComboPages); //0x60
kmCall(0x8062e870, AddChangeComboPages); //0x61
kmCall(0x8062e0e4, AddChangeComboPages); //0x59
kmCall(0x8062e900, AddChangeComboPages); //0x62
kmCall(0x8062e990, AddChangeComboPages); //0x63
//P2
kmCall(0x8062e708, AddChangeComboPages); //0x5e
kmCall(0x8062e798, AddChangeComboPages); //0x5f
kmCall(0x8062ea68, AddChangeComboPages); //0x64
kmCall(0x8062eaf8, AddChangeComboPages); //0x65
kmCall(0x8062eb88, AddChangeComboPages); //0x66
kmCall(0x8062ec18, AddChangeComboPages); //0x67


kmWrite32(0x80623d50, 0x60000000);
ExpCharacterSelect *AddCharSelect() {
    return new(ExpCharacterSelect);
}
kmCall(0x80623d5c, AddCharSelect);

void ExpCharacterSelect::BeforeControlUpdate() {
    CtrlMenuCharacterSelect::ButtonDriver *array = this->ctrlMenuCharSelect.driverButtonsArray;
    s32 roulette = this->rouletteCounter;
    if (roulette == 0x50) {
        for (CtrlMenuCharacterSelect::ButtonDriver *button = &array[0]; button < &array[0x1A]; button++) {
            button->manipulator.inaccessible = true;
            button->HandleDeselect(0, 0);
        }
    }
    if (roulette > 0) {
        u32 prevChar = this->rolledCharId;
        Random random;
        if (roulette == 1) this->rolledCharId = this->randomizedCharId;
        else while (this->rolledCharId == prevChar) this->rolledCharId = random.NextLimited(24);
        array[prevChar].HandleDeselect(0, -1);
        array[this->rolledCharId].HandleSelect(0, -1);
        array[this->rolledCharId].Select(0);
        this->rouletteCounter--;
    }
    else if (roulette == 0) {
        this->rouletteCounter = -1;

        array[this->randomizedCharId].HandleClick(0, -1);
    }
}
//store correct buttons in sectionMgr98

kmWrite32(0x80623e58, 0x60000000);
ExpBattleKartSelect *AddBattleKartSelect() {
    return new(ExpBattleKartSelect);
}
kmCall(0x80623e64, AddBattleKartSelect);

void ExpBattleKartSelect::BeforeControlUpdate() {
    s32 kart = this->selectedKart;
    if (kart >= 0 && this->currentState == 0x4) {
        PushButton *kartButton = (PushButton *)this->controlGroup.controlArray[kart];
        kartButton->HandleSelect(0, -1);
        kartButton->Select(0);
        kartButton->HandleClick(0, -1);
        PushButton *otherButton = (PushButton *)this->controlGroup.controlArray[kart ^ 1];
        otherButton->HandleDeselect(0, -1);
        this->selectedKart = -1;
    }
}


kmWrite32(0x80623d68, 0x60000000);
ExpKartSelect *AddKartSelect() {
    return new(ExpKartSelect);
}
kmCall(0x80623d74, AddKartSelect);

void ExpKartSelect::BeforeControlUpdate() {
    s32 roulette = this->rouletteCounter;
    if (roulette >= 0) {
        LayoutUIControl *globalButtonHolder = (LayoutUIControl *)this->controlGroup.controlArray[2]; //holds the 6 controls that each hold a pair of buttons
        ButtonMachine *randomizedButton = (ButtonMachine *)globalButtonHolder->childrenGroup.controlArray[this->randomizedKartPos / 2]->childrenGroup.controlArray[this->randomizedKartPos % 2];
        if (roulette == 0x50) {

            LayoutUIControl *buttonHolder;
            for (buttonHolder = (LayoutUIControl *)globalButtonHolder->childrenGroup.controlArray[0];
                buttonHolder <= (LayoutUIControl *)globalButtonHolder->childrenGroup.controlArray[6]; buttonHolder++) {

                ButtonMachine *leftButton = (ButtonMachine *)buttonHolder->childrenGroup.controlArray[0];
                leftButton->manipulator.inaccessible = true;
                leftButton->HandleDeselect(0, 0);

                ButtonMachine *rightButton = (ButtonMachine *)buttonHolder->childrenGroup.controlArray[1];
                rightButton->manipulator.inaccessible = true;
                rightButton->HandleDeselect(0, 0);
            }
            this->curButtonId = randomizedButton->buttonId;
        }
        if (roulette > 0) {
            Random random;
            int prevKart = this->rolledKartPos;
            ButtonMachine *prevButton = (ButtonMachine *)globalButtonHolder->childrenGroup.controlArray[prevKart / 2]->childrenGroup.controlArray[prevKart % 2];
            prevButton->HandleDeselect(0, -1);

            int nextKart = prevKart;
            if (roulette == 1) nextKart = this->randomizedKartPos;
            else while (nextKart == prevKart) nextKart = random.NextLimited(12);
            ButtonMachine *nextButton = (ButtonMachine *)globalButtonHolder->childrenGroup.controlArray[nextKart / 2]->childrenGroup.controlArray[nextKart % 2];
            nextButton->HandleSelect(0, -1);
            nextButton->Select(0);
            this->rolledKartPos = nextKart;
            this->rouletteCounter--;
        }
        else if (roulette == 0) {
            this->rouletteCounter = -1;
            randomizedButton->HandleClick(0, -1);
        }
    }
}

kmWrite32(0x80623f60, 0x60000000);
ExpMultiKartSelect *AddMultiKartSelect() {
    return new(ExpMultiKartSelect);
}
kmCall(0x80623f6c, AddMultiKartSelect);
void ExpMultiKartSelect::BeforeControlUpdate() {
    s32 roulette = this->rouletteCounter;
    Random random;
    SectionMgr *menudata = SectionMgr::sInstance;
    for (int i = 0; i < menudata->sectionMgr98->localPlayerCount; i++) { //in all likelihood always 2
        if (roulette >= 0) {

            if (roulette == 0x50) {
                this->arrows[i].manipulator.inaccessible = true;
                SectionId sectionId = menudata->curSection->sectionId;
                u32 options = 12;
                if (sectionId == SECTION_P2_WIFI_BATTLE_VOTING || sectionId == SECTION_P2_WIFI_FROOM_BALLOON_VOTING || sectionId == SECTION_P2_WIFI_FROOM_COIN_VOTING) {
                    options = 2;
                }
                this->arrows[i].SelectInitial(options, this->rolledKartPos[i]);
            }
            if (roulette > 0) {
                if (random.NextLimited(2) == 0) this->arrows[i].HandleRightPress(i, -1);
                else this->arrows[i].HandleLeftPress(i, 0);
            }
            else if (roulette == 0) this->arrows[i].HandleClick(i, -1);
        }
    }
    this->rouletteCounter--;
}



void DriftSelectBeforeControlUpdate(Pages::DriftSelect *driftSelect) {
    ExpCharacterSelect *charSelect = SectionMgr::sInstance->curSection->Get<ExpCharacterSelect>(PAGE_CHARACTER_SELECT);
    if (charSelect->rouletteCounter != -1 && driftSelect->currentState == 0x4) {
        PushButton *autoButton = (PushButton *)driftSelect->controlGroup.controlArray[1];
        autoButton->HandleDeselect(0, -1);
        PushButton *manualButton = (PushButton *)driftSelect->controlGroup.controlArray[0];
        manualButton->HandleSelect(0, -1);
        manualButton->Select(0);
        manualButton->HandleClick(0, -1);
        charSelect->rouletteCounter = -1;
    }
}
kmWritePointer(0x808D9DF8, DriftSelectBeforeControlUpdate);

void MultiDriftSelectBeforeControlUpdate(Pages::MultiDriftSelect *multiDriftSelect) {
    ExpCharacterSelect *charSelect = SectionMgr::sInstance->curSection->Get<ExpCharacterSelect>(PAGE_CHARACTER_SELECT);;
    if (charSelect->rouletteCounter != -1 && multiDriftSelect->currentState == 0x4) {
        for (int i = 0; i < SectionMgr::sInstance->sectionMgr98->localPlayerCount; i++) {
            PushButton *autoButton = multiDriftSelect->externControls[0 + 2 * i];
            autoButton->HandleDeselect(i, -1);
            PushButton *manualButton = multiDriftSelect->externControls[1 + 2 * i];
            manualButton->HandleSelect(i, -1);
            manualButton->Select(i);
            manualButton->HandleClick(i, -1);
        }
        charSelect->rouletteCounter = -1;
    }
}
kmWritePointer(0x808D9C10, DriftSelectBeforeControlUpdate);

void AddCharSelectLayer(Pages::CountDownTimer *page, PageId id, u32 r5) {
    Section *section = SectionMgr::sInstance->curSection;
    SectionId sectionId = section->sectionId;
    if (sectionId == SECTION_P1_WIFI_VS_VOTING || sectionId == SECTION_P1_WIFI_FROOM_VS_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_TEAMVS_VOTING || sectionId == SECTION_P1_WIFI_BATTLE_VOTING
        || sectionId == SECTION_P1_WIFI_FROOM_BALLOON_VOTING || sectionId == SECTION_P1_WIFI_FROOM_COIN_VOTING) {
        ExpVR *votingPage = section->Get<ExpVR>(PAGE_VR); //always present when 0x90 is present
        if (votingPage->comboButtonState != 0) id = PAGE_CHARACTER_SELECT;
    }
    return page->AddPageLayer(id, r5);
}
kmCall(0x806509d0, AddCharSelectLayer);
}//namespace PulsarUI
