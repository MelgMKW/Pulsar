#ifndef _ITEMOBJKOURATOGEZO_
#define _ITEMOBJKOURATOGEZO_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

//_sinit_ at 807aea78
namespace Item {
class ObjKouraTogezo : public ObjTargeting { //blue shell actually inherits a second class also used by reds and bombs
public:
    static Obj** CreateArray(u32 count); //807ab9e0
    ObjKouraTogezo(); //807abc14
    void RemoveFromScn() override;  //807abf2c vtable 808d23d8
    void InitSelf() override; //0x8 807ac008
    void UpdateModelPosition() override;  //0x10 807ac7d4
    void UpdateModelPositionNoClip() override; //0x14 807ac9ec
    void SpawnModel() override; //0x18 807abf70
    bool SetInitialPosition(PlayerObj& playerSub) override; //0x20 807ac634
    void OnCollision() override; //0x24 807ae414
    void vf_0x2c() override; //0x2c 807ae574
    void vf_0x30() override; //0x30 807ae6ec

    void UpdateThunk(); //807a38f8
    void Update(); //807ad118

    bool AcquireTarget(u32 playerId); //807b45b0 returns true if acquired

    u8 unknown_0x24c[0x330 - 0x24c]; //will document later

    Item::Player* playerTargeted; //0x280
    u8 unknown_0x24c[0x330 - 0x24c]; //will document later
    ModelDirector* bombCore; //0x330
    u8 unknown_0x334[4];
};
size_assert(ObjKouraTogezo, 0x338);
}//namespace Item

#endif