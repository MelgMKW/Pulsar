#ifndef _KARTSTATUS_
#define _KARTSTATUS_

//Formerly PlayerSub1c
#include <kamek.hpp>
#include <game/Kart/KartLink.hpp>
#include <game/Kart/KartValues.hpp>

namespace Kart {

class Status {
public:
    explicit Status(const Values& values); //805943b4
    void Reset(); //8059455c
    void Init(); //80594594

    void UpdateFromInput(); //8059487c
    UnkType ComputeStartBoost(); //805959d4
    UnkType ApplyStartBoost(int startBoostIdx); //80595af8
    UnkType UpdateCollisions(); //80594bd4
    void StartOobWipe(u32 state); //805946f4
    virtual ~Status(); //80595cc4 vtable 808b6534
    u32 bitfield0; //bit flags: //0x4
    /*
    0x1         0 accelerate
    0x2         1 brake
    0x4         2 drift input
    0x8         3 drift (manual)
    0x10        4 oob, before being respawned
    0x20        5 wall 3 collision
    0x40        6 wall collision
    0x80        7 first frame of hop
    0x100       8 first frame of acceleration
    0x200       9 first frame of groundtime
    0x400       10 floor collision with the kart body
    0x800       11 floor collision with any wheel
    0x1000      12 floor collision with all wheels
    0x2000      13 stick left
    0x8000      15 airtime > 20
    0x10000     16 sticky road
    0x40000     18 ground
    0x80000     19 hop
    0x100000    20 boost
    0x800000    23 air start
    0x1000000   24 stick right
    0x2000000   26 mushroom boost
    0x8000000   27 charging a slipstream
    0x10000000  28 drift (auto)
    0x20000000  29 wheelie
    0x40000000  30 jump pad enabled
    0x80000000  31 ramp boost
    */
    u32 bitfield1; //0x8 bit flags: 
    /*
    0x1         0 hit by an item or an object
    0x2         1 first frame of respawn
    0x8         3 first frame of cannon
    0x10        4 in cannon
    0x20        5 first frame of trick
    0x40        6 in a trick
    0x80        7 offroad invincibility
    0x200       9 zipper collision
    0x400       10 over a zipper
    0x800       11 mushroom collision
    0x2000      13 zipper boost
    0x8000      15 zipper trick
    0x100000    20 mt boost
    0x400000    22 in a trick
    0x40000000  30 on a trickable surface
    0x80000000  31 in a star
    */
    u32 bitfield2; //0xC bit flags:
    /*
    0x1         0 charging a slipstream
    0x2         1 in a slipstream
    0x4         2 wheelie bump
    0x10        4 wheelie rotation
    0x80        7 shocked
    0x2000      13 post respawn
    0x4000      14 post respawn 2
    0x8000      15 in a mega
    0x10000     16 crushed
    0x40000     18 stopped
    0x80000     19 vanished
    0x400000    22 has jump pad dir
    0x8000000   27 in a bullet
    0x10000000  28 ink applied
    0x20000000  29 has a tc
    */
    u32 bitfield3; //0x10 bit flags:
    /*
    0x8         3 wall collision thing
    0x20        5 hwg (horizontal wall glitch)
    0x100       8 start boost charge
    */
    u32 bitfield4; //0x14 bit flags:
    /*
       0x1      0 cpu-controlled
       0x2      1 real local
       0x4      2 local
       0x8      3 remote
       0x10     4 automatic drift
       0x40     6 ghost
       0x1000   12 has stopped
    */
    Link* link; //0x18
    u32 airtime;
    u8 unknown_0x20[0x28 - 0x20];
    Vec3 floorNor;
    Vec3 unknown_0x34;
    u8 unknown_0x40[0x6b - 0x40];
    s32 hwgTimer;
    u8 unknown_0x70[0x74 - 0x70];
    u32 boostRampType;
    u32 jumpPadType; //essentially used to access jump pad properties array
    u8 unknown_0x7c[0x7f - 0x7c];
    u32 cnptId;
    u8 unknown_0x84[0x88 - 0x84];
    float stickX; //0x88
    float stickY; //0x8c
    u32 oobWipeState; //0x90
    s16 oobWipeFrame; //0x94
    bool bool_0x96;
    bool bool_0x97;
    u8 unknown_0x98[0x9c - 0x98];
    float startBoostCharge; //0x9c
    s32 startBoostIdx; //-1 when burning out
    u8 unknown_0xa4[2];
    s16 trickableTimer;
    u8 unknown_0xa8[0xc0 - 0xa8];
}; //Total size 0xc0

}//namespace kart

#endif