/*
Stebler, CLF (main documentation), Melg
*/
#ifndef _ITEMMANAGER_
#define _ITEMMANAGER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/Item/Obj/ItemObjHolder.hpp>
#include <MarioKartWii/Item/ItemPlayer.hpp>
#include <MarioKartWii/Kart/KartPointers.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

class DriverController;
class DriverMgr;

namespace Item {
class Player;

class Manager {
public:
    static Manager* sInstance; //809c3618
    static Manager* CreateInstance(); //80799138
    static void DestroyInstance(); //80799188
    Manager(); //807992d8 inlined
    ~Manager(); //80799670 inlined
    void Init(); //80799794
    void Update(); //80799850
    void CreateItemDirect(); //80799fbc
    void GenerateItemDirect(); //8079a12c
    void SpawnCloudForLocal(u8 playerId); //8079a298
    void SpawnCloudForRemote(u8 playerId); //8079a3b8 called online when someone gets a TC, sends a USE TC EVENT
    int CheckKartCollision(const Kart::Player& kartPlayer); //returns number of items hit
    void InitItemDirects(); //80799e50

    void UpdatePlayers(); //80799acc inlined
    void UpdateObjHolders(); //80799f8 inlined
    void UpdateAllObjModelPos(); //807999a0 inlined
    void UpdateTotalItemCountMinus30(); //80799a50 inlined

    static int GetHeldCount(ItemObjId itemObjId); //8079a65c
    static void DoSomethingWithFIBObjTevColors(); //8079a5f4
    static bool IsThereCapacityForItem(ItemId id); //80799be8 is behaviour's numberOfItems less than (objHolderCapacity - objHolder totalCount)

    EGG::TDisposer<Manager> disposer; //80798f9c vtable 808d1960
    u8 playerCount; //0x10
    u8 unknown_0x11[3];
    Player* players; //0x14
    Player* otherLocalOnlinePlayersplayer[12]; //0x18
    ObjHolder itemObjHolders[0xF]; //0x48 One per objId
    Obj* curItemObj[16]; //0x264
    Obj dummyObj; //0x2a4 base one? dummy?
    s32 totalItemCountMinus30; //0x42c presumably 30 is a maximum? the game checks if the value is > -5, ie there are fewer than 25 items
};//Total Size 0x430
size_assert(Manager, 0x430);

DriverMgr* GetDriverMgr(); //80790e30
u16 GetKMPObjectsCount(); //80790e3c
const KMP::Holder<GOBJ>* GetGOBJHolder(u16 idx); //80790e6c
u16 GetKMPObjectId(const KMP::Holder<GOBJ>& gobj); //80790e60
bool IsTT(); //80790e1c
bool IsAwards(const DriverMgr& driverMgr); //80790e28
float XZVECMag(Vec* Vec); //807a18ec vec.y is set to 0
void GetQuatFromMat(Quat* dest, const Mtx34& src); //807b9dd4 probably global or another class

}//namespace Item

#endif