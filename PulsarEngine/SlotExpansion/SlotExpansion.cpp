#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Other/GhostManager.hpp>
#include <MarioKartWii/UI/Page/Menu/CupSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/CourseSelect.hpp>
#include <MarioKartWii/UI/Page/Other/Votes.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace Pulsar {

//TrackSlot
//Patches course buttons IDs so that it goes vertical than horizontal rather than the opposite
kmWrite32(0x807e525c, 0x937403CC); //Course buttons ids

//CourseId of 1st button is 4*CupID due to reordering
kmWrite32(0x8084182c, 0x5400103A);
kmWrite32(0x80841830, 0x60000000);

//CourseSelect::LoadNextPage patch mentioned above
int UpdateSlot(const Pages::CourseSelect* page, const CtrlMenuCourseSelectCourse* control, const PushButton* button) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    cupsConfig->SaveSelectedCourse(*button);
    return cupsConfig->GetCorrectTrackSlot();
}

asmFunc UpdateSlotWrapper() {
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

void SetVotedTrack(Pages::Vote* vote) { //cast because we actually want to transmit a pulsarId
    vote->SetVotedCourseId(static_cast<CourseId>(CupsConfig::sInstance->selectedCourse));
}
kmCall(0x8084099c, SetVotedTrack);

//CtrlMenuCupSelectCup::OnCupButtonClick patch that updates lastSelectCup so that the game remembers it in btw races
void UpdateLastSelCup(Pages::CupSelect* page, CtrlMenuCupSelectCup& cups, PushButton& button, u32 hudSlotId) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    if(button.buttonId != cupsConfig->lastSelectedCup) {
        cupsConfig->lastSelectedCup = static_cast<PulsarCupId>(button.buttonId);
        cupsConfig->selectedCourse = cupsConfig->ConvertTrack_PulsarCupToTrack(cupsConfig->lastSelectedCup, 0);
    }
    PushButton** buttons = reinterpret_cast<PushButton**>(cups.childrenGroup.controlArray);
    for(int i = 0; i < 8; ++i) if(buttons[i] == &button) cupsConfig->lastSelectedCupButtonIdx = i;
    page->LoadNextPage(cups, button, hudSlotId);
    RaceData::sInstance->menusScenario.settings.cupId = cupsConfig->lastSelectedCup % 8;
}
kmCall(0x807e5da8, UpdateLastSelCup);



//Loads correct file
static void FormatTrackPath(char* path, u32 length, const char* format, const char* fileName) {
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const PulsarId pulsarId = cupsConfig->winningCourse; //fileName already set through racedata's courseId, which has been set to realId before
    if(IsBattle() || CupsConfig::IsReg(pulsarId)) snprintf(path, 0x80, format, fileName);
    else {
        CourseId realId = CupsConfig::ConvertTrack_PulsarIdToRealId(pulsarId);
        if(cupsConfig->HasOddCups() && realId >= (cupsConfig->GetCtsTrackCount() - 4)) realId = static_cast<CourseId>(realId % 4);
        snprintf(path, 0x80, "Race/Course/%d", realId);
    }
}
kmCall(0x80540820, FormatTrackPath);
kmCall(0x80540870, FormatTrackPath);
kmCall(0x80541bc4, FormatTrackPath);
kmWrite32(0x80531fbc, 0x38800000); //fix incorrect courseId array read
kmWrite32(0x805407d4, 0x48000020); //prevent reuse of szs if same courseId

//Fixes GP since it usually uses racedata's courseId which only holds the slot
RacedataScenario* UseCorrectCourse(RacedataScenario* scenario) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    cupsConfig->winningCourse = cupsConfig->ConvertTrack_PulsarCupToTrack(cupsConfig->lastSelectedCup, scenario->settings.raceNumber); //FIX HERE
    scenario->settings.courseId = cupsConfig->GetCorrectTrackSlot();
    return scenario;
};
kmWrite32(0x8052f220, 0x60000000);

//Wrapper around function above
asmFunc UseCorrectCourseWrapper() {
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
static void VSRaceRandomFix(SectionParams* m98) { //properly randomizes tracks and sets the first one
    m98->vsRaceLimit = 32;
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    Random random;
    PulsarId id;
    bool isRepeat;
    for(int i = 0; i < 32; ++i) {
        do {
            id = cupsConfig->RandomizeTrack(&random);
            isRepeat = false;
            for(int j = 0; j < i; ++j) {
                if(m98->vsTracks[j] == id) {
                    isRepeat = true;
                    break;
                }
            }
        } while(isRepeat);
        m98->vsTracks[i] = static_cast<CourseId>(id);
    }

    cupsConfig->winningCourse = static_cast<PulsarId>(m98->vsTracks[0]);
    RaceData::sInstance->menusScenario.settings.courseId = cupsConfig->GetCorrectTrackSlot();
};
kmBranch(0x805e32ec, VSRaceRandomFix);
kmWrite32(0x8084e5e4, 0x60000000); //nop racedata courseId store since it's done in the function

//Same as GP, racedata only ever has courseId
static void VSRaceOrderedFix(SectionParams* params) {
    register const Pages::CourseSelect* course;
    asm(mr course, r29;);
    u32 rowIdx = 0;
    for(int i = 0; i < 4; ++i) {
        const CourseButton& cur = course->CtrlMenuCourseSelectCourse.courseButtons[i];
        if(cur.IsSelected()) {
            rowIdx = i;
            break;
        }
    }
    params->vsRaceLimit = 32;
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    //const PulsarId initial = cupsConfig->winningCourse;
    PulsarCupId cupId = cupsConfig->lastSelectedCup;
    u32 idx = 0;
    while(idx < 32) {
        params->vsTracks[idx] = static_cast<CourseId>(cupsConfig->ConvertTrack_PulsarCupToTrack(cupId, rowIdx));
        ++idx;
        ++rowIdx;
        if(rowIdx == 4) {
            cupId = cupsConfig->GetNextCupId(cupId, 1);
            rowIdx = 0;
        }
    }
};
kmCall(0x80840a24, VSRaceOrderedFix);

CourseId VSNextTrackFix(PulsarId pulsarId) {//properly sets the next track
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    cupsConfig->winningCourse = pulsarId;
    return cupsConfig->GetCorrectTrackSlot();
}
kmBranch(0x808606cc, VSNextTrackFix);

kmWrite32(0x8085a944, 0x48000018);
static void DemoFix(register RaceData* raceData) {
    register CourseId id;
    asm(mr id, r0;);
    asm(stw r0, 0x1758 (raceData););
    CupsConfig::sInstance->winningCourse = static_cast<PulsarId>(id);
}
kmCall(0x8085a95c, DemoFix);

}//namespace Pulsar