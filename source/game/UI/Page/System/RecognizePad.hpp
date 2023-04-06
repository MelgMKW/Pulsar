#ifndef _RECOGNIZEPAD_
#define _RECOGNIZEPAD_
#include <kamek.hpp>
#include <game/UI/Page/System/System.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>


//_sinit_ at 80601958
class PadControl : LayoutUIControl {
    PadControl(); //806012bc
    ~PadControl() override; //806012f8 808ba4f8
    void InitSelf() override; //80601410 0x18
    void OnUpdate() override; //8060147c 0x1c
    int GetRuntimeTypeInfo() const override; //0x28 8060194c
    const char *GetClassName() const override; //0x2c 806012b0
    void Load(const char *folderName, const char *ctrName, const char *variant, u32 hudSlotId, u8 team, u32 unknown_0x180, u32 padSlotAndType); //80601350
    u32 hudSlotId;
    u32 padSlotAndType; //0x178
    u8 team; //0x17c colours the controller frame
    u8 padding[3];
    u32 unknown_0x180; //if set to 2, controller image disappears
}; //total size 0x184
size_assert(PadControl, 0x184);

class RecognizePadWindow : public LayoutUIControl {
    RecognizePadWindow(); //806017e4
    ~RecognizePadWindow() override; //80601820
    void InitSelf() override; //806018f4 0x18
    void OnUpdate() override; //806018f8 0x1c
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //806018fc 0x20
    int GetRuntimeTypeInfo() const override; //0x28 80601934
    const char *GetClassName() const override; //0x2c 806017d4
    void Load(const char *folderName, const char *ctrName, const char *variant); //80601878
};

namespace Pages {
class RecognizePad : public System {

    RecognizePad(); //8061bffc always inlined
    ~RecognizePad() override; //8061c058 vtable 808bb594
    void OnInit() override; //0x28 8061c0d8
    void OnActivate() override; //0x30 8061c1c0
    void OnDeactivate() override; //0x34 8061c288
    void BeforeEntranceAnimations() override; //0x38 8061c384
    void AfterExitAnimations() override; //0x44 8061c3c8
    void AfterControlUpdate() override; //0x4c 8061c2e4
    int GetRuntimeTypeInfo() const override; //0x60 8061d1e0
    bool CheckForConditions() override; //0x64 8061c40c checks if controller has been disconnected obviously
    bool isVisible() override; //0x68 8061c518
    PadControl padControl; //0x44
    RecognizePadWindow recognizePadWindow; //0x1c8
    BlackBackControlForMessage background; //0x33c
    u32 hudSlotId; //0x4b0
    bool isMultiplayer; //0x4b4
    u8 padding[3];
    u32 padSlotAndType; //0x4b8
    u32 unknown_0x4bc; //type? setting it to 4 auto clicks A
};//total size 0x4c0
size_assert(RecognizePad, 0x4c0);

class RecognizePadMenu : public RecognizePad {
    RecognizePadMenu(); //8061c53c
    ~RecognizePadMenu() override; //8061c5a4 vtable 808bb528
    const char *GetClassName() const override; //8061d1c8 0xc
    bool IsDVDEnabled() override; //8061c86c 0x18
    void BeforeEntranceAnimations() override; //0x38 8061c628
    void AfterEntranceAnimations() override; //0x3c 8061c720
    void BeforeExitAnimations() override; //0x40 8061c76c
    void AfterExitAnimations() override; //0x44 8061c780
    void BeforeControlUpdate() override; //0x48 8061c7c4
    int GetRuntimeTypeInfo() const override; //8061d1d4
}; //0x4c0
}//namespace Pages

#endif