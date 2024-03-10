#include <core/nw4r/ut/Misc.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <UI/UI.hpp>
#include <UI/ChangeCombo/ChangeCombo.hpp>

namespace Pulsar {
namespace UI {

kmWrite32(0x806508d4, 0x60000000); //Add VR screen outside of 1st race in frooms
kmWrite32(0x806240e0, 0x60000000); //nop the new
Pages::VR* AddComboPages() {
    return new(ExpVR);
}
kmCall(0x806240ec, AddComboPages);


ExpVR::ExpVR() : comboButtonState(0) {
    this->onRandomComboClick.subject = this;
    this->onRandomComboClick.ptmf = &ExpVR::RandomizeCombo;
    this->onChangeComboClick.subject = this;
    this->onChangeComboClick.ptmf = &ExpVR::ChangeCombo;
}

kmWrite32(0x8064a61c, 0x60000000); //nop initControlGroup

kmWrite24(0x808998b3, 'PUL'); //WifiMemberConfirmButton -> PULiMemberConfirmButton
void ExpVR::OnInit() {
    this->InitControlGroup(0x11);
    VR::OnInit();

    this->AddControl(0xF, this->randomComboButton, 0);
    this->randomComboButton.Load(UI::buttonFolder, "PULiMemberConfirmButton", "Random", 1, 0, false);
    this->randomComboButton.SetOnClickHandler(this->onRandomComboClick, 0);

    this->AddControl(0x10, this->changeComboButton, 0);
    this->changeComboButton.Load(UI::buttonFolder, "PULiMemberConfirmButton", "Change", 1, 0, false);
    this->changeComboButton.SetOnClickHandler(this->onChangeComboClick, 0);
    this->changeComboButton.manipulator.SetAction(START_PRESS, this->changeComboButton.onClickHandlerObj, 0);

    const Section* section = SectionMgr::sInstance->curSection;

    Pages::CountDownTimer* countdownPage = section->Get<Pages::CountDownTimer>();
    CountDown* timer = &countdownPage->countdown;

    Pages::CharacterSelect* charPage = section->Get<Pages::CharacterSelect>();
    charPage->timer = timer;
    charPage->ctrlMenuCharSelect.timer = timer;

    Pages::KartSelect* kartPage = section->Get<Pages::KartSelect>();
    if(kartPage != nullptr) kartPage->timer = timer;

    Pages::BattleKartSelect* kartBattlePage = section->Get<Pages::BattleKartSelect>();
    if(kartBattlePage != nullptr) kartBattlePage->timer = timer;

    Pages::MultiKartSelect* multiKartPage = section->Get<Pages::MultiKartSelect>();
    if(multiKartPage != nullptr) multiKartPage->timer = timer;

    Pages::DriftSelect* driftPage = section->Get<Pages::DriftSelect>();
    if(driftPage != nullptr) driftPage->timer = timer;

    Pages::MultiDriftSelect* multiDriftPage = section->Get<Pages::MultiDriftSelect>();
    if(multiDriftPage != nullptr) {
        multiDriftPage->nextSectionOnButtonClick = SECTION_NONE;
        multiDriftPage->timer = timer;
    }
}




void ExpVR::RandomizeCombo(PushButton& randomComboButton, u32 hudSlotId) {
    this->comboButtonState = 1;
    this->EndStateAnimated(randomComboButton.GetAnimationFrameSize(), 0);
    Random random;
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    const Section* section = sectionMgr->curSection;
    SectionParams* sectionParams = sectionMgr->sectionParams;
    for(int hudId = 0; hudId < sectionParams->localPlayerCount; hudId++) {
        const CharacterId character = random.NextLimited<CharacterId>(24);
        const u32 randomizedKartPos = random.NextLimited(12);
        const KartId kart = kartsSortedByWeight[CharacterIDToWeightClass(character)][randomizedKartPos];

        sectionParams->characters[hudId] = character;
        sectionParams->players[hudId] = kart;
        sectionParams->combos[hudId].selCharacter = character;
        sectionParams->combos[hudId].selKart = kart;

        ExpCharacterSelect* charSelect = section->Get<ExpCharacterSelect>(); //guaranteed to exist on this page
        charSelect->randomizedCharIdx[hudId] = character;
        charSelect->rolledCharIdx[hudId] = character;
        charSelect->rouletteCounter = ExpVR::randomDuration;
        charSelect->ctrlMenuCharSelect.selectedCharacter = character;
        charSelect->controlsManipulatorManager.inaccessible = true;
        ExpBattleKartSelect* battleKartSelect = section->Get<ExpBattleKartSelect>();
        if(battleKartSelect != nullptr) {
            battleKartSelect->selectedKart = random.NextLimited(2);
            battleKartSelect->controlsManipulatorManager.inaccessible = true;
        }

        ExpKartSelect* kartSelect = section->Get<ExpKartSelect>();
        if(kartSelect != nullptr) {
            kartSelect->rouletteCounter = ExpVR::randomDuration;
            kartSelect->randomizedKartPos = randomizedKartPos;
            kartSelect->rolledKartPos = randomizedKartPos;
            kartSelect->controlsManipulatorManager.inaccessible = true;
        }

        ExpMultiKartSelect* multiKartSelect = section->Get<ExpMultiKartSelect>();
        if(multiKartSelect != nullptr) {
            multiKartSelect->rouletteCounter = ExpVR::randomDuration;
            multiKartSelect->rolledKartPos[0] = randomizedKartPos;
            u32 options = 12;
            if(IsBattle()) options = 2;
            multiKartSelect->rolledKartPos[1] = random.NextLimited(options);
            multiKartSelect->controlsManipulatorManager.inaccessible = true;
        }
    }
}

void ExpVR::ChangeCombo(PushButton& changeComboButton, u32 hudSlotId) {
    this->comboButtonState = 2;
    this->EndStateAnimated(changeComboButton.GetAnimationFrameSize(), 0);
}

static void AddChangeComboPages(Section* section, PageId id) {
    section->CreateAndInitPage(id);
    section->CreateAndInitPage(PAGE_CHARACTER_SELECT);
    bool isBattle = IsBattle();
    PageId kartPage  = PAGE_KART_SELECT;
    PageId driftPage = PAGE_DRIFT_SELECT;
    if(SectionMgr::sInstance->sectionParams->localPlayerCount == 2) {
        kartPage = PAGE_MULTIPLAYER_KART_SELECT;
        driftPage = PAGE_MULTIPLAYER_DRIFT_SELECT;
    }
    else if(isBattle) kartPage = PAGE_BATTLE_KART_SELECT;
    section->CreateAndInitPage(kartPage);
    section->CreateAndInitPage(driftPage);
}

//58 59 5e 5f 60 61
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
ExpCharacterSelect* AddCharSelect() {
    return new(ExpCharacterSelect);
}
kmCall(0x80623d5c, AddCharSelect);

void ExpCharacterSelect::BeforeControlUpdate() {
    //CtrlMenuCharacterSelect::ButtonDriver* array = this->ctrlMenuCharSelect.driverButtonsArray;
    const s32 roulette = this->rouletteCounter;
    if(roulette > 0) {
        --this->rouletteCounter;
        this->controlsManipulatorManager.inaccessible = true;
    }
    for(int hudId = 0; hudId < SectionMgr::sInstance->sectionParams->localPlayerCount; ++hudId) {
        const CharacterId prevChar = this->rolledCharIdx[hudId];
        Random random;
        const bool isGoodFrame = roulette % 4 == 1;
        if(roulette == 1) this->rolledCharIdx[hudId] = this->randomizedCharIdx[hudId];
        else if(isGoodFrame) while(this->rolledCharIdx[hudId] == prevChar) {
            this->rolledCharIdx[hudId] = static_cast<CharacterId>(random.NextLimited(24));
        }
        if(isGoodFrame) {
            this->ctrlMenuCharSelect.GetButtonDriver(prevChar)->HandleDeselect(hudId, -1);
            CtrlMenuCharacterSelect::ButtonDriver* nextButton = this->ctrlMenuCharSelect.GetButtonDriver(rolledCharIdx[hudId]);
            nextButton->HandleSelect(hudId, -1);
            nextButton->Select(0);
            //array[prevChar].HandleDeselect(0, -1);
            //array[this->rolledCharIdx].HandleSelect(0, -1);

        }
        else if(roulette == 0) this->ctrlMenuCharSelect.GetButtonDriver(randomizedCharIdx[hudId])->HandleClick(hudId, -1);
    }

    //array[this->randomizedCharIdx].HandleClick(0, -1);
}
//store correct buttons in sectionParams

kmWrite32(0x80623e58, 0x60000000);
ExpBattleKartSelect* AddBattleKartSelect() {
    return new(ExpBattleKartSelect);
}
kmCall(0x80623e64, AddBattleKartSelect);

void ExpBattleKartSelect::BeforeControlUpdate() {

    const s32 kart = this->selectedKart;
    if(kart >= 0 && this->currentState == 0x4) {
        this->controlsManipulatorManager.inaccessible = true;
        this->selectedKart = -1;
        PushButton* otherButton = this->controlGroup.GetControl<PushButton>(kart ^ 1);
        PushButton* kartButton = this->controlGroup.GetControl<PushButton>(kart);
        otherButton->HandleDeselect(0, -1);
        kartButton->HandleSelect(0, -1);
        kartButton->Select(0);
        kartButton->HandleClick(0, -1);
    }
}


kmWrite32(0x80623d68, 0x60000000);
ExpKartSelect* AddKartSelect() {
    return new(ExpKartSelect);
}
kmCall(0x80623d74, AddKartSelect);

void ExpKartSelect::BeforeControlUpdate() {
    s32 roulette = this->rouletteCounter;

    if(roulette > 0) {
        this->controlsManipulatorManager.inaccessible = true;
        Random random;
        const u32 prevRoll = this->rolledKartPos;
        ButtonMachine* prevButton = this->GetKartButton(prevRoll);
        prevButton->HandleDeselect(0, -1);

        u32 nextRoll = prevRoll;
        const bool isGoodFrame = roulette % 4 == 1;
        if(roulette == 1) nextRoll = this->randomizedKartPos;
        else if(isGoodFrame) while(nextRoll == prevRoll) nextRoll = random.NextLimited(12);
        if(isGoodFrame) {
            ButtonMachine* nextButton = this->GetKartButton(nextRoll);
            nextButton->HandleSelect(0, -1);
            nextButton->Select(0);
            this->rolledKartPos = nextRoll;
        }
        this->rouletteCounter--;
    }
    else if(roulette == 0) {
        this->rouletteCounter = -1;
        this->GetKartButton(this->randomizedKartPos)->HandleClick(0, -1);
    }

}

ButtonMachine* ExpKartSelect::GetKartButton(u32 idx) const {
    const UIControl* globalButtonHolder = this->controlGroup.GetControl(2); //holds the 6 controls (6 rows) that each hold a pair of buttons
    return globalButtonHolder->childrenGroup.GetControl(idx / 2)->childrenGroup.GetControl<ButtonMachine>(idx % 2);
}

kmWrite32(0x80623f60, 0x60000000);
ExpMultiKartSelect* AddMultiKartSelect() {
    return new(ExpMultiKartSelect);
}
kmCall(0x80623f6c, AddMultiKartSelect);
void ExpMultiKartSelect::BeforeControlUpdate() {
    Random random;
    const s32 roulette = this->rouletteCounter;
    if(roulette > 0) {
        this->rouletteCounter--;
        this->controlsManipulatorManager.inaccessible = true;
    }
    for(int hudId = 0; hudId < SectionMgr::sInstance->sectionParams->localPlayerCount; ++hudId) { //in all likelihood always 2
        if(roulette == ExpVR::randomDuration) this->arrows[hudId].SelectInitial(this->rolledKartPos[hudId]);
        if(roulette > 8) {
            const bool isGoodFrame = roulette % 4 == 1;
            if(isGoodFrame) {
                if(random.NextLimited(2) == 0) this->arrows[hudId].HandleRightPress(hudId, -1);
                else this->arrows[hudId].HandleLeftPress(hudId, 0);
            }
        }
        else if(roulette == 0) this->arrows[hudId].HandleClick(hudId, -1);
    }

}

void DriftSelectBeforeControlUpdate(Pages::DriftSelect* driftSelect) {
    ExpCharacterSelect* charSelect = SectionMgr::sInstance->curSection->Get<ExpCharacterSelect>();
    if(charSelect->rouletteCounter != -1 && driftSelect->currentState == 0x4) {
        driftSelect->controlsManipulatorManager.inaccessible = true;
        PushButton* autoButton = driftSelect->controlGroup.GetControl<PushButton>(1);
        PushButton* manualButton = driftSelect->controlGroup.GetControl<PushButton>(0);
        autoButton->HandleDeselect(0, -1);
        manualButton->HandleSelect(0, -1);
        manualButton->Select(0);
        manualButton->HandleClick(0, -1);
        charSelect->rouletteCounter = -1;
    }
}
kmWritePointer(0x808D9DF8, DriftSelectBeforeControlUpdate);

void MultiDriftSelectBeforeControlUpdate(Pages::MultiDriftSelect* multiDriftSelect) {

    SectionMgr* sectionMgr = SectionMgr::sInstance;
    ExpCharacterSelect* charSelect = sectionMgr->curSection->Get<ExpCharacterSelect>();
    if(charSelect->rouletteCounter != -1 && multiDriftSelect->currentState == 0x4) {
        multiDriftSelect->controlsManipulatorManager.inaccessible = true;
        for(int i = 0; i < sectionMgr->sectionParams->localPlayerCount; ++i) {
            PushButton* autoButton = multiDriftSelect->externControls[0 + 2 * i];
            PushButton* manualButton = multiDriftSelect->externControls[1 + 2 * i];
            autoButton->HandleDeselect(i, -1);
            manualButton->HandleSelect(i, -1);
            manualButton->Select(i);
            manualButton->HandleClick(i, -1);
        }
        charSelect->rouletteCounter = -1;
    }
}
kmWritePointer(0x808D9C10, MultiDriftSelectBeforeControlUpdate);

void AddCharSelectLayer(Pages::CountDownTimer* page, PageId id, u32 r5) {
    const ExpVR* votingPage = SectionMgr::sInstance->curSection->Get<ExpVR>(); //always present when 0x90 is present
    if(votingPage->comboButtonState != 0) id = PAGE_CHARACTER_SELECT;
    return page->AddPageLayer(id, r5);
}
kmCall(0x806509d0, AddCharSelectLayer);

asmFunc LoadCorrectPageAfterDrift() { //r0 has gamemode
    ASM(
        nofralloc;
    cmpwi r0, MODE_PUBLIC_BATTLE;
    beq - isBattle;
    cmpwi r0, MODE_PRIVATE_BATTLE;
    bne + end;
isBattle:
    li r0, 3;
end:
    cmpwi r0, 3;
    blr;
    )
}
kmCall(0x8084e670, LoadCorrectPageAfterDrift);

void LoadCorrectPageAfterMultiDrift(Pages::MultiDriftSelect* page, u32 animDirection, float animLength) {
    page->EndStateAnimated(animLength, animDirection);
    if(SectionMgr::sInstance->curSection->Get<ExpVR>() != nullptr) {
        page->nextPageId = IsBattle() ? PAGE_BATTLE_CUP_SELECT : PAGE_CUP_SELECT;
    }
}
kmCall(0x8084b68c, LoadCorrectPageAfterMultiDrift);

}//namespace UI
}//namespace Pulsar
