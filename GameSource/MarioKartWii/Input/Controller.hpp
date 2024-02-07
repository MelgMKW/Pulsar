/*
Manager is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#ifndef _INPUT_CONTROLLER_
#define _INPUT_CONTROLLER_
#include <kamek.hpp>
#include <core/rvl/pad.hpp>
#include <core/rvl/kpad.hpp>
#include <core/rvl/wpad.hpp>
#include <MarioKartWii/Input/InputState.hpp>
#include <MarioKartWii/Input/GhostWriter.hpp>

enum ControllerType {
    WHEEL = 0x0, //0xCHANNEL11
    NUNCHUCK = 0x1, //0xCHANNEL12
    CLASSIC = 0x2, //0xCHANNEL13
    GCN = 0x3, //0xCHANNEL14
    DUMMY = 0x4,
    CPU = 0x5,
    CONTROLLER_TYPE_NONE = -1
};

enum ControllerType2 {
    TYPE2_WHEEL = 0x0, //0xCHANNEL11
    TYPE2_NUNCHUCK = 0x1, //0xCHANNEL12
    TYPE2_CLASSIC = 0x2, //0xCHANNEL13
    TYPE2_GCN = 0x3, //0xCHANNEL14
    TYPE2_NONE = 0x4
};

namespace Input {

class Controller {
public:
    Controller(); //8051eba8 
    virtual ~Controller(); //8051f1ec vtable 808b2ed8
    virtual void UpdateImpl(State& state, UIState& uiState) = 0;
    virtual ControllerType GetType() const; //0x10 8051ce7c returns -1
    virtual bool HasRumble() const; //0x14 80521d84
    virtual void ActivateRumble(); //0x18 8052208c
    virtual void StopRumble(); //0x1c 805220a4
    virtual void Connect(); //0x20 8051f00c
    virtual double func_0x24(); //0x24 80522834
    virtual void TogglePointer(bool enablePointer); //0x28 80522824
    virtual bool isPointerEnabled() const; //0x2c 8052281c
    virtual void UpdateBatteryField(); //0x30 8051f010
    virtual int GetChannel() const; //0x34 80522494
    virtual void SetDriftType(bool isDriftAuto); //0x38 8051f37c
    virtual int GetRuntimeTypeInfo() const; //0x3c 8051f07c
    virtual u8 GetRemainingBattery() const; //0x40 8051f074 
    virtual void Init(bool isDriftAuto); //0x44 8051f308 could be called init too

    void Update(); //8051ed14
    State inputState;  //0x4
    UIState uiinputState; //0x1c
    bool hasError; //0x50 WPADError for example
    bool isDriftAuto;
    u8 unknown_0x52[2];
    u32 battery; //0x54
    bool unknown_0x58;
    u8 padding[3];
    UIState unknownUIState; //0x5c
}; //total size 0x90
size_assert(Controller, 0x90);

class DummyController : public Controller {
public:
    //no ctor
    ~DummyController() override; //805232b0 vtable 808b3020
    void UpdateImpl(State& state, UIState& uiState) override; //80524ab0 just a blr
}; //total size 0x90

class MotionController;
class WiiController : public Controller {
public:
    WiiController(); //8051f088
    ~WiiController() override; //80522934 vtable 808b2e90
    void UpdateImpl(State& state, UIState& uiState) override; //0xc 8051fc84
    ControllerType GetType() const override; //0x10 8052292c returns 0x8dc (0 1 2)
    bool HasRumble() const override; //0x14 805228dc checks wiimote internal setting
    void ActivateRumble() override; //0x18 805228d0
    void StopRumble() override; //0x1c 805228c4
    void Connect() override; //0x20 805228b4
    void TogglePointer(bool enablePointer) override; //0x28 8051ffb8
    bool isPointerEnabled() const override; //0x2c 805228f4
    int GetChannel() const override; //0x34 80522924
    u8 GetRemainingBattery() const override; //0x40 8051f3d0
    void Init(bool isDriftAuto) override; //0x44 8051f22c

    void UpdateStatesClassic(const WPAD::CLStatus& classicStatus, State& state, UIState& uiState); //8051f410 CLStatus from KPAD::UnifiedWpadStatus
    //The next 2 use WPAD::Status/WPAD::FSStatus with MotionController directly
    void UpdateStatesNunchuck(UIState& uiState, State& state); //8051fa7c
    void UpdateStatesCore(UIState& uiState, State& state); //8051fbe0
    static void WPADInfoCallback(s32 channel, s32 result); //8051f384 updates controller's battery using wpadInfo's battery
    void UpdateBattery(s32 result); //8051f3b4 inlined in the func above

    KPAD::Status kpadStatus[16]; //0x90
    s32 samplingCount; //0x8d0 from KPAD::Read
    u32 channel; //0x8d4 = slot
    ControllerType2 type2; //0x8d8
    ControllerType type; //0x8dc
    WPAD::Info wpadInfo; //0x8e0

    u16 clButtons; //0x8f8
    u16 unknown_0x8fa;
    u16 unkControllerCounter; //0x8fc goes up to 20 as soon as deviceType changes to 255, until that value, the controller isn't updated
    u16 coreControllerCounter; //0x8fe goes up to 10 as soon as deviceType changes to core, until that value, the controller isn't update
    WPAD::DeviceType wpadType; //0x900
    u8 unknown_0x904;
    u8 padding;
    u16 somePointerCounter; //0x906
    Vec2 horizon; //0x908
    Vec2 horiVec; //0x910
    float dist; //0x918
    MotionController* motionController; //0x91c
};//total size 0x920 seems other controllers related
size_assert(WiiController, 0x920);

class GCNController : public Controller {
public:
    GCNController(); //8051ffd0
    ~GCNController() override; //0x8 80522874 vtable 808b2e48
    void UpdateImpl(State& state, UIState& uiState) override; //0xc 805201b0
    ControllerType GetType() const override; //0x10 8052286c returns 3
    bool HasRumble() const override; //0x14 805206fc checks RKSYS setting
    void ActivateRumble() override; //0x18 80522858
    void StopRumble() override; //0x1c 8052284c
    void Connect() override; //0x20 80522840
    int GetChannel() const override; //0x34 80522864
    void Init(bool isDriftAuto) override; //0x44 80520118
    PAD::Status padStatus; //0x90
    u32 channel; //0x9c = slot 
    float cStickHorizontal; //0xa0
    float cStickVertical; //0xa4
    u16 buttonRaw; //0xa8
    u8 unknown_0xaa[0xb0 - 0xaa];
};//total size 0xb0 seems GCN related
size_assert(GCNController, 0xb0);

class GhostController : public Controller {
    GhostController(); //80520730
    ~GhostController() override; //80520924 vtable 808b2e00
    void UpdateImpl(State& state, UIState& uiState) override; //80520b9c
    ControllerType GetType() const override; //0x10 8052282c returns 4
    double func_0x24() override; //0x24 80520a60
    void SetDriftType(bool isDriftAuto); //0x38 80522828
    void Init(bool isDriftAuto) override; //0x44 80520998
    RKGInputs* ghostInputs; //0x90
    GhostActionStream* actionStream; //0x94
    GhostDirectionStream* directionStream; //0x98
    GhostTrickStream* trickStream; //0x9c
    u8 unknown_0xa0[6];
    bool isReadingGhost; //0xa6 will not read if set to false
    u8 padding;
};//total size 0xa8

class AIController : public Controller {
public:
    ~AIController() override; //805227dc vtable 808b2fd8
    void UpdateImpl(State& state, UIState& uiState) override; //80524a58
    ControllerType GetType() const override; //0x10 80524aa8

    State cpuInputState; //0x90
}; //0xa8


class MotionControllerSub {
public:
    MotionControllerSub(); //8071b86c
    virtual ~MotionControllerSub(); //8071bd1c vtable 808c9454
    u8 unknown[0x18];
};

class MotionController { //only for nunchuck and wheel (core)
public:
    MotionController(); //80745884
    virtual ~MotionController(); //8074595c vtable 808cb780
    void Init(bool isDriftAuto); //807459e4
    void UpdateForNunchuck(State& state, const KPAD::Status& status); //80745be4
    void UpdateForCore(State& state, const KPAD::Status& status); //80745de4
    MotionControllerSub* sub; //0x4
    u32 unknown_0x8[2];
    u8 unknown_0x10[2];
    u8 padding[2];
    float unknown_0x14;
    u8 unknown_0x18[0x58 - 0x18];
    float unknown_0x58[4];
    u8 unknown_0x68[0x80 - 0x68];
    u16 unknown_0x80;
    u8 unknown_0x82;
    u8 padding2;
    u32 unknown_0x84[4];
};
size_assert(MotionController, 0x94);

}//namespace Input
#endif