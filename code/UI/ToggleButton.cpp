#include <UI/ToggleButton.hpp>

ToggleButton::ToggleButton(): localPlayerBitfield(1), state(false) {
    this->onSelectHandler.subject = this;
    this->onSelectHandler.ptmf = static_cast<void(LayoutUIControl:: *)(u32, u32)>(&ToggleButton::HandleSelect);
    this->onDeselectHandler.subject = this;
    this->onDeselectHandler.ptmf = static_cast<void(LayoutUIControl:: *)(u32, u32)>(&ToggleButton::HandleDeselect);
    this->onClickHandler.subject = this;
    this->onClickHandler.ptmf = static_cast<void(LayoutUIControl:: *)(u32, u32)>(&ToggleButton::HandleClick);
};

void ToggleButton::Init() {
    LayoutUIControl::Init();
    AnimationGroup *group = this->animator.GetAnimationGroupById(0); //loop
    group->PlayAnimationAtFrameAndDisable(0, 0.0f);

    group = this->animator.GetAnimationGroupById(1); //select, the looping animation
    group->PlayAnimationAtFrame(0, 0.0f);

    group = this->animator.GetAnimationGroupById(2); //selectin, the button getting bigger on select
    group->PlayAnimationAtFrame(1, 0.0f);

    group = this->animator.GetAnimationGroupById(3); //ok, text animation on click
    group->PlayAnimationAtFrame(1, 0.0f);

    group = this->animator.GetAnimationGroupById(4); //choice, pattern and colours on click
    group->PlayAnimationAtFrame(this->state ? 2 : 0, 0.0f);
    this->manipulator.SetEnabledHudSlots(this->localPlayerBitfield);
};

void ToggleButton::Update() {
    LayoutUIControl::Update();
    AnimationGroup *group = this->animator.GetAnimationGroupById(1);
    if (group->curAnimation == 0) {
        group = this->animator.GetAnimationGroupById(0);
        group->PlayAnimationAtFrameAndDisable(0, 30.0f);
        this->drawPriority = 0.0f;
    }
    else {
        group = this->animator.GetAnimationGroupById(0);
        nw4r::lyt::AnimTransformBasic *transform = group->animations[group->curAnimation].transform;
        if (transform != NULL) {
            group->isActive = true;
            this->drawPriority = 0.0f;
        }
    }
    if (this->fuchi_pattern != NULL) {
        ControlManipulator *holder = &this->manipulator;
        RGBA16 primary;
        RGBA16 secondary;
        holder->GetHudColor(&primary, &secondary);
        nw4r::lyt::Material *material = this->fuchi_pattern->GetMaterial();
        material->tevColours[1].r = primary.red;
        material->tevColours[1].g = primary.green;
        material->tevColours[1].b = primary.blue;
        material->tevColours[1].a = primary.alpha;

        material->tevColours[2].r = secondary.red;
        material->tevColours[2].g = secondary.green;
        material->tevColours[2].b = secondary.blue;
        material->tevColours[2].a = secondary.alpha;
    }
}

void ToggleButton::Load(const char *folderName, const char *ctrName, const char *variant, u32 localPlayerCount, bool r10, bool inaccessible) {
    this->localPlayerBitfield = localPlayerCount;
    ControlLoader loader(this);
    const char *anims[24] = { "Loop", "Loop", NULL,
    "Select", "Free", "FreeToSelect", "Select", "SelectToFree", NULL,
    "SelectIn","SelectIn", "SelectStop", NULL,
    "OK", "OK", "OKStop", NULL,
    "Choice", "ChoiceOff", "ChoiceOffToOn", "ChoiceOn", "ChoiceOnToOff", NULL, NULL };

    loader.Load(folderName, ctrName, variant, anims);
    nw4r::lyt::Pane *pane = this->layout.GetPaneByName("fuchi_pattern");
    this->fuchi_pattern = pane;

    pane = this->layout.GetPaneByName("touch");
    this->manipulator.boundingBox.touchPane = pane;
    this->manipulator.boundingBox.onSelectControlHandler = (&this->onSelectHandler);
    this->manipulator.boundingBox.onDeselectControlHandler = (&this->onDeselectHandler);
    this->manipulator.Init(0, false, false);
    this->manipulator.SetAction(FORWARD_PRESS, (&this->onClickHandler), false);

    ControlsManipulatorManager *manager = (ControlsManipulatorManager *)this->parentGroup->parentPage->manipulatorManager;
    manager->AddControlManipulator(&this->manipulator);
}

void ToggleButton::ToggleState(bool state) {
    if (this->state != state) {
        u32 id = this->state ? 0 : 2;
        this->animator.GetAnimationGroupById(4)->PlayAnimationAtFrame(id, 0.0f);
        this->state = !this->state;
    }
}

void ToggleButton::SelectInitial(u32 hudSlotId) {
    this->manipulator.parentManager->SetControlManipulator(hudSlotId, &this->manipulator, -1);
    AnimationGroup *group = this->animator.GetAnimationGroupById(1);
    if (group->curAnimation == 0) {
        group->PlayAnimationAtFrame(1, 0.0f);
    }
    else if (group->curAnimation == 3) {
        float frameSize = (float)group->animations[group->curAnimation].transform->GetFrameSize();
        group->PlayAnimationAtPercent(1, 1.0f - 4.0f / frameSize);
    }
    group = this->animator.GetAnimationGroupById(2);
    group->PlayAnimationAtFrame(0, 0.0f);
}

void ToggleButton::HandleSelect(u32 hudSlotId, u32 r5) {
    AnimationGroup *group = this->animator.GetAnimationGroupById(1);
    if (group->curAnimation == 0) {
        group->PlayAnimationAtFrame(1, 0.0f);
    }
    else if (group->curAnimation == 3) {
        float frameSize = (float)group->animations[group->curAnimation].transform->GetFrameSize();
        group->PlayAnimationAtPercent(1, 1.0f - 4.0f / frameSize);
    }
    group = this->animator.GetAnimationGroupById(2);
    group->PlayAnimationAtFrame(0, 0.0f);
    this->PlaySound(0xC, hudSlotId);
}

void ToggleButton::HandleDeselect(u32 hudSlotId, u32 r5) {
    AnimationGroup *group = this->animator.GetAnimationGroupById(1);
    if (group->curAnimation == 1) {
        float frameSize = (float)group->animations[group->curAnimation].transform->GetFrameSize();
        group->PlayAnimationAtPercent(1, 1.0f - 38.0f / frameSize);
    }
    else if (group->curAnimation == 2) group->PlayAnimationAtFrame(3, 0.0f);
}

void ToggleButton::HandleClick(u32 hudSlotId, u32 r5) {
    AnimationGroup *group = this->animator.GetAnimationGroupById(2);
    group->PlayAnimationAtFrame(0, 0.0f);
    group = this->animator.GetAnimationGroupById(3);
    group->PlayAnimationAtFrame(0, 0.0f);

    group = this->animator.GetAnimationGroupById(4); //choice group, off, offtoon, on, ontooff
    if (this->state == true && group->curAnimation == 1 || this->state == false && group->curAnimation == 3) {
        float frameSize = (float)group->animations[group->curAnimation].transform->GetFrameSize();
        group->PlayAnimationAtPercent(1, 1.0f - 75.0f / frameSize);
    }
    else if (this->state == true && group->curAnimation == 2) group->PlayAnimationAtFrame(3, 0.0f);

    else if (this->state == false && group->curAnimation == 0) group->PlayAnimationAtFrame(1, 0.0f);

    this->state = !this->state;
    u32 soundId = this->state == true ? 0x20 : 0xD;
    this->PlaySound(soundId, -1);
    this->onChangeHandler->operator()(this);
}
