#ifndef _MENUDRIVERMODEL_MGR_
#define _MENUDRIVERMODEL_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/3D/Model/Menu/MenuModelMgr.hpp>

class Mii;
class MiiHeadsModel;
class ToadetteHair;

class DriverModelAnmCalculator {
public:
    DriverModelAnmCalculator(); //inlined
    virtual ~DriverModelAnmCalculator(); //8081e74c vtable 808d6dc0

    void Determine(CharacterId charId, KartId kartId, u32 type); //80831c1c type 1 = wink, 2 = gut
    static const char* GetPrefix(KartId id); //80831d20 sel, kart, etc... id = -1 means sel
    u32 state;
    char anmName[0x10];
}; //0x18

class MenuDriverModel : public MenuModel {
public:
    enum State {
        MENUDRIVERMODEL_STATE_ONCHARSELECT = 1,
        MENUDRIVERMODEL_STATE_ONKARTSELECT = 2
    };
    MenuDriverModel(); //8082f860
    ~MenuDriverModel() override; //80830708 vtable 808d8c44
    void Init() override;  //0xc 8082f8f8
    void Update() override; //0x10 8082ff0c
    void SwitchState(u8 playerId, State newState); //8082fb78 for example with state == 2, will switch to OnKartAnms
    void Draw(u8 playerId); //80830a80 toggles chars not shown off so it only shows one model at a time

    u8 unknown_0x4[4];
    State state; //0x8
    ModelTransformator* charSelTransformator; //0xC
    ModelTransformator* onKartTransformator; //0x10
    u8 unknown_0x14[4];
    u32 id; //0x18
    u8 unknown_0x1c[0x28 - 0x1c];
}; //0x28

class MenuDriverModelMgr {
public:
    struct Player {
        CharacterId id;
        bool isVisible;
        u8 padding[3];
        MenuDriverModel* playerModel;
    }; //0xC

    MenuDriverModelMgr(u8 playerCount); //80830180
    virtual ~MenuDriverModelMgr(); //80831bd4 vtable 808d8c38
    void Update(); //808307b0
    void TogglePlayerModel(u8 playerId, bool isVisible); //80830c3c
    void SetPlayerCharacter(u8 playerId, CharacterId id); //80830d00 updates players[id] values
    void PrepareDriverOnKartAnms(u8 playerId); //80830c64 prepares a new Transformator since the model has 2 "stances", alone and on a kart

    MenuDriverModel* models; //0x4
    u8 playerCount; //0x8
    u8 modelCount; //0x9 playerCount * 2 (for miis) + 24 characters
    u8 padding[2];
    u32 longestChrLength; //0xC in frames
    Player players[4]; //0x10
    u8 unknown_0x40[4]; //0xc
    Mii* miis; //0x44 one per player
    MiiHeadsModel* miiHeads; //0x48 one per player
    ToadetteHair* bangs; //0x4c
    u32 unknown_0x50; //0x50
}; //0x54




#endif