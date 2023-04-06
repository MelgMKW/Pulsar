#ifndef _MANIPULATOR_
#define _MANIPULATOR_
#include <kamek.hpp>
#include <core/egg/egg.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/Input/inputdata.hpp>

class ControlManipulator;

enum Action { //each value represent an action, itself represented by an actionHandler in PushButton's pageElementActionHolder and a bool in the same struct 
    FORWARD_PRESS,
    BACK_PRESS,
    START_PRESS,
    UP_PRESS,
    DOWN_PRESS,
    LEFT_PRESS,
    RIGHT_PRESS,
    UNK_PRESS,
    SWITCH_PRESS, //minus and Z
    UNK_PRESS_0x9 = 0x9
};

class ButtonInfo {
public:
    ButtonInfo(); //inlined for pageactionHandler, 805eee24 for pages
    virtual ~ButtonInfo(); //805eeed0 vtable 808b9a80
    virtual void Reset();  //0xc 805eef10, calls reset
    virtual void Update(ControllerHolder *controllerHolder); //0x10 805eef20
    virtual void Init(); //0x14 805ef138
    u32 forwardPressTime; //0x4 2 or A
    u32 backPressTime; //0x8 1 or B
    u32 startPressTime; //0xc + or start
    u32 upPressTime; //0x10
    u32 downPressTime; //0x14
    u32 leftPressTime; //0x18
    u32 rightPressTime; //0x1c
    u32 unknown_0x20; //0x20
    u32 spectateSwitchPressTime; //0x24 - + x + z
    bool buttonHeld[9]; //0x28set to true if button is held
    u8 unknown_0x31[3]; //padding
}; //total size 0x34
size_assert(ButtonInfo, 0x34);

class ControlButtonInfo : public ButtonInfo {
public:
    ControlButtonInfo(); //805ef780 always inlined
    ~ControlButtonInfo() override; //805ef848 vt 808b9a30 at 0x8
    void Reset() override;  //0xc 805ef888, calls reset
    void Update(ControllerHolder *controllerHolder) override; //0x10 805ef898
    void Init() override; //0x14 805ef958
    u32 framesToNextAction; //0x34, almost certainly wrong
    u32 framesOnCurControl; //0x38
    bool isPointerActive; //0x3c
    u8 unknown_0x3D[3]; //padding?
    Vec2 pointerPosition;
    bool enabled; //if this control button info is taking inputs
    u8 unknown_0x49[3]; //padding?
    ControlManipulator *childManipulator; //set by controls that have children like RadioControl or TabControl
    u8 unknown_0x50[0x54 - 0x50];
};//0x54
size_assert(ControlButtonInfo, 0x54);

class ControlManipulatorHolder { //holds an action holder
public:
    ControlManipulatorHolder(); //805f0a98
    ~ControlManipulatorHolder(); //805f0b94

    ControlManipulator *curManipulator;
    u32 curChildId; //for controls that have children like RadioControl or TabControl
    ControlButtonInfo info; //0xC
}; //total size 0x5C
size_assert(ControlManipulatorHolder, 0x5C);

class ManipulatorManager { //PARENT
public:
    ManipulatorManager(); //805eeb68  808b9a98
    virtual int GetRuntimeTypeInfo() const; //805bd704 vtable 0x808b9a98
    virtual ~ManipulatorManager(); //805eeb8c
    virtual void Init(u32 localPlayerBitfield, bool isMultiplayer); //0x10 805eebcc r4 related to inputs
    virtual void *GetHolderList() const; //805f2cf4, just a blr as no list
    virtual void CheckActions(); //0x18 805eec58
    virtual void Activate(u32 hudSlotId, u32 localPlayerBitfield2, bool isMultiplayer); //805eec5c
    virtual void OnDeactivate(bool isMultiplayer); //0x20 805eece8
    virtual void OnReset(); //0x24 805eed84
    virtual void OnActivate(); //0x28 805f2cf0
    virtual void Update(); //0x2c 805eed98 checks controller type but does nothing with it
    virtual bool IsPointerEnabled(); //0x30 805f2ce8 returns false which then disables wii pointer?
    virtual bool CheckPlayerPointer(); //805cedc4

    void UpdatePlayerBitfield2(u32 localPlayerBitfield); //0x805eec50
    void Load(); // 805eed70

    u32 activeLocalPlayerBitfield; //0x4 if bit i is set then local player i's inputs work    
    u32 localPlayerBitfield; //0x8

    bool inaccessible; //0xC if set to true, actions are blocked
    bool isMultiplayer;
    u8 unknown_0xE[0x10 - 0xE]; //padding?
    static ControllerHolder *GetControllerHolder(u8 id); //805eee0c
};//total size 0x10
size_assert(ManipulatorManager, 0x10);

class PageManipulatorManager : public ManipulatorManager { //sets actions for page, equivalent to ControlsManipulatorManager but for pages 80601d04 checks actions
public:
    PageManipulatorManager(); //805ef240
    int GetRuntimeTypeInfo() const override; //0x805f2cf8 vtable 808b9a48
    ~PageManipulatorManager() override; //0xc 805ef2fc
    void Init(u32 localPlayerBitfield, bool isMultiplayer) override; //0x10 805ef364
    void CheckActions() override; //0x18 805ef43c
    void Activate(u32 hudSlotId, u32 localPlayerBitfield2, bool isMultiplayer) override; //805ef5a8
    void OnReset() override; //0x24 805ef688
    void SetGlobalHandler(Action input, PtmfHolder_1A<Page, void, u32> *handler, bool isTriggered); //805ef768
    PtmfHolder_1A<Page, void, u32> *globalHandlers[9]; //0x10 805f15cc, first arg is buttin info id
    bool isTriggered[9]; //0x34
    u8 unknown_0x3D[3]; //padding
    ButtonInfo buttoninfoArray[5]; //0x40 5th corresponds to inputdata's dummy controller
}; //Total Size 0x144
size_assert(PageManipulatorManager, 0x144);

enum Directions {
    DIRECTION_NONE,
    DIRECTION_UP = 0x1,
    DIRECTION_DOWN = 0x2,
    DIRECTION_RIGHT = 0x4,
    DIRECTION_LEFT = 0x8,
};
class ControlsManipulatorManager : public ManipulatorManager { //contains multiple action handlers, tied to a page
public:
    ControlsManipulatorManager(); //805f09a8
    int GetRuntimeTypeInfo() const override; //805f2cdc vtable 0x808b99e8
    ~ControlsManipulatorManager() override; //805f0bd4
    void Init(u32 localPlayerBitfield, bool isMultiplayer) override; //0x10 805f0c48
    void *GetHolderList() const override; //805f0e30
    void CheckActions() override; //0x18 805f0e94
    void Activate(u32 hudSlotId, u32 localPlayerBitfield2, bool isMultiplayer) override; //805f1bc0
    void OnDeactivate(bool isMultiplayer) override; //805f1cf4 //0x20
    void OnReset() override; //0x24 805f1e14
    void OnActivate() override; //0x28 805f1f3c
    void Update() override; //805f1f40 0x2c y
    bool IsPointerEnabled() override; //805f2cd4 returns true, maybe means pointer is enabled?
    bool CheckPlayerPointer() override; //805f22d4

    //Most funcs are inlined
    void AddControlManipulator(ControlManipulator *manipulator); //805f0d44 adds it to the list
    void SetGlobalHandler(Action id, PtmfHolder_1A<Page, void, u32> *handler, bool repeatable, bool ispointerDisabled); //805f0d84
    void SetControlManipulator(u32 hudSlotId, ControlManipulator *manipulator, u32 childId); //805f0da0, for initial selected control
    void SetChildControlManipulator(u32 hudSlotId, ControlManipulator *child, u32 childId); //805f20ec
    void SetDistanceFunc(u32 type); //805f0db4 0x2 = all wrapping 0x3 = no wrapping
    void InitHolders(u8 hudSlotId, bool enabled); //805f2100
    bool IsActionAllowed(u8 holderId); //805f2134
    bool HasDirectionalGlobalHandler(u8 directions); //805f216c 1,2,8,4 for up, down, left, right, can call it with an or of directions
    bool func_805f21e4(u8 holderId); //weird
    bool func_805f226c(u8 hudSlotId, u8 r5);

    EGG::List manipulatorsList; //0x10
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> *globalHandlers[9]; //805f15cc, applies to all controls
    bool repeatable[9]; //the input triggers the action every 15 frames if this is set to true and the action doesn't change the curManipulator
    bool isPointerDisabled[9];
    u8 unknown_0x52[2]; //padding?
    ControlManipulatorHolder holders[5]; //0x54, 5th corresponds to inputdata's dummy controller
    int (*calcDistanceFunc)(ControlManipulator *subject, ControlManipulator *other, Directions direction,
        bool hasHorizontalWrapping, bool hasVerticalWrapping); //0x220
};//total size 0x224
size_assert(ControlsManipulatorManager, 0x224);

class ControlBoundingBox {
public:
    ControlBoundingBox(); //805f058c
    ~ControlBoundingBox(); //805f05cc
    void CalculateBounds(); //805f0618
    bool TriggerOnSelectHandler(u8 hudSlotId); //805f08a0 inlined, returns false if no handler
    bool TriggerOnDeselectHandler(u8 hudSlotId); //805f08f0 inlined, returns false if no handler

    nw4r::lyt::Pane *touchPane; //0
    Vec3 boundingBoxOrigin; //0x4
    Vec2 boundingBoxSize; //0x10
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> *onSelectControlHandler;  //0x18 tied to control's handleSelect
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> *onDeselectControlHandler; //0x1C
    u32 childId; //-1 if not in the array
    u8 bool_0x24; //0x24, unsure 8063ffd8
    u8 padding[3];
}; //total size 0x28
size_assert(ControlBoundingBox, 0x28);

class ControlManipulator {
public:
    ControlManipulator(); //805efaf8 
    nw4r::ut::LinkListNode link;
    virtual ~ControlManipulator(); //805efbd4 vtable 808b9a20
    void Init(u32 childCount, bool r5, bool inaccessible); //805efc48
    void SetAction(Action id, PtmfHolder_2A<LayoutUIControl, void, u32, u32> *handler, bool repeatable); //805efcf8
    void SetEnabledHudSlots(u32 localPlayerBitfield); //805efd14
    bool HasDirectionalHandler(u8 directions); //805efdc8 1,2,8,4 for up, down, left, right, can call it with an or of directions
    bool TriggerAction(Action actionId, u8 hudSlotId, u32 childId); //805efe40 (inlined at 805f19ac) childId refers to the childcontrol (like a radio button) whose action is triggered   
    void Load(); //805efef4
    void Update(); //805f0040
    void GetHudColor(RGBA16 *primary, RGBA16 *secondary) const; //805f03dc
    void GetHudSlotIdColorSingle(u8 hudSlotId, RGBA16 *out) const; //805f04d8
    int CalcDistanceBothWrapping(ControlManipulator *other, Directions direction); //805f0d38 calls calcdistance with true, true
    int CalcDistanceVerticalWrappingOnly(ControlManipulator *other, Directions direction); //805f0e18 calls calcdistance with false, true
    int CalcDistanceNoWrapping(ControlManipulator *other, Directions direction); //805f0e24 calls calcdistance with false, false
    int CalcDistance(ControlManipulator *other, Directions direction, bool hasHorizontalWrapping, bool hasVerticalWrapping); //mode: 0 returns 0, 1 only up, 2 both
    int CalcDistanceLinear(ControlsManipulatorManager *otherController, Directions direction); //0x805f2948
    static void GetHudSlotIdColor(u8 hudSlotId, RGBA16 *primary, RGBA16 *secondary); //805f0440

    ControlBoundingBox boundingBox; //0xC
    ControlBoundingBox *childrenControlsBoundingBoxArray; //805efc98 array here 0x34
    u32 childrenBoundingBoxCount; //0x38
    ControlsManipulatorManager *parentManager; //0x3c
    PtmfHolder_2A<LayoutUIControl, void, u32, u32> *actionHandlers[9]; //each corresponds to an Action, size based on ctor
    bool repeatable[9]; //same
    u8 unknown_0x6D[3]; //padding?
    u32 enabledHudSlotsBitfield; //if bit i is set, listens to play i
    bool unknown_0x74; //r5 from init
    bool inaccessible; //0x75
    u8 unknown_0x76[2]; //padding?
    u32 allowedPlayerId; //0 in single, else 1 2 3 4 (5 is everyone is allowed to select the control)
    u32 activeFrames; //probably same thing as above
    u32 distance; //converted from a float
}; //total size 0x84
size_assert(ControlManipulator, 0x84);
#endif