/*
InputData is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#ifndef _INPUTDATA_
#define _INPUTDATA_
#include <kamek.hpp>
#include <game/File/KRM.hpp>
#include <game/System/Ghost.hpp>
#include <game/System/Identifiers.hpp>


enum Buttons {
    WHEEL_DPAD_LEFT = 0x1,
    WHEEL_DPAD_RIGHT = 0x2,
    WHEEL_DPAD_DOWN = 0x4,
    WHEEL_DPAD_UP = 0x8,
    WHEEL_A = 0x800,
    WHEEL_B = 0x400,
    WHEEL_MINUS = 0x1000,
    WHEEL_PLUS = 0x10,
    WHEEL_HOME = 0x8000,
    WHEEL_1 = 0x200,
    WHEEL_2 = 0x100,

    NUNCHUCK_DPAD_LEFT = 0x1,
    NUNCHUCK_DPAD_RIGHT = 0x2,
    NUNCHUCK_DPAD_DOWN = 0x4,
    NUNCHUCK_DPAD_UP = 0x8,
    NUNCHUCK_A = 0x800,
    NUNCHUCK_B = 0x400,
    NUNCHUCK_MINUS = 0x1000,
    NUNCHUCK_PLUS = 0x10,
    NUNCHUCK_HOME = 0x8000,
    NUNCHUCK_1 = 0x200,
    NUNCHUCK_2 = 0x100,
    NUNCHUCK_C = 0x4000,
    NUNCHUCK_Z = 0x2000,

    CLASSIC_DPAD_LEFT = 0x2,
    CLASSIC_DPAD_RIGHT = 0x2000,
    CLASSIC_DPAD_DOWN = 0x4000,
    CLASSIC_DPAD_UP = 0x1,
    CLASSIC_A = 0x10,
    CLASSIC_B = 0x40,
    CLASSIC_X = 0x8,
    CLASSIC_Y = 0x20,
    CLASSIC_MINUS = 0x1000,
    CLASSIC_PLUS = 0x40,
    CLASSIC_HOME = 0x800,
    CLASSIC_L = 0x2000,
    CLASSIC_R = 0x200,
    CLASSIC_ZL = 0x80,
    CLASSIC_Z = 0x4,

    GCN_DPAD_LEFT = 0x1,
    GCN_DPAD_RIGHT = 0x2,
    GCN_DPAD_DOWN = 0x4,
    GCN_DPAD_UP = 0x8,
    GCN_A = 0x100,
    GCN_B = 0x200,
    GCN_X = 0x400,
    GCN_Y = 0x800,
    GCN_Z = 0x10,
    GCN_START = 0x1000,
    GCN_L = 0x40,
    GCN_R = 0x20
};

struct KPADStatus {
    u8 unknown_0x0[0x10 - 0x0];
    float acc_value;
    float acc_speed;
    u8 unknown_0x18[0x74 - 0x18];
    float cStickHorizontal;
    float cStickVertical;
    u8 unknown_7C[0x84 - 0x7C];
}; //total size 0x84

struct WPADInfo {
    u32 dpd;
    u32 speaker;
    u32 attach;
    u32 lowBat;
    u32 nearempty;
    u8 battery;
    u8 led;
    u8 protocol;
    u8 firmware;
}; //total size 0x18

struct PADStatus {
    u16 buttons;
    s8 horizontalStickU8;
    s8 verticalStickU8; // -62 to 62
    s8 horizontalCStickU8;
    s8 verticalCStickU8; // -50 to 50
    u8 unknown_0x6[0xC - 0x6];
}; //total size 0xC

class InputState {
public:
    virtual void unknown_vtable();
    // vtable 808b2f2c
    u16 buttonActions; // bit flags:
    /*
    0x1 = accelerate
    0x2 = brake + reverse (used for SSMT)
    0x4 = use item
    0x8 = hop + drift
    0x20 = rear-view camera
    */
    u16 buttonRaw; // bit flags, vary slightly by controller
    float stickX; // -1.0 to 1.0 //0x8
    float stickY; // -1.0 to 1.0 //0xC
    u8 quantisedStickX; // 0-14
    u8 quantisedStickY; // 0-14
    u8 motionControlFlick; // 1 up, 2 down, 3 left, 4 right; includes the first frame of d-pad presses
    u8 motionControlFlick2; // not sure what the difference is from the other one
    u8 unknown_0x14[0x18 - 0x14];
}; // Total size 0x18

class UIInputState {
public:
    virtual void unknown_vtable(); //0x808b2f20
    u16 buttonActions; //bit flags: //0x4
    /*
        0x1 = forward press
        0x2 = back press
        0x4 = start/+ press
        0x8 = up press
        0x10 = down press
        0x20 = left press
        0x40 = right press
        0x100 = x/Z
    */
    u16 rawButtons; //0x6
    u16 buttonRaw; // bit flags, vary slightly by controller //0x8
    float stickX; // -1.0 to 1.0 //0xC
    float stickY; // -1.0 to 1.0 //0x10
    u8 unknown_0x14[0x18 - 0x14]; //0x14
    u8 quantisedStickX; // 0-14 0x18
    u8 quantisedStickY; // 0-14 0x19
    u8 unknown_0x1A[0x34 - 0x1A];
}; //total size 0x34

class Controller {
public:
    Controller(); //8051eba8 
    virtual ~Controller(); //8051f1ec vtable 808b2ed8
    virtual void Update() = 0;
    virtual int GetType() const; //0x10 8051ce7c returns -1
    virtual bool HasRumble(); //0x14 80521d84
    virtual void ActivateRumble(); //0x18 8052208c
    virtual void StopRumble(); //0x1c 805220a4
    virtual void Connect(); //0x20 8051f00c
    virtual double func_0x24(); //0x24 80522834
    virtual void TogglePointer(bool enablePointer); //0x28 80522824
    virtual bool isPointerEnabled(); //0x2c 8052281c
    virtual void UpdateBatteryField(); //0x30 8051f010
    virtual int GetSlot() const; //0x34 80522494
    virtual void SetDriftType(bool isDriftAuto); //0x38 8051f37c
    virtual int GetRuntimeTypeInfo() const; //0x3c 8051f07c
    virtual int GetRemainingBattery() const; //0x40 8051f074
    virtual void Init(bool isDriftAuto); //0x44 8051f308 could be called init too
    InputState inputState;  //0x4
    UIInputState uiinputState; //0x1c
    u8 unknown_0x50;
    bool isDriftAuto;
    u8 unknown_0x52[2];
    u32 battery;
    u8 unknown_0x58[0x90 - 0x58];
}; //total size 0x90

class DummyController : public Controller {
public:
    //no ctor
    ~DummyController() override; //805232b0 vtable 808b3020
    void Update() override; //80524ab0 just a blr
}; //total size 0x90

class WiiController : public Controller {
public:
    WiiController(); //8051f088
    ~WiiController() override; //80522934 vtable 808b2e90
    void Update() override; //0xc 8051fc84
    int GetType() const override; //0x10 8052292c returns 0x8dc (0 1 2)
    bool HasRumble() override; //0x14 805228dc checks wiimote internal setting
    void ActivateRumble() override; //0x18 805228d0
    void StopRumble() override; //0x1c 805228c4
    void Connect() override; //0x20 805228b4
    void TogglePointer(bool enablePointer) override; //0x28 8051ffb8
    bool isPointerEnabled() override; //0x2c 805228f4
    int GetSlot() const override; //0x34 80522924
    int GetRemainingBattery() const override; //0x40 8051f3d0
    void Init(bool isDriftAuto) override; //0x44 8051f22c
    KPADStatus kpadStatus[16];
    u8 unknown_0x8d0[0x8d4 - 0x8d0];
    u32 channel; //0x8d4 = slot
    u32 type; //0x8dc
    u32 type2;
    WPADInfo wpadInfo;
    u8 unknown_0x8F8[0x900 - 0x8f8];
    u32 wpadType;
    u8 unknown_0x904[0x920 - 0x904];
};//total size 0x920 seems other controllers related

class GCNController : public Controller {
public:
    GCNController(); //8051ffd0
    ~GCNController() override; //0x8 80522874 vtable 808b2e48
    void Update() override; //0xc 805201b0
    int GetType() const override; //0x10 8052286c returns 3
    bool HasRumble() override; //0x14 805206fc checks RKSYS setting
    void ActivateRumble() override; //0x18 80522858
    void StopRumble() override; //0x1c 8052284c
    void Connect() override; //0x20 80522840
    int GetSlot() const override; //0x34 80522864
    void Init(bool isDriftAuto) override; //0x44 80520118
    PADStatus padStatus; //0x90
    u32 channel; // = slot 
    float cStickHorizontal;
    float cStickVertical;
    u8 unknown_0xa8[0xb0 - 0xa8];
};//total size 0xb0 seems GCN related

class GhostController : public Controller {
    GhostController(); //80520730
    ~GhostController() override; //80520924 vtable 808b2e00oh
    void Update() override; //80520b9c
    int GetType() const override; //0x10 8052282c returns 4
    void Init(bool isDriftAuto) override; //0x44 80520998

    u8 unknown_0x0[0xa8 - 0x90];
};//total size 0xa8

class ControllerHolder {
public:
    ControllerHolder(); // 80520f64 - inlined in RealControllerHolder()
    virtual ~ControllerHolder(); // 805222b4 vtable 808b2dd8
    virtual void Update(); // 80521198
    virtual int unknown2(); // 80521110
    virtual int unknown3();// 805226f4
    virtual int unknown4();// 8051ce84
    virtual int  unknown5();// 8051ce8c
    virtual int  unknown6();// 80520ebc
    // vtable 808b2dd8
    Controller *controller; //0x4
    Controller *controller2;
    Controller *controller3; //0xc
    u8 unknown_0x10[0x28 - 0x10];
    InputState inputStates[2]; // 0 is current frame, 1 is previous    0x28
    UIInputState uiinputStates[2]; //0 is current frame, 1 is previous 0x58
    u8 unknown_0xC0[0xd8 - 0xc0];
    static int ConvertType(u32 type); //80523a58 if wiimote based, returns 3, gcn returns 1, other returns 0
}; // Total size 0xd8

struct RKGInputBuffer {
    u8 input[0x2774];
};


class GhostWriter {
public:
    GhostWriter(); //80524ac4
    virtual ~GhostWriter(); //80524c2c vtable 808b3068
    u8 unknown_0x4[0x14 - 0x4];
    u32 state; //0x14
    u8 unknown_0x18[4];
}; //0x1C 

class RealControllerHolder : public ControllerHolder {
public:
    RealControllerHolder(); // 805220bc 
    ~RealControllerHolder() override; // 805222f4 vtable 808b2d90
    void Update() override; //0xc 80521768
    int unknown2() override; // 80522708
    int unknown4() override; // 80522700
    int unknown5() override; // 805226f8
    int unknown6() override; // 80520ebc

    // vtable 808b2d90
    void SetController(Controller *controller, u32 *r5); //80521554 r5 is a pointer, but unsure to what as it's always NULL
    void RequestRumble(double intensity, Controller *controller, u32 length, u8 r6); //80521acc
    RKGInputBuffer *rkgInputBuffer; // 0xd8 0x2774 byte buffer for storing a controller input section of an RKG file
    u8 unknown_0xdc[0xe8 - 0xdc];
    GhostWriter *ghostWriter; //0xE8
}; // Total size 0xec

class VirtualControllerHolder : public ControllerHolder {
public:
    VirtualControllerHolder(); //805234a0
    ~VirtualControllerHolder() override; // 8052279c vtable 808b2db4
    int unknown3() override; // 805219ac

    // vtable 808b2db4
    u8 unknown_0xd8[0x180 - 0xd8];
}; // Total size 0x180

class RumbleManager { //name based on RequestRumble extensively loading class fields
    //no ctor
    virtual ~RumbleManager(); //80525204 vtable 808b30fc
    void Init(KRM *vibrationKRM); //805250c8
    KRM *rawKRM;
    void **krmEntries; //
    void **krmEntries2; //0xc
};


class InputData {
public:
    static InputData *sInstance; // 809bd70c
    static InputData *getStaticInstance(); // 8052313c
    static void destroyStaticInstance(); // 8052318c
    InputData(); // 805232f0
    virtual ~InputData(); // 805231dc vtable 808b2fc8
    void Update(); //805238f0
    void UpdateControllers(u8 isPaused); //805237e8
    void ResetRealController(u8 id); //80524264
    void ResetDummyController(); //80523eac
    void InitGhostController(u8 id, RKGInputData *data, bool isAuto); //8052453c
    void UpdateGCNInputs(u8 id, PADStatus *status);
    RealControllerHolder realControllerHolders[4]; //0x4 Stores inputs from a real controller at the same console
    VirtualControllerHolder virtualControllerHolders[12]; //0x3b4 Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
    ControllerHolder controllerHolder; //0x15b4 dummy?


    u32 unknown_0x168c;
    DummyController dummyController; //0x1690
    WiiController wiiControllers[4]; //0x1720
    GCNController gcnControllers[4]; //0x3ba0
    GhostController ghostControllers[4]; //0x3e60
    RumbleManager rumbleManager;
    u8 unknown_0x4110[0x4154 - 0x4110];
    bool isPaused; //0x4154
    bool isMirror; //0x4155
    u8 unknown_0x4156[0x415c - 0x4156];
}; // Total size 0x415c
size_assert(InputData, 0x415c);
#endif