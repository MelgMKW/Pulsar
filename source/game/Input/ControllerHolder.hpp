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


namespace Input {

class Controller;

class ControllerHolder {
public:
    ControllerHolder(); //80520f64 - inlined in RealControllerHolder()
    virtual ~ControllerHolder(); //805222b4 vtable 808b2dd8
    virtual void Update(); //80521198
    virtual int unknown2(); //80521110
    virtual int unknown3();//805226f4
    virtual int unknown4();//8051ce84
    virtual int  unknown5();//8051ce8c
    virtual int  unknown6();//80520ebc
    //vtable 808b2dd8
    Controller* controller; //0x4
    Controller* controller2;
    Controller* controller3; //0xc
    u8 unknown_0x10[0x28 - 0x10];
    State inputStates[2]; //0 is current frame, 1 is previous    0x28
    UIState uiinputStates[2]; //0 is current frame, 1 is previous 0x58
    u16 isDriftAuto; //0xc0
    u8 unknown_0xC2[0xd8 - 0xc2];
}; //Total size 0xd8

struct RKGInputBuffer {
    u8 input[0x2774];
};

class GhostWriter {
public:
    GhostWriter(); //80524ac4
    virtual ~GhostWriter(); //80524c2c vtable 808b3068
    void WriteFrame(u16 buttonActions, u8 quantisedStickX, u8 quantisedStickY, u8 motionControlFlickUnmirrored); //80524e74
    void* inputs; //0x4
    u8 unknown_0x8[0x14 - 0x8];
    u32 state; //0x14
    u8 unknown_0x18[4];
}; //0x1C 

class RealControllerHolder : public ControllerHolder {
public:
    RealControllerHolder(); //805220bc 
    ~RealControllerHolder() override; //805222f4 vtable 808b2d90
    void Update() override; //0xc 80521768
    int unknown2() override; //80522708
    int unknown4() override; //80522700
    int unknown5() override; //805226f8
    int unknown6() override; //80520ebc
    void SetController(const Controller* controller, u32* r5); //80521554 r5 is a pointer, but unsure to what as it's always nullptr
    void RequestRumble(double intensity, Controller* controller, u32 length, u8 r6); //80521acc
    void SetDriftType(u16 isDriftAuto); //80520f2c
    RKGInputBuffer* rkgInputBuffer; //0xd8 0x2774 byte buffer for storing a controller input section of an RKG file
    void* rkgInputsBuffer; //0xdc
    u8 unknown_0xe0[8];
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