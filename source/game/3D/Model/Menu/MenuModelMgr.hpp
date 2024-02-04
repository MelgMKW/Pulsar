#ifndef _MENUMODEL_MGR_
#define _MENUMODEL_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/3D/Model/ModelDirector.hpp>

class TextureHolder;
class BackModelMgr;
class MenuDriverModelMgr;
class MenuKartModelMgr;

enum BackModelType {
    BACKMODEL_STOPWATCH,
    BACKMODEL_TROPHY,
    BACKMODEL_FLAG,
    BACKMODEL_BALOON
};


extern EGG::Allocator* menuAllocator; //80386e64, based on the address, probably for something low-level

class MenuModelBRRESHandle {
    MenuModelBRRESHandle(); //8081e284
    virtual ~MenuModelBRRESHandle(); //8081e29c vtable 808d6dcc

    bool BindDriverBRRES(CharacterId id); //8081e358
    bool LoadDriverModel(ModelDirector& dest, CharacterId id); //8081e78c

    bool BindKartBRRES(u8 playerId, KartId kartId, Team team); //8081e548 mdf_kart.brres of ys-allkart.szs for ex
    bool LoadKartModel(ModelDirector& dest, Team team); //8081edc0
    bool LinkDriverAnim(u8 playerId, ModelDirector& kartModel, CharacterId id); //8081eac4 used after selecting a char

    bool BindBackBRRES(BackModelType idx); //8081e658 binds handler to the brres
    bool LoadBackModel(ModelDirector& dest); //8081ef14

    bool MdlExists(const char* mdlName); //8081efdc

    g3d::ResFile menuModelBRRES; //0x4
}; //0x8

class MenuModel {
public:
    virtual ~MenuModel();
    virtual void Init(); //0xc 80831c18
    virtual void Update(); //0x10 80831c14
    virtual void ToggleVisible(bool isVisible); //0x14 80830a5c
    virtual void ToggleTransparent(bool isTransparent); //0x18 8059f4f0 see ModelDirector's same func

    ModelDirector* model; //0x4
};

class MenuModelMgr {
public:
    static MenuModelMgr* sInstance; //809c1988
    static MenuModelMgr* CreateInstance(); //8059dfbc
    static void DestroyInstance(); //8059e04c
    MenuModelMgr(); //8059e080 inlined
    void Start(); //8059e1fc
    void Init(u8 playerCount, void* funcInr5); //8059e250
    void Update(); //8059e4a8
    void RequestDriverModel(u8 playerId, CharacterId id); //8059e568
    void RequestKartModel(u8 hudSlotId, KartId id); //8059e580
    void RequestBackModel(BackModelType type); //8059e598
    void TogglePlayerModel(u8 playerId, bool isVisible); //8059e5a4
    GX::TexObj* GetTexObj(u8 playerId); //8059e5dc
    TextureHolder* GetDriverTexture(u8 playerId); //8059e634
    TextureHolder* GetKartTexture(u8 playerId, u32 kartIdx); //8059e644
    void ToggleBackModel(bool isVisible); //8059e5d4
    void ResetKartModels(u8 playerId); //8059e550
    void Draw(u8 playerId); //8059e4fc toggles the chars/karts not shown off

    EGG::TDisposer<MenuModelMgr> disposer; //8059df24 vtable 808b68cc
    virtual ~MenuModelMgr(); //0x10 8059e0e4 vtable 808b68c0

    MenuDriverModelMgr* driverModels; //0x14
    MenuKartModelMgr* kartModels; //0x18
    BackModelMgr* backModelMgr; //0x1c
    bool isActive; //0x20 if false, all models freeze and stop changing/animating
    u8 playerCount; //0x21 probably displayed models count?
    u8 padding[2];
    TextureHolder* driverTextures; //0x24 1 per 0x21
    TextureHolder* backTexture; //0x28
    EGG::Heap* otherHeap; //0x2c
    u8 unknown_0x30[0x3c - 0x30];
    EGG::Heap* heap; //0x3c
}; //0x40

#endif