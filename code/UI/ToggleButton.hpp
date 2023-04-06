#ifndef _TOGGLEBUTTON_
#define _TOGGLEBUTTON_
#include <kamek.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Page/Page.hpp>

/*Custom control which is a button that can be toggled on and off.
In retrospect, could likely be done solely with PushButton but I had not seen that PushButton has a "LoadWithAnims" function
*/
class ToggleButton : public LayoutUIControl {
public:
    ToggleButton();
    void Init() override;
    void Update() override;
    void Load(const char *folderName, const char *ctrName, const char *variant, u32 localPlayerCount, bool r10, bool inaccessible);
    void SetOnChangeHandler(PtmfHolder_1A<Page, void, ToggleButton *> *handler) { this->onChangeHandler = handler; } //80637d24
    void ToggleState(bool state); //changes the state without an animation
    void SelectInitial(u32 hudSlotId);
private:
    void HandleSelect(u32 hudSlotId, u32 r5); //80638988
    void HandleDeselect(u32 hudSlotId, u32 r5); //80638a7c
    void HandleClick(u32 hudSlotId, u32 r5); //80638c64
    ControlManipulator manipulator; //0x174
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onSelectHandler; //80638988 1f8
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onDeselectHandler; //80638a7c 20C
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onClickHandler; //80638c64  220
    PtmfHolder_1A<Page, void, ToggleButton *> *onChangeHandler; //234
    u32 localPlayerBitfield; //238
public:
    bool state; //true for ON //23C
    u32 buttonId; //if multiple buttons //240
private:
    nw4r::lyt::Pane *fuchi_pattern; //244
};
#endif