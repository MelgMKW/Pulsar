#ifndef _EGG_DISPLAY_
#define _EGG_DISPLAY_
#include <types.hpp>
#include <core/egg/Thread.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/ut/Color.hpp>

namespace EGG {

void DrawDoneCallback(); //801780b4
void PostRetraceCallback(u32 retraceCount);

class Video {
public:
    static u32 GetTickPerVRetrace(u32 format); //80243e70
    static u32 GetTickPerVRetrace(); //80243ed0
    GX::RenderModeObj* Configure(GX::RenderModeObj* newRenderMode, u32 r5); //80243d6c returns previous
    GX::RenderModeObj* Initialize(GX::RenderModeObj* newRenderMode, u32 r5); //80243d18 returns previous
    static GX::RenderModeObj* GetStandardRenderModeObj(const GX::RenderModeObj** defaultObjs); //80243db4
    GX::RenderModeObj* mode;
    u32 bitfield;
    u32 unknown;
};//total size 0xc

class Display {
public:
    Display(u8 timeBtwFrames); //80219e68
    bool clear;
    u8 padding[3];
    virtual void beginFrame(); //80219eb4 vtable 802a2b28
    virtual void beginRender(); //80219fa8
    virtual void endRender(); //80219fac
    virtual void endFrame(); //80219fb0
    virtual void getTickPerFrame(); //80219eb0
    void copyEFBtoXFB(); //80219fb4
    void CalcFrequency(); //8021a06c
    u8 timeBtwFrames; //0x8
    u8 unknown_0x9;
    u8 padding2[2];
    u32 unknown_0xc; //0xC
    u32 frameCount;
    ut::Color clearColor; //0x14 setcopyclear
    u32 clearZ; //0x18 same as above
    u32 tick; //0x1c
    u32 frequency; //0x20
    float unknown_0x24;
}; //0x28

class AsyncDisplay : public Display {
public:
    static void HandleAlarmWrapper(OS::Alarm* alarm, OS::Context* context); //8020fd10

    AsyncDisplay(u8 timeBtwFrames); //8020fd18
    void beginFrame() override; //8020fe24 vtable 802a26e0
    void beginRender() override; //8020ff98
    void endRender() override; //8020ff9c
    void postVRetrace(); //80210024
    void startSyncNTSC(u8 r4); //8020fd8c
    void HandleAlarm(OS::Alarm* alarm, OS::Context* context); //8020fd10
    OS::Alarm syncAlarm; //0x28
    u8 unknown_0x54[4];
    OS::ThreadQueue threadQueue; //0x58
    u8 unknown_0x64[0x10];
    u8 startSyncr4; //0x70
    u8 padding[3];
    u32 tickPerVRetraceNTSC; //0x74
    u32 tickPerVRetrace; //0x78
    u8 unknown_0x7c[4];
    u32 postVITick; //0x80
    u32 unknown_0x84;
}; //0x88

}//namespace EGG
#endif