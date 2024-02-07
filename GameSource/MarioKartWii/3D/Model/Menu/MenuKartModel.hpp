#ifndef _MENUKartMODEL_MGR_
#define _MENUKartMODEL_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/3D/Model/Menu/MenuModelMgr.hpp>

namespace Pages {
class ModelRenderer;
} // namespace Pages


class UnkModelClass {
public:
    UnkModelClass(); //80832cbc
    ~UnkModelClass(); //80832cc0
}; //0x1c

class MenuKartDisplayModel : public MenuModel { //the models inside the kartSelect buttons
public:
    ~MenuKartDisplayModel() override; //8082f8b8 vtable 808d8c60
    TextureHolder* texture; //0x8
}; //0xC

class MenuKartModel : public MenuModel { //the main model but also the display model
public:
    MenuKartModel(); //80831f60
    ~MenuKartModel() override; //80831f84 vtable 808d8c8c
    void Init() override; //0xc 80832240
    void Update() override; //0x10 8083275c
    void Load(u8 playerId, CharacterId characterId, KartId kartId, EGG::Heap* heap, u16 width, u16 height); //80831fc4

    KartId kart; //0x8
    CharacterId character; //0xC
    EGG::Allocator* allocator; //0x10

    u8 unknown_0x10[0x18 - 0x10];
    MenuKartDisplayModel unk; //0x18
    u16 bitField; //0x24 1 = not unlocked
    u8 unknown_0x26[0x2c - 0x26];
}; //0x2c

class MenuKartModelMgr {
public:
    MenuKartModelMgr(u8 playerCount); //80832ae8
    virtual ~MenuKartModelMgr(); //808334a0 vtable 808d8c80
    void Update(); //8083300c
    void Load(); //80832d00 only loads if conditions (section, AllkartArchivesLoader state) are met
    void ToggleVisible(u8 playerId, bool isVisible); //808333ac
    void SetKartModel(u8 playerId, KartId id); //80833290
    void Reset(u8 playerId); //808332e8
    void Draw(u8 playerId); //808331c4 toggles karts not shown off
    MenuKartModel* GetMenuKartModel(u8 playerId, u32 mdlIdx); //80833474

    struct Player {
        MenuKartModel* modelsArray;
        u32 idx; //0x4 from 0 to 11
        bool hasLoadRequest; //0x8
        bool isLocked; //0x9
        bool isModelVisible; //0xA
        u8 padding;
        Team team; //0xC
    }; //0x10

    u8 modelCount; //0x4
    u8 playerCount; //0x5
    u8 padding[2];
    Player players[4]; //0x8

    u16 KartScale[2]; //0x48 converted from KartSelect's Vec2 and adjusted from Section's scale
    void (Pages::ModelRenderer::* prepareFunc)(u8); //0x4c
    u32 unknown_0x50;
    UnkModelClass* unk; //0x54
    u8 unknown_0x54[0x5c - 0x54];
}; //0x5c





#endif