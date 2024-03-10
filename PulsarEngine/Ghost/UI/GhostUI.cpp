#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <Ghost/UI/GhostUI.hpp>
#include <Ghost/GhostManager.hpp>
#include <UI/UI.hpp>

namespace  Pulsar {
namespace UI {
//When the player goes back to the main menu, MultiGhostMgr is destroyed
static void DestroyMultiGhostManager(Section& section, PageId pageId) {
    section.CreateAndInitPage(pageId);
    Ghosts::Manager::DestroyInstance();
}
kmCall(0x8062cf98, DestroyMultiGhostManager);

//GhostInfoControl BRCTR
static void LoadCustomGhostInfoBRCTR(ControlLoader& loader, const char* folderName, const char* ctrName,
    const char* variantName, const char** anims) {
    loader.Load(folderName, "PULGhostInfo", variantName, anims);
}
kmCall(0x805e28c0, LoadCustomGhostInfoBRCTR);

ExpGhostSelect* CreateExpandedSelectGhostPage() {
    Ghosts::Manager::CreateInstance();
    return new(ExpGhostSelect);
};
kmCall(0x80623dec, CreateExpandedSelectGhostPage);
kmWrite32(0x80623de0, 0x60000000); //nop the new
kmWrite32(0x80639958, 0x3880000B); //Add controls

ExpGhostSelect::ExpGhostSelect() {
    this->onChallengeGhostClickHandler.ptmf = &ExpGhostSelect::OnChallengeGhostPress;
    this->onWatchReplayClickHandler.ptmf = &ExpGhostSelect::OnWatchReplayPress;
    this->onRightArrowPressHandler.ptmf = &ExpGhostSelect::OnRightArrowPress;
    this->onLeftArrowPressHandler.ptmf = &ExpGhostSelect::OnLeftArrowPress;
    this->onSelectGhostChangeHandler.subject = this;
    this->onSelectGhostChangeHandler.ptmf = &ExpGhostSelect::OnSelectGhostChange;
}

void ExpGhostSelect::OnInit() {
    GhostSelect::OnInit();
    this->AddControl(0x9, this->bottomText, 0);
    this->bottomText.Load();
    this->selectGhostButton.buttonId = 0xA;
    this->AddControl(0xA, this->selectGhostButton, 0);
    this->selectGhostButton.Load(1, UI::buttonFolder, "SelectGhost", "SelectGhost"); //check multighost
    this->selectGhostButton.SetOnClickHandler(this->onSelectGhostChangeHandler, 0);

    this->Reset();
}

//BottomText will display the current TTmode as well as if the player has a trophy on the track
void ExpGhostSelect::OnActivate() {
    GhostSelect::OnActivate();
    const System* system = System::sInstance;
    if(Info::HasTrophies()) {
        u32 bmgId;
        const TextInfo text = GetCourseBottomText(CupsConfig::sInstance->winningCourse, &bmgId);
        this->bottomText.SetMessage(bmgId, &text);
    }
    this->ctrlMenuPageTitleText.SetMessage(BMG_CHOOSE_GHOST_DATA);
    this->Reset();
    this->selectGhostButton.SetMessage(BMG_SELECT_GHOST);
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
    Ghosts::Manager::sInstance->EnableGhost(entry, true);
}

void ExpGhostSelect::OnWatchReplayPress(PushButton& button, u32 hudSlotId) {
    GhostSelect::OnWatchReplayPress(button, hudSlotId);
    const GhostListEntry& entry = this->ghostList->entries[this->page];
    Ghosts::Manager::sInstance->EnableGhost(entry, true);
}

void ExpGhostSelect::OnSelectGhostChange(ToggleButton& button, u32) {
    Ghosts::Manager* mgr = Ghosts::Manager::sInstance;
    const GhostListEntry& entry = this->ghostList->entries[this->page];

    if(button.GetState() == true) {
        u32 index = mgr->lastUsedSlot;
        if(mgr->EnableGhost(entry, false)) {
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
    TextInfo text;
    text.intToPass[0] = this->selectedGhostsCount;
    this->ctrlMenuPageTitleText.SetMessage(BMG_GHOST_SELECTED_COUNTER, &text);
    this->SetToggleBMG();
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
    if(this->page == this->selectedGhostsPages[0] || this->page == this->selectedGhostsPages[1] || this->page == this->selectedGhostsPages[2]) {
        if(button.GetState() == false) {
            button.ToggleState(true);
        }
    }
    else if(button.GetState() == true) button.ToggleState(false);
    this->SetToggleBMG();
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
}

//Complete rewrite TTSplits BeforeEntranceAnimations; this will request a RKG if needed (flap or top 10 time)
void BeforeEntranceAnimations(Pages::TTSplits* page) {
    //Init Variables
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    SectionParams* m98 = sectionMgr->sectionParams;
    m98->isNewTime = false;
    m98->fastestLapId = 0xFFFFFFFF;
    m98->unknown_0x3D8 = false;
    TimeEntry entry;
    entry.character = RaceData::sInstance->racesScenario.players[0].characterId;
    entry.kart = RaceData::sInstance->racesScenario.players[0].kartId;
    entry.controllerType = sectionMgr->pad.GetType(sectionMgr->pad.GetCurrentID(0));
    const Mii* mii = m98->playerMiis.GetMii(0);
    Mii::ComputeRFLStoreData(entry.miiData, &mii->info.createID);

    //Find which lap is the best
    RaceInfoPlayer* raceInfoPlayer = RaceInfo::sInstance->players[0];
    page->timers[0] = *raceInfoPlayer->raceFinishTime;
    page->ctrlRaceTimeArray[0]->SetTimer(&page->timers[0]);
    page->ctrlRaceTimeArray[0]->OnFocus();
    Timer* bestLap = &page->timers[0];
    u32 bestLapId = 1;
    for(int i = 1; i < page->splitsRowCount; ++i) {
        raceInfoPlayer->FillTimerWithSplits(i, &page->timers[i]);
        if((*bestLap) > page->timers[i]) {
            bestLap = &page->timers[i];
            bestLapId = i;
        }
        CtrlRaceTime* curRaceTime = page->ctrlRaceTimeArray[i];
        curRaceTime->SetTimer(&page->timers[i]);
        curRaceTime->OnFocus();
    }
    //enhanced replay
    if(sectionMgr->curSection->sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL
        && sectionMgr->curSection->sectionId <= SECTION_WATCH_GHOST_FROM_MENU) {
        page->ctrlRaceTimeArray[0]->EnableFlashingAnimation();
        page->ctrlRaceTimeArray[bestLapId]->EnableFlashingAnimation();
        page->ctrlRaceCount.isHidden = false;
        page->ctrlRaceCount.Animate();
        page->PlaySound(0xDD, -1);
        page->savedGhostMessage.SetMessage(UI::BMG_SAVED_GHOST);
    }

    //Finish Time Leaderboard check and request
    else {
        Ghosts::Manager* manager = Ghosts::Manager::sInstance;
        bool hasFlap = false;
        manager->entry = entry;
        manager->GetLeaderboard().EntryToTimer(manager->entry.timer, Ghosts::ENTRY_FLAP);
        //TimeEntry bestLap = entry;
        if(manager->entry.timer > *bestLap) {
            manager->entry.timer = *bestLap;
            hasFlap = true;
            m98->fastestLapId = bestLapId;
            page->ctrlRaceTimeArray[bestLapId]->EnableFlashingAnimation();
        }
        entry.timer = page->timers[0];
        const s32 position = manager->GetLeaderboard().GetPosition(page->timers[0]);
        m98->leaderboardPosition = position;
        if(position == 0) {
            page->ctrlRaceCount.isHidden = false;
            page->ctrlRaceCount.Animate();
            m98->unknown_0x3D8 = true;
            if(Input::Manager::sInstance->realControllerHolders[0].ghostWriter->status != 3 && page->timers[0].minutes < 6) {
                m98->isNewTime = true;
            }
            page->ctrlRaceTimeArray[0]->EnableFlashingAnimation();
            page->PlaySound(0xDD, -1);
            page->savedGhostMessage.SetMessage(UI::BMG_SAVED_GHOST);

        }
        else if(position < 0) page->ctrlRaceCount.isHidden = true;
        if(hasFlap || position >= 0) {
            bool gotTrophy = manager->SaveGhost(entry, position, hasFlap);
            if(gotTrophy) page->savedGhostMessage.SetMessage(UI::BMG_TROPHY_EARNED);
        }
    }
}
kmWritePointer(0x808DA614, BeforeEntranceAnimations);


static void TrophyBMG(CtrlMenuInstructionText& bottomText, u32 bmgId) {
    TextInfo text;
    const System* system = System::sInstance;
    const Settings::Mgr* settings = Settings::Mgr::GetInstance();
    u32 trophyCount = settings->GetTrophyCount(system->ttMode);
    u32 totalCount = settings->GetTotalTrophyCount(system->ttMode);
    text.intToPass[0] = trophyCount;
    text.intToPass[1] = totalCount;
    text.bmgToPass[0] = BMG_TT_MODE_BOTTOM_CUP + system->ttMode;
    bmgId = BMG_TT_BOTTOM_CUP_NOTROPHY;
    if(totalCount > 0 && Info::HasTrophies()) bmgId = BMG_TT_BOTTOM_CUP;
    bottomText.SetMessage(bmgId, &text);
}
kmCall(0x8084144c, TrophyBMG);

void IndividualTrophyBMG(Pages::CourseSelect& courseSelect, CtrlMenuCourseSelectCourse& course, PushButton& button, u32 hudSlotId) {
    if(RaceData::sInstance->menusScenario.settings.gamemode != MODE_TIME_TRIAL) {
        courseSelect.UpdateBottomText(course, button, hudSlotId);
    }
    else {
        u32 bmgId;
        CupsConfig* cupsConfig = CupsConfig::sInstance;
        const TextInfo text = GetCourseBottomText(cupsConfig->ConvertTrack_PulsarCupToTrack(cupsConfig->lastSelectedCup, button.buttonId), &bmgId); //FIX HERE
        courseSelect.bottomText->SetMessage(bmgId, &text);
    }
}
kmCall(0x807e54ec, IndividualTrophyBMG);

//Global function as it is also used by CourseSelect
const TextInfo GetCourseBottomText(PulsarId id, u32* bmgId) {
    const System* system = System::sInstance;
    const Settings::Mgr* settings = Settings::Mgr::GetInstance();
    if(settings->GetTotalTrophyCount(system->ttMode) > 0) *bmgId = BMG_TT_BOTTOM_COURSE;
    else *bmgId = BMG_TT_BOTTOM_COURSE_NOTROPHY;

    bool hasTrophy = Settings::Mgr::GetInstance()->HasTrophy(id, system->ttMode);
    TextInfo text;
    text.bmgToPass[0] = BMG_TT_MODE_BOTTOM_CUP + system->ttMode;
    u32 passedBmgId = BMG_NO_TROPHY;
    if(hasTrophy) passedBmgId = BMG_TROPHY;
    text.bmgToPass[1] = passedBmgId;
    return text;
}

}//namespace UI
}//namespace Pulsar