#include <MarioKartWii/UI/Page/Menu/MiiSelect.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Other/FriendRoom.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <core/System/SystemManager.hpp>
#include <UI/TeamSelect/TeamSelect.hpp>
#include <UI/UI.hpp>


namespace Pulsar {
namespace UI {

u8 TeamSelect::teams[24] = { 0 };
bool TeamSelect::isEnabled = false;
const char* TeamSelect::border = "border";
const char* TeamSelect::miiBg = "bg";

TeamSelect::TeamSelect() {
    hasBackButton = true;
    externControlCount = 0;
    internControlCount = 26;
    extraControlNumber = 0;
    controlSources = 2;
    titleBmg = BMG_TEAM_SELECT;
    nextPageId = PAGE_NONE;
    prevPageId = PAGE_FRIEND_ROOM;
    nextSection = SECTION_NONE;
    movieStartFrame = -1;
    isLocked = false;
    activePlayerBitfield = 1;

    onArrowClickHandler.subject = this;
    onArrowClickHandler.ptmf = &TeamSelect::OnArrowClick;
    onArrowSelectHandler.subject = this;
    onArrowSelectHandler.ptmf = &TeamSelect::OnArrowSelect;
    onArrowDeselectHandler.subject = this;
    onArrowDeselectHandler.ptmf = &TeamSelect::OnArrowDeselect;
    onButtonClickHandler.subject = this;
    onButtonClickHandler.ptmf = &TeamSelect::OnButtonClick;
    onButtonSelectHandler.subject = this;
    onButtonSelectHandler.ptmf = &TeamSelect::OnButtonSelect;
    onButtonDeselectHandler.subject = this;
    onButtonDeselectHandler.ptmf = &TeamSelect::OnButtonDeselect;
    onBackPressHandler.subject = this;
    onBackPressHandler.ptmf = &TeamSelect::OnBackPress;
    onToggleButtonClick.subject = this;
    onToggleButtonClick.ptmf = &TeamSelect::OnToggleButtonClick;


    this->controlsManipulatorManager.Init(1, false);
    this->SetManipulatorManager(controlsManipulatorManager);
    this->controlsManipulatorManager.SetGlobalHandler(START_PRESS, onStartPressHandler, false, false);
    this->controlsManipulatorManager.SetGlobalHandler(BACK_PRESS, onBackPressHandler, false, false);
    activePlayerBitfield = 1;

}


void TeamSelect::OnInit() {
    this->miiGroup = &SectionMgr::sInstance->curSection->Get<Pages::FriendRoomManager>()->miiGroup;
    Menu::OnInit();
    /*
    for(u8 aid = 0; aid < 12; aid++) {
        u32 idx = this->CalcIdx(aid);
        if(idx != 0xFF && this->teams[aid] == 1) {
            this->RotateArrow(this->arrows[idx], 1);
        }

    }
    */
}


void TeamSelect::BeforeEntranceAnimations() {
    Pages::Menu::BeforeEntranceAnimations();
    if(this->toggle.GetState() != this->isEnabled) this->toggle.ToggleState(this->isEnabled);
    this->toggle.SelectInitialButton(0);
    const u32 bmgId = this->toggle.GetState() == false ? BMG_TEAMS_DISABLED : BMG_TEAMS_ENABLED;
    this->toggle.SetMessage(bmgId);
    this->isLocked = false;

    for(int idx = 0; idx < 12; idx++) {
        this->miis[idx].animator.GetAnimationGroupById(0).PlayAnimationAtFrameAndDisable(0, 0.0f);
    }
    for(u8 teamsArrayIdx = 0; teamsArrayIdx < 24; teamsArrayIdx++) {
        u32 idx = this->CalcIdx(teamsArrayIdx);
        u8 curTeam = 0;
        if(idx != 0xFF) {
            u8 curTeam = this->teams[teamsArrayIdx];
            if(curTeam == 1) this->RotateArrow(this->arrows[idx], 1);
            this->SetColours(idx, curTeam);
            this->miis[idx].animator.GetAnimationGroupById(0).PlayAnimationAtFrameAndDisable(!curTeam, 0.0f);
        }
    }

}

void TeamSelect::BeforeControlUpdate() {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub* sub = &controller->subs[0];
    if(sub->connectionUserDatas[0].playersAtConsole == 0) sub = &controller->subs[1];

    int idx = 0;
    for(int aid = 0; aid < 12; ++aid) {
        if(sub->availableAids & (1 << aid)) {
            for(int player = 0; player < sub->connectionUserDatas[aid].playersAtConsole; player++) {
                LayoutUIControl& mii = this->miis[idx];
                mii.SetMiiPane("chara", *this->miiGroup, aid * 2 + player, 2);
                mii.SetMiiPane("chara_shadow", *this->miiGroup, aid * 2 + player, 2);
                mii.isHidden = false;
                mii.animator.GetAnimationGroupById(0).PlayAnimationAtFrameAndDisable(!this->teams[aid + 12 * player], 0.0f);
                this->arrowMiiIdx[idx] = aid * 2 + player;
                this->SetColours(idx, this->teams[aid + 12 * player]);
                this->RotateArrow(this->arrows[idx], this->teams[aid + 12 * player]);

                PushButton& arrow = this->arrows[idx];
                arrow.isHidden = false;
                arrow.manipulator.inaccessible = false;
                if(arrow.IsSelected()) {
                    this->text.miis[0] = this->miiGroup->GetMii(this->arrowMiiIdx[arrow.buttonId]);
                    this->name.SetMessage(BMG_MII_NAME, &this->text);
                }
                ++idx;
            }
        }
    }
    for(int remIdx = idx; remIdx < 12; remIdx++) {

        this->miis[remIdx].isHidden = true;
        this->arrows[remIdx].isHidden = true;
        this->arrows[remIdx].manipulator.inaccessible = true;
    }
}

UIControl* TeamSelect::CreateControl(u32 id) {
    if(id > 26) return nullptr;
    const u32 count = this->controlCount;
    this->controlCount++;
    char variant[0x40];
    if(id < 12) {
        this->AddControl(count, this->arrows[id], 0);
        snprintf(variant, 0x40, "Arrow%d", id);
        this->arrows[id].Load(UI::buttonFolder, "TeamArrow", variant, 1, 0, false);
        this->arrows[id].buttonId = id;
        this->arrows[id].SetOnClickHandler(this->onArrowClickHandler, 0);
        this->arrows[id].SetOnSelectHandler(this->onArrowSelectHandler);
        return &this->arrows[id];
    }
    else if(id < 24) {
        id = id - 12;
        this->AddControl(count, this->miis[id], 0);
        ControlLoader loader(&this->miis[id]);
        snprintf(variant, 0x40, "Mii%d", id);
        const char* brctr = "TeamMii";
        static const char* miiAnim[5] ={ "Translate", "TranslateRight", "TranslateLeft", nullptr, nullptr };
        loader.Load(UI::controlFolder, brctr, variant, miiAnim);
        return &this->miis[id];
    }
    else if(id == 24) {
        this->AddControl(count, this->name, 0);
        ControlLoader loader(&this->name);
        const char* brctr = "TeamName";
        loader.Load(UI::controlFolder, brctr, brctr, nullptr);
        return &this->name;

    }
    else /*if(id == 25)*/ {
        this->AddControl(count, this->toggle, 0);
        this->toggle.Load(1, UI::buttonFolder, "TeamSelectEnable", "Enable");
        this->toggle.SetOnClickHandler(this->onToggleButtonClick, 0);
        return &this->toggle;
    }
}

void TeamSelect::OnArrowClick(PushButton& button, u32 hudSlotId) {
    const u32 id = button.buttonId;
    u8 teamsArrayIdx = this->CalcTeamsArrayIdx(id);
    if(teamsArrayIdx != 0xFF) {
        const u8 newTeam = TeamSelect::teams[teamsArrayIdx] ^ 1;
        TeamSelect::teams[teamsArrayIdx] = newTeam;
        this->RotateArrow(button, newTeam);
        this->SetColours(id, newTeam);
        this->miis[id].animator.GetAnimationGroupById(0).PlayAnimationAtFrameAndDisable(!newTeam, 0.0f);
    }
}

void TeamSelect::OnArrowSelect(PushButton& button, u32 hudSlotId) {
    this->text.miis[0] = this->miiGroup->GetMii(this->arrowMiiIdx[button.buttonId]);
    this->name.SetMessage(BMG_MII_NAME, &this->text);
}

void TeamSelect::OnToggleButtonClick(ToggleButton& button, u32) {
    const u32 bmgId = button.GetState() == false ? BMG_TEAMS_DISABLED : BMG_TEAMS_ENABLED;
    this->isEnabled = button.GetState();
    button.SetMessage(bmgId);
}

int TeamSelect::GetActivePlayerBitfield() const {
    return this->activePlayerBitfield;
}

int TeamSelect::GetPlayerBitfield() const {
    return this->playerBitfield;
}

ManipulatorManager& TeamSelect::GetManipulatorManager() {
    return this->controlsManipulatorManager;
}

UIControl* TeamSelect::CreateExternalControl(u32 id) {
    return nullptr;
}

void TeamSelect::SetButtonHandlers(PushButton& button) {
    button.SetOnClickHandler(this->onButtonClickHandler, 0);
    button.SetOnSelectHandler(this->onButtonSelectHandler);
    button.SetOnDeselectHandler(this->onButtonDeselectHandler);
}

void TeamSelect::OnBackPress(u32 hudSlotId) {
    this->EndStateAnimated(0.0f, 1);
}

void TeamSelect::OnButtonClick(PushButton& button, u32 hudSlotId) {
    this->EndStateAnimated(button.GetAnimationFrameSize(), 1);
}

u8 TeamSelect::CalcTeamsArrayIdx(u32 idx) {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub* sub = &controller->subs[0];
    if(sub->connectionUserDatas[0].playersAtConsole == 0) sub = &controller->subs[1];

    u32 curIdx = 0;
    for(u8 curAid = 0; curAid < 12; ++curAid) {
        if(sub->availableAids & (1 << curAid)) {
            for(int player = 0; player < sub->connectionUserDatas[curAid].playersAtConsole; player++) {
                if(curIdx == idx) return curAid + 12 * player;
                ++curIdx;
            }
        }
    }
    return 0xFF;
}

u32 TeamSelect::CalcIdx(u8 teamsArrayIdx) {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub* sub = &controller->subs[0];
    if(sub->connectionUserDatas[0].playersAtConsole == 0) sub = &controller->subs[1];

    bool isGuest = teamsArrayIdx >= 12;
    u8 aid = isGuest ? teamsArrayIdx - 12 : teamsArrayIdx;
    if(!(sub->availableAids & (1 << aid)) || isGuest && sub->connectionUserDatas[aid].playersAtConsole < 2) return 0xFF;

    //the aid is valid, therefore it has an idx
    u32 idx = 0;
    for(u8 curAid = 0; curAid < aid; ++curAid) {
        if(sub->availableAids & (1 << curAid)) {
            for(int player = 0; player < sub->connectionUserDatas[curAid].playersAtConsole; player++) ++idx;
        }
    }
    return isGuest ? idx + 1 : idx;
}

void TeamSelect::RotateArrow(PushButton& button, u8 team) {
    RotateArrowPane(button, "chara_shadow", team);
    RotateArrowPane(button, "color_yajirushi", team);
    RotateArrowPane(button, "chara_c_down", team);
    RotateArrowPane(button, "chara_light_01", team);
}

void TeamSelect::RotateArrowPane(PushButton& button, const char* name, u8 team) {
    lyt::Picture* pane = static_cast<lyt::Picture*>(button.layout.GetPaneByName(name));
    nw4r::math::VEC2* vec = reinterpret_cast<nw4r::math::VEC2*>(pane->texCoords.data);

    bool isRed = team == 1;
    vec[0].x = isRed ? 0.0f : 1.0f;
    vec[1].x = isRed ? 1.0f : 0.0f;
    vec[2].x = isRed ? 0.0f : 1.0f;
    vec[3].x = isRed ? 1.0f : 0.0f;

}

void TeamSelect::SetColours(u32 idx, u8 team) {
    s16 r = 33;
    s16 b = 0xFF;
    s16 g = 33;
    if(team == 1) {
        r = 0xDC;
        b = 0;
        g = 33;
    }
    nw4r::lyt::Material* arrowBorder = this->arrows[idx].layout.GetPaneByName(this->border)->GetMaterial();
    arrowBorder->tevColours[0].r = r;
    arrowBorder->tevColours[0].g = 0;
    arrowBorder->tevColours[0].b = b;
    arrowBorder->tevColours[0].a = 255;
    arrowBorder->tevColours[1].r = r;
    arrowBorder->tevColours[1].g = 0;
    arrowBorder->tevColours[1].b = b;
    arrowBorder->tevColours[1].a = 255;


    nw4r::lyt::Material* miiBg = this->miis[idx].layout.GetPaneByName(this->miiBg)->GetMaterial();
    miiBg->tevColours[1].r = r;
    miiBg->tevColours[1].g = 0;
    miiBg->tevColours[1].b = b;
    miiBg->tevColours[1].a = 255;


    nw4r::lyt::Material* miiBorder = this->miis[idx].layout.GetPaneByName(this->border)->GetMaterial();
    if(r == 0xDC) r = 0xb3;
    else {
        r = 0;
        g = 0;
    }
    miiBorder->tevColours[0].r = r;
    miiBorder->tevColours[0].g = 0;
    miiBorder->tevColours[0].b = b;
    miiBorder->tevColours[0].a = 255;
    miiBorder->tevColours[1].r = r;
    miiBorder->tevColours[1].g = 0;
    miiBorder->tevColours[1].b = b;
    miiBorder->tevColours[1].a = 255;
}

}//namespace UI
}//namespace Pulsar