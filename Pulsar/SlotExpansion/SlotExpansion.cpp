#include <game/Archive/ArchiveRoot.hpp>
#include <game/Race/RaceData.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Page/Other/GhostManager.hpp>
#include <game/UI/Page/Menu/CupSelect.hpp>
#include <game/UI/Page/Menu/CourseSelect.hpp>
#include <game/UI/Page/Other/Votes.hpp>
#include <game/GlobalFunctions.hpp>
#include <SlotExpansion/CupsDef.hpp>

namespace Pulsar {

//TrackSlot
//Patches course buttons IDs so that it goes vertical than horizontal rather than the opposite
kmWrite32(0x807e525c, 0x937403CC); //Course buttons ids

//CourseId of 1st button is 4*CupID due to reordering
kmWrite32(0x8084182c, 0x5400103A);
kmWrite32(0x80841830, 0x60000000);

//CourseSelect::LoadNextPage patch mentioned above
int UpdateSlot(Pages::CourseSelect* page, CtrlMenuCourseSelectCourse* control, PushButton* button) {
    CupsDef* cups = CupsDef::sInstance;
    cups->SaveSelectedCourse(*button);
    return cups->GetCorrectTrackSlot();
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
    vote->SetVotedCourseId(static_cast<CourseId>(CupsDef::sInstance->selectedCourse));
}
kmCall(0x8084099c, SetVotedTrack);

//CtrlMenuCupSelectCup::OnCupButtonClick patch that updates lastSelectCup so that the game remembers it in btw races
void UpdateLastSelCup(Pages::CupSelect* page, CtrlMenuCupSelectCup& cups, PushButton& button, u32 hudSlotId) {
    CupsDef* cupsDef = CupsDef::sInstance;
    if(button.buttonId != cupsDef->lastSelectedCup) {
        cupsDef->lastSelectedCup = static_cast<PulsarCupId>(button.buttonId);
        cupsDef->selectedCourse = CupsDef::ConvertTrack_PulsarCupToTrack(cupsDef->lastSelectedCup);
    }
    PushButton** buttons = reinterpret_cast<PushButton**>(cups.childrenGroup.controlArray);
    for(int i = 0; i < 8; ++i) if(buttons[i] == &button) cupsDef->lastSelectedCupButtonIdx = i;
    page->LoadNextPage(cups, button, hudSlotId);
    RaceData::sInstance->menusScenario.settings.cupId = cupsDef->lastSelectedCup % 8;
}
kmCall(0x807e5da8, UpdateLastSelCup);



//Loads correct file
void FormatTrackPath(char* path, u32 length, const char* format, const char* fileName) {
    const CupsDef* cups = CupsDef::sInstance;
    const PulsarId pulsarId = cups->winningCourse; //fileName already set through racedata's courseId, which has been set to realId before
    if(IsBattle() || CupsDef::IsReg(pulsarId)) snprintf(path, 0x80, format, fileName);
    else {
        CourseId realId = CupsDef::ConvertTrack_PulsarIdToRealId(pulsarId);
        if(cups->hasOddCups && realId >= (cups->GetCtsTrackCount() - 4)) realId = static_cast<CourseId>(realId % 4);
        snprintf(path, 0x80, "Race/Course/%d", realId);
    }
}
kmCall(0x80540820, FormatTrackPath);
kmCall(0x80540870, FormatTrackPath);
kmCall(0x80541bc4, FormatTrackPath);
kmWrite32(0x80531fbc, 0x38800000); //fix incorrect courseId array read


void FixGrandPrix(Pages::CupSelect* page, SectionId nextSection, PushButton& button) {
    CupsDef::sInstance->winningCourse = CupsDef::ConvertTrack_PulsarCupToTrack(static_cast<PulsarCupId>(button.buttonId));
    page->ChangeSectionById(SECTION_VS_RACE_PANORAMA, button);
};
kmCall(0x80841854, FixGrandPrix);


//Fixes GP since it usually uses racedata's courseId which only holds the slot
RacedataScenario* UseCorrectCourse(RacedataScenario* scenario) {
    CupsDef* cups = CupsDef::sInstance;
    cups->winningCourse = CupsDef::ConvertTrack_PulsarCupToTrack(cups->lastSelectedCup) + static_cast<u32>(scenario->settings.raceNumber);
    scenario->settings.courseId = cups->GetCorrectTrackSlot();
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
void VSRaceRandomFix(SectionParams* m98) { //properly randomizes tracks and sets the first one
    m98->vsRaceLimit = 32;
    CupsDef* cups = CupsDef::sInstance;
    Random random;
    PulsarId id;
    bool isRepeat;
    for(int i = 0; i < 32; ++i) {
        do {
            id = cups->RandomizeTrack(random);
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

    cups->winningCourse = static_cast<PulsarId>(m98->vsTracks[0]);
    RaceData::sInstance->menusScenario.settings.courseId = cups->GetCorrectTrackSlot();
};
kmBranch(0x805e32ec, VSRaceRandomFix);
kmWrite32(0x8084e5e4, 0x60000000); //nop racedata courseId store since it's done in the function

//Same as GP, racedata only ever has courseId
void VSRaceOrderedFix(SectionParams* m98) {
    m98->vsRaceLimit = 32;
    const CupsDef* cups = CupsDef::sInstance;
    const PulsarId initial = cups->winningCourse;
    PulsarCupId cupId = CupsDef::ConvertCup_PulsarTrackToCup(initial);
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 4; ++j) m98->vsTracks[i * 4 + j] = static_cast<CourseId>(cupId * 4 + j);
        cupId = cups->GetNextCupId(cupId, 1);
    }
};
kmCall(0x80840a24, VSRaceOrderedFix);

CourseId VSNextTrackFix(PulsarId pulsarId) {//properly sets the next track
    CupsDef* cups = CupsDef::sInstance;
    cups->winningCourse = pulsarId;
    return cups->GetCorrectTrackSlot();
}
kmBranch(0x808606cc, VSNextTrackFix);

kmWrite32(0x8085a944, 0x48000018);
void DemoFix(register RaceData* raceData) {
    register CourseId id;
    asm(mr id, r0;);
    asm(stw r0, 0x1758 (raceData););
    CupsDef::sInstance->winningCourse = static_cast<PulsarId>(id);
}
kmCall(0x8085a95c, DemoFix);

}//namespace Pulsar