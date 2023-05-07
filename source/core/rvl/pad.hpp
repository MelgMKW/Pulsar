#ifndef _PAD_
#define _PAD_
#include <types.hpp>

namespace PAD {

enum Buttons {
    PAD_BUTTON_LEFT = 0x1,
    PAD_BUTTON_RIGHT = 0x2,
    PAD_BUTTON_DOWN = 0x4,
    PAD_BUTTON_UP = 0x8,
    PAD_BUTTON_Z = 0x10,
    PAD_BUTTON_R = 0x20,
    PAD_BUTTON_L = 0x40,
    PAD_BUTTON_A = 0x100,
    PAD_BUTTON_B = 0x200,
    PAD_BUTTON_X = 0x400,
    PAD_BUTTON_Y = 0x800,
    PAD_BUTTON_START = 0x1000
};

enum Error {
    PAD_ERR_NONE = 0,
    PAD_ERR_NO_CONTROLLER = -1,
    PAD_ERR_NOT_READY = -2,
    PAD_ERR_TRANSFER = -3
};

struct Status {
    u16 buttons; //bitfield of Buttons enum
    s8 stickX; //-128 to 127
    s8 stickY; //-127 to 127
    s8 cStickX;
    s8 cStickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    s8 error; //see enum
};
size_assert(Status, 0xC);

BOOL Init(); //801af2f0
BOOL Reset(u32 mask); //801af0dc
u32  Read(Status* dest); //801af44c
void ClampCircle(Status* status); //801ae6f4
void Clamp(Status* status, u32 type); //801ae7dc
BOOL Recalibrate(u32 mask); //801aef1e4
void ControlMotor(int channel, u32 command); //801af908


}//namespace PAD



#endif