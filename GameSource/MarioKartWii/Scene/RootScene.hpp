#ifndef _ROOTSCENE_
#define _ROOTSCENE_
#include <MarioKartWii/Scene/GameScene.hpp>

class RootScene : public BaseScene {
public:
    static RootScene* sInstance; //809bd740
    static void RequestRootScene(); //80543b10 creates a GameSceneCreator and request a scene change with it, only works if no gamescene has been created yet
    RootScene(); //80542878
    ~RootScene() override; //805129a8 vtable 808b3c48
    void calc() override;   //0xc  80543c88
    void draw() override;   //0x10 80543c8c
    void enter() override;  //0x14 80543b84
    void exit() override;   //0x18 80543c84

    void CreateInstances(); //80542d4c creates stuff like AudioManager, Manager etc...
    void InitInstances(); //805438b4

    //Inlined funcs
    void SetHeapsGroupId(u32 groupId); //80542a10
    void CreateArchiveMgr(); //80542a18 
    void CreateGroup1Instances(); //80542a80 nandmgr, rksysmgr, inputmgr, mimgr, cins
    void CreateAudioMgr(); //80542ae0
    void CreateScnMgrCreator(); //80542b5c
    void CreateRacedata(); //80542ba0
    void CreateEffectsMgr(); //80542be4
    void CreateHomeMenuMgr(); //80542c2c
    void CreateRKNetInstances(); //80542c74
    void CreateUIInstances(); //80542cc4

    u8 unknown_0xc70[8];
    EGG::ExpHeap* audioHeap; //0xc78
    u8 unknown_0xc7c[0xcd8 - 0xc7c]; //0xc7c
}; //0xcb8


#endif