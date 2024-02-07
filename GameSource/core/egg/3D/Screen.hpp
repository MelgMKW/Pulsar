#ifndef _EGG_SCREEN_
#define _EGG_SCREEN_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Frustum.hpp>

namespace EGG {

struct ViewPort { //unofficial
    float left;
    float top;
    float wd;
    float ht;
    float nearz;
    float farz;
};

class Screen : public Frustum {
public:
    Screen(); //8023d2b4
    Screen(const Screen& other); //8023d840
    ~Screen() override; //8022014c vtable 802a3f0c
    void LoadDirectly() override; //8023d4e8
    void CopyToG3D(g3d::Camera& camera) override; //8023d67c

    ViewPort& GetViewPort(); //8023dbd8

    u32 unknown_0x3C;
    float unknown_0x40[2];

    ViewPort viewPort; //0x48
}; //0x60
}//namespace EGG
#endif