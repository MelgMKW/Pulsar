#ifndef _SHEETSELECT_
#define _SHEETSELECT_
#include <kamek.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
//_sinit_ at 806374e8

class SheetSelectControl : public UIControl { //arrowpair
public:
    class SheetSelectButton : public LayoutUIControl { //select is equivalent to clicking for these
    public:
        SheetSelectButton(); //inlined but at 80636470
        ~SheetSelectButton() override; //0x80636564 vtable 0x808be998
        void Init() override; //0xc 806367f8 
        void Update() override; //0x10 806369e4
        void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 80637344
        int GetRuntimeTypeInfo() const override; //0x28 806374ac
        const char *GetClassName() const override; //0x2c 80636460
        void Load(u32 buttonId, const char *folderName, const char *ctrName, const char *variant, const char **anims, bool r8, bool inaccessible); //806365cc
        void HandleSelect(u32 hudSlotId); //80636d08
        void AfterSelect(u32 hudSlotId); //806371ac
        void SetEnabledHudSlots(u32 playerBitField); //80636c2c
        void Toggle(bool enabled); //80636c48
        void Select(u32 hudSlotId); //806371ac
        static void Trigger2APtmf(PtmfHolder_2A<LayoutUIControl, void, u32, u32> *handler, u32 hudSlotId, u32 childId); //806374b8
        SheetSelectControl *GetParentControl() const; //80636c6c
        ControlManipulator manipulator;
        PtmfHolder_2A<LayoutUIControl, void, u32, u32> onSelectHandler; //vtable = 0x808be9d4 function = 80636d08
        PtmfHolder_2A<LayoutUIControl, void, u32, u32> onDeselectHandler; //vtable = 0x808be9d4 function = 80636fc4 0x20C
        PtmfHolder_2A<LayoutUIControl, void, u32, u32> onScrollHandler; //vtable = 0x808be9d4 function = 806371ac
        u32 buttonId; //0x234 0x0 for left, 0x1 for right
        u32 localPlayerBitfield; //copied straight from arrowpaircontrol
        bool enabled;
        u8 unknown_0x23d[0x240 - 0x23d]; //might be padding
        u32 *fuchi_pattern;
        u32 *rootPane;
    }; //total size 0x248
    SheetSelectControl(); //80635ec4 
    ~SheetSelectControl() override; //8063607c vtable 0x808be950
    void Init() override; //806362e8
    int GetRuntimeTypeInfo() const override; //0x28 806374a0
    const char *GetClassName() const override; //0x2c 80635eb8
    virtual void func_0x38(); //0x38 806361e4 just a blr
    virtual void AfterRightScroll(); //0x3c 806363d4 just a blr
    virtual void AfterLeftScroll(); //0x40 8063645c just a blr
    virtual int GetArrowAnimationType() const; //0x44 80637474 returns 0, if changed to 1 the arrows pop instead of sliding to the sides
    void Load(const char *folderName, const char *rightArrowctrName, const char *rightArrowVariantName,
        char *leftArrowctrname, const char *leftArrowVariantName, u32 localPlayerBitfield, bool r10, bool inaccessible); //80636120
    void SetRightArrowHandler(PtmfHolder_2A<Page, void, SheetSelectControl *, u32> *handler); //806361e8
    void SetLeftArrowHandler(PtmfHolder_2A<Page, void, SheetSelectControl *, u32> *handler); //806361f0
    void HandleRightArrowSelect(u32 hudSlotId); //80636350 inlined triggers ptmf at 0x98
    void HandleLeftArrowSelect(u32 hudSlotId); //806363d8 inlined
    void SetEnabledHudSlots(u32 playerBitfield); //806361f8 inlined?
    void Toggle(u32 playerBitfield, bool enabled); //80636264
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> *rightArrowHandler; //0x98
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> *leftArrowHandler; //0x9C
    u32 localPlayerBitfield;
    u8 unknown_0xA4[0xa8 - 0xa4];
    SheetSelectButton rightArrow; //0xa8
    SheetSelectButton leftArrow;
}; //total size 0x538
size_assert(SheetSelectControl, 0x538);
size_assert(SheetSelectControl::SheetSelectButton, 0x248);

class SheetSelectControlScaleFade : public SheetSelectControl {
public:
    //no ctor
    ~SheetSelectControlScaleFade() override; //805dbfdc vtable 808BE908
    int GetRuntimeTypeInfo() const override; //0x28 80637494
    const char *GetClassName() const override; //0x2c 8063747c
    int GetArrowAnimationType() const override; //0x44 8063748c
};
#endif