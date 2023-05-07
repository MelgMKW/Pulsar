/*
Manager is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#ifndef _INPUT_STATE_
#define _INPUT_STATE_
#include <kamek.hpp>

namespace Input {

class State {
public:
    State() {}
    virtual ~State(); //8051ec94 vtable 808b2f2c
    void Reset(); //8051e85c
    void SetStickXMirrorCheck(u8 quantisedStickX); //8051e960
    void SetStickX(u8 quantisedStickX); //8051e9e8
    static float ConvertQuantised(u8 quantisedStick); //8051ea28
    void SetStickY(u8 quantisedStickY); //8051ea60
    bool operator== (State& rhs); //8051e89c
    void SetMotionControlFlick(u8 motionControlFlickUnmirrored); //8051eb68

    u16 buttonActions; //bit flags:
    /*
    0x1 = accelerate
    0x2 = brake + reverse (used for SSMT)
    0x4 = use item
    0x8 = hop + drift
    0x20 = rear-view camera
    */
    u16 buttonRaw; //0x6 bit flags, vary slightly by controller
    float stickX; //-1.0 to 1.0 //0x8
    float stickY; //-1.0 to 1.0 //0xC
    u8 quantisedStickX; //0-14
    u8 quantisedStickY; //0-14
    u8 motionControlFlick; //1 up, 2 down, 3 left, 4 right; includes the first frame of d-pad presses
    u8 motionControlFlickUnmirrored; //0x13
    u8 unknown_0x14[0x18 - 0x14];
}; //Total size 0x18

class UIState {
public:
    UIState() {}
    virtual ~UIState(); //8051ecd4 vtable 808b2f20
    void Reset(); //8051e904
    void SetStickXMirrorCheck(u8 quantisedStickX); //8051eaa0
    void SetStickY(u8 quantisedStickY); //8051eb28
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
    float stickX; //-1.0 to 1.0 //0x8
    float stickY; //-1.0 to 1.0 //0xc
    u8 unknown_0x10[0x18 - 0x10]; //0x10
    u8 quantisedStickX; //0-14 0x18
    u8 quantisedStickY; //0-14 0x19
    u8 unknown_0x1A[0x34 - 0x1A];
}; //total size 0x34
size_assert(UIState, 0x34);

}//namespace Input
#endif