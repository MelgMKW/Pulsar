#ifndef _RKSYSTEM_
#define _RKSYSTEM_
#include <types.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Audio/AudioMgr.hpp>
#include <core/egg/ProcessMeter.hpp>
#include <core/egg/Display.hpp>
#include <core/RK/RKSceneManager.hpp>
#include <core/rvl/gx/GXStruct.hpp>

//using namespace EGG;

class DiscCheckThread {
public:
    static DiscCheckThread* sInstance; //80385FC0
    static void Create(EGG::Heap* heap); //80008c10

};
#endif