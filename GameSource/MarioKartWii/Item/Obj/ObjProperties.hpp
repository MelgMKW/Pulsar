#ifndef _ITEMOBJPROPERTIES_
#define _ITEMOBJPROPERTIES_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Item/Obj/ItemEVENT.hpp>

namespace Item {
class Obj;

void LoadObjProperties(); //80790ad8
void InitAllObjProperties(); //80790afc


struct ObjProperties {
    static ObjProperties objProperties[15]; //809c2f48

    ObjProperties(const ObjProperties& rel); //80790e7c copy constructor from rodata's static array "copyFromRel"
    static void ComputeCapacities(); //80790fb8
    Obj** (*CreateArray)(u32 count); //0
    u32 limit; //0x4
    u32 competitionLimit;
    u32 capacity; //0xc
    u32 capacity2;
    u8 unknown_0x14[4];

    Ptmf_0A<Obj, void> updateObjThunkPtmf; //0x18
    int (*PrepareEVENTPacket)(const EVENTBuffer::Entry* recvEntry, Obj* obj, u32 r5); //0x24 also stores stuff, but unsure, returns size of the packet
    u32 eventPacketSize; //0x28
    u8 unknown_0x2c[4];
    float backwardDrawDistance; //0x30
    float forwardDrawDistance; //0x34   
    float unknown_0x38; //0x38
    float entitySmallRadius; //0x3c
    float entityBigRadius; //0x40
    float unknown_0x44;
    float entityScale; //0x48
    float unknown_0x4c[2];
    u8 unknown_0x54[0x58 - 0x54];
    bool canFallOnTheGround; //0x58
    bool canFallOnTheGround2; //0x59
    bool killOnCollision; //0x5a
    u8 unknown_0x5b[0x6c - 0x5b];
    float unknown_0x6c;
    bool unknown_0x70;
    u8 unknown_0x71[0x74 - 0x71];
}; // Total size 0x74
size_assert(ObjProperties, 0x74);

extern float greenShellSpeed;
extern float redShellInitialSpeed;
extern float redShellSpeed;
extern float blueShellSpeed;
extern float blueShellMinimumDiveDistance; //big because it's squared
extern float blueShellHomingSpeed;


}//namespace Item
#endif