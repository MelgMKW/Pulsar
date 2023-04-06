#ifndef _TABCONTROL_
#define _TABCONTROL_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/Manipulator.hpp>

//_sinit_ at 80638e6c
class TabControl : public LayoutUIControl { //change mii top buttons contains OptionButtons 808beb80
public:
    class OptionButton : public LayoutUIControl {
    public:
        OptionButton(); //80638048
        ~OptionButton() override; //8063813c vtable 808beb80
        void Init() override; //80638370
        void Update() override; //8063851c
        int GetRuntimeTypeInfo() const override; //80638e30
        const char *GetClassName() const override; //80638038
        void Load(u32 buttonId, const char *folderName, const char *ctrName, const char *variant, const char **anims, bool r8, bool inaccessible); //806381a4
        void HandleSelect(u32 hudSlotId, u32 childId); //80638988
        void HandleDeselect(u32 hudSlotId, u32 childId); //80638a7c
        void HandleClick(u32 hudSlotId, u32 childId); //80638c64
        void ChangeButtonState(bool state); //true to select, false to unselect 80638830
        void SetInitialState(bool state); //806387d0 inlined same as change button state but without the OnToOff/OffToOn animations
        void SetEnabledHudSlots(u32 playerBitField); //806386c8
        TabControl *GetParentControl() const; //806386d0
        static void Trigger2APtmf(PtmfHolder_2A<OptionButton, void, u32, u32> *handler, u32 hudSlotId, u32 childId); //80638e3c
        ControlManipulator manipulator; //0x174 to 0x1F8
        PtmfHolder_2A<OptionButton, void, u32, u32> onSelectHandler; //80638988
        PtmfHolder_2A<OptionButton, void, u32, u32> onDeselectHandler; //80638a7c //0x20c
        PtmfHolder_2A<OptionButton, void, u32, u32> onClickHandler; //80638c64
        u32 buttonId; //0x234
        nw4r::lyt::Pane *fuchi_pattern;
        nw4r::lyt::Pane *color_base;
    }; //total size 0x240

    TabControl(); //80637ad0 
    ~TabControl() override; //80637b2c vtable 808beb3c
    void Init() override; //80637EC0
    void Update() override; //80637f94
    int GetRuntimeTypeInfo() const override; //80638e24
    const char *GetClassName() const override; //80637ac4
    virtual void OnDeactivateingEnd(); //0x3c 80637d20
    virtual void func_0x40(); //80638e20
    void Load(u32 buttonsCount, u32 initialButtonId, const char *folderName, const char *ctrName, const char **optionVariants, u32 localPlayerBitfield, bool r10, bool inaccessible);  //80637ba4
    void SetOnClickHandler(PtmfHolder_3A<Page, void, OptionButton *, u32, u32> *onChangeHandler); //80637d24
    void SetEnabledHudSlots(u32 playerBitField); //80637d2c
    void SelectInitial(u32 buttonId); //80637da8
    void SelectButtonNoPtmf(u32 buttonId); //80637e48 doesn't trigger the ptmf, not sure why you'd ever need this
    void SelectButton(u32 hudSlotId, u32 buttonId); //80637f98 manual way to select a button
    PtmfHolder_3A<Page, void, TabControl *, u32, u32> *onClickHandler; //0x174 r6 is buttonId
    u32 localPlayerBitfield; //unsure //0x178
    u32 buttonsCount; //0x17C
    u32 selectedButtonID; //0x180
    u32 unknown_0x184; //0x184
    OptionButton *optionButtonsArray; //0x188
}; //total size 0x18C
size_assert(TabControl, 0x18C);
size_assert(TabControl::OptionButton, 0x240);

#endif