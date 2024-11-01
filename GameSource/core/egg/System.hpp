#ifndef _EGGSYSTEM_
#define _EGGSYSTEM_
#include <types.hpp>
#include <core/rvl/os/OSContext.hpp>
#include <core/rvl/os/OSAlarm.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Audio/AudioMgr.hpp>
#include <core/egg/3D/XFB.hpp>
#include <core/egg/ProcessMeter.hpp>
#include <core/egg/Display.hpp>
#include <core/RK/RKSceneManager.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace EGG {

void AlarmHandler(OS::Alarm* alarm, OS::Context* context); //8020fd10

class TSystem { //names obtained from BBA
public:
    static TSystem mInstance; //802a4080
    static TSystem* sInstance; //80385fc8
    static TSystem* sInstance2; //80386F60
    virtual Video* GetVideo(); //0x8 800099ac vtable 80270c2c
    virtual Heap* GetSystemHeap(); //0xC 800099b4
    virtual Display* GetDisplay(); //0x10 80009818
    virtual XfbManager* GetXFBMgr(); //0x14 800099bc
    virtual PerformanceView* GetPerfView(); //0x18 80009830
    virtual SceneManager* GetSceneMgr(); //0x1C 80009828
    virtual ExpAudioMgr* GetAudioMgr(); //0x20 800099c4
    virtual void OnBeginFrame(); //0x24 80009820
    virtual void OnEndFrame(); //0x28 80009824
    virtual void InitRenderMode(); //0x2c 80009190
    virtual void InitMemory(); //0x30 80242504
    virtual void Run(); //0x34 8024269c
    virtual void Initialize(); //0x38 80008fb4

    void* MEM1ArenaLo;
    void* MEM1ArenaHi;
    void* MEM2ArenaLo;
    void* MEM2ArenaHi;
    u32 memorySize; //0x14
    ExpHeap* EGGRootMEM1; //0x18
    ExpHeap* EGGRootMEM2;  //0x1C
    ExpHeap* EGGRootDebug; //0x20
    ExpHeap* EGGSystem;  //0x24
    void* heapSystem; //thread
    u32 unknown_0x2C; //just the start of mem1?
    u32 unknown_0x30; //idk
    u32 sysHeapSize;
    u32 gxFifoBufSize;
    GX::RenderModeObj* mode;
    ExpAudioMgr* audioManager; //0x40
    Video* video; //0x44
    void* xfbManager; //0x48
    AsyncDisplay* asyncDisplay; //0x4c
    ProcessMeter* processMeter; //0x50
    SceneManager* sceneManager; //0x54 //actually a RKSceneManager
};
}//namespace EGG


#endif