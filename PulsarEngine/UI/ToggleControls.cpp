#include <UI/ToggleControls.hpp>

namespace  Pulsar {
namespace UI {

static const char* anims[7] ={ "Choice", "ChoiceOff", "ChoiceOffToOn", "ChoiceOn", "ChoiceOnToOff", nullptr, nullptr };

void ToggleButton::ToggleState(bool state) {
    if(this->state != state) {
        u32 id = this->state ? 0 : 2;
        this->animator.GetAnimationGroupById(4).PlayAnimationAtFrame(id, 0.0f); //choice
        this->state = !this->state;
    }
}

void ToggleButton::OnClick(u32, u32) {
    AnimationGroup& choiceGroup = this->animator.GetAnimationGroupById(4); //choice group, off, offtoon, on, ontooff
    const u32 curAnimation = choiceGroup.curAnimation;
    const bool curState = this->state;
    this->state = !this->state;
    if(curState == true && curAnimation == 1 || curState == false && curAnimation == 3) {
        float frameSize = static_cast<float>(choiceGroup.animations[curAnimation].transform->GetFrameSize());
        choiceGroup.PlayAnimationAtPercent(1, 1.0f - 75.0f / frameSize);
    }
    else if(curState == true && curAnimation == 2) choiceGroup.PlayAnimationAtFrame(3, 0.0f);
    else if(curState == false && curAnimation == 0) choiceGroup.PlayAnimationAtFrame(1, 0.0f);
}

void ToggleButton::Load(u32 localPlayerBitfield, const char* folderName, const char* ctrName, const char* variant) {
    this->LoadWithAnims(anims, folderName, ctrName, variant, localPlayerBitfield, 0);
    AnimationGroup& choiceGroup = this->animator.GetAnimationGroupById(4); //choice, pattern and colours on click
    choiceGroup.PlayAnimationAtFrame(this->state ? 2 : 0, 0.0f);
}

/*
void ToggleControl::Load(const char* folderName, const char* ctrName, const char* variant) {
    ControlLoader loader(this);
    loader.Load(folderName, ctrName, variant, anims);
    AnimationGroup& choiceGroup = this->animator.GetAnimationGroupById(0); //choice, pattern and colours on click
    choiceGroup.PlayAnimationAtFrame(this->state ? 2 : 0, 0.0f);
}

void ToggleControl::ToggleState(bool state) {
    if(this->state != state) {
        u32 id = this->state ? 0 : 2;
        this->animator.GetAnimationGroupById(0).PlayAnimationAtFrame(id, 0.0f); //choice
        this->state = !this->state;
    }
}

void ToggleControl::ToggleStateAnimated() {
    AnimationGroup& choiceGroup = this->animator.GetAnimationGroupById(0); //choice group, off, offtoon, on, ontooff
    const u32 curAnimation = choiceGroup.curAnimation;
    const bool curState = this->state;
    this->state = !this->state;
    if(curState == true && curAnimation == 1 || curState == false && curAnimation == 3) {
        float frameSize = static_cast<float>(choiceGroup.animations[curAnimation].transform->GetFrameSize());
        choiceGroup.PlayAnimationAtPercent(1, 1.0f - 75.0f / frameSize);
    }
    else if(curState == true && curAnimation == 2) choiceGroup.PlayAnimationAtFrame(3, 0.0f);
    else if(curState == false && curAnimation == 0) choiceGroup.PlayAnimationAtFrame(1, 0.0f);
}
*/

/*
void ToggleButton::SelectInitial(u32 hudSlotId) {
    this->manipulator.parentManager->SetControlManipulator(hudSlotId, this->manipulator, -1);
    this->AnimateSelect();
}



void ToggleButton::HandleClick(u32 hudSlotId, u32 r5) {
    AnimationGroup& selectInGroup = this->animator.GetAnimationGroupById(2);
    selectInGroup.PlayAnimationAtFrame(0, 0.0f);
    AnimationGroup& okGroup = this->animator.GetAnimationGroupById(3);
    okGroup.PlayAnimationAtFrame(0, 0.0f);

    AnimationGroup& choiceGroup = this->animator.GetAnimationGroupById(4); //choice group, off, offtoon, on, ontooff
    if(this->state == true && choiceGroup.curAnimation == 1 || this->state == false && choiceGroup.curAnimation == 3) {
        float frameSize = static_cast<float>(choiceGroup.animations[choiceGroup.curAnimation].transform->GetFrameSize());
        choiceGroup.PlayAnimationAtPercent(1, 1.0f - 75.0f / frameSize);
    }
    else if(this->state == true && choiceGroup.curAnimation == 2) choiceGroup.PlayAnimationAtFrame(3, 0.0f);

    else if(this->state == false && choiceGroup.curAnimation == 0) choiceGroup.PlayAnimationAtFrame(1, 0.0f);

    this->state = !this->state;
    u32 soundId = this->state == true ? 0x20 : 0xD;
    this->PlaySound(soundId, -1);
    if(onChangeHandler != nullptr) this->onChangeHandler->operator()(*this);
}
*/
}//namespace UI
}//namespace Pulsar