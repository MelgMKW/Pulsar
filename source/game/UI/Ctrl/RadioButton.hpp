#ifndef _RADIOBUTTON_
#define _RADIOBUTTON_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/Manipulator.hpp>

//_sinit_ at 80607130
class RadioButtonControl : public LayoutUIControl {
public:
    class OptionButton : public LayoutUIControl {
    private:
        OptionButton(); //0x80606858
        ~OptionButton() override; //80606894 vtable 0x808baa24
        void Init() override; //80606994
        void Update() override; //0x10 80606a14
        int GetRuntimeTypeInfo() const override; //0x28 806070f4
        const char *GetClassName() const override; //0x2c 80606848
        void Load(const char *folderName, const char *ctrName, const char *variant); //806068ec inlined
        void ToggleSelect(bool State); //80606e24
        void ToggleChose(bool State); //80606c48 called by Radio HandleClick, enables or disables the red fuchi
        RadioButtonControl GetParentControl() const; //80606ad0
        void SetBorderColours(RGBA16 *primary, RGBA16 *secondary); //inlined 80606f88
        void SetColor_BaseColours(RGBA16 *colour); //8060703c

        nw4r::lyt::Pane *fuchi_pattern;
        nw4r::lyt::Pane *color_base;
    };//total size 0x17c
    RadioButtonControl(); //80605724
    ~RadioButtonControl() override; //806058c8 vtable 808ba9e0
    void Init() override; //0xc 80605f24
    void Update() override; //0x10 80606100
    int GetRuntimeTypeInfo() const override; //0x28 806070e8
    const char *GetClassName() const override; //0x2c 80605718
    virtual void OnDeactivateingEnd(); //0x3c 80605d50
    virtual void func_0x40(); //0x40 806070e4

    void Load(u32 buttonsCount, u32 initialButtonId, const char *folderName, const char *ctrName, const char *variant, const char *optionCtrName,
        const char **optionVariants, u32 localPlayerBitfield, u8 arg10, u8 arg11); //8060594c
    void SelectInitialButton(u8 hudSlotId); //80605d74
    void HandleSelect(u32 hudSlotId, u32 curChildId); //806062d8
    void HandleDeselect(u32 hudSlotId, u32 curChildId); //80606434
    void HandleButtonSelect(u32 hudSlotId, u32 curChildId); //80606568 only possible with the pointer
    void HandleClick(u32 hudSlotId, u32 curChildId); //80606620
    void HandleRightPress(u32 hudSlotId, u32 curChildId); //806066d4
    void HandleLeftPress(u32 hudSlotId, u32 curChildId); //80606790
    void SetOnClickHandler(PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *handler); //80605d54
    void SetOnSelectHandler(PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *handler);//80605d5c
    void SetOnDeselectHandler(PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *handler);  //80605d64
    void SetOnChangeHandler(PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *handler); //80605d6c
    static void Trigger2APtmf(PtmfHolder_2A<LayoutUIControl, void, u32, u32> *handler, u32 hudSlotId, u32 curChildId); //80607130
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onSelectHandlerObj; //0x174 vtable 808baa60 806062d8
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onDeselectHandlerObj; //0x188 vtable 808baa60 80606434
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onButtonSelectObj; //0x19C vtable 808baa60 80606568 only possible with the pointer
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onClickHandlerObj; //0x1B0 vtable 808baa60 80606620
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onRightPressHandlerObj; //0x1C4 vtable 808baa60 806066d4
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> onLeftPressHandlerObj; //0x1D8 vtable 808baa60 80606790
    u32 localPlayerBitfield; //0x1EC
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *onClickHandler; //0x1F0
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *onSelectHandler; //0x14
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *onDeselectHandler; //0x1f8
    PtmfHolder_3A<Page, void, RadioButtonControl *, u32, u32> *onChangeHandler; //0x1fc called by both handle select and deselect
    u32 buttonsCount; //0x200
    u32 chosenButtonId; //init at -1
    u32 selectedButtonId;
    u32 id; //if there are multiple radiobuttonctrol
    ControlManipulator manipulator; //0x210
    RadioButtonControl::OptionButton *optionButtonsArray; //0x294
}; //total size 0x298
size_assert(RadioButtonControl, 0x298);
size_assert(RadioButtonControl::OptionButton, 0x17c);
#endif