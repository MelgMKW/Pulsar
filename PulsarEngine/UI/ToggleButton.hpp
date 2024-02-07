#ifndef _TOGGLEBUTTON_
#define _TOGGLEBUTTON_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>


class ToggleButton : public PushButton {
public:
    ToggleButton() : state(false) {}
    void Load(u32 localPlayerBitfield, const char* folderName, const char* ctrName, const char* variant);
    void ToggleState(bool state); //changes the state without an animation
    inline bool GetState() const { return this->state; }
private:
    void OnClick() override {
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
    bool state;
};
#endif