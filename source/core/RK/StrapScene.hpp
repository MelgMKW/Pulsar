#ifndef _STRAPSCENE_
#define _STRAPSCENE_
#include <core/RK/RKSceneManager.hpp>
#include <core/egg/Thread.hpp>
#include <core/nw4r/g3d/res/ResFile.hpp>

class StrapScene : public RKScene {
    StrapScene(); //800072c0
    ~StrapScene(); //80007448 vtable 802585b0
    void calc() override;   //0xc  800079d0
    void draw() override;   //0x10 80007bc8
    void enter() override;  //0x14 800074d8
    void exit() override;   //0x18 80007f2c
    bool CheckInput(); //800077c8 to skip strap screen, returns true if button was pressed
    static void LinkModule(); //800074a4
    void *decompStrapSZS; //0xc70 english.szs for example
    nw4r::g3d::ResFile strapBrres; //0xc74
    EGG::TaskThread *taskThread;
    u8 unknown_0xc78[0xc80 - 0xc78];
    GXTexObj textures[2]; //0xc80 SZS has 2 tex0
    u32 frameCount;  //0xcc0
    u32 frameCount2; //0xcc4
    bool buttonWasPressed; //0xcc8
    u8 padding[3];
    u8 unknown_0xccc[2];
    u16 input; //0xcce
    u8 unknown_0xcce[0xcd8 - 0xcce]; //0xcc8
}; //0xcd8


#endif