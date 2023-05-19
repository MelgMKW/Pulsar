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
#include <game/Input/InputState.hpp>
#include <game/Input/Controller.hpp>
#include <game/Input/GhostWriter.hpp>

namespace Input {

class Controller;

class ControllerHolder {
public:
    ControllerHolder(); //80520f64 - inlined in RealControllerHolder()
    virtual ~ControllerHolder(); //805222b4 vtable 808b2dd8
    virtual void Update(); //80521198
    virtual void Init(); //80521110
    virtual int unknown3();//805226f4
    virtual RKGInputs* GetRKGInputs() const;//8051ce84
    virtual int GetInputsCount();//8051ce8c
    virtual int unknown6();//80520ebc
    //vtable 808b2dd8
    Controller* curController; //0x4
    Controller* prevController;
    Controller* controller3; //0xc
    u8 unknown_0x10[0x28 - 0x10];
    State inputStates[2]; //0 is current frame, 1 is previous    0x28
    UIState uiinputStates[2]; //0 is current frame, 1 is previous 0x58
    u16 isDriftAuto; //0xc0
    u8 unknown_0xC2[0xd8 - 0xc2];
}; //Total size 0xd8

class RealControllerHolder : public ControllerHolder {
public:
    RealControllerHolder(); //805220bc 
    ~RealControllerHolder() override; //805222f4 vtable 808b2d90
    void Update() override; //0xc 80521768
    void Init() override; //80522708
    RKGInputs* GetRKGInputs() const override; //80522700
    int GetInputsCount() override; //805226f8
    int unknown6() override; //80520ebc
    void SetController(const Controller* controller, u32* r5); //80521554 r5 is a pointer, but unsure to what as it's always nullptr
    void RequestRumble(double intensity, Controller* controller, u32 length, u8 r6); //80521acc
    void SetDriftType(u16 isDriftAuto); //80520f2c

    void StartGhostReading(); //805215d4
    void EndGhostWriting(); //80521688
    void SetGhostController(GhostController* controller, const RKGInputs* rawInputs, bool isAuto); //80521844

    RKGInputs* rkgInputBuffer; //0xd8 0x2774 byte buffer for storing a controller input section of an RKG file
    RKGInputs* filledRkgInputBuffer; //0xdc only != nullPtr if buffer has stored inputs, so ghost writer copy function returned >0
    u32 rkgInputsSize; //0xe0 how much space was actually used
    bool isGhostReadingDisabled; //0xe4
    u8 padding[3];
    GhostWriter* ghostWriter; //0xE8
}; //Total size 0xec

class VirtualControllerHolder : public ControllerHolder {
public:
    VirtualControllerHolder(); //805234a0
    ~VirtualControllerHolder() override; //8052279c vtable 808b2db4
    int unknown3() override; //805219ac

    //vtable 808b2db4
    u8 unknown_0xd8[0x180 - 0xd8];
}; //Total size 0x180

}//namespace Input
#endif