#include <MarioKartWii/Race/Racedata.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <MarioKartWii/UI/Page/Menu/CourseSelect.hpp>
#include <Ghost/UI/ExpGhostSelect.hpp>
#include <Ghost/GhostManager.hpp>
#include <Settings/Settings.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace  Pulsar {
namespace UI {
//When the player goes back to the main menu, MultiGhostMgr is destroyed
static void DestroyMultiGhostManager(Section& section, PageId pageId) {
    section.CreateAndInitPage(pageId);
    Ghosts::Mgr::DestroyInstance();
}
kmCall(0x8062cf98, DestroyMultiGhostManager);

//GhostInfoControl BRCTR
static void LoadCustomGhostInfoBRCTR(ControlLoader& loader, const char* folderName, const char* ctrName,
    const char* variantName, const char** anims) {
    loader.Load(folderName, "PULGhostInfo", variantName, anims);
}
kmCall(0x805e28c0, LoadCustomGhostInfoBRCTR);
kmWrite32(0x80639958, 0x3880000C); //Add controls

ExpGhostSelect::ExpGhostSelect() {
    Ghosts::Mgr::CreateInstance();
    this->onChallengeGhostClickHandler.ptmf = &ExpGhostSelect::OnChallengeGhostPress;
    this->onWatchReplayClickHandler.ptmf = &ExpGhostSelect::OnWatchReplayPress;
    this->onRightArrowPressHandler.ptmf = &ExpGhostSelect::OnRightArrowPress;
    this->onLeftArrowPressHandler.ptmf = &ExpGhostSelect::OnLeftArrowPress;
    this->onSelectGhostChangeHandler.subject = this;
    this->onSelectGhostChangeHandler.ptmf = &ExpGhostSelect::OnSelectGhostChange;
    this->onStartPressHandler.subject = this;
    this->onStartPressHandler.ptmf = &ExpGhostSelect::OnStartPress;
}

void ExpGhostSelect::OnInit() {
    GhostSelect::OnInit();
    this->AddControl(0x9, this->bottomText, 0);
    this->bottomText.Load();
    this->selectGhostButton.buttonId = 0xA;
    this->AddControl(0xA, this->selectGhostButton, 0);
    this->selectGhostButton.Load(1, UI::buttonFolder, "SelectGhost", "SelectGhost"); //check multighost
    this->selectGhostButton.SetOnClickHandler(this->onSelectGhostChangeHandler, 0);
    this->manipulatorManager.SetGlobalHandler(START_PRESS, onStartPressHandler, false, false);
    this->AddControl(0xB, this->favGhost, 0);
    ControlLoader loader(&this->favGhost);
    loader.Load(UI::controlFolder, "PULInstruction", "OTTGhost", nullptr);
    this->Reset();
}

//BottomText will display the current TTmode as well as if the player has a trophy on the track
void ExpGhostSelect::OnActivate() {
    GhostSelect::OnActivate();
    const System* system = System::sInstance;
    if (system->GetInfo().HasTrophies()) {
        u32 bmgId;
        const Text::Info text = GetCourseBottomText(CupsConfig::sInstance->GetWinning(), &bmgId);
        this->bottomText.SetMessage(bmgId, &text);
    }
    this->ctrlMenuPageTitleText.SetMessage(BMG_CHOOSE_GHOST_DATA);
    this->Reset();
    this->selectGhostButton.SetMessage(BMG_SELECT_GHOST);

    const TTMode mode = system->ttMode;
    bool isStarVisibleOnActivate = false;
    if (mode < TTMODE_150_FEATHER) {
        const GhostList* list = this->ghostList;
        for (int i = 0; i < list->count; ++i) {
            if (list->entries[i].padding[0] == Ghosts::Mgr::GetInstance()->GetFavGhostFileIndex(mode)) {
                this->favGhostIndex = i;
            }
        }
        if (this->favGhostIndex == this->page) isStarVisibleOnActivate = true;
    }
    this->info->SetPaneVisibility("star", isStarVisibleOnActivate);
}

void ExpGhostSelect::OnDeactivate() {
    Ghosts::Mgr::sInstance->SaveLeaderboard();
}
//Creates space by making the usual 3 buttons smaller, could be done without a BRCTR but this is easier to maintain
static void LoadButtonWithCustBRCTR(PushButton& button, const char* folderName, const char* ctrName, const char* variant,
    u32 localPlayerBitfield, u32 r8, bool inaccessible)
{
    button.Load(folderName, "GhostListButton", variant, localPlayerBitfield, r8, inaccessible);
}
kmCall(0x80639ab8, LoadButtonWithCustBRCTR);
kmCall(0x80639ad8, LoadButtonWithCustBRCTR);
kmCall(0x80639af8, LoadButtonWithCustBRCTR);


void ExpGhostSelect::OnChallengeGhostPress(PushButton& button, u32 hudSlotId) {
    GhostSelect::OnChallengeGhostPress(button, hudSlotId);
    const GhostListEntry& entry = this->ghostList->entries[this->page];
    Ghosts::Mgr::sInstance->EnableGhost(entry, true);
}

void ExpGhostSelect::OnWatchReplayPress(PushButton& button, u32 hudSlotId) {
    GhostSelect::OnWatchReplayPress(button, hudSlotId);
    const GhostListEntry& entry = this->ghostList->entries[this->page];
    Ghosts::Mgr::sInstance->EnableGhost(entry, true);
}

void ExpGhostSelect::OnSelectGhostChange(ToggleButton& button, u32) {
    Ghosts::Mgr* mgr = Ghosts::Mgr::sInstance;
    const GhostListEntry& entry = this->ghostList->entries[this->page];

    if (button.GetState() == true) {
        u32 index = mgr->lastUsedSlot;
        if (mgr->EnableGhost(entry, false)) {
            this->selectedGhostsPages[index] = this->page;
            this->selectedGhostsCount = (this->selectedGhostsCount + 1) > 3 ? 3 : (this->selectedGhostsCount + 1);
        }
        else button.ToggleState(false);
    }
    else {
        mgr->DisableGhost(entry);
        this->selectedGhostsPages[mgr->lastUsedSlot] = -1;
        this->selectedGhostsCount -= 1;
    }
    Text::Info text;
    text.intToPass[0] = this->selectedGhostsCount;
    this->ctrlMenuPageTitleText.SetMessage(BMG_GHOST_SELECTED_COUNTER, &text);
    this->SetToggleBMG();
}

void ExpGhostSelect::OnStartPress(u32) {
    bool isStarVisible;
    if (this->favGhostIndex == this->page) {
        this->favGhostIndex = -1;
        isStarVisible = false;
    }
    else {
        this->favGhostIndex = this->page;
        isStarVisible = true;
    }
    this->PlaySound(isStarVisible ? SOUND_ID_SMALL_HIGH_NOTE : SOUND_ID_BACK_PRESS, 0);
    Ghosts::Mgr::sInstance->SetFavGhost(this->ghostList->entries[this->page], System::sInstance->ttMode, isStarVisible);
    this->info->SetPaneVisibility("star", isStarVisible);

}

void ExpGhostSelect::OnRightArrowPress(SheetSelectControl& control, u32 hudSlotId) {
    GhostSelect::OnRightArrowPress(control, hudSlotId);
    this->OnNewPage();
}

void ExpGhostSelect::OnLeftArrowPress(SheetSelectControl& control, u32 hudSlotId) {
    GhostSelect::OnLeftArrowPress(control, hudSlotId);
    this->OnNewPage();
}

void ExpGhostSelect::OnNewPage() {
    ToggleButton& button = this->selectGhostButton;
    if (this->page == this->selectedGhostsPages[0] || this->page == this->selectedGhostsPages[1] || this->page == this->selectedGhostsPages[2]) {
        if (button.GetState() == false) button.ToggleState(true);
    }
    else if (button.GetState() == true) button.ToggleState(false);

    this->SetToggleBMG();

    bool isStarHidden;
    if (this->page == this->favGhostIndex) {
        isStarHidden = true;
    }
    else isStarHidden = false;
    this->info->SetPaneVisibility("star", isStarHidden);

}

void ExpGhostSelect::SetToggleBMG() {
    ToggleButton& button = this->selectGhostButton;
    const u32 bmgId = button.GetState() == false ? BMG_SELECT_GHOST : BMG_GHOST_SELECTED;
    button.SetMessage(bmgId);
}

void ExpGhostSelect::Reset() {
    this->selectedGhostsPages[0] = -1;
    this->selectedGhostsPages[1] = -1;
    this->selectedGhostsPages[2] = -1;
    this->selectedGhostsCount = 0;
    this->selectGhostButton.ToggleState(false);
    this->favGhostIndex = -1;
}

//Complete rewrite TTSplits BeforeEntranceAnimations; this will request a RKG if needed (flap or top 10 time)
void BeforeEntranceAnimations(Pages::TTSplits* page) {
    //Init Variables
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    SectionParams* sectionParams = sectionMgr->sectionParams;
    sectionParams->isNewTime = false;
    sectionParams->fastestLapId = 0xFFFFFFFF;
    sectionParams->unknown_0x3D8 = false;
    RKSYS::LicenseLdbEntry entry;

    const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    const u8 playerId = scenario.settings.hudPlayerIds[0];
    entry.character = scenario.players[playerId].characterId;
    entry.kart = scenario.players[playerId].kartId;
    entry.controllerType = sectionMgr->pad.GetType(sectionMgr->pad.GetCurrentID(0));
    const Mii* mii = sectionParams->playerMiis.GetMii(0);
    Mii::ComputeRFLStoreData(entry.miiData, &mii->info.createID);

    //Find which lap is the best
    RaceinfoPlayer* raceInfoPlayer = Raceinfo::sInstance->players[playerId];
    page->timers[0] = *raceInfoPlayer->raceFinishTime;
    page->ctrlRaceTimeArray[0]->SetTimer(&page->timers[0]);
    page->ctrlRaceTimeArray[0]->OnFocus();
    Timer* bestLap = &page->timers[0];
    u32 bestLapId = 1;
    for (int i = 1; i < page->splitsRowCount; ++i) {
        raceInfoPlayer->FillTimerWithSplits(i, &page->timers[i]);
        if ((*bestLap) > page->timers[i]) {
            bestLap = &page->timers[i];
            bestLapId = i;
        }
        CtrlRaceTime* curRaceTime = page->ctrlRaceTimeArray[i];
        curRaceTime->SetTimer(&page->timers[i]);
        curRaceTime->OnFocus();
    }

    //No saving and no new record in OTT for now
    if (System::sInstance->IsContext(PULSAR_MODE_OTT)) return;

    //enhanced replay
    if (sectionMgr->curSection->sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL
        && sectionMgr->curSection->sectionId <= SECTION_WATCH_GHOST_FROM_MENU) {
        page->ctrlRaceTimeArray[0]->EnableFlashingAnimation();
        page->ctrlRaceTimeArray[bestLapId]->EnableFlashingAnimation();
        page->ctrlRaceCount.isHidden = false;
        page->ctrlRaceCount.FadeIn();
        page->PlaySound(SOUND_ID_NEW_RECORD, -1);
        page->savedGhostMessage.SetMessage(UI::BMG_SAVED_GHOST);
    }

    //Finish Time Leaderboard check and request
    else {
        Ghosts::Mgr* manager = Ghosts::Mgr::sInstance;
        bool hasFlap = false;
        manager->entry = entry;
        manager->GetLeaderboard().EntryToTimer(manager->entry.timer, Ghosts::ENTRY_FLAP);
        if (manager->entry.timer > *bestLap) {
            manager->entry.timer = *bestLap;
            hasFlap = true;
            sectionParams->fastestLapId = bestLapId;
            page->ctrlRaceTimeArray[bestLapId]->EnableFlashingAnimation();
        }
        entry.timer = page->timers[0];
        const s32 position = manager->GetLeaderboard().GetPosition(page->timers[0]);
        sectionParams->leaderboardPosition = position;
        if (position == 0) {
            page->ctrlRaceCount.isHidden = false;
            page->ctrlRaceCount.FadeIn();
            sectionParams->unknown_0x3D8 = true;
            if (Input::Manager::sInstance->realControllerHolders[0].ghostWriter->status != 3 && page->timers[0].minutes < 6) {
                sectionParams->isNewTime = true;
            }
            page->ctrlRaceTimeArray[0]->EnableFlashingAnimation();
            page->PlaySound(SOUND_ID_NEW_RECORD, -1);
            page->savedGhostMessage.SetMessage(UI::BMG_SAVED_GHOST);

        }
        else if (position < 0) page->ctrlRaceCount.isHidden = true;
        if (hasFlap || position >= 0) {
            bool gotTrophy = manager->SaveGhost(entry, position, hasFlap);
            if (gotTrophy) page->savedGhostMessage.SetMessage(UI::BMG_TROPHY_EARNED);
        }
    }
}
kmWritePointer(0x808DA614, BeforeEntranceAnimations);


static void TrophyBMG(CtrlMenuInstructionText& bottomText, u32 bmgId) {
    Text::Info text;
    const System* system = System::sInstance;
    const Settings::Mgr& settings = Settings::Mgr::Get();
    u32 trophyCount = settings.GetTrophyCount(system->ttMode);
    u32 totalCount = settings.GetTotalTrophyCount(system->ttMode);
    text.intToPass[0] = trophyCount;
    text.intToPass[1] = totalCount;
    text.bmgToPass[0] = BMG_TT_MODE_BOTTOM_CUP + system->ttMode;
    bmgId = BMG_TT_BOTTOM_CUP_NOTROPHY;
    if (totalCount > 0 && system->GetInfo().HasTrophies()) bmgId = BMG_TT_BOTTOM_CUP;
    bottomText.SetMessage(bmgId, &text);
}
kmCall(0x8084144c, TrophyBMG);

void IndividualTrophyBMG(Pages::CourseSelect& courseSelect, CtrlMenuCourseSelectCourse& course, PushButton& button, u32 hudSlotId) {
    if (Racedata::sInstance->menusScenario.settings.gamemode != MODE_TIME_TRIAL) {
        courseSelect.UpdateBottomText(course, button, hudSlotId);
    }
    else {
        u32 bmgId;
        CupsConfig* cupsConfig = CupsConfig::sInstance;
        const Text::Info text = GetCourseBottomText(cupsConfig->ConvertTrack_PulsarCupToTrack(cupsConfig->lastSelectedCup, button.buttonId), &bmgId); //FIX HERE
        courseSelect.bottomText->SetMessage(bmgId, &text);
    }
}
kmCall(0x807e54ec, IndividualTrophyBMG);

//Global function as it is also used by CourseSelect
const Text::Info GetCourseBottomText(PulsarId id, u32* bmgId) {
    const System* system = System::sInstance;
    const Settings::Mgr& settings = Settings::Mgr::Get();
    if (settings.GetTotalTrophyCount(system->ttMode) > 0) *bmgId = BMG_TT_BOTTOM_COURSE;
    else *bmgId = BMG_TT_BOTTOM_COURSE_NOTROPHY;

    const bool hasTrophy = settings.HasTrophy(id, system->ttMode);
    Text::Info text;
    text.bmgToPass[0] = BMG_TT_MODE_BOTTOM_CUP + system->ttMode;
    u32 passedBmgId = BMG_NO_TROPHY;
    if (hasTrophy) passedBmgId = BMG_TROPHY;
    text.bmgToPass[1] = passedBmgId;
    return text;
}

void SetRankingsBMG() {

}


}//namespace UI
}//namespace Pulsar