/*
Manager is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#ifndef _INPUT_CONTROLLER_HOLDER_
#define _INPUT_CONTROLLER_HOLDER_
#include <kamek.hpp>
#include <MarioKartWii/Input/InputState.hpp>
#include <MarioKartWii/Input/Controller.hpp>
#include <MarioKartWii/Input/GhostWriter.hpp>
#include <MarioKartWii/Input/Rumble.hpp>

namespace Input {

class Controller;

class ControllerParams {
    void Fill(const Controller& src); //80522364
    ControllerType type;
    WUD::BTD_ADDR address; //0x4
    u8 padding[2];
    u32 channel; //0xc
};

class ControllerHolder {
public:
    ControllerHolder(); //80520f64 - inlined in RealControllerHolder()
    virtual ~ControllerHolder(); //805222b4 vtable 808b2dd8
    virtual void Update(bool writeGhostFrame); //0xc 80521198
    virtual void Init(); //0x10 80521110
    virtual void CopyCPUInputs(const State& cpuInputs); //0x14 805226f4
    virtual RKGInputs* GetRKGInputs() const; //0x18 8051ce84
    virtual int GetInputsCount(); //0x1c 8051ce8c
    virtual void CreateRumbleController(); //0x20 80520ebc

    void RequestRumble(u32 krmEntryIdx, bool replaceActiveIfNoFreeRumble, float f1); //80521a34
    void RequestRumble(Controller* controller, u32 krmEntryIdx, bool replaceActiveIfNoFreeRumble, float f1); //80521acc
    void RequestRumbleByDuration(u32 duration, bool replaceActiveIfNoFreeRumble, float f1); //80521ed0
    void RequestRumbleByDurationNoFaderCheck(u32 duration, bool replaceActiveIfNoFreeRumble, float f1); //80521f8c
    void StopAllRumble(); //80522014

    //Wrappers around Controller funcs
    void ActivateRumble() const; //80522078
    void StopCurrentRumble() const; //80522090
    void ResetSelfController(); //805220a8

    Controller* curController; //0x4
    Controller* prevController;
    Controller* controller3; //0xc
    u32 rumbleLength; //0x10
    u8 hasActiveRumble; //0x14
    u8 padding[3];
    Rumble* activeRumble; //0x18
    u8 unknown_0x1c[4];
    RumbleController* rumbleControllers[2]; //0x20
    State inputStates[2]; //0x28 0 is current frame, 1 is previous
    UIState uiinputStates[2]; //0x58 0 is current frame, 1 is previous
    u16 isDriftAuto; //0xc0
    u8 padding2[2];
    u16 idleFrameCounter; //0xc2
    u16 unknown_0xc4;
    ControllerParams params; //0xc8
}; //Total size 0xd8

class RealControllerHolder : public ControllerHolder {
public:
    RealControllerHolder(); //805220bc 
    ~RealControllerHolder() override; //805222f4 vtable 808b2d90
    void Update(bool writeGhostFrame) override; //0xc 80521768
    void Init() override; //0x10 80522708
    RKGInputs* GetRKGInputs() const override; //0x18 80522700
    int GetInputsCount() override; //0x1c 805226f8


    void SetController(Controller* controller, void* r5 = nullptr); //80521554 r5 is a pointer, but unsure to what as it's always nullptr
    void SetDriftType(u16 isDriftAuto); //80520f2c
    void StartGhostReading(); //805215d4
    void EndGhostWriting(); //80521688
    void SetGhostController(GhostController* controller, const RKGInputs* rawInputs, bool isAuto); //80521844
    void PrepareForRace(); //80521930

    RKGInputs* rkgInputBuffer; //0xd8 0x2774 byte buffer for storing a controller input section of an RKG file
    RKGInputs* filledRkgInputBuffer; //0xdc only != nullPtr if buffer has stored inputs, so ghost writer copy function returned >0
    u32 rkgInputsSize; //0xe0 how much space was actually used
    bool blockInputs; //0xe4
    u8 padding[3];
    GhostWriter* ghostWriter; //0xE8
}; //Total size 0xec

class AIControllerHolder : public ControllerHolder {
public:
    AIControllerHolder(); //805234a0
    ~AIControllerHolder() override; //8052279c vtable 808b2db4
    void CopyCPUInputs(const State& cpuInputs) override; //805219ac

    AIController aiController; //0xd8
}; //Total size 0x180

}//namespace Input
#endif