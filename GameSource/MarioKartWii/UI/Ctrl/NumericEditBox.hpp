#ifndef _NUMERICEDITBOX_
#define _NUMERICEDITBOX_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/Manipulator.hpp>


//_sinit_ at 805cadc0
class NumericEditBox : public LayoutUIControl {
public:
    class EditLetter : public LayoutUIControl {
    public:
        EditLetter(); //805caaf0
        ~EditLetter() override; //805cab2c vtable 808b82f8
        void Init() override; //0xc 805cac0c
        void Update() override; //0x10 805cac8c
        const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805cad84
        const char* GetClassName() const override; //0x2c 805caae0
        void Load(const char* folderName, const char* ctrName, const char* variant); //805cab84
        void AddDigit(u32 digit); //805cac90 inlined
        void RemoveDigit(); //805cace4 inlined
        void ToggleCursor(bool isEnabled); //805cacf0 inlined
        void AnimateDigit(); //805cad3c inlined

        u32 curDigit; //0x174 -1 if no digit, 0-9 if currently showing/holding a digit
    };
    NumericEditBox(); //805c98a0
    ~NumericEditBox() override; //805c99f8 vtable 808b82b8
    void Init() override; //0xc 805ca438
    void Update() override; //0x10 805ca53c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805cad78
    const char* GetClassName() const override; //0x2c 805c9894
    virtual void vf_0x3c(); //0x3c 805c9ebc

    void Load(u32 digitCount, const char* folderName, const char* boxCtrName, const char* variant, const char* digitCtrName,
        const char* digitVariant, u32 localPlayerBitfield, bool r5, bool inaccessible); //805c9a7c r5 == manipulator's init r5
    void SelectInitial(u32 hudSlotId); //805c9ec0
    void Select(u32 hudSlotId); //805c9f14
    void RemoveAllDigits(); //805c9f34
    bool HasFullDigits(); //805c9fe8
    bool HasUnusedDigit(); //805ca028
    u64 ComputeSum(); //805ca068 returns sum(digits[i] * pow(10, digitCount -i)) ie the friendcode as a concatenated number
    void AddDigit(u32 digit); //805ca0c8 also resets all "unused" editletters
    void RemoveDigit(); //805ca250
    void HandleUpPress(u32 hudSlotId, u32 r5); //805ca6e8
    void HandleDownPress(u32 hudSlotId, u32 r5); //805ca7c0
    void HandleClick(u32 hudSlotId, u32 r5); //805ca870
    void HandleRightPress(u32 hudSlotId, u32 r5); //805ca94c
    void HandleLeftPress(u32 hudSlotId, u32 r5); //805caa24

    PtmfHolder_2A<NumericEditBox, void, u32, u32> onUpPressHandlerObj; //0x174 805ca6e8 selection
    PtmfHolder_2A<NumericEditBox, void, u32, u32> onDownPressHandlerObj; //0x188 805ca7c0 deselection
    PtmfHolder_2A<NumericEditBox, void, u32, u32> onClickHandlerObj; //0x19c 805ca870
    PtmfHolder_2A<NumericEditBox, void, u32, u32> onRightPressHandlerObj; //0x1b0 805ca94c
    PtmfHolder_2A<NumericEditBox, void, u32, u32> onLeftPressHandlerObj; //0x1c4 805caa24
    u32 localPlayerBitfield; //0x1d8
    u32 digitCount; //0x1dc
    u32 curDigitCount; //0x1e0 how many digits have been entered
    ControlManipulator controlManipulator; //0x1e4
    lyt::Pane* fuchi_pattern; //0x268
    lyt::Pane* color_base; //0x26c
    EditLetter* digits; //0x270
};//Total Size 0x274
size_assert(NumericEditBox::EditLetter, 0x178);
size_assert(NumericEditBox, 0x274);


#endif