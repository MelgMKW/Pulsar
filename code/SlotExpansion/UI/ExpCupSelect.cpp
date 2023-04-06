#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Page/Menu/CourseSelect.hpp>
#include <Pulsar.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <UI/BMG.hpp>
#include <Settings/PlayerData.hpp>

//Create
namespace PulsarUI {
kmWrite32(0x80623d98, 0x60000000);
ExpCupSelect *CreateCupSelect() {
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
    onStartPressHandler.ptmf = static_cast<void (Pages::Menu:: *)(u32)>(&ExpCupSelect::OnStartPress);
    onBackPressHandler.subject = this;
    onBackPressHandler.ptmf = static_cast<void (Pages::Menu:: *)(u32)>(&ExpCupSelect::OnBackPress);
    randomizedId = (CourseId)-1;
    this->controlsManipulatorManager.SetGlobalHandler(START_PRESS, (PtmfHolder_1A<Page, void, u32>*) & onStartPressHandler, false, false);

}

//Patch distance func to remove horizontal wrapping
kmWrite32(0x80841244, 0x38800001);

//SheetSelect
UIControl *ExpCupSelect::CreateControl(u32 controlId) {
    if (controlId == 2) {
        this->AddControl(2, &this->arrows, 0);
        arrows.SetRightArrowHandler((PtmfHolder_2A<Page, void, SheetSelectControl *, u32>*) & this->onRightArrowSelectHandler);
        arrows.SetLeftArrowHandler((PtmfHolder_2A<Page, void, SheetSelectControl *, u32>*) & this->onLeftArrowSelectHandler);
        arrows.Load(Pulsar::buttonFolder, "PULCupsArrowRight", "ButtonArrowRight",
            "PULCupsArrowLeft", "ButtonArrowLeft", 1, 0, false);
        this->controlCount++;
        return &this->arrows;
    }
    else if (controlId == 3) {
        this->AddControl(3, &this->randomControl, 0);
        ControlLoader loader(&this->randomControl);
        loader.Load(Pulsar::controlFolder, "RandomTrackCup", "RandomControls", NULL);
        return &this->randomControl;
    }
    else return CupSelect::CreateControl(controlId);
}

void ExpCupSelect::OnRightArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId) {
    this->OnArrowSelect(2);
}

void ExpCupSelect::OnLeftArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId) {
    this->OnArrowSelect(-2);
}

void ExpCupSelect::OnArrowSelect(s32 direction) {
    Pulsar *pulsar = Pulsar::sInstance;
    CtrlMenuCupSelectCup *cups = &this->ctrlMenuCupSelectCup;
    cups->curCupID = pulsar->GetNextCupId(cups->curCupID, direction);
    this->ctrlMenuCupSelectCourse.UpdateTrackList(cups->curCupID);
    PushButton **buttons = (PushButton **)cups->childrenGroup.controlArray;
    for (int i = 0; i < 8; i++) {
        PushButton *curButton = buttons[i];
        u32 nextId = pulsar->GetNextCupId(curButton->buttonId, direction);
        curButton->buttonId = nextId;
        this->UpdateCupData(nextId, curButton);
    }

}

void ExpCupSelect::OnStartPress(u32 hudSlotId) {
    if (RaceData::sInstance->menusScenario.settings.gamemode == MODE_TIME_TRIAL && this->randomizedId == -1) {
        Random random;
        this->randomizedId = Pulsar::sInstance->RandomizeTrack(&random);
    }
}

void ExpCupSelect::AfterControlUpdate() {
    CupSelect::AfterControlUpdate();
    Pulsar *pulsar = Pulsar::sInstance;
    if (RaceData::sInstance->menusScenario.settings.gamemode == MODE_TIME_TRIAL) {

        ControllerType controllerType = ControllerType(SectionMgr::sInstance->pad.padInfos[0].controllerSlotAndType & 0xFF);
        u32 randomBmg = BMG_RANDOM_CUP;
        this->randomControl.SetMsgId(randomBmg);

        bool isInaccessible = true;
        PushButton **buttons = (PushButton **)this->ctrlMenuCupSelectCup.childrenGroup.controlArray;
        if (this->randomizedId != -1) {
            SheetSelectControl::SheetSelectButton *arrow;
            u32 randomizedCupIdx = Pulsar::ConvertCup_PulsarIdToIdx(this->randomizedId / 4);
            u32 button0Idx = Pulsar::ConvertCup_PulsarIdToIdx(buttons[0]->buttonId);
            u32 button7Idx = Pulsar::ConvertCup_PulsarIdToIdx(buttons[7]->buttonId);
            u32 cupCount = pulsar->GetTotalCupCount();

            bool isCurOnScreen = false;
            for (int i = 0; i < 8; i++) {
                u32 cupI = (button0Idx + i) % cupCount;
                if (cupI == randomizedCupIdx) isCurOnScreen = true;
            }
            u32 low = abs(randomizedCupIdx - button0Idx);
            low = Min(low, cupCount - low);
            u32 high = abs(randomizedCupIdx - button7Idx);
            high = Min(high, cupCount - high);
            if (!isCurOnScreen) {
                if (high <= low) arrow = &this->arrows.rightArrow;
                else arrow = &this->arrows.leftArrow;
                arrow->Select(0);
            }
            else {
                u32 finalButtonIdx = abs(randomizedCupIdx - button7Idx);
                finalButtonIdx = 7 - Min(finalButtonIdx, cupCount - finalButtonIdx);
                buttons[finalButtonIdx]->Select(0);
                buttons[finalButtonIdx]->HandleClick(0, 0);
                Pages::CourseSelect *coursePage = SectionMgr::sInstance->curSection->Get<Pages::CourseSelect>(PAGE_COURSE_SELECT);
                CourseButton *courseButton = &coursePage->CtrlMenuCourseSelectCourse.courseButtons[this->randomizedId % 4];
                pulsar->SaveSelectedCourse(courseButton);
                courseButton->Select(0);
                //coursePage->CtrlMenuCourseSelectCourse.courseButtons[this->randomizedId % 4].HandleClick(0, -1);
                this->randomizedId = (CourseId)-1;
                isInaccessible = false;
            }
            for (int i = 0; i < 8; i++) buttons[i]->manipulator.inaccessible = isInaccessible;
            this->arrows.leftArrow.manipulator.inaccessible = isInaccessible;
            this->arrows.rightArrow.manipulator.inaccessible = isInaccessible;
        }
    }
}

void ExpCupSelect::OnBackPress(u32 hudSlotId) {
    this->randomizedId = (CourseId)-1;
    CupSelect::OnBackPress(hudSlotId);
}

//Disable movies
void ExpCupSelect::OnMoviesActivate(u32 r4) {}

kmWrite32(0x808404f8, 0x60000000);

//brlyt TPL stuff
const char *regCupNames[8] = { "kinoko", "koura", "flower", "banana", "star", "konoha", "oukan", "thunder" };



void ExpCupSelect::UpdateCupData(u32 pulsarCupId, LayoutUIControl *control) {
    u32 bmgId;
    char tplName[0x20];
    TextInfo info;
    u32 realCupId = Pulsar::ConvertCup_PulsarIdToRealId(pulsarCupId);
    if (Pulsar::IsRegCup(pulsarCupId)) {
        snprintf(tplName, 0x20, "tt_cup_icon_%s_00.tpl", &cupTPLs[realCupId][8]);
        bmgId = BMG_REGCUPS;
    }
    else {
        if (realCupId > 99) {
            wchar_t cupName[0x20];
            swprintf(cupName, 0x20, L"Cup %d", realCupId);
            info.strings[0] = cupName;
            realCupId = 0;
            bmgId = BMG_TEXT;
        }
        else {
            bmgId = BMG_CUPS;
            snprintf(tplName, 0x20, "icon_%02d.tpl", realCupId);
        }
    }
    control->SetMsgId(bmgId + realCupId, &info);
    Pulsar::ChangeImage(control, "icon", tplName);
    Pulsar::ChangeImage(control, "icon_light_01", tplName);
    Pulsar::ChangeImage(control, "icon_light_02", tplName);
}








}//namespace PulsarUI