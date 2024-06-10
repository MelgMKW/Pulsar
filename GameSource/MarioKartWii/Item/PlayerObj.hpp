#ifndef _ITEM_PLAYEROBJ_
#define _ITEM_PLAYEROBJ_

#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Kart/KartPointers.hpp>

namespace Item {
class Player;

class PlayerObj { //most of the values are only updated when an item is used or tethered
public:
    enum UseType {
        ONLY_USE, //mushroom

        //TETHERED ITEMS = the 3 next use types
        TRAIL, //green shell          
        TRIPLE_TRAIL, //triple banana          
        SPIN, //triple green shells          


        NO_ITEM
    };
    static Ptmf_0A<PlayerObj, void> PrepareHandlers[5]; //808d18d0, one per use type prepare functions as the item is about to spawn
    static Ptmf_0A<PlayerObj, void> UpdateHandlers[5]; //808d1900, one per use type
    PlayerObj(); //80791760
    ~PlayerObj(); //8079765c
    void Init(Player* itemPlayer); //80791840

    void TrailPrepare(); //80792b08
    void TripleTrailPrepare(); //807931dc
    void SpinPrepare(); //8079455c

    void SpinCalc(); //807941f0 calculates the parameters of the rotation of the spin, this is called by both prepare and update

    void UpdateTetheredItems(); //8079231c updates UseType 1-3 BEFORE they've been released
    void TrailUpdate(); //80792c68
    void TripleTrailUpdate(); //8079356c
    void SpinUpdate(); //80794694

    void UpdateRemote(); //80795668

    void UseItem(bool isRemote); //80791910 r4 might be isRemote?
    void LoseItem(u32 playerIdx); //80795350 unsure what playerIdx does, only used in onlineRaces
    bool UpdateParams(); //80791e5c positions, matrixes etc... returns true if scale was changed

    void ComputeWheelPosRelativeToKart(); //807955c4
    Kart::Link kartLink; //0x0
    Player* itemPlayer; //0xC
    u8 playerId; //0x10
    u8 padding[3];
    ItemObjId itemObjId; //0x14 seems to only change for items you can hold "behind" (including triple shells)
    ItemId itemId; //same 0x18
    u32 useType; //0x1c 0x0 if can only be used (mushroom eg) 0x1 if trailing behind 0x2 if trailing behind triples, 0x3 if spinning, 0x4 if no item
    ItemObj* usedObjs[3]; //0x20 stored by ObjHolder::Spawn

    Vec3 unknown_vecs0x2c[3]; //0x2c

    u32 activeItemCount; //0x50 eg 0x2 if 2 remaining spinning shells
    ItemObjId unknown_0x54;

    Mtx33 transposeKartRotMtx; //0x58 col 1 2 3 of kart's transMtx

    Vec3 playerPos; //0x7c 4th col of kart's transMtx
    Vec3 playerSpeed; //0x88
    float engineSpeed; //0x94
    float speedRatioCapped; //0x98
    Vec3 posDifference; //0x9c playerPos - prevPlayerPos
    float hopPosY; //0xa8
    bool unknown_0xac; //0xac
    u8 padding2[3];
    Vec3 kartScale; //0xb0
    Vec3 wheelPosRelativeToKart; //0xbc Inv(KartTransMtx) * WheelPos
    float backToCenterKartVertDistance; //0xc8 2nd (bike) or 4th (kart) wheel YPos - kartYPos
    float wheelieCorrection; //0xcc 80791f70 too lazy so this name'll do for now
    Vec2 rotatingRadius; //0xd0
    float rotatingRadiusXTimesParam; //0xd8 0.8 for karts, 0.9 for bikes
    Vec2 rotatingDistance; //0xdc used as itemScaleFactor
    Vec3 itemPos; //0xe0 relative to the player
    u8 unknown_0xf0[0xc];
    Vec3 unknown_vecs0xfc[3];

    u8 unknown_0x120[0x148 - 0x120];

    void* unknown_0x148[2]; //0x148
    u8 unknown_0x150[4];
    bool isNotDragged; //0x154
    u8 unknown_0x155[0x174 - 0x155];
    u16 spawnedObjs[3]; //0x174
    u8 unknown_0x17a[0x180 - 0x17a];


}; //Total Size 0x180
size_assert(PlayerObj, 0x180);

}//namespace Item


#endif