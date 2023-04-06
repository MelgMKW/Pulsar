#ifndef _ROOTSCENE_
#define _ROOTSCENE_
#include <game/Scene/BaseScene.hpp>

class RootScene : public BaseScene {
public:
    RootScene *sInstance; //0x809bd740
    RootScene(); //80542878
    ~RootScene() override; //805129a8 vtable 808b3c48
    void calc() override;   //0xc  80543c88
    void draw() override;   //0x10 80543c8c
    void enter() override;  //0x14 80543b84
    void exit() override;   //0x18 80543c84

    void CreateInstances(); //80542d4c creates stuff like AudioManager, InputData etc...
    void InitInstances(); //805438b4

    u8 unknown_0xc70[8];
    EGG::ExpHeap *audioHeap; //0xc78
    u8 unknown_0xc7c[0xcd8 - 0xc7c]; //0xc7c
}; //0xcb8


#endif