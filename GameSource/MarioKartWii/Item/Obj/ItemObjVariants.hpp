#ifndef _ITEMOBJVARIANTS_
#define _ITEMOBJVARIANTS_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

namespace Item {
class ObjMiddle;
class ObjHolder;
class Player;

//throw behind, forward, dropping counts as a special cased behind throw
class ObjThrowable : public ObjMiddle { //this has a vtable but it doesn't inherit anything, it's one of the myriad of copies of Obj's vtable
public:
    void OnFinishThrow(); //807b6910
    //height also depends on speed because the game appears to try to keep time as a constant (for a given height)
    void SetInitialPositionImpl(PlayerObj& playerObj, u32 groundEffectDelay, bool isThrow, float speed, float throwHeight, float dropHeight); //807b7104
    float delayBeforeGroundEffect; //0x1a0 puff of smoke, small ground reaction, bomb standing up etc...
}; //0x1a4

class ObjTargeting : public ObjMiddle {
public:
    //vtable 808d2280
    float delayBeforeGroundEffect; //0x1a0 puff of smoke, small ground reaction, bomb standing up etc...
    u8 unknown_0x1a4[0x1ec - 0x1a4];
    Vec3 unknown_vec3s[8]; //0x1ec
}; //0x24c
size_assert(ObjTargeting, 0x24c);

class ObjExplosion {
public:
    //state is item dependant, see enums in the classes for bomb and kouratogezo
    virtual ~ObjExplosion(); //807a49b4 vtable 808d1c28
    u16 state; //0x2
    u8 padding[2];
    u32 nextState; //held at -1 if there is no next state
    u32 timer; //0xc
    u16* ptmfIdxArray; //0x14
    void* ptrToStructContainingPtmfArray; //0x18 807a4d74 here for example
    Obj* obj; //0x1c
}; //0x20

}//namespace Item
#endif