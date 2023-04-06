#ifndef _EGG_SCREEN_
#define _EGG_SCREEN_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Frustum.hpp>

namespace EGG {
class Screen : public Frustum {
public:
    Screen(); //8023d2b4
    ~Screen() override; //8022014c
    void LoadDirectly() override; //8023d4e8
    void LoadIntoCamera(nw4r::g3d::CameraData *data) override; //8023d67c
    u32 unknown_0x3C;
    float unknown_0x40[2];
}; //0x48
}//namespace EGG
#endif