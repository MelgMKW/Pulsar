/*
Stebler, CLF (main documentation), Melg
*/
#ifndef _ITEMMANAGER_
#define _ITEMMANAGER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/Item/Obj/ItemObj.hpp>
#include <game/Item/ItemPlayer.hpp>
#include <game/Race/Kart/KartPointers.hpp>
#include <game/KMP/Controller.hpp>
#include <game/System/Identifiers.hpp>




class KartModel;

namespace Item{
class Player;
class Manager {
public:
    static Manager* sInstance; //809c3618
    static Manager* GetStaticInstance(); //80799138
    static void DestroyStaticInstance(); //80799188
    Manager(); //807992d8 inlined
    ~Manager(); //80799670 inlined
    void Update(); //80799850
    void CreateItemDirect(); //80799fbc
    void GenerateItemDirect(); //8079a12c
    void SpawnCloud(u8 playerId); //8079a298
    int CheckKartCollision(const Kart& kart); //returns number of items hit
    EGG::TDisposer<Manager> disposer; //80798f9c vtable 808d1960
    u8 playerCount; //0x10
    u8 unknown_0x11[3];
    Player* players; //0x14
    Player* otherLocalOnlinePlayersplayer[12];
    ObjHolder itemObjolders[0xF]; //One per objId 0x48
    Obj* curItemObj[16]; //0x264
    ObjBase dummyObj; //base one? dummy?
    u8 unknown_0x418[0x430 - 0x418];
};//Total Size 0x430
size_assert(Manager, 0x430);

}//namespace Item

#endif