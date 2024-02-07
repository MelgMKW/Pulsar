#ifndef _KPAD_
#define _KPAD_
#include <types.hpp>
#include <core/rvl/wpad.hpp>
#include <core/rvl/mtx/mtx.hpp>

namespace KPAD { //KPAD, high-level wii remote library

struct Vec2 {
    float x;
    float y;
};

union EXStatus { //extension status +0x60 to all offsets
    struct { //nunchuck
        Vec2 stick; //0x0 clamp_stick_cross
        Vec accelometer; //0x8
        float accValue; //0x14
        float accSpeed; //0x18
    } fs;

    struct { //classic
        u32 hold; //0x0
        u32 trig; //0x4
        u32 release; //0x8
        Vec2 stickL; //0xc
        Vec2 stickR; //0x14
        float triggerl; //0x1c
        float triggerR; //0x20
    } cl;

    /* balance
    struct {
    double tgc_weight;
    double weight[4];
    double weight_ave[4];
    s32 weight_err;
    s32 tgc_weight_err;
    } bl;
    */
};

struct MPDir {
    Vec X; //0x0
    Vec Y; //0xc
    Vec Z; //0x18
};
size_assert(MPDir, 0x24);

struct MPStatus {
    Vec mpls; //0x0
    Vec angle; //0xc
    MPDir dir; //0x18
};
size_assert(MPStatus, 0x3c);

struct Status {
    u32 hold; //0x0 buttons held
    u32 trig; //0x4 buttons trigger since last sample
    u32 release;  //0x8 buttons released since last sample

    //read_kpad_acc
    Vec accelerometer;   //0xc
    float accMag;   //0x18 sqrt of acc
    float accVariation;   //0x1c 

    //read_kpad_dpd and calc_dpd_variable
    Vec2 pointerPos;   //0x20
    Vec2 angle;   //0x28
    float pointerMag; //0x30
    Vec2 horizon; //0x34
    Vec2 horiVec; //0x3c added to horizon
    float horizonMag; //0x44
    float dist; //0x48
    float distVec; //0x4c added to distance
    float distVariation; //0x50

    //calc_acc_vertical
    Vec2 accVertical; //0x54

    u8 extension; //0x5c see wpad's deviceType enum
    u8 error; //0x5d see wpad error
    u8 pointerGravityValid; //0x5e
    u8 format; //0x5f see wpad data format enum
    EXStatus extStatus; //0x60
};
size_assert(Status, 0x84);

/*
struct KPADStatus {
    u8 unknown_0x0[0x10 - 0x0];
    float acc_value;
    float acc_speed;
    u8 unknown_0x18[0x74 - 0x18];
    float cStickHorizontal;
    float cStickVertical;
    u8 unknown_7C[0x84 - 0x7C];
}; //total size 0x84
*/


struct UnifiedWpadStatus {
    union {
        WPAD::Status core;
        WPAD::FSStatus fs; //nunchuck
        WPAD::CLStatus cl; //classic
        //WPAD::TRStatus tr; //presumably unsupported in mkwii train
        //WPAD::BLStatus bl; //presumably unsupported in mkwii wii board balance
        WPAD::MPStatus mp; //merged?
        //WPAD::BKStatus bk; //bulk, dev only?
    } u;
    u8 format; //0x36 see WPAD format enum
    u8 padding; //0x37
};
size_assert(UnifiedWpadStatus, 0x38);

void SetFSStickClamp(s8 min, s8 max); //801950a0
void SetPosParam(s32 channel, float play_radius, float sensitivity); //801950b4
void SetHoriParam(s32 channel, float play_radius, float sensitivity); //801950d0
void SetDistParam(s32 channel, float play_radius, float sensitivity); //801950ec
void SetAccParam(s32 channel, float play_radius, float sensitivity); //80195108
void InitEx(UnifiedWpadStatus unifiedBuffers[], u32 bufferCount); //80197aac
s32 Read(s32 channel, Status buffers[], u32 bufferCount); //80197380 returns number of buffers read
void GetUnifiedWpadStatus(s32 channel, UnifiedWpadStatus* dest, u32 count); //8019812c

}//namespace WPAD



#endif