#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Page/Menu/CupSelect.hpp>
#include <game/UI/Page/Menu/CourseSelect.hpp>
#include <game/UI/Page/Other/GhostSelect.hpp>
#include <game/UI/Page/Other/Votes.hpp>
#include <Pulsar.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <UI/BMG.hpp>

namespace PulsarUI {
//Change brctr names
kmWrite24(0x808a85ef, 0x50554c); //used by 807e5754

void LoadCtrlMenuCourseSelectCupBRCTR(ControlLoader *loader, const char *folderName, const char *ctrName,
    const char *variant, const char **animNames) {
    loader->Load(Pulsar::buttonFolder, "PULrseSelectCup", variant, animNames); //Move to button to avoid duplication of cup icon tpls
}
kmCall(0x807e4538, LoadCtrlMenuCourseSelectCupBRCTR);

void LoadCorrectTrackListBox(ControlLoader *loader, const char *folder, const char *normalBrctr, const char *variant, const char **anims) {
    loader->Load(folder, "PULSelectNULL", variant, anims);
}
kmCall(0x807e5f24, LoadCorrectTrackListBox);

//BMG
int GetTrackBMG(CourseId pulsarId) {
    u32 bmgId;
    u32 realId = Pulsar::ConvertTrack_PulsarIdToRealId(pulsarId);
    if (Pulsar::IsReg(pulsarId)) bmgId = BMG_REGS;
    else bmgId = BMG_TRACKS;
    return bmgId + realId;
}

int GetCorrectTrackBMGById(u8 cupTrackIdx) {
    Pages::CupSelect *cup = SectionMgr::sInstance->curSection->Get<Pages::CupSelect>(PAGE_CUP_SELECT);
    u32 curCupId;
    if (cup == NULL) curCupId = 0;
    else curCupId = cup->ctrlMenuCupSelectCup.curCupID;
    return GetTrackBMG((CourseId)(cupTrackIdx + 4 * curCupId));
}
kmWrite32(0x807e6184, 0x7FA3EB78);
kmCall(0x807e6188, GetCorrectTrackBMGById);
kmWrite32(0x807e6088, 0x7F63DB78);
kmCall(0x807e608c, GetCorrectTrackBMGById);

int GetCurTrackBMG() {
    return GetTrackBMG(Pulsar::sInstance->winningCourse);
}

void SetVSIntroBmgId(LayoutUIControl *trackName) {
    u32 bmgId = GetCurTrackBMG();
    TextInfo info;
    info.bmgToPass[0] = bmgId;
    u32 authorId;
    if (bmgId < BMG_TRACKS) authorId = BMG_NINTENDO;
    else authorId = bmgId + BMG_AUTHORS - BMG_TRACKS;
    info.bmgToPass[1] = authorId;
    trackName->SetMsgId(BMG_INFO_DISPLAY, &info);
}
kmCall(0x808552cc, SetVSIntroBmgId);

void SetGhostInfoTrackBMG(GhostInfoControl *control, const char *textBoxName) {
    control->SetTextBoxMsg(textBoxName, GetCurTrackBMG(), NULL);
}
kmCall(0x805e2a4c, SetGhostInfoTrackBMG);

kmWrite32(0x80644104, 0x3b5b0000);
void CourseVoteBMG(VoteControl *vote, bool isCourseIdInvalid, CourseId courseVote, MiiGroup *miiGroup, u32 playerId, bool isLocalPlayer, u32 team) {
    u32 bmgId = courseVote;
    if (bmgId != 0x1101 || bmgId < 0x2498) bmgId = GetTrackBMG(courseVote);
    vote->Fill(isCourseIdInvalid, bmgId, miiGroup, playerId, isLocalPlayer, team);
}
kmCall(0x806441b8, CourseVoteBMG);



kmWrite32(0x80644340, 0x7F64DB78);
void WinningTrackBMG(CourseId winningCourse, Pages::Vote *vote) {
    vote->trackBmgId = GetTrackBMG(winningCourse);
}
kmCall(0x80644344, WinningTrackBMG);

//Rewrote InitSelf to start with correct TPLs
void ExtCupSelectCupInitSelf(CtrlMenuCupSelectCup *cups) {
    Pulsar *pulsar = Pulsar::sInstance;
    cups->curCupID = pulsar->lastSelectedCup;
    PushButton **buttons = (PushButton **)cups->childrenGroup.controlArray;
    for (int i = 0; i < 8; i++) {
        PushButton *curButton = buttons[i];
        u32 id = pulsar->GetNextCupId(pulsar->lastSelectedCup, i - pulsar->lastSelectedButtonIdx);
        buttons[i]->buttonId = id;
        ExpCupSelect::UpdateCupData(id, buttons[i]);
        buttons[i]->SetOnClickHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & cups->onCupButtonClickHandler, 0);
        buttons[i]->SetOnSelectHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & cups->onCupButtonSelectHandler);
        buttons[i]->SetPlayerBitfield(SectionMgr::sInstance->curSection->Get<Pages::CupSelect>(PAGE_CUP_SELECT)->GetPlayerBitfield());
    }
    buttons[pulsar->lastSelectedButtonIdx]->SelectInitialButton(0);
};
kmWritePointer(0x808d324c, ExtCupSelectCupInitSelf); //807e5894

void ExtCourseSelectCupInitSelf(CtrlMenuCourseSelectCup *courseCups) {
    Pulsar *pulsar = Pulsar::sInstance;
    for (int i = 0; i < 8; i++) {
        CtrlMenuCourseSelectCupSub *cur = &courseCups->cupIcons[i];
        u32 id = pulsar->GetNextCupId(pulsar->lastSelectedCup, i - pulsar->lastSelectedButtonIdx);
        ExpCupSelect::UpdateCupData(id, cur);
        cur->animator.GetAnimationGroupById(0)->PlayAnimationAtFrame(0, 0.0f);
        bool clicked = pulsar->lastSelectedButtonIdx == i ? true : false;
        cur->animator.GetAnimationGroupById(1)->PlayAnimationAtFrame(!clicked, 0.0f);
        cur->animator.GetAnimationGroupById(2)->PlayAnimationAtFrame(!clicked, 0.0f);
        cur->animator.GetAnimationGroupById(3)->PlayAnimationAtFrame(clicked, 0.0f);
        cur->selected = clicked;
        cur->SetRelativePosition(&courseCups->positionAndscale[1]);
    }
    Section *curSection = SectionMgr::sInstance->curSection;



    Pages::CupSelect *cup = curSection->Get<Pages::CupSelect>(PAGE_CUP_SELECT);
    NoteModelControl *positionArray = cup->modelPosition;


    switch (cup->extraControlNumber) {
    case(2):
        positionArray[0].positionAndscale[1].position.x = -52.0f;
        positionArray[0].positionAndscale[1].position.y = -8.0f;
        positionArray[0].positionAndscale[1].scale.x = 0.875f;
        positionArray[0].positionAndscale[1].scale.z = 0.875f;
        positionArray[1].positionAndscale[1].position.x = -52.0f;
        positionArray[1].positionAndscale[1].position.y = -13.0f;
        positionArray[1].positionAndscale[1].scale.x = 0.875f;
        positionArray[1].positionAndscale[1].scale.z = 0.875f;
        break;
    case(1):
        positionArray[0].positionAndscale[1].position.x = -32.0f;
        positionArray[0].positionAndscale[1].position.y = -32.0f;
        positionArray = curSection->Get<Pages::CourseSelect>(PAGE_COURSE_SELECT)->modelPosition;
        positionArray[0].positionAndscale[1].position.x = -32.0f;
        positionArray[0].positionAndscale[1].position.y = -32.0f;
        break;
    case(4):
        positionArray[3].positionAndscale[1].position.x = 64.0f;
        positionArray[3].positionAndscale[1].position.y = -55.25f;
        positionArray[3].positionAndscale[1].scale.x = 0.6875f;
        positionArray[3].positionAndscale[1].scale.z = 0.6875f;
    case(3):
        positionArray[0].positionAndscale[1].position.x = 64.0f;
        positionArray[0].positionAndscale[1].position.y = -64.0f;
        positionArray[0].positionAndscale[1].scale.x = 0.6875f;
        positionArray[0].positionAndscale[1].scale.z = 0.6875f;
        positionArray[1].positionAndscale[1].position.x = 64.0f;
        positionArray[1].positionAndscale[1].position.y = -64.0f;
        positionArray[1].positionAndscale[1].scale.x = 0.6875f;
        positionArray[1].positionAndscale[1].scale.z = 0.6875f;
        positionArray[2].positionAndscale[1].position.x = 64.0f;
        positionArray[2].positionAndscale[1].position.y = -55.25f;
        positionArray[2].positionAndscale[1].scale.x = 0.6875f;
        positionArray[2].positionAndscale[1].scale.z = 0.6875f;
        break;
    }
};
kmWritePointer(0x808d3190, ExtCourseSelectCupInitSelf); //807e45c0

void ExtCourseSelectCourseInitSelf(CtrlMenuCourseSelectCourse *course) {
    Pulsar *pulsar = Pulsar::sInstance;
    Section *curSection = SectionMgr::sInstance->curSection;
    Pages::CupSelect *cupPage = curSection->Get<Pages::CupSelect>(PAGE_CUP_SELECT);
    Pages::CourseSelect *coursePage = curSection->Get<Pages::CourseSelect>(PAGE_COURSE_SELECT);
    //channel ldb stuff ignored
    u32 cupId = cupPage->clickedCupId;
    for (int i = 0; i < 4; i++) {
        PushButton *curButton = &course->courseButtons[i];
        curButton->buttonId = i;
        u32 bmgId = GetCorrectTrackBMGById(i);
        curButton->SetMsgId(bmgId);
        if (pulsar->lastSelectedCup * 4 + i == pulsar->selectedCourse) {
            coursePage->SelectButton(curButton);
        }
    };
};
kmWritePointer(0x808d30d8, ExtCourseSelectCourseInitSelf); //807e5118

//Multiplayer Fix
kmWrite32(0x807e56d4, 0x60000000);
kmWrite32(0x807e5f04, 0x60000000);

//TPL
//CupSelectCup patch, disable picture panes
kmWrite32(0x807e57a4, 0x60000000);
kmWrite32(0x807e57bc, 0x60000000);
kmWrite32(0x807e57d4, 0x60000000);

//CourseSelectCup patch, disable picture panes
kmWrite32(0x807e4550, 0x60000000);
kmWrite32(0x807e4568, 0x60000000);
kmWrite32(0x807e4580, 0x60000000);
}//namespace PulsarUI