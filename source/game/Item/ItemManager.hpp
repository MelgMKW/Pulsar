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



class ItemPlayer;
class KartModel;

class ItemManager {
public:
    static ItemManager *sInstance; //809c3618
    static ItemManager *GetStaticInstance(); //80799138
    static void DestroyStaticInstance(); //80799188
    ItemManager(); //807992d8 inlined
    ~ItemManager(); //80799670 inlined
    void Update(); //80799850
    void CreateItemDirect(); //80799fbc
    void GenerateItemDirect(); //8079a12c
    void SpawnCloud(); //8079a298
    int CheckKartCollision(Kart *kart); //returns number of items hit
    EGG::TDisposer<ItemManager> disposer; //80798f9c vtable 808d1960
    u8 playerCount; //0x10
    u8 unknown_0x11[3];
    ItemPlayer *players; //0x14
    ItemPlayer *otherLocalOnlinePlayersplayer[12];
    ItemObjHolder itemObjolders[0xF]; //One per objId 0x48
    ItemObj *curItemObj[16]; //0x264
    ItemObjBase dummyObj; //base one? dummy?
    u8 unknown_0x418[0x430 - 0x418];
};//Total Size 0x430
size_assert(ItemManager, 0x430);



#endif