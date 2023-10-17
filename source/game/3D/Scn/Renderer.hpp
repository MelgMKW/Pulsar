#ifndef _RENDERER_
#define _RENDERER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/3D/Scn/GameScreen.hpp>
#include <game/3D/Scn/ScnManager.hpp>


class Renderer : public EGG::Disposer {
public:
    static Renderer* cur[2]; //809c1848 1st is main, 2nd is created for stuff like Miis

    static ut::List renderList[2]; //809c1830 and 809c183c, one per scene

    Renderer(GameScreen& screen); //805642b8
    ~Renderer() override; //8056430c vtable 808b4bd0
    virtual void vf_0xC() = 0; //0xc
    virtual void Draw() = 0; //0x10

    void Remove(); //80564fbc uses the internal idx to choose the list
    void Remove(u32 listIdx); //805652ac
    void RemoveFrom1stList(); //805652c4 from 
    void RemoveFrom2ndList(); //805652c4 from 
    void Register(u32 listIdx); //80565114 never appends
    void Register2ndList(); //80565268 never appends screen
    void Register(bool appendScreen); //805652e8
    void RegisterAndAppendScreen(); //80565164 will always appendScreen


    GameScreen& screen; //0x10
    u32 listIdx;
    nw4r::ut::Link link; //0x18
    ScnMgr* scnMgr; //0x20
};


class RendererWithModels : public Renderer {
public:
    RendererWithModels(GameScreen& screen); //80564378
    ~RendererWithModels() override; //805643cc vtable 808b4bb8
    virtual void vf_0xC() override; //0xc 80564444

    void Draw() override; //0x10 80564458 sets proj to type currently held by Screen and then calls ScnMgr's DrawModels
    virtual void DrawWithProjection(u32 projType, u32 r5); //0x14 805644a8
    virtual void DrawModels() = 0; //0x18

};

//virtually identical to models because Draw calls DrawWithProjection with r4 = screen's cur projType and r5 0, which is essentially what Models' Draw does already
class RendererMixed : public RendererWithModels {
    RendererMixed(GameScreen& screen); //80564618
    ~RendererMixed() override; //805646e4 vtable 808b4ba0
    virtual void Draw() override; //0x10 8056466c functionally does the exact same thing as Models' draw
}; //0x24




//IMPLEMENTATIONS
class RendererRaceUIOrtho : public Renderer { //the screen it's tied with covers the whole TV area, this is used for UI
public:
    RendererRaceUIOrtho(GameScreen& screen); //805b423c
    ~RendererRaceUIOrtho() override; //805b4280 vtable 808b7278
    void vf_0xC() override; //805b4314
    void Draw() override; //805b42d8 sets proj to ortho then draws the cur section
};

class RendererRaceUIScreen : public Renderer { //renders UI that is specific to a single part of the TV, which in mkwii is only racers names (?)
    RendererRaceUIScreen(GameScreen& screen); //805b4110 
    ~RendererRaceUIScreen() override; //805b4154 vtable 808b728c
    void vf_0xC() override; //805b4318
    void Draw() override; //0x10 805b41ac
};

class RendererRaceModels : public RendererWithModels {
public:
    RendererRaceModels(GameScreen& screen, ScnMgr* scnMgr); //805b431c
    ~RendererRaceModels() override; //805b4684 vtable 808b72e0

    void Draw() override; //0x10 805b4488 
    void DrawModels() override; //0x18 805b4368
    virtual void vf_0x1c(); //805b43bc
};

class RendererMenu : public RendererMixed { //draws the UI in menu scenes but can also draw models (character models, miis, karts)
public:
    RendererMenu(GameScreen& screen); //8059eca8 also creates a CameraLook
    ~RendererMenu() override; //805671ac vtable 808b69b0
    void vf_0xC() override; //8059ed30
    void Draw() override; //8059f508
    void DrawModels() override; //0x18 8059ed68 

    u8 unknown_0x24[0x2c - 0x24];
    GameScreen* modelsScreen; //0x2c different from the ctor's one
    ScnMgr* scnMgr; //0x30
}; //0x34

class RendererGlobe : public RendererMenu {
public:
    RendererGlobe(GameScreen& screen); //80567170
    ~RendererGlobe() override; //80567268
};

class RendererMii : public RendererMixed {
public:
    RendererMii(GameScreen& screen); //80564688
    ~RendererMii() override; //805647bc vtable 808b4b88
    void DrawModels() override; //0x1c 80564760
    u8 unknown_0x24;
    u8 padding[3];
}; //0x28

//809c1858 Renderer

#endif