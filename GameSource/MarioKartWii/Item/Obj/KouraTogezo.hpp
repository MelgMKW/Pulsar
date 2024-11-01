#ifndef _ITEMOBJKOURATOGEZO_
#define _ITEMOBJKOURATOGEZO_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObjVariants.hpp>

//_sinit_ at 807aea78
namespace Item {

class ObjKouraTogezoBase : public ObjTargeting {
    void SpawnModel() override; //0x18 807b3efc vtable 808d25a8
    u8 unknown_0x24c[0x280 - 0x24c];
    Item::Player* playerTargeted; //0x280
    u8 unknown_0x284[0x2bc - 0x284];
}; //0x2bc

class ObjKouraTogezo : public ObjKouraTogezoBase, public ObjExplosion { //blue shell actually inherits a second class also used by reds and bombs
public:
    static Obj** CreateArray(u32 count); //807ab9e0
    static void* SendOrExtractShootEVENT(void* packet, Obj* obj, bool extractOrSend); //807ae5d0

    /*blue shells:
    -first fly following item routes until a target (1st) is acquired (through distance)
    -then once they approach 1st, they home in, leaving routes and instead moving towards the target
    -then once they're close enough, they dive in and lower their altitude to a set one above the player
    -then they over for a few frames at that set altitude
    -then they explode from that altitude
     */
    enum State {
        STATE_SPAWNING,
        STATE_ROUTEFLYING,
        STATE_HOMING_IN,
        STATE_DIVING_IN,
        STATE_HOVERING,
        STATE_EXPLODING,
    };

    ObjKouraTogezo(); //807abc14
    //ObjKouraTogezoBase vtable 808d23d8 at 0x0
    void RemoveFromScn() override;  //807abf2c 
    void InitSelf() override; //0x8 807ac008
    void UpdateModelPosition() override;  //0x10 807ac7d4
    void UpdateModelPositionNoClip() override; //0x14 807ac9ec
    void SpawnModel() override; //0x18 807abf70
    bool SetInitialPosition(PlayerObj& playerObj) override; //0x20 807ac634
    int OnKill() override; //0x24 807ae414
    void OnFinishKill() override; //0x2c 807ae574
    void vf_0x30() override; //0x30 807ae6ec
    void Reset(); //807ac49c
    void ResetTargeting(); //807b3eec sets playerTargeted ptr to nullptr

    //ObjExplosion vtable 808D2410 at 0x2bc
    ~ObjKouraTogezo() override; //thunk 807aeae4 func 807ae9bc
    void UpdateThunk(); //807a38f8
    void Update(); //807ad118

    void UpdateRouteFlying(); //807ad5ec before the shell has acquired a target
    void UpdateHomeIn(); //807ad824 homing in towards the target
    void UpdateDiveIn(); //807ad958 finished homing in, now dives straight down
    void UpdateHover(); //807adc5c
    void UpdateExplosion(); //807ae34c
    u8 CalcTargetedPlayerId() const; //807ac1a8
    bool AcquireTarget(u8 playerId, u32 r5); //807b45b0 returns true if acquired, the shell stops following the route and goes for the player
    u8 GetTargetedPlayerId() const; //807ae8b0 already calculated

    u8 unknown_0x2dc[0x2ec - 0x2dc];
    u8 targetedPlayerId; //0x2ec
    u8 unknown_0x2ed[0x330 - 0x2ed];
    ModelDirector* bombCore; //0x330
    u8 unknown_0x334[4];
};
size_assert(ObjKouraTogezo, 0x338);
}//namespace Item

#endif