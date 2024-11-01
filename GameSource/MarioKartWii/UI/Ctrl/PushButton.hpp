#ifndef _PUSHBUTTON_
#define _PUSHBUTTON_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/Manipulator.hpp>

/*
Contributors:
-stebler, kHacker35000vr, Melg
*/

//_sinit_ at 805be64c
class PushButton : public LayoutUIControl {
public:
    PushButton(); //805bd3a8
    ~PushButton() override; //805bd4b0 vtable 808B776C
    void Init() override; //0xc 805bdbe0
    void Update() override; //0x10 805bdd98
    //virtual void Draw(); //0x14 8063dd84
    //virtual void InitSelf(); 0x18 805be600
    //virtual void OnUpdate(); 0x1c 805bd2e0
    //virtual void SetPositionAnim(PositionAndScale &positionAndScale, float curFrame); 0x20  8063d194
    //virtual void func_805bd2dc(); 0x24 805bd2dc
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805be610
    const char* GetClassName() const override; //0x2c 805bd39c
    //virtual void func_0x30(); //called PAGE_buttonHolder 0x30 8063e61c
    //virtual void func_0x34(); 0x34 805bd2d8
    //virtual void LoadNewLayout(char *folderName, const char*lytName); //0x38 8063d954 unused, ControlLoader does it
    virtual void OnDeactivate(); //0x3c 805bd710
    virtual void OnSelect(u32 hudSlotId, u32 r5); //0x40 805be12c
    virtual void OnDeselect(u32 hudSlotId, u32 r5); //0x44 805be354
    virtual void OnClick(u32 hudSlotId, u32 r5); //0x48 805be42c
    void SelectInitial(u32 hudSlotId); //805bdaf0
    void SelectFocus();
    void Select(u32 hudSlotId);

    //Adds Loop, Select, SelectIn and Ok groups to the anims array
    void LoadWithAnims(const char** newAnims, const char* folderName, const char* ctrName,
        const char* variant, u32 localPlayerBitfield, u32 r8); //805bd720
    void Load(const char* folderName, const char* ctrName, const char* variant, u32 localPlayerBitfield, u32 r8, bool inaccessible); //805bd518
    void SetOnClickHandler(const PtmfHolder_2A<Page, void, PushButton&, u32>& handler, u8 r5);
    void SetOnSelectHandler(const PtmfHolder_2A<Page, void, PushButton&, u32>& handler); //805bdae0
    void SetOnDeselectHandler(const PtmfHolder_2A<Page, void, PushButton&, u32>& handler); //805bdae8

    float GetAnimationFrameSize() const; //805bdf88
    void HandleSelect(u32 hudSlotId, u32 r5); //805bdffc
    void HandleDeselect(u32 hudSlotId, u32 r5); //805be130
    void HandleClick(u32 hudSlotId, u32 r5); //805be358
    void SetPlayerBitfield(u32 bitField); //805bdbd4
    bool IsSelected() const; //805bdf44

    ControlManipulator manipulator; //0x174
    PtmfHolder_2A<PushButton, void, u32, u32> onSelectHandlerObj; //0x1F8
    PtmfHolder_2A<PushButton, void, u32, u32> onDeselectHandlerObj; //0x20C
    PtmfHolder_2A<PushButton, void, u32, u32> onClickHandlerObj; //0x220
    const PtmfHolder_2A<Page, void, PushButton&, u32>* onClickHandler; //0x234
    const PtmfHolder_2A<Page, void, PushButton&, u32>* onSelectHandler; //0x238
    const PtmfHolder_2A<Page, void, PushButton&, u32>* onDeselectHandler; //0x23C
    s32 buttonId; //0x240
    u32 localPlayerBitfield; //0x244
    nw4r::lyt::Pane* fuchi_pattern; //0x248
    nw4r::lyt::Pane* color_base; //0x24c
    u32 clickSoundId;
};//Total Size 0x254
size_assert(PushButton, 0x254);

class PushButtonScaleFade : public PushButton {
public:
    PushButtonScaleFade(); //805be448
    ~PushButtonScaleFade() override; //805be55c vtable 808b7720
    void SetPositionAnim(PositionAndScale& positionAndScale, float curFrame) override; //0x20 805be5c8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805be604
    const char* GetClassName() const override; //0x2c 805be438
};

#endif