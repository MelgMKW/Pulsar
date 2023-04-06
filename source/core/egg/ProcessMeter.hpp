#ifndef _EGG_PROCESSMETER_
#define _EGG_PROCESSMETER_
#include <types.hpp>
#include <core/egg/Thread.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/ut/Color.hpp>

namespace EGG {
class ProcessMeter;

class PerformanceView { //vtable not present in-game?
public:
    virtual void measureBeginFrame();   //0x8
    virtual void measureEndFrame();     //0xc
    virtual void measureBeginRender();  //0x10
    virtual void measureEndRender();    //0x14
    virtual void callbackDrawSync(u16 token);    //0x18
    virtual void vf_0x1c();             //0x1c 80234a00
    virtual void draw();                //0x20
    virtual void setVisible(bool isVisible);          //0x24
    virtual void isVisible();           //0x28
};

class ProcessBar {
public:
    ProcessBar(nw4r::ut::Color color, float yOrigin, float ySize): xOrigin(0.0), xSize(0.0), tickBegin(0),
        tickEnd(0), color(color), yOrigin(yOrigin), ySize(ySize), bitfield(0) {}; //inlined
    float xOrigin;
    float xSize;
    u32 tickBegin;
    u32 tickEnd;
    nw4r::ut::Color color; //0x10
    float yOrigin; //0x14
    float ySize;
    u8 bitfield; //0x1c, 1 to disable
    u8 padding[3];
    nw4r::ut::Link processBarLink; //0x20
}; //0x28
size_assert(ProcessBar, 0x28);

class CpuMonitor { //red bar
public:
    CpuMonitor(const nw4r::ut::Color color, float yOrigin): bar(color, yOrigin, 1.0f) {}; //inlined
    virtual void show(); //0x8 80238750 vtable 802a3d60
    virtual void hide();  //0xc 80238760
    virtual void measureBegin(); //0x10 802386dc
    virtual void measureEnd(); //0x14 80238714
    ProcessBar bar;
}; //0x2c
size_assert(CpuMonitor, 0x2c);

class CpuGpMonitor : public CpuMonitor { //cpumonitor's bar is the green
public:
    struct Next {
        void *gxFifoWritePtr; //from GXGetFifoPtrs
        u16 curGXDrawSyncToken;
        u8 padding[2];
        Next *next;
        CpuGpMonitor *cpuGpMonitor;
    }; //0x10
    CpuGpMonitor(const nw4r::ut::Color color, float yOrigin); //inlined
    void show() override; //80238804 vtable 802a3d48
    void hide() override;  //80238820
    void measureBegin() override; //80238770
    void measureEnd() override; //802387bc
    ProcessBar blueBar;
    u16 unknown_0x54;
    u8 padding[2];
    ProcessMeter *processMeter; //0x58
    Next begin;
    Next end;
}; //0x7c
size_assert(CpuGpMonitor, 0x7c);

class ProcessMeter : public Thread, public PerformanceView {
public:
    explicit ProcessMeter(u32 r4); //0x8023883c
    ~ProcessMeter() override; //80239628 vtable 802a3ce0
    void *Run() override; //80238d8c


    //0x48, vtable parent 2 802a3cf8
    void measureBeginFrame() override;          //0x8  thunk 802396b8 func 80238a94
    void measureEndFrame() override;            //0xc  thunk 802396b0 func 80238d10
    void measureBeginRender() override;         //0x10 thunk 802396a8 func 80238d20
    void measureEndRender() override;           //0x14 thunk 802396a0 func 80238d30
    void callbackDrawSync(u16 token) override;  //0x18 thunk 80239698 func 80238d40
    void draw() override;                       //0x20 thunk 80239690 func 80239338
    void setVisible(bool isVisible) override;   //0x24 thunk 80239688 func 80238f14
    void isVisible() override;                  //0x28 thunk 80239680 func 80238f3c

    void append(CpuMonitor *cpuMonitor); //80238f48
    void append(CpuGpMonitor *cpuGpMonitor); //80238f54
    void callbackDrawSyncStatic(); //80234a04
    void SetDrawSync(CpuGpMonitor::Next *next); //80238e38
    void drawSetting(float width, float height); //802393e0
    void draw(u32 videoTicks, float width, float height);

    nw4r::ut::Color lineColor; //0x4c
    float unknown_0x50[4];
    nw4r::ut::List processBarList; //0x60
    CpuGpMonitor::Next *beginNext;
    CpuGpMonitor::Next *endNext;
    ProcessBar bgBar; //0x74
    CpuMonitor cpuMonitor; //0x9c
    CpuGpMonitor cpuGpMonitor; //0xc8
    u32 linesCount; //0x144
    float bgYSize; //0x148
    u8 unknown_0x14C[4];
    u16 drawSyncToken; //0x150
    bool visible; //0x152
    u8 unknown_0x153;
}; //0x154
size_assert(ProcessMeter, 0x154);
}//namespace EGG
#endif