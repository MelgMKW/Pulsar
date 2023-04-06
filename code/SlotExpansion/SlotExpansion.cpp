#include <game/System/Archive.hpp>
#include <game/Race/RaceData.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Page/Other/GhostManager.hpp>
#include <game/UI/Page/Menu/CupSelect.hpp>
#include <game/UI/Page/Menu/CourseSelect.hpp>
#include <game/UI/Page/Other/Votes.hpp>
#include <Pulsar.hpp>



//TrackSlot
//Patches course buttons IDs so that it goes vertical than horizontal rather than the opposite
kmWrite32(0x807e525c, 0x937403CC); //Course buttons ids

//CourseId of 1st button is 4*CupID due to reordering
kmWrite32(0x8084182c, 0x5400103A);
kmWrite32(0x80841830, 0x60000000);

//CourseSelect::LoadNextPage patch mentioned above
int UpdateSlot(Pages::CourseSelect *page, CtrlMenuCourseSelectCourse *control, PushButton *button) {
    Pulsar *pulsar = Pulsar::sInstance;
    pulsar->SaveSelectedCourse(button);
    return pulsar->GetCorrectTrackSlot();
}

asm void UpdateSlotWrapper() {
    ASM(
        nofralloc;
    mflr r31;
    bl UpdateSlot;
    mtlr r31;
    mr r31, r3;
    blr;
    )
}
kmCall(0x80840858, UpdateSlotWrapper);

void SetVotedTrack(Pages::Vote *vote) {
    vote->SetVotedCourseId(Pulsar::sInstance->selectedCourse);
}
kmCall(0x8084099c, SetVotedTrack);

//CtrlMenuCupSelectCup::OnCupButtonClick patch that updates lastSelectCup so that the game remembers it in btw races
void UpdateLastSelCup(Pages::CupSelect *page, CtrlMenuCupSelectCup *cups, PushButton *button, u32 hudSlotId) {
    Pulsar *pulsar = Pulsar::sInstance;
    if (button->buttonId != pulsar->lastSelectedCup) {
        pulsar->lastSelectedCup = button->buttonId;
        pulsar->selectedCourse = (CourseId)(pulsar->lastSelectedCup * 4);
    }
    PushButton **buttons = (PushButton **)cups->childrenGroup.controlArray;
    for (int i = 0; i < 8; i++) if (buttons[i] == button) pulsar->lastSelectedButtonIdx = i;
    page->LoadNextPage(cups, button, hudSlotId);
    RaceData::sInstance->menusScenario.settings.cupId = pulsar->lastSelectedCup % 8;
}
kmCall(0x807e5da8, UpdateLastSelCup);



//Loads correct file
void FormatTrackPath(char *path, u32 length, const char *format, const char *fileName) {
    Pulsar *pulsar = Pulsar::sInstance;
    GameMode gamemode = RaceData::sInstance->menusScenario.settings.gamemode;
    CourseId pulsarId = pulsar->winningCourse; //fileName already set through racedata's courseId, which has been set to realId before
    if (gamemode == MODE_BATTLE || gamemode == MODE_PUBLIC_BATTLE || gamemode == MODE_PRIVATE_BATTLE
        || gamemode == MODE_AWARD || pulsar->IsReg(pulsarId)) snprintf(path, 0x80, format, fileName);
    else {
        CourseId realId = pulsar->ConvertTrack_PulsarIdToRealId(pulsarId);
        if (pulsar->hasOddCups && realId >= (pulsar->GetCtsTrackCount() - 4)) realId = (CourseId)(realId % 4);
        snprintf(path, 0x80, "Race/Course/%d", realId);
    }
}
kmCall(0x80540820, FormatTrackPath);
kmCall(0x80540870, FormatTrackPath);
kmCall(0x80541bc4, FormatTrackPath);
kmWrite32(0x80531fbc, 0x38800000); //fix incorrect courseId array read


void FixGrandPrix(Pages::CupSelect *page, SectionId nextSection, PushButton *button) {
    Pulsar::sInstance->winningCourse = (CourseId)(button->buttonId * 4);
    page->ChangeSectionById(SECTION_VS_RACE_PANORAMA, button);
};
kmCall(0x80841854, FixGrandPrix);

/*
using Pulsar::extSlotToTrackId;
using Pulsar::winningCourse;
asm void GetCorrectSlotArray(){
   ASM(
      lis r5, winningCourse@ha;
      lwz r6, winningCourse@l(r5);
      add r6, r6, r4;
      stw r6, winningCourse@l(r5);
      lis r5, extSlotToTrackId@h;
      ori r5, r5, extSlotToTrackId@l;
   )
};
kmBranch(0x8052f210, GetCorrectSlotArray);
kmPatchExitPoint(GetCorrectSlotArray, 0x8052f214);
*/

//Fixes GP since it usually uses racedata's courseId which only holds the slot
RacedataScenario *UseCorrectCourse(RacedataScenario *scenario) {
    Pulsar *pulsar = Pulsar::sInstance;
    pulsar->winningCourse = (CourseId)(pulsar->lastSelectedCup * 4 + scenario->settings.raceNumber);
    scenario->settings.courseId = pulsar->GetCorrectTrackSlot();
    return scenario;
};
kmWrite32(0x8052f220, 0x60000000);

//Wrapper around function above
asm void UseCorrectCourseWrapper() {
    ASM(
        nofralloc;
    mflr r0;
    stw r0, 0x8(sp);
    bl UseCorrectCourse;
    lwz r0, 0x8(sp);
    mtlr r0;
    blr;
    )
}
kmBranch(0x8052f224, UseCorrectCourseWrapper);
kmPatchExitPoint(UseCorrectCourseWrapper, 0x8052f228);

//Badly written, but does the job even though it can in theory hang forever, as unlikely as it is
void VSRaceRandomFix(SectionMgr98 *m98) { //properly randomizes tracks and sets the first one
    m98->vsRaceLimit = 32;
    Pulsar *pulsar = Pulsar::sInstance;
    Random random;
    CourseId id;
    bool isRepeat;
    for (int i = 0; i < 32; i++) {
        do {
            id = pulsar->RandomizeTrack(&random);
            isRepeat = false;
            for (int j = 0; j < i; j++) {
                if (m98->vsTracks[j] == id) {
                    isRepeat = true;
                    break;
                }
            }
        } while (isRepeat);
        m98->vsTracks[i] = id;
    }

    pulsar->winningCourse = m98->vsTracks[0];
    RaceData::sInstance->menusScenario.settings.courseId = pulsar->GetCorrectTrackSlot();
};
kmBranch(0x805e32ec, VSRaceRandomFix);
kmWrite32(0x8084e5e4, 0x60000000); //nop racedata courseId store since it's done in the function

//Same as GP, racedata only ever has courseId
void VSRaceOrderedFix(SectionMgr98 *m98) {
    m98->vsRaceLimit = 32;
    Pulsar *pulsar = Pulsar::sInstance;
    CourseId initial = pulsar->winningCourse;
    u32 cupId = initial / 4;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) m98->vsTracks[i * 4 + j] = (CourseId)(cupId * 4 + j);
        cupId = pulsar->GetNextCupId(cupId, 1);
    }
};
kmCall(0x80840a24, VSRaceOrderedFix);

CourseId VSNextTrackFix(CourseId id) {//properly sets the next track
    Pulsar *pulsar = Pulsar::sInstance;
    pulsar->winningCourse = id;
    return pulsar->GetCorrectTrackSlot();
}
kmBranch(0x808606cc, VSNextTrackFix);
