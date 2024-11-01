/*
Credits:
kHacker35000vr and the Sanbo team (dolphin map, PageText)
stebler (names for some of the classes)
Melg
*/

#ifndef _GHOSTRANKINGSPAGE_
#define _GHOSTRANKINGSPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <MarioKartWii/UI/Ctrl/UpDown.hpp>

enum RankingType {
    FRIEND,
    CONTINENTAL,
    WORLDWIDE,
};

class RankingItemSelector {
public:
    virtual ~RankingItemSelector(); //806199fc vtable 808bb430
    virtual float vf_0x10() = 0;
    void SetParams(u32 r4, RankingItem* array, u32 itemCount); //80619a58
    u32 r4;
    RankingItem* array; //0x34
    u32 itemCount; //0x38
    Random random; //0xa8
}; //0xc0

class RankingItemSelectorTA : public RankingItemSelector {
public:
    RankingItemSelectorTA(); //8061aba0
    ~RankingItemSelectorTA() override; //8061abec vtable 808bb410
    float vf_0x10(); //8061adfc
};
class RankingRuler : public LayoutUIControl {
public:
    RankingRuler(); //80619114
    ~RankingRuler() override; //80619150 vtable 808bb270
    void InitSelf() override; //0x18 8061921c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80619908
    const char* GetClassName() const override; //0x2c 80619104
    void Load(); //806191a8
}; //0x174

class RankingItem : public LayoutUIControl {
public:
    enum State {
        DISABLED,
        WILL_ACTIVATE,
        ANIMATING_FOR_ACTIVATION,
        ACTIVATED,
        DISAPPEARING,
    };
    enum Type {
        PERSONAL_BEST, //yellow
        OTHER_TIME, //blue

        TOP_10 = 6,
        STRANGER = 8,
    };
    ~RankingItem() override; //806169f0 vtable 808bb398
    void OnUpdate() override; //0x1c 80616c24
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 8061992c
    const char* GetClassName() const override; //0x2c 80616994
    virtual void Disable(); //0x3c 806170c4
    virtual void Enable(); //0x40 806170d8
    virtual void Appear(); //0x44 806170ec
    virtual void MakeAccessible(); //0x48 806171f0
    virtual void Disappear(); //0x4c 806171f4
    virtual void vf_0x50() = 0; //0x50 
    virtual void vf_0x54() = 0; //0x54 
    virtual void vf_0x58() = 0; //0x58 
    virtual void vf_0x5c() = 0; //0x5c 
    virtual void vf_0x60() = 0; //0x60 
    virtual void vf_0x64() = 0; //0x64 

    void FinishLoad(Type type, u32 r5, u32 idx); //80616a48
    Type type; //0x174 type?
    u32 loadr5; //0x178
    u32 idx; //0x17c
    State state; //0x180
    u32 unknown_0x180[2]; //0x180
    RankingGraphControl* graphParent; //0x188
    lyt::Pane* null_all; //0x18c
    u8 unknown_0x174[0x1b4 - 0x174]; //0x174
};

class RankingItemSelectable : public RankingItem {
public:
    RankingItemSelectable(); //806173b8
    ~RankingItemSelectable() override; //806174cc vtable 808bb318
    void InitSelf() override; //0x18 8061799c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80619920
    const char* GetClassName() const override; //0x2c 806173a8
    void Disable() override; //0x3c 80617a30
    void Enable() override; //0x40 80617a4c
    void MakeAccessible() override; //0x48 80617f64
    void Disappear() override; //0x4c 80617f80 disables via animation, used when switching tracks/ranking type
    void vf_0x50() override; //0x50 80617fb8
    void vf_0x54() override; //0x54 80617fd4
    void vf_0x58() override; //0x58 80617fec
    void vf_0x5c() override; //0x5c 80618004
    void vf_0x60() override; //0x60 80618020
    void vf_0x64() override; //0x64 806182ec

    void Load(Type type, u32 r5, u32 idx); //8061753c
    void OnSelect(u32 hudSlotId, u32 r5); //806182f0
    void OnDeselect(u32 hudSlotId, u32 r5); //80618aec
    void OnClick(u32 hudSlotId, u32 r5); //80618c50

    ControlManipulator controlManipulator; //0x1b4
    PtmfHolder_3A<RankingItemSelectable, void, UpDownControl&, u32, u32> onSelectHandler; //0x238 806182f0
    PtmfHolder_3A<RankingItemSelectable, void, UpDownControl&, u32, u32> onDeselectHandler; //0x24c 80618aec
    PtmfHolder_3A<RankingItemSelectable, void, UpDownControl&, u32, u32> onClickHandler; //0x260 80618c50
}; //0x274

class RankingItemStranger : public RankingItem {
public:
    RankingItemStranger(); //80618f2c
    ~RankingItemStranger() override; //80618f88 vtable 808bb2b0
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80619914
    const char* GetClassName() const override; //0x2c 80618f1c
    void Enable() override; //0x40 8061907c
    void vf_0x50() override; //0x50 806190ac
    void vf_0x54() override; //0x54 806190c8
    void vf_0x58() override; //0x58 806190e0
    void vf_0x5c() override; //0x5c 806190f8
    void vf_0x60() override; //0x60 806190fc
    void vf_0x64() override; //0x64 80619100
    void Load(Type type, u32 r5, u32 idx); //80618fe4
};

class RankingWindow : public LayoutUIControl {
public:
    RankingWindow(); //80619434
    ~RankingWindow() override; //80619470 vtable 808bb234
    void InitSelf() override; //0x18 80619638
    void OnUpdate() override; //0x1c 80619644
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 806198fc
    const char* GetClassName() const override; //0x2c 80619424
    u8 unknown_0x174[4];
}; //0x178

class RankingGraphControl : public LayoutUIControl {
public:
    RankingGraphControl(); //80611878 inlined
    ~RankingGraphControl() override; //806118f0 vtable 808baf68
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80615014
    const char* GetClassName() const override; //0x2c 8061186c
    virtual void Load() = 0; //0x3c
    virtual RankingWindow* GetWindow(RankingItem::Type itemType) = 0; //0x40
    virtual void DisplayItems() = 0; //0x44
    virtual void DisableAllItems() = 0; //0x48

    void LoadAssets(); //80611990 gets inlined in the Load vf
    MiiGroup miiGroup; //0x174
    LayoutUIControl control; //0x20c
    RankingRuler rulers[6]; //0x380
    u8 unknown_0xc38[4];
    RankingType selRankingType; //0xc3c
    u8 unknown_0xc40[4];
    RankingItem* displayedItems; //0xc44 array of size 239 for TA since that's the total number of rankingitems
    u32 totalItemCount; //0xc48
    u8 unknown_0xc4c[0xc54 - 0xc4c];
};//0xc54

class RankingGraphControlTimeAttack : public RankingGraphControl {
public:
    RankingGraphControlTimeAttack(); //806123c8
    ~RankingGraphControlTimeAttack() override; //8061250c vtable 808baf1c
    void InitSelf() override; //0x18 80612a68
    void OnUpdate() override; //0x1c 80612a8c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80615008
    const char* GetClassName() const override; //0x2c 806123b8
    void Load() override; //0x3c 8061267c
    RankingWindow* GetWindow(RankingItem::Type itemType) override; //0x40 80612a90
    void DisplayItems() override; //0x44 80612c3c
    void DisableAllItems() override; //0x48 80612c9c

    void UpdateImpl(); //80611a3c
    void DisplayItemsOnlineRankings(); //806138a4
    void DisplayItemsFriendsRankings(); //80612dbc

    RankingItemSelectable pbWindow[4]; //0xc54 one for each license
    RankingItemSelectable itemSelectable2[30]; //0x1624
    RankingItemSelectable itemSelectable3; //0x5fbc
    RankingItemSelectable itemSelectable4; //0x6230
    RankingItemSelectable itemSelectable5; //0x64a4
    RankingItemSelectable itemSelectable6; //0x6718
    RankingItemSelectable itemSelectable7; //0x698c
    RankingItemStranger fillerItems[200]; //0x6c00
    RankingWindow pbWindow; //0x1c0a0
    RankingWindow otherTimeWindow; //0x1c218
    RankingWindow top10Window; //0x1c390
    RankingWindow window4; //0x1c508
    void* dummyDistributionMapBin; //0x1c80
}; //0x1c680

namespace Pages {


class RankingGraph : public Page { //ID 0xA8, also 0xA9
public:

    static const PageId pageId = PAGE_COURSE_RANKING_GRAPH;
    RankingGraph(); //806153b4
    ~RankingGraph() override; //80615650 vtable 808bb034
    PageId GetNextPage() const override; //0x10 80616700
    void OnInit() override; //0x28 80615738
    void OnDispose() override; //0x2c 80615bd8
    void OnActivate() override; //0x30 80615c8c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80616708
    void OnButtonClick(PushButton& button, u32 hudSlotId); //805c18a4
    void OnButtonSelect(PushButton& button, u32 hudSlotId); //805c1ad0
    void OnBackPress(u32 hudSlotId); //805c1b24

    void OnTAUpDownChange(UpDownControl* control, u32 hudSlotId, u32 optionId); //80615f4c
    void OnTAUpDownClick(UpDownControl* control, u32 hudSlotId); //80615f68
    void OnTATextChange(TextUpDownValueControl::TextControl* control, u32 hudSlotId); //80615fb4
    void OnCompetitionUpDownChange(UpDownControl* control, u32 hudSlotId, u32 optionId); //80616038
    void OnCompetitionTextChange(TextUpDownValueControl::TextControl* control, u32 hudSlotId); //80616054
    void OnRankingTypeUpDownChange(UpDownControl* control, u32 hudSlotId, u32 optionId); //80616180
    void OnRankingTypeTextChange(TextUpDownValueControl::TextControl* control, u32 hudSlotId); //806162a4
    void OnBackButtonClick(u32 hudSlotId); //806162b4
    void OnBackPress(u32 hudSlotId); //80616300
    void SetBottomText(u32 bmgId, Text::Info* info = nullptr); //80616320


    PtmfHolder_3A<RankingGraph, void, UpDownControl&, u32, u32> onTAUpDownChangeHandler; //0x44 80615f4c
    PtmfHolder_2A<RankingGraph, void, UpDownControl&, u32> onTAUpDownClickHandler; //0x58 80615f68
    PtmfHolder_2A<RankingGraph, void, TextUpDownValueControl::TextControl&, u32> onTATextChangeHandler; //0x6c 80615fb4
    PtmfHolder_3A<RankingGraph, void, UpDownControl&, u32, u32> onCompetitionUpDownChangeHandler; //0x80 80616038
    PtmfHolder_2A<RankingGraph, void, TextUpDownValueControl::TextControl&, u32> onCompetitionTextChangeHandler; //0x94 80616054

    PtmfHolder_3A<RankingGraph, void, UpDownControl&, u32, u32> onRankingTypeUpDownChangeHandler; //0xa8 80616180
    PtmfHolder_2A<RankingGraph, void, TextUpDownValueControl::TextControl&, u32> onRankingTypeTextChangeHandler; //0xbc 806162a4

    PtmfHolder_2A<RankingGraph, void, PushButton&, u32> onBackButtonClickHandler; //0xd0 806162b4
    PtmfHolder_1A<RankingGraph, void, u32> onBackPressHandler;  //0xe4 80616300
    ControlsManipulatorManager controlsManipulatorManager; //0xf8
    UpDownControl TAOrCompetitionArrows; //0x31c
    TextUpDownValueControl courseText; //0x8e4
    UpDownControl rankingTypeArrows; //0xd58
    TextUpDownValueControl rankingTypeText; //0x1320
    RankingGraphControl* graph; //0x1794
    CtrlMenuBackButton backButton; //0x1798
    CtrlMenuInstructionText bottomText; //0x19fc
    PageId nextPage; //0x1b70
    RankingType selRankingType; //0x1b74
    CourseId curSelCourseId; //0x1b78
    CourseId TAupDownCourseIds[32]; //0x1b7c
    u32 upDownCompetitionIds[10]; ///0x1bfc
    u8 unknown_0x1c24[4];
}; //0x1c28

}//namespace Pages

#endif