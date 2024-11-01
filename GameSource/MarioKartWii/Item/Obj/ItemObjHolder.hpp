#ifndef _ITEMOBJHOLDER_
#define _ITEMOBJHOLDER_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/Item/Obj/ItemObjVariants.hpp>

namespace Item {

class ObjHolder { //one instance per objID
public:
    ObjHolder(); //80795cc8
    ~ObjHolder(); //807994dc

    void HideAll(); //80795d94
    void Init(ItemObjId id, u32* initialIdx); //80795ccc
    void Update(); //80796470
    void Spawn(u32 quantity, ItemObj* usedObjHolder, u8 playerId, const Vec3& playerPos, bool r8); //80795e04 usedObj is filled by the function for each obj used
    int GetTotalItemCount() const; //807974ac held by players + body count
    void UpdateModelPositions(); //80796b30

    bool ProcessRecvEVENT(RKNet::EVENTAction action, u16 recvEntryValueunk2, const EVENTBuffer::Entry& entry, u32 time, bool r8); //80796ca0
    Obj* ProcessRecvShootEVENT(u16 recvEntryValueunk2, const EVENTBuffer::Entry& entry, bool isBreak, bool isDrop, u32 unused = 0); //80796f70 for actions Shoot, HitDragged, Drop
    bool ProcessRecvHitFreeEVENT(const EVENTBuffer::Entry& entry); //80797140
    void OnFinishThrow(ObjThrowable* objThrowable); //80796bbc
    bool SortObjs(); //80796348
    void OnObjKillFinish(Obj* objKillFinished); //80795f68 called when an obj has finished being killed

    ItemObjId itemObjId;
    Obj** itemObj; //0x4
    u32 capacity; //unsure what the diff is with limit
    u32 capacity2;
    u32 bodyCount; //0x10 count on the track, including trailing/spinning
    u32 spawnedCount; //0x14
    u32 finishedThrowCount; //0x18 only incremented when the object has finished its throw (for example the fib growing) movement/anm
    u32 limit; //0x1c
    u8 unknown_0x20[0x24 - 0x20];
};//Total Size 0x24
size_assert(ObjHolder, 0x24);

}//namespace Item
#endif