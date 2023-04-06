#ifndef _GAMESCENE_
#define _GAMESCENE_
#include <core/RK/RKSceneManager.hpp>
#include <game/System/Archive.hpp>

enum SceneId {
    SCENE_ID_MENU = 0x1,
    SCENE_ID_RACE = 0x2,
    SCENE_ID_TEST = 0x3,
    SCENE_ID_GLOBE = 0x4,
    SCENE_ID_UNK5 = 0x5,
    SCENE_ID_UNK6 = 0x6,
    SCENE_ID_UNK7 = 0x7,
    SCENE_ID_UNK8 = 0x8,
    SCENE_ID_UNK9 = 0x9,
    SCENE_ID_UNK10 = 0xa,
    SCENE_ID_UNK11 = 0xb
};

class GameSceneCreator : public RKSceneCreator { //also creates the rootscene
public:
    Scene *create(u32 sceneId) override; //8054aa64 vtable 808b3cb0
    void destroy(u32 sceneId) override;  //8054ab28
};

class BaseScene : public RKScene { //used by RootScene only?
public:
    ~BaseScene() override; //8051a368 vtable 808b2d10
    void calc() override;   //0xc  8051c02c
    void draw() override;   //0x10 8051c028
    void enter() override;  //0x14 8051c024
    void exit() override;   //0x18 8051c020
    void reinit() override; //0x1c 8051c01c
    void incoming_child_destroy() override; //0x20 8051c010
    void outgoing_child_create() override; //0x24 8051c00c
}; //0xc70

class ArchiveLink {
    nw4r::ut::Link link;
    ArchivesHolder *holder;
    ArchiveSource source;
};

class GameScene : public BaseScene {
public:
    static const GameScene *GetCurrent(); //8051bed0, gets current scene from SceneManager and if id != 0 and != 5, returns it
    GameScene(); //8051a1e0
    ~GameScene() override; //8051a3c0 vtable 808b2c98
    void calc() override;   //0xc  8051b3c8
    void draw() override;   //0x10 8051bc78
    void enter() override;  //0x14 8051ab58
    void exit() override;   //0x18 8051b250
    void reinit() override; //0x1c 8051b7b0
    virtual bool isSpectating(); //0x28 8051b790
    virtual int vf_0x2c(); //0x2c 8051b798
    virtual void OnCalc() = 0; //0x30
    virtual void OnExit() = 0; //0x34
    virtual void OnEnter() = 0; //0x38 creates heaps, loads files, calls OnEnterEnd, CreateAndInitInstances amongst other things
    virtual void OnEnterEnd() = 0; //0x3c when enter has finished everything
    virtual void OnReinit(); //0x40 8051b8d0
    virtual void CreateAndInitInstances() = 0; //0x44 switches section and creates the relevant objects
    virtual void vf_0x48(); //0x48 8051b3c4
    virtual int GetScreenCount(); //0x4c 8051aa4c
    virtual int vf_0x50(); //0x50 8051b7a0
    virtual bool isPaused(); //0x54 8051b8d4 also updates stuff it it is paused in racescene
    virtual void vf_0x58(); //0x58 8051aa54
    virtual void vf_0x5c(); //0x5c 8051b9d0

    void FinalizeEnter(); //8051a4dc calls OnEnterEnd
    void AddArchiveHolder(ArchivesHolder *archive, ArchiveSource source); //80540450
    void FadeIn(); //8051a41c inlined
    void FadeOutToNewScene(); //8051a480 inlined
    void FadeOutToReinit(); //8051b094
    void ChangeScene(u32 sceneId); //8051afe8
    void UnmountArchives(); //8051aae8 inlined
    void SetFramerate(u8 frameRate); //8051af84 0 for 60fps?
    void Reset(); //8051b0f4 called on reinit
    void CreateChildScene(u32 sceneId); //8051b0e0

    ExpHeap *someSoundHeap; //0xc70
    nw4r::ut::List archivesLinkList; //0xc74 list of archive links
    ExpHeap *archiveHeapMem1; //0xc80, adjusted to the size of the archives, so not usable
    ExpHeap *archiveHeapMem2; //0xc84
    ExpHeap *structsMem1; //0xc88 used for stuff like controls, pages, sections, Kart etc...
    ExpHeap *structsMem2; //0xc8c
    u32 unknown_0xc90;
    ExpHeapGroup structsHeaps; //0xc94
    u8 unknown_0x18a0[0x18d4 - 0x18a0];
    ExpHeapGroup archiveHeaps; //0x18d4
    u8 unknown_0x24e0[0x2514 - 0x24e0];
    u32 someRandomThing; //0x2514 8051ac44
    u32 someRandomThing2; //0x2518 8051ac44
    void *randomTimes32; //0x251c
    void *random2Times32; //0x2520
    bool unknown_0x2530[2];
    u8 unknown_0x2532[0x2544 - 0x2532];
    u32 nextId; //0x2544
    u8 unknown_0x2548[0x254c - 0x2548];

};
#endif