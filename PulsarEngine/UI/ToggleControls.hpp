#ifndef _TOGGLEBUTTON_
#define _TOGGLEBUTTON_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>

namespace  Pulsar {
namespace UI {
/*
class ToggleControl : public LayoutUIControl {
public:
    ToggleControl() : state(false) {}
    void Load(const char* folderName, const char* ctrName, const char* variant);
    void ToggleState(bool state); //changes the state without an animation
    void ToggleStateAnimated();
    inline bool GetState() const { return this->state; }
private:
    bool state;
};
*/
class ToggleButton : public PushButton {
public:
    ToggleButton() : state(false) {}
    void Load(u32 localPlayerBitfield, const char* folderName, const char* ctrName, const char* variant);
    void ToggleState(bool state); //changes the state without an animation
    inline bool GetState() const { return this->state; }
private:
    void OnClick(u32 hudSlotId, u32 r5) override;
    bool state;
};
}//namespace UI
}//namespace Pulsar

#endif