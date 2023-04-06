#ifndef _UPDOWNCONTROL_
#define _UPDOWNCONTROL_

#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/Manipulator.hpp>


//_sinit_ at 80642a20
class UpDownDisplayedText {
public:
    UpDownDisplayedText() {}; //inlined? //808bf3d8 vtable
    virtual LayoutUIControl *GetTextControl() const = 0; //0x8 
    virtual void InitText(bool state) = 0; //0xc 
    virtual void OnSelect(bool state, u32 hudSlotId) = 0; //0x10 
    virtual void SetMessage(u32 optionId) = 0; //0x14 
    virtual void SetMessageAnimated(u32 optionId) = 0; //0x18 
    virtual void OnClick() = 0; //0x1c 
    virtual void Animate(u32 hudSlotId) = 0; //0x20 
    virtual float Get3rdAnimStartFrame() const = 0; //0x24 
    virtual void SetBorderColours(RGBA16 *primary, RGBA16 *secondary) = 0; //0x28 
    virtual void SetColor_BaseColours(RGBA16 *colour) = 0; //0x2c 
}; //total size 0x4
size_assert(UpDownDisplayedText, 0x4);

class TextUpDownValueControl : public LayoutUIControl, public UpDownDisplayedText {
public:
    class TextControl : public LayoutUIControl {
    private:
        TextControl(); // 806410e0
        ~TextControl() override; //8064111c vtable 808bf430
        void InitSelf() override; //0x18 806411e8
        int GetRuntimeTypeInfo() const override; //0x28 80642998
        const char *GetClassName() const override; //0x2c 806410d0
        void Load(const char *folderName, const char *ctrName, const char *variant); //80641174 inlined
        void ToggleSelect(bool state); //806412f8
    }; //total size 0x174

    TextUpDownValueControl(); //806405d0
    //LayoutUIControl vt 808bf39c
    ~TextUpDownValueControl() override; //8064063C
    void Init() override; //0xc 806407dc
    void Update() override; //0x10 806408fc
    int GetRuntimeTypeInfo() const override; //0x28 8064298c
    const char *GetClassName() const override; //0x2c 806405c0
    //UpDownDisplayText vt 808bf3d8
    LayoutUIControl *GetTextControl() const override; //0x8 thunk 80642a98 func 80642988 just a blr
    void InitText(bool state) override; //0xc thunk 80642a90 func 80640aa0 bool is true if UpDownControl's parent manipulator manager has a manipulator that matches its own
    void OnSelect(bool state, u32 hudSlotId) override; //0x10 thunk 80642a88 func 80640b68
    void SetMessage(u32 optionId) override; //0x14 thunk 80642a80 func 80640cdc
    void SetMessageAnimated(u32 optionId) override; //0x18 thunk 80642a78 func 80640d0c
    void OnClick() override; //0x1c thunk 80642a70 func 80640dfc
    void Animate(u32 hudSlotId) override; //0x20 thunk 80642a68 func 80640e68 called OnScroll and OnClick
    float Get3rdAnimStartFrame() const override; //0x24 thunk 80642a60 func 80640f00unsure and it's never called
    void SetBorderColours(RGBA16 *primary, RGBA16 *secondary) override; //0x28 thunk 80642a58 func 80640f74 by editing fuchi_pattern mat
    void SetColor_BaseColours(RGBA16 *colour) override; //0x2c thunk 80642a50 func 80641028 color_base seems to always be null so doesn't do anything

    void SetOnTextChangeHandler(PtmfHolder_2A<Page, void, TextControl *, u32> *handler); //806407d4
    void Load(const char *folderName, const char *ctrName, const char *variant, const char *textControlCtrName, const char *textControlVariant); //806406b0

    PtmfHolder_2A<Page, void, TextControl *, u32> *onTextChangeHandler; //0x178 when you scroll, r5 has button ID
    TextControl textControl[2]; //array 0x17C
    TextControl *activeTextValueControl; // 0x464
    TextControl *otherTextValueControl; // 0x468 they invert everytime the button is moved, might mean each textControl only holds half?
    nw4r::lyt::Pane *fuchi_pattern;
    nw4r::lyt::Pane *color_base; //0x470
}; //total size 0x474
size_assert(TextUpDownValueControl, 0x474);
size_assert(TextUpDownValueControl::TextControl, 0x174);

//if you click/select etc... on one of the arrows with the pointer, curChildId is not -1 and the Handle function also triggers
//for example HandleClick triggers the onChangePtmf if the arrow was clicked, but just clicking on the number doesn't
class UpDownControl : public LayoutUIControl {
public:
    class UpDownButton : public LayoutUIControl {
    private:
        UpDownButton(); //0x8063fdc0
        ~UpDownButton() override; //8063fdfc vtable 0x808bf4b0
        void Init() override; //0xc 8063ff18
        void Update() override; //0x10 8063ffb0
        int GetRuntimeTypeInfo() const override; //0x28 806429b4
        const char *GetClassName() const override; //0x2c 8063fdb0
        void Load(const char *folderName, const char *ctrName, const char *variant, ControlBoundingBox *boudingBox); //8063fe54 inlined
        void SetIsVisibleOnIdle(bool isVisible); //806405b0
        void ToggleSelect(bool state, u32 hudSlotId); //8063f8e0 bool 1 = select, 0 = deselect
        void HandleClick(); //80640360 inlined just plays some animations

        bool isVisibleOnIdle;
        UpDownControl *GetParentControl() const; //8064009c
        u8 padding[3];
        nw4r::lyt::Pane *fuchi_pattern;
        nw4r::lyt::Pane *color_base; //can't find it it seems
        nw4r::lyt::Pane *color_yajirushi; //can't find it either //0x180
        ControlBoundingBox *boudingBox; //0x184
    };//total size 0x188

    UpDownControl(); //0x8063e960
    ~UpDownControl() override; //0x8063eb5c vtable 808bf46c
    void Init() override; //0xc 8063f16c
    void Update() override; //0x10 8063f2a8
    int GetRuntimeTypeInfo() const override; //0x28 806429a8
    const char *GetClassName() const override; //0x2c 8063e954
    virtual void OnDeactivateingEnd(); //0x3c 8063f01c called at the end of load
    virtual void func_0x40(); //806429a4

    void SetOnChangeHandler(PtmfHolder_3A<Page, void, UpDownControl *, u32, u32> *handler); //8063f020
    void SetOnClickHandler(PtmfHolder_2A<Page, void, UpDownControl *, u32> *handler); //8063f028
    void SetOnSelectHandler(PtmfHolder_2A<Page, void, UpDownControl *, u32> *handler); //8063f030
    void SetOnDeselectHandler(PtmfHolder_2A<Page, void, UpDownControl *, u32> *handler); //8063f038

    void Load(u32 optionCount, u32 initialOptionId, const char *folderName, const char *ctrName, const char *variant, const char *buttonRCtrName, const char *buttonRvariant,
        char *buttonLCtrName, const char *buttonLvariant, UpDownDisplayedText *text, u32 localPlayerBitfield, u8 unk_13, bool isNotSelectable, bool isLooped, bool onClickSendsToNextControl);
    void HandleSelect(u32 hudSlotId, u32 curChildId); //8063f694
    void HandleDeselect(u32 hudSlotId, u32 curChildId); //8063f7c4
    void HandleClick(u32 hudSlotId, u32 curChildId); //8063f8f8
    void HandleRightPress(u32 hudSlotId, u32 curChildId); //8063fb64
    void HandleLeftPress(u32 hudSlotId, u32 curChildId); //8063fc90
    void HandleButtonSelect(u32 hudSlotId, u32 curChildId); //8063f8c8 only possible with the pointer
    void HandleButtonDeselect(u32 hudSlotId, u32 curChildId); //8063f8e0 same
    void SelectInitial(u32 optionsCount, u32 initialButton); //8063f0c0
    void SetPlayerBitfield(u32 playerBitfield); //8063f160
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onSelectHandlerObj; //0x174 vtable 808bf4ec 8063f694
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onDeselectHandlerObj; //0x188 vtable 808bf4ec 8063f7c4
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onButtonSelectHandlerObj; //0x19C vtable 808bf4ec 8063f8c8
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onButtonDeselectHandlerObj; //0x1B0 vtable 808bf4ec 8063f8e0
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onClickHandlerObj; //0x1C4 vtable 808bf4ec 8063f8f8
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onRightPressHandler; //0x1D8 vtable 808bf4ec 8063fb64
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onLeftPressHandler; //0x1EC vtable 808bf4ec 8063fc90
    u32 localPlayerBitfield; //0x200
    u32 curSelectedOption; //0x204
    u32 optionsCount; //0x208
    u32 id; //if there are multiple UpDownControl
    u8 unknown_0x210[4];
    UpDownDisplayedText *text; //0x214
    ControlManipulator manipulator; //0x218
    PtmfHolder_3A<Page, void, UpDownControl *, u32, u32> *onChangeHandler; //0x29c hud slot Id, cur selected option
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *onClickHandler; //0x2a0
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *onSelectHandler; //0x2a4
    PtmfHolder_2A<Page, void, UpDownControl *, u32> *onDeselectHandler; //0x2a8
    nw4r::lyt::Pane *fuchi_pattern; //0x2ac
    nw4r::lyt::Pane *color_base; //0x2b0
    UpDownButton arrowButtons[2];
    u32 soundID; //init at 0x13, sound to play when the arrows are pressed
};  //0x5C8
size_assert(UpDownControl, 0x5C8);
size_assert(UpDownControl::UpDownButton, 0x188);




#endif