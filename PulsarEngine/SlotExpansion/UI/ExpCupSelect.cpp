#include <core/nw4r/ut/Misc.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Menu/CourseSelect.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <UI/UI.hpp>
#include <Settings/Settings.hpp>




//Create
namespace Pulsar {
namespace UI {
kmWrite32(0x80623d98, 0x60000000);
ExpCupSelect* CreateCupSelect() {
    return new ExpCupSelect;
};
kmCall(0x80623da4, CreateCupSelect);

ExpCupSelect::ExpCupSelect() {
    internControlCount += 2;
    onRightArrowSelectHandler.subject = this;
    onRightArrowSelectHandler.ptmf = &ExpCupSelect::OnRightArrowSelect;
    onLeftArrowSelectHandler.subject = this;
    onLeftArrowSelectHandler.ptmf = &ExpCupSelect::OnLeftArrowSelect;
    onStartPressHandler.subject = this;
    onStartPressHandler.subject = this;
    onStartPressHandler.ptmf = &ExpCupSelect::OnStartPress;
    onBackPressHandler.subject = this;
    onBackPressHandler.ptmf = &ExpCupSelect::OnBackPress;
    randomizedId = PULSARID_NONE;
    this->controlsManipulatorManager.SetGlobalHandler(START_PRESS, onStartPressHandler, false, false);

    CupsConfig* cupsConfig = CupsConfig::sInstance;
    cupsConfig->ToggleCTs(!CupsConfig::IsRegsSituation());
    if(cupsConfig->GetTotalCupCount() <= 8) {
        this->arrows.leftArrow.manipulator.inaccessible = true;
        this->arrows.leftArrow.isHidden = true;
        this->arrows.rightArrow.manipulator.inaccessible = true;
        this->arrows.rightArrow.isHidden = true;
    }
}

void ExpCupSelect::OnActivate() {
    this->randomizedId = PULSARID_NONE;
    PushButton** buttons = reinterpret_cast<PushButton**>(this->ctrlMenuCupSelectCup.childrenGroup.controlArray);
    for(int i = 0; i < 8; ++i) buttons[i]->manipulator.inaccessible = false;
    this->arrows.leftArrow.manipulator.inaccessible = false;
    this->arrows.rightArrow.manipulator.inaccessible = false;
    Pages::CupSelect::OnActivate();
}


//Patch distance func to remove horizontal wrapping
static void CupSelectDistanceFunc(ControlsManipulatorManager* manipulator, u32 type) {
    if(CupsConfig::sInstance->GetCtsTrackCount() != 0) type = 1;
    manipulator->SetDistanceFunc(type);
}
kmCall(0x80841248, CupSelectDistanceFunc);
//SheetSelect
UIControl* ExpCupSelect::CreateControl(u32 controlId) {
    if(controlId == 2) {
        this->AddControl(2, this->arrows, 0);
        arrows.SetRightArrowHandler(this->onRightArrowSelectHandler);
        arrows.SetLeftArrowHandler(this->onLeftArrowSelectHandler);
        const char* rightArrow = "CupsArrowR";
        const char* leftArrow = "CupsArrowL";
        arrows.Load(UI::buttonFolder, rightArrow, rightArrow, leftArrow, leftArrow, 1, 0, false);
        ++this->controlCount;
        return &this->arrows;
    }
    else if(controlId == 3) {
        this->AddControl(3, this->randomControl, 0);
        ControlLoader loader(&this->randomControl);
        loader.Load(UI::controlFolder, "RandomTrackCup", "RandomControls", nullptr);
        return &this->randomControl;
    }
    else return CupSelect::CreateControl(controlId);
}

void ExpCupSelect::OnRightArrowSelect(SheetSelectControl& control, u32 hudSlotId) {
    this->OnArrowSelect(2);
}

void ExpCupSelect::OnLeftArrowSelect(SheetSelectControl& control, u32 hudSlotId) {
    this->OnArrowSelect(-2);
}

void ExpCupSelect::OnArrowSelect(s32 direction) {
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    CtrlMenuCupSelectCup& cups = this->ctrlMenuCupSelectCup;
    cups.curCupID = cupsConfig->GetNextCupId(static_cast<PulsarCupId>(cups.curCupID), direction);
    this->ctrlMenuCupSelectCourse.UpdateTrackList(cups.curCupID);
    PushButton** buttons = reinterpret_cast<PushButton**>(cups.childrenGroup.controlArray);
    for(int i = 0; i < 8; ++i) {
        const PulsarCupId nextId = cupsConfig->GetNextCupId(static_cast<PulsarCupId>(buttons[i]->buttonId), direction);
        buttons[i]->buttonId = nextId;
        this->UpdateCupData(nextId, *buttons[i]);
    }

}

void ExpCupSelect::OnStartPress(u32 hudSlotId) {
    const GameMode gamemode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isValid = gamemode == MODE_TIME_TRIAL || gamemode == MODE_VS_RACE;
    if(isValid && this->randomizedId == -1) {
        this->randomizedId = CupsConfig::sInstance->RandomizeTrack();
    }
}

void ExpCupSelect::AfterControlUpdate() {
    CupSelect::AfterControlUpdate();
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    const GameMode gamemode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isValid = gamemode == MODE_TIME_TRIAL || gamemode == MODE_VS_RACE;
    if(!isValid) {
        this->randomControl.isHidden = true;
    }
    else {
        this->randomControl.isHidden = false;
        this->randomControl.SetMessage(BMG_RANDOM_CUP);

        bool isInaccessible = true;
        PushButton** buttons = reinterpret_cast<PushButton**>(this->ctrlMenuCupSelectCup.childrenGroup.controlArray);
        if(this->randomizedId != PULSARID_NONE) {
            SheetSelectControl::SheetSelectButton* arrow;
            const u32 subtraHend = !cupsConfig->HasRegs() * 8;
            const u32 randomizedCupButtonIdx = CupsConfig::ConvertCup_PulsarIdToIdx(CupsConfig::ConvertCup_PulsarTrackToCup(this->randomizedId)) - subtraHend;
            const u32 button0Idx = CupsConfig::ConvertCup_PulsarIdToIdx(static_cast<PulsarCupId>(buttons[0]->buttonId)) - subtraHend;
            const u32 button7Idx = CupsConfig::ConvertCup_PulsarIdToIdx(static_cast<PulsarCupId>(buttons[7]->buttonId)) - subtraHend;
            const u32 cupCount = cupsConfig->GetTotalCupCount();

            bool isCurOnScreen = false;
            for(int i = 0; i < 8; ++i) {
                u32 cupI = (button0Idx + i) % cupCount;
                if(cupI == randomizedCupButtonIdx) isCurOnScreen = true;
            }
            u32 low = nw4r::ut::Abs<s32>(randomizedCupButtonIdx - button0Idx);
            low = nw4r::ut::Min(low, cupCount - low);
            u32 high = nw4r::ut::Abs<s32>(randomizedCupButtonIdx - button7Idx);
            high = nw4r::ut::Min(high, cupCount - high);
            if(!isCurOnScreen) {
                if(high <= low) arrow = &this->arrows.rightArrow;
                else arrow = &this->arrows.leftArrow;
                arrow->Select(0);
            }
            else {
                u32 finalButtonIdx = nw4r::ut::Abs<s32>(randomizedCupButtonIdx - button7Idx);
                finalButtonIdx = 7 - nw4r::ut::Min(finalButtonIdx, cupCount - finalButtonIdx);
                buttons[finalButtonIdx]->Select(0);
                buttons[finalButtonIdx]->HandleClick(0, 0);
                Pages::CourseSelect* coursePage = SectionMgr::sInstance->curSection->Get<Pages::CourseSelect>();
                CourseButton& courseButton = coursePage->CtrlMenuCourseSelectCourse.courseButtons[this->randomizedId % 4];
                cupsConfig->SaveSelectedCourse(courseButton);
                courseButton.Select(0);
                //coursePage->CtrlMenuCourseSelectCourse.courseButtons[this->randomizedId % 4].HandleClick(0, -1);
                this->randomizedId = PULSARID_NONE;
                isInaccessible = cupsConfig->GetCtsTrackCount() == 0; //keep the arrows inaccessible if there are no cts
            }
            for(int i = 0; i < 8; ++i) buttons[i]->manipulator.inaccessible = isInaccessible;
            this->arrows.leftArrow.manipulator.inaccessible = isInaccessible;
            this->arrows.rightArrow.manipulator.inaccessible = isInaccessible;
        }
    }
}

void ExpCupSelect::OnBackPress(u32 hudSlotId) {
    this->randomizedId = PULSARID_NONE;
    CupSelect::OnBackPress(hudSlotId);
}

//Disable movies
void ExpCupSelect::OnMoviesActivate(u32 r4) {}

kmWrite32(0x808404f8, 0x60000000);

//brlyt TPL stuff
const char* regCupNames[8] ={ "kinoko", "koura", "flower", "banana", "star", "konoha", "oukan", "thunder" };



void ExpCupSelect::UpdateCupData(PulsarCupId pulsarCupId, LayoutUIControl& control) {
    u32 bmgId;
    char tplName[0x20];
    TextInfo info;
    u32 realCupId = CupsConfig::ConvertCup_PulsarIdToRealId(pulsarCupId);
    if(CupsConfig::IsRegCup(pulsarCupId)) {
        snprintf(tplName, 0x20, "tt_cup_icon_%s_00.tpl", &cupTPLs[realCupId][8]);
        bmgId = BMG_REGCUPS;
    }
    else {
        u32 tplId = realCupId;
        u16 iconCount = Info::GetCupIconCount();
        if(realCupId > iconCount - 1) {
            wchar_t cupName[0x20];
            swprintf(cupName, 0x20, L"Cup %d", realCupId);
            info.strings[0] = cupName;
            tplId = tplId % iconCount;
            realCupId = 0;
            bmgId = BMG_TEXT;
        }
        else bmgId = BMG_CUPS;
        snprintf(tplName, 0x20, "icon_%03d.tpl", tplId);
    }
    control.SetMessage(bmgId + realCupId, &info);
    ChangeImage(control, "icon", tplName);
    ChangeImage(control, "icon_light_01", tplName);
    ChangeImage(control, "icon_light_02", tplName);
}



}//namespace UI
}//namespace Pulsar