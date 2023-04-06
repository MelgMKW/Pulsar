#ifndef _EGGSCENE_
#define _EGGSCENE_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Fader.hpp>

namespace EGG {

class SceneManager;
class Scene;

class SceneCreator { //vtable got done away by the compiler
    virtual Scene *create(u32 sceneId); //0x8
    virtual void destroy(u32 sceneId);  //0xc
}; //0x4 

size_assert(SceneCreator, 0x4);
class Scene : public EGG::Disposer {
public:
    Scene(); //8023ad10
    ~Scene() override;     //8023ad84, vtable 802a3de0
    virtual void calc();   //0xc  80007f4c
    virtual void draw();   //0x10 80007f48
    virtual void enter();  //0x14 80007f44
    virtual void exit();   //0x18 80007f40
    virtual void reinit(); //0x1c 80007f3c
    virtual void incoming_child_destroy(); //0x20 80007f38
    virtual void outgoing_child_create(); //0x24 80007f34
    ExpHeap *parentHeap; //0x10
    ExpHeap *mem1Heap; //0x14
    ExpHeap *mem2Heap; //0x18
    void *unknown_0x1c; //0x1c
    Scene *parent; //0x20
    Scene *child;
    u32 id;
    SceneManager *manager; //0x2c
}; //0x30
size_assert(Scene, 0x30);

class SceneManager {
public:
    SceneManager(SceneCreator *creator); //8023addc
    virtual void calc();                //0x8  8023ae60 vtable 802a3e08
    virtual void draw();                //0xc  8023aeac 
    virtual void calcCurrentScene();    //0x10 8023b588
    virtual void calcCurrentFader();    //0x14 8023b5a8
    virtual void drawCurrentScene();    //0x18 8023b800
    virtual void drawCurrentFader();    //0x1c 8023b890
    virtual void createDefaultFader();  //0x20 8023b8b0
    void createScene(u32 sceneId, Scene *parent); //8023b0e4
    void createChildScene(u32 sceneId, Scene *parent); //8023b248
    Scene *findParentScene(u32 sceneId); //8023b940
    void destroyScene(Scene *scene); //8023b3f0
    void destroyCurrentScene(bool destroyIfNoParent); //8023b2ac
    bool destroyToSelectSceneId(u32 sceneId); //8023b344 destroys from current scene until sceneId then switches to sceneId
    void setupNextSceneId(); //8023b910 non-official
    void incomingCurrentScene(); //8023b568
    void outgoingParentScene(Scene *parent); //8023b92c calls outgoing_child_create

    void reinitCurrentScene(); //8023aef8
    void changeUncleScene(u32 sceneId); //8023af84
    void changeSiblingScene(u32 sceneId); //8023afe0
    void fadeIn(); //8023ae4c non-official

    bool changeSiblingSceneAfterFadeOut(u32 sceneId); //8023afe8 initiates a fadeout and prepares a scene change
    bool reinitCurrentSceneAfterFadeOut(); //8023af18 initiates a fadeout and prepares a scene reinit
    SceneCreator *curSectionCeator; //0x4
    u8 unknown_0x8[4];
    Scene *currentScene; //0xc
    Scene *parentOfCurrent; //0x10
    u32 nextSceneId; //0x14
    u32 currentSceneId; //0x18
    u32 someKindOfSceneId; //0x1c
    u32 actionAfterFade; //0x20 0 changeUncle, 1 changeSibling, 2 outgoingParent, 4 destroyToSelect, 3 reinit
    ColorFader *colorFader; //0x24
    u32 nextSceneMEM; //0x28, 1 for mem2, unsure
    SceneCreator *nextSceneCreator; //0x2c



}; //0x30
size_assert(SceneManager, 0x30);

}//namespace EGG


#endif