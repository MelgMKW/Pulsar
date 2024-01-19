#ifndef _BACKMODEL_
#define _BACKMODEL_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/3D/Model/Menu/MenuModelMgr.hpp>

using namespace nw4r;
class BackModelMgr {
public:
    BackModelMgr(); //8082f408
    virtual ~BackModelMgr(); //8082f4d4 vtable 808d8b98
    void Start(); //8082f514
    void Update(); //8082f5f8
    void SetBackModel(BackModelType type, bool reAnimate); //8082f780 reAnimate only works if type = curType and plays the transition again
    void ToggleVisible(bool isVisible); //8082f84c

    ModelDirector* cur; //0x4
    ModelDirector* mdlArray; //0x8
    BackModelType curType; //0xC used to get scale from a float array as well as position
}; //0x10



#endif