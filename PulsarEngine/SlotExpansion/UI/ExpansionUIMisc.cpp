#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Menu/CupSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/CourseSelect.hpp>
#include <MarioKartWii/UI/Page/Other/GhostSelect.hpp>
#include <MarioKartWii/UI/Page/Other/Votes.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>


namespace Pulsar {
namespace UI {
//Change brctr names
kmWrite24(0x808a85ef, 'PUL'); //used by 807e5754

static void LoadCtrlMenuCourseSelectCupBRCTR(ControlLoader& loader, const char* folderName, const char* ctrName,
    const char* variant, const char** animNames) {
    loader.Load(UI::buttonFolder, "PULrseSelectCup", variant, animNames); //Move to button to avoid duplication of cup icon tpls
}
kmCall(0x807e4538, LoadCtrlMenuCourseSelectCupBRCTR);

static void LoadCorrectTrackListBox(ControlLoader& loader, const char* folder, const char* normalBrctr, const char* variant, const char** anims) {
    loader.Load(folder, "PULSelectNULL", variant, anims);
}
kmCall(0x807e5f24, LoadCorrectTrackListBox);

//BMG
int GetTrackBMGId(PulsarId pulsarId) {
    u32 bmgId;
    const u32 realId = CupsConfig::ConvertTrack_PulsarIdToRealId(pulsarId);
    if(CupsConfig::IsReg(pulsarId)) bmgId = realId > 32 ? BMG_BATTLE : BMG_REGS;
    else bmgId = BMG_TRACKS;
    return bmgId + realId;
}

int GetTrackBMGByRowIdx(u32 cupTrackIdx) {
    const Pages::CupSelect* cup = SectionMgr::sInstance->curSection->Get<Pages::CupSelect>();
    PulsarCupId curCupId;
    if(cup == nullptr) curCupId = PULSARCUPID_FIRSTREG;
    else curCupId = static_cast<PulsarCupId>(cup->ctrlMenuCupSelectCup.curCupID);
    return GetTrackBMGId(CupsConfig::sInstance->ConvertTrack_PulsarCupToTrack(curCupId, cupTrackIdx)); //FIX HERE
}
kmWrite32(0x807e6184, 0x7FA3EB78);
kmCall(0x807e6188, &GetTrackBMGByRowIdx);
kmWrite32(0x807e6088, 0x7F63DB78);
kmCall(0x807e608c, GetTrackBMGByRowIdx);

int GetCurTrackBMG() {
    return GetTrackBMGId(CupsConfig::sInstance->winningCourse);
}

static void SetVSIntroBmgId(LayoutUIControl* trackName) {
    u32 bmgId = GetCurTrackBMG();
    TextInfo info;
    info.bmgToPass[0] = bmgId;
    u32 authorId;
    if(bmgId < BMG_TRACKS) authorId = BMG_NINTENDO;
    else authorId = bmgId + BMG_AUTHORS - BMG_TRACKS;
    info.bmgToPass[1] = authorId;
    trackName->SetMessage(BMG_INFO_DISPLAY, &info);

}
kmCall(0x808552cc, SetVSIntroBmgId);

static void SetAwardsResultCupInfo(LayoutUIControl& awardType, const char* textBoxName, u32 bmgId, TextInfo& info) {
    PulsarCupId id = CupsConfig::sInstance->lastSelectedCup;
    if(!CupsConfig::IsRegCup(id)) {
        awardType.layout.GetPaneByName("cup_icon")->flag &= ~1;
        u32 realCupId = CupsConfig::ConvertCup_PulsarIdToRealId(id);
        u32 cupBmgId;
        u16 iconCount = Info::GetCupIconCount();
        if(realCupId > iconCount - 1) {
            wchar_t cupName[0x20];
            swprintf(cupName, 0x20, L"Cup %d", realCupId);
            info.strings[0] = cupName;
            cupBmgId = BMG_TEXT;
        }
        else cupBmgId = BMG_CUPS + realCupId;
        info.bmgToPass[1] = cupBmgId;
    }
    awardType.SetTextBoxMessage(textBoxName, bmgId, &info);
}
kmCall(0x805bcb88, SetAwardsResultCupInfo);

static void SetGPIntroInfo(LayoutUIControl& titleText, u32 bmgId, TextInfo& info) {

    PulsarCupId id = CupsConfig::sInstance->lastSelectedCup;
    if(!CupsConfig::IsRegCup(id)) {
        titleText.layout.GetPaneByName("cup_icon")->flag &= ~1;
        u32 realCupId = CupsConfig::ConvertCup_PulsarIdToRealId(id);
        u32 cupBmgId;
        u16 iconCount = Info::GetCupIconCount();
        if(realCupId > iconCount - 1) {
            wchar_t cupName[0x20];
            swprintf(cupName, 0x20, L"Cup %d", realCupId);
            info.strings[0] = cupName;
            cupBmgId = BMG_TEXT;
        }
        else cupBmgId = BMG_CUPS + realCupId;
        info.bmgToPass[1] = cupBmgId;

    }
    titleText.SetMessage(bmgId, &info);
}
kmCall(0x808553b4, SetGPIntroInfo);

static void SetGPBottomText(CtrlMenuInstructionText& bottomText, u32 bmgId, TextInfo& info) {
    register ExpCupSelect* cupPage;
    asm(mr cupPage, r31;);
    PulsarCupId id = static_cast<PulsarCupId>(cupPage->ctrlMenuCupSelectCup.curCupID);

    if(!CupsConfig::IsRegCup(id)) {
        u32 realCupId = CupsConfig::ConvertCup_PulsarIdToRealId(id);
        register u32 cc;
        asm(mr cc, r28;);
        u8 status = Settings::Mgr::GetGPStatus(realCupId, cc);
        u32 trophyBmg;
        u32 rankBmg;
        if(status == 0xFF) {
            trophyBmg = BMG_GP_BLANK;
            rankBmg= BMG_GP_BLANK;
        }
        else {
            trophyBmg = BMG_GP_GOLD_TROPHY + Settings::Mgr::ComputeTrophyFromStatus(status);
            rankBmg = BMG_GP_RANK_3STARS + Settings::Mgr::ComputeRankFromStatus(status);
        }
        info.bmgToPass[1] = trophyBmg;
        info.bmgToPass[2] = rankBmg;
    }
    bottomText.SetMessage(bmgId, &info);
}
kmCall(0x80841720, SetGPBottomText);

static void SaveGPResult(SavedGhostsHandler* handler, u32 r4, u32 r5, u32 r6, u32 r7, u32 r8, u32 r9, bool isNew) {
    const PulsarCupId id = CupsConfig::sInstance->lastSelectedCup;
    if(!CupsConfig::IsRegCup(id)) {
        const u32 realCupId = CupsConfig::ConvertCup_PulsarIdToRealId(id);
        const GPRank rank = RaceData::sInstance->awardScenario.players[0].ComputeGPRank();
        register u32 trophy;
        asm(mr trophy, r31;);
        register u32 cc;
        asm(mr cc, r29;);
        Settings::Mgr::SetGPStatus(realCupId, cc, trophy, rank);
    }
    else if(isNew) handler->NotifyNewLicenseContent();
}
kmWrite32(0x805bd1d4, 0x418200d8);
kmCall(0x805bd2ac, SaveGPResult);

static void SetGhostInfoTrackBMG(GhostInfoControl* control, const char* textBoxName) {
    control->SetTextBoxMessage(textBoxName, GetCurTrackBMG());
}
kmCall(0x805e2a4c, SetGhostInfoTrackBMG);

kmWrite32(0x808406e8, 0x388000ff); //store 0xFF on timeout instead of -1
kmWrite32(0x808415ac, 0x388000ff);
kmWrite32(0x80643004, 0x3be000ff);
kmWrite32(0x808394e8, 0x388000ff);
kmWrite32(0x80644104, 0x3b5b0000);
static void CourseVoteBMG(VoteControl* vote, bool isCourseIdInvalid, PulsarId courseVote, MiiGroup& miiGroup, u32 playerId, bool isLocalPlayer, u32 team) {
    u32 bmgId = courseVote;
    if(bmgId != 0x1101 && bmgId < 0x2498) bmgId = GetTrackBMGId(courseVote);
    vote->Fill(isCourseIdInvalid, bmgId, miiGroup, playerId, isLocalPlayer, team);
}
kmCall(0x806441b8, CourseVoteBMG);

static bool BattleArenaBMGFix(SectionId sectionId) {
    register PulsarId id;
    asm(mr id, r28;);
    CupsConfig::sInstance->winningCourse = id;
    return IsOnlineSection(sectionId);
}
kmCall(0x8083d02c, BattleArenaBMGFix);


//kmWrite32(0x80644340, 0x7F64DB78);
static void WinningTrackBMG(PulsarId winningCourse) {
    register Pages::Vote* vote;
    asm(mr vote, r27;);
    vote->trackBmgId = GetTrackBMGId(winningCourse);
}
kmCall(0x80644344, WinningTrackBMG);

//Rewrote InitSelf to start with correct TPLs
static void ExtCupSelectCupInitSelf(CtrlMenuCupSelectCup* cups) {
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    PulsarCupId selCup = cupsConfig->lastSelectedCup;
    cups->curCupID = selCup;
    PushButton** buttons = reinterpret_cast<PushButton**>(cups->childrenGroup.controlArray);

    for(int i = 0; i < 8; ++i) {
        const PulsarCupId id = cupsConfig->GetNextCupId(selCup, i - cupsConfig->lastSelectedCupButtonIdx);
        buttons[i]->buttonId = id;
        ExpCupSelect::UpdateCupData(id, *buttons[i]);
        buttons[i]->SetOnClickHandler(cups->onCupButtonClickHandler, 0);
        buttons[i]->SetOnSelectHandler(cups->onCupButtonSelectHandler);
        buttons[i]->SetPlayerBitfield(SectionMgr::sInstance->curSection->Get<Pages::CupSelect>()->GetPlayerBitfield());
    }
    buttons[cupsConfig->lastSelectedCupButtonIdx]->SelectInitialButton(0);
};
kmWritePointer(0x808d324c, ExtCupSelectCupInitSelf); //807e5894

static void ExtCourseSelectCupInitSelf(CtrlMenuCourseSelectCup* courseCups) {
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    for(int i = 0; i < 8; ++i) {
        CtrlMenuCourseSelectCupSub& cur = courseCups->cupIcons[i];
        const PulsarCupId id = cupsConfig->GetNextCupId(cupsConfig->lastSelectedCup, i - cupsConfig->lastSelectedCupButtonIdx);
        ExpCupSelect::UpdateCupData(id, cur);
        cur.animator.GetAnimationGroupById(0).PlayAnimationAtFrame(0, 0.0f);
        const bool clicked = cupsConfig->lastSelectedCupButtonIdx == i ? true : false;
        cur.animator.GetAnimationGroupById(1).PlayAnimationAtFrame(!clicked, 0.0f);
        cur.animator.GetAnimationGroupById(2).PlayAnimationAtFrame(!clicked, 0.0f);
        cur.animator.GetAnimationGroupById(3).PlayAnimationAtFrame(clicked, 0.0f);
        cur.selected = clicked;
        cur.SetRelativePosition(courseCups->positionAndscale[1]);
    }
    const Section* curSection = SectionMgr::sInstance->curSection;
    Pages::CupSelect* cup = curSection->Get<Pages::CupSelect>();
    NoteModelControl* positionArray = cup->modelPosition;

    switch(cup->extraControlNumber) {
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
            positionArray = curSection->Get<Pages::CourseSelect>()->modelPosition;
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

static void ExtCourseSelectCourseInitSelf(CtrlMenuCourseSelectCourse* course) {
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const Section* curSection = SectionMgr::sInstance->curSection;
    const Pages::CupSelect* cupPage = curSection->Get<Pages::CupSelect>();
    Pages::CourseSelect* coursePage = curSection->Get<Pages::CourseSelect>();
    //channel ldb stuff ignored
    const u32 cupId = cupPage->clickedCupId;

    PushButton* toSelect = &course->courseButtons[0];
    for(int i = 0; i < 4; ++i) {
        PushButton& curButton = course->courseButtons[i];
        curButton.buttonId = i;
        const u32 bmgId = GetTrackBMGByRowIdx(i);
        curButton.SetMessage(bmgId);
        if(cupsConfig->ConvertTrack_PulsarCupToTrack(cupsConfig->lastSelectedCup, i) == cupsConfig->selectedCourse) {
            toSelect = &curButton;
        }
    };
    coursePage->SelectButton(*toSelect);
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
}//namespace UI
}//namespace Pulsar