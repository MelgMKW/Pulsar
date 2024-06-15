#ifndef _GAMESCREEN_
#define _GAMESCREEN_
#include <kamek.hpp>
#include <core/egg/3D/Screen.hpp>
#include <core/egg/3D/Camera.hpp>

class GameCamera;

class GameScreen : public EGG::Screen {
public:
    GameScreen(u32 r4, u32 idx); //8056581c idx is hudSlotId in races
    ~GameScreen() override; //80567130 vtable 808b4c20

    void Init(); //80566ca0
    void CalcDimensions(u32 screenCount); //80566e38 splits the TV space based on idx and total screen count
    void SetAndLoadProjection(u32 projType, u32 r5); //80566020
    void SetProjection(u32 projType, u32 r5); //805661e8
    void Set4_3AspectRatio();  //80566c20 sets width and height to 832/456, or rather by EGG::Screen::InitParams values
    void Set16_9AspectRatio(); //80566bb8 sets width and height to 608/456
    void SetAndLoadOrthoProj(u32 r4); //80565da0

    u8 unknown_0x60[0x68 - 0x60]; //0x48
    u32 idx; //0x68
    GameCamera* perspectiveCam; //0x6c
    EGG::OrthoCamera uiCamera; //0x70 used for UI, but essentially always kept at the default parameters
    float unknown_0x100[2];
    u32 r4ctorArg; //0x108

}; //0x10c

class ScreensHolder {
public:
    static ScreensHolder mInstance; //809c1868

    virtual ~ScreensHolder(); //8056572c vtable 808b4c04
    virtual void Init(u32 screenCount); //80565674
    virtual void Init(u32 screenCount, bool useSomeHeap); //805674a4
    virtual void vf_0x14(); //805656c4 
    static void Init();//8056483c

    u32 screenCount;
    GameScreen** gameScreens; //0x8 one per screen
};

#endif