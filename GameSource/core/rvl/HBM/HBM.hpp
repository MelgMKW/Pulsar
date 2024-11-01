#ifndef _HBM_
#define _HBM_
#include <types.hpp>
#include <core/rvl/MEM/MEMallocator.hpp>
#include <core/rvl/mtx/MTX.hpp>
#include <core/rvl/KPAD.hpp>

namespace HBM {

typedef int (*SoundCallback)(int evt, int num);

struct KPadData {
    KPAD::Status* kpad;
    Vec2D        pos;
    u32         use_devtype;
}; //0x10

struct ControllerData {
    KPadData wiiCon[4];
}; //0x40

enum SelectBtnNum { //decided upon button, as in the one that was ultimately selected
    HBM_SELECT_NULL = -1,
    HBM_SELECT_HOMEBTN = 0,
    HBM_SELECT_BTN1,
    HBM_SELECT_BTN2,
    HBM_SELECT_BTN3,
    HBM_SELECT_BTN4,
    HBM_SELECT_MAX
};

struct DataInfo {
    void* layout;
    void* spkSe;
    void* msg;
    void* config;
    void* mem;  //0x10
    SoundCallback soundCB;
    int   backFlag;
    int   region;
    int   cursor; //0x20
    int   messageFlag;
    u32   configBufSize;
    u32   memSize;
    float   frameDelta; //0x30
    Vec2D  adjust; //0x34
    MEM::Allocator* pAllocator; //0x3c
}; //0x40

void Create(const DataInfo* dataInfo); //801773d0
void Init(); //80177520

void CreateSound(const void* soundData, void* memBuf, u32 memSize); //80177740
SelectBtnNum Calc(const ControllerData* controller); //80177554
void Draw(); //801775a4
SelectBtnNum  GetSelectBtnNum(); //80177700
void SetAdjustFlag(int flag); //80177724
void UpdateSound(); //80177744



} //namespace HBM
#endif

