#ifndef _CTRLMENUTEXT_
#define _CTRLMENUTEXT_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>

//_sinit_ at 807e9c10
class CtrlMenuObiTop : public LayoutUIControl {
    //no ctor
    ~CtrlMenuObiTop() override; //807e9b7c vtable 808d365c
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //807e9a68
    int GetRuntimeTypeInfo() const override; //0x28 807e9bd4
    const char *GetClassName() const override; //0x2c 807e9250
}; //0x174
size_assert(CtrlMenuObiTop, 0x174);

class CtrlMenuPageTitleText : public LayoutUIControl {
public:
    ~CtrlMenuPageTitleText() override; //805baf10 vtable 808d36d4
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 807e9898
    int GetRuntimeTypeInfo() const override; //0x28 807e9bec
    const char *GetClassName() const override; //0x2c 807e9230
    void SetMsgId(u32 bmgId, const TextInfo *text = NULL); //807e987c
    void Load(bool r4); //807e947c
}; //total size 0x174

class CtrlMenuInstructionText : public LayoutUIControl {
public:
    ~CtrlMenuInstructionText() override; //805c00c0 vtable 808d3698
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 807e999c
    int GetRuntimeTypeInfo() const override; //0x28 807e9be0
    const char *GetClassName() const override; //0x2c 807e9240
    void Load(); //807e9904
    void SetMsgId(u32 bmgId, const TextInfo *text = NULL); //807e9a38
}; //total size 0x174

class CtrlMenuBackButton : public PushButton {
public:
    CtrlMenuBackButton() {
        bmgId = 0x7d1;
        unknown_0x258 = 0;
        alpha = 0.0f;
    }; //inlined but defined so it can be inherited from 
    ~CtrlMenuBackButton() override; //805be7f4 vtable 808d374c
    void InitSelf() override; //0x18 807e93b8
    void OnUpdate() override; //0x1c 807e9270
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 807e9410
    int GetRuntimeTypeInfo() const override; //0x28 807e9c04
    const char *GetClassName() const override; //0x2c 807e9214
    void SetPlayerBitfield(); //807e9610
    u32 bmgId; //0x254
    u32 unknown_0x258;
    float alpha;
    char *pane;
}; //total size 0x264
size_assert(CtrlMenuBackButton, 0x264);

class CtrlMenuDummyBack : public LayoutUIControl {
    ~CtrlMenuDummyBack() override; //80603890
    void OnUpdate() override; //0x1c 807e9724
    int GetRuntimeTypeInfo() const override; //0x28 807e9bf8
    const char *GetClassName() const override; //0x2c 807e9220
    u8 unknown_0x174[0x18c - 0x174];
};
size_assert(CtrlMenuDummyBack, 0x18c);
#endif