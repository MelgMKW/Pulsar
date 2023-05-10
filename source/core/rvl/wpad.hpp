#ifndef _WPAD_
#define _WPAD_
#include <types.hpp>

namespace WPAD { //Wireless PAD, low-level wii remote library

enum Buttons {
    WPAD_BUTTON_LEFT    = 0x1,
    WPAD_BUTTON_RIGHT   = 0x2,
    WPAD_BUTTON_DOWN    = 0x4,
    WPAD_BUTTON_UP      = 0x8,
    WPAD_BUTTON_PLUS    = 0x10,
    WPAD_BUTTON_2       = 0x100,
    WPAD_BUTTON_1       = 0x200,
    WPAD_BUTTON_B       = 0x400,
    WPAD_BUTTON_A       = 0x800,
    WPAD_BUTTON_MINUS   = 0x1000,
    WPAD_BUTTON_Z       = 0x2000,
    WPAD_BUTTON_C       = 0x4000,
    WPAD_BUTTON_HOME    = 0x8000
};

enum ClButtons {
    WPAD_CL_BUTTON_UP     = 0x1,
    WPAD_CL_BUTTON_LEFT   = 0x2,
    WPAD_CL_TRIGGER_ZR    = 0x4,
    WPAD_CL_BUTTON_X      = 0x8,
    WPAD_CL_BUTTON_A      = 0x10,
    WPAD_CL_BUTTON_Y      = 0x20,
    WPAD_CL_BUTTON_B      = 0x40,
    WPAD_CL_TRIGGER_ZL    = 0x80,
    WPAD_CL_UNKNOWN_0x100 = 0x100,
    WPAD_CL_TRIGGER_R     = 0x200,
    WPAD_CL_BUTTON_PLUS   = 0x400,
    WPAD_CL_BUTTON_HOME   = 0x800,
    WPAD_CL_BUTTON_MINUS  = 0x1000,
    WPAD_CL_TRIGGER_L     = 0x2000,
    WPAD_CL_BUTTON_DOWN   = 0x4000,
    WPAD_CL_BUTTON_RIGHT  = 0x8000
};

enum Error {
    WPAD_ERR_NONE = 0,
    WPAD_ERR_NO_CONTROLLER = -1,
    WPAD_ERR_BUSY = -2,
    WPAD_ERR_TRANSFER = -3,
    WPAD_ERR_INVALID = -4,
    WPAD_ERR_NOPERM = -5,
    WPAD_ERR_BROKEN = -6,
    WPAD_ERR_CORRUPTED = -7
};

enum BatteryLevel {
    BATTERY_LEVEL_CRITICAL = 0,
    BATTERY_LEVEL_LOW = 1,
    BATTERY_LEVEL_MEDIUM = 2,
    BATTERY_LEVEL_HIGH = 3,
    BATTERY_LEVEL_MAX = 4
};

enum DeviceType {
    WPAD_DEV_CORE           = 0,
    WPAD_DEV_NUNCHUK        = 1, //FREESTYLE
    WPAD_DEV_CLASSIC        = 2,
    WPAD_DEV_MPLUS          = 5, //not supported in mkwii
    WPAD_DEV_MPLUS_NUNCHUK  = 6, //not supported in mkwii
    WPAD_DEV_MPLUS_CLASSIC  = 7, //not supported in mkwii
    WPAD_DEV_MPLS_FUTURE    = 250, //not supported in mkwii
    WPAD_DEV_FUTURE         = 251,
    WPAD_DEV_NOT_SUPPORTED  = 252,
    WPAD_DEV_NOT_FOUND      = 253,
    WPAD_DEV_UNKNOWN        = 255
};

enum DataFormat {
    WPAD_FMT_CORE              =  0,
    WPAD_FMT_CORE_ACC          =  1,
    WPAD_FMT_CORE_ACC_DPD      =  2,
    WPAD_FMT_NUNCHUCK          =  3,
    WPAD_FMT_NUNCHUCK_ACC      =  4,
    WPAD_FMT_NUNCHUCK_ACC_DPD  =  5,
    WPAD_FMT_CLASSIC           =  6,
    WPAD_FMT_CLASSIC_ACC       =  7,
    WPAD_FMT_CLASSIC_ACC_DPD   =  8,
    WPAD_FMT_CORE_ACC_DPD_FULL =  9,
    WPAD_FMT_MPLS              = 16
};

struct DPDObject {
    s16 x;
    s16 y;
    u16 size;
    u8 traceId;
    u8 padding;
};
size_assert(DPDObject, 0x8);

struct Acc { //accelerometer
    s16 x;
    s16 y;
    s16 z;
};

struct Status {
    u16 buttons; //bitfield of Buttons enum
    Acc accelerometers;
    DPDObject objects[4];
    u8 deviceType; //extension
    u8 error;
};
size_assert(Status, 0x2a);



struct FSStatus { //FreeStyle = nunchuck
    Status coreStatus;
    Acc fsAccelerometers; //0x2b
    s8 fsStickX;
    s8 fsStickY;
};
size_assert(FSStatus, 0x32);
struct CLStatus {
    Status coreStatus; //0x0
    u16 clButtons; //0x2a
    s16 clLStickX; //0x2c
    s16 clLStickY; //0x2e
    s16 clRStickX; //0x30
    s16 clRStickY; //0x32
    u8 clTriggerL; //0x34
    u8 clTriggerR; //0x35
};
size_assert(CLStatus, 0x36);

struct MPStatus { //merged?
    Status status;
    union {
        struct { //nunchuck
            s16 fsAccX;
            s16 fsAccY;
            s16 fsAccZ;
            s8  fsStickX;
            s8  fsStickY;
        } fs;
        struct { //classic
            u16 clButton;
            s16 clLStickX;
            s16 clLStickY;
            s16 clRStickX;
            s16 clRStickY;
            u8  clTriggerL;
            u8  clTriggerR;
        } cl;
    } extension;
};
size_assert(MPStatus, 0x36);

struct Info {
    BOOL pointer;
    BOOL speaker; //0x4
    BOOL attach; //0x8
    BOOL lowBat; //0xc
    BOOL nearempty; //0x10
    u8 battery; //0x14
    u8 led; //0x18
    u8 unknown[2];
};
size_assert(Info, 0x18);

typedef void (*Callback)(s32 channel, s32 result);
typedef void (*SamplingCallback)(s32 channel);
typedef void (*ConnectCallback)(s32 channel, s32 reason);
typedef void (*ExtensionCallback)(s32 channel, s32 result);
typedef void (*FlushCallback)(u32 result);
typedef void (*WPADSyncDeviceCallback)(s32  result, s32 num);
typedef void* (*WPADAlloc)(u32  size);
typedef u8(*WPADFree)(void* ptr);
void Init(); //801bf5c4

//WUD Wrapper
BOOL StartSimpleSync(); //801bf634
BOOL StartFastSimpleSync(); //801bf638
BOOL StopSimpleSync(); ////801bf63c
WPADSyncDeviceCallback SetSimpleSyncCallback(WPADSyncDeviceCallback  callback); //801bf640
void RegisterAllocator(WPADAlloc alloc, WPADFree free); //801bf644
u32  GetWorkMemorySize(); //801bf648
s32 GetStatus(); //801bf64c



u8 GetRadioSensitivity(s32 channel); //801bf650
u8 GetSensorBarPosition(); //801bf714
void GetAccGravityUnit(s32 channel, u32 type, Acc* acc); //801c07d0
void Disconnect(s32 channel); //801c08cc
s32 Probe(s32 channel, u32* type); //801c0990
SamplingCallback SetSamplingCallback(s32 channel, SamplingCallback callback); //801c0a1c
ConnectCallback SetConnectCallback(s32 channel, ConnectCallback callback); //801c0a84
ExtensionCallback SetExtensionCallback(s32 channel, ExtensionCallback callback); //801c0aec
u32 GetDataFormat(s32 channel); //801c0b54
s32 SetDataFormat(s32 channel, u32 fmt); //801c0b9c
s32 GetInfoAsync(s32 channel, Info* info, Callback callback); //801c0ca4
void ControlMotor(s32 channel, u32 command); //801c0ec4
void EnableMotor(BOOL enable); //801c0f90
BOOL IsMotorEnabled(); //801c0fc4
BOOL SaveConfig(FlushCallback callback); //801c11e0
void Read(s32 channel, void* status); //801c128c
void SetAutoSamplingbuffer(s32 channel, void* buffer, u32 length); //801c142c
BOOL IsSpeakerEnabled(s32 channel); //801c17ec
s32 ControlSpeaker(s32 channel, u32 command, Callback callback); //801c1830
u8 GetSpeakerVolume(); //801c2e4c
void SetSpeakerVolume(u8 volume); //801c2e80
s32 SendStreamData(s32 channel, void* buffer, u16 length); //801c30008
BOOL CanSendStreamData(s32 channel); //801c308c
u8 GetDpdSensitivity(); //801c329c
BOOL IsDpdEnabled(s32 channel); //801c32a4
s32 ControlDpd(s32 channel, u32 command, Callback callback); //801c3318

}//namespace WPAD



#endif