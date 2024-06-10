#ifndef _ITEMOBJPROPERTIES_
#define _ITEMOBJPROPERTIES_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

namespace Item {
class Obj;

void LoadObjProperties(); //80790ad8
void InitAllObjProperties(); //80790afc


struct ObjProperties {
    static ObjProperties objProperties[15]; //809c2f48

    ObjProperties(const ObjProperties& rel); //80790e7c copy constructor from rodata's static array "copyFromRel"
    static void ComputeCapacities(); //80790fb8
    Obj** (*CreateArray)(u32 count);
    u32 limit; //0x4
    u32 competitionLimit;
    u32 capacity; //0xc
    u32 capacity2;
    u8 unknown_0x14[4];

    Ptmf_0A<Obj, void> updateObjThunkPtmf; //0x18
    int (*CalcEventPacketSize)(u32 r3, Obj* obj, u32 r5); //0x24 also stores stuff, but unsure
    u32 eventPacketSize; //0x28
    u8 unknown_0x2c[4];
    float backwardDrawDistance; //0x30
    float forwardDrawDistance;
    float unknown_0x38[7];
    u8 unknown_0x54[0x58 - 0x54];
    bool canFallOnTheGround; //0x58
    bool canFallOnTheGround2; //0x59
    bool unknown_0x5a[2];
    u8 unknown_0x5b[0x6c - 0x5b];
    float unknown_0x6c;
    bool unknown_0x70;
    u8 unknown_0x71[0x74 - 0x71];
}; // Total size 0x74

extern float greenShellSpeed;
extern float redShellInitialSpeed;
extern float redShellSpeed;
extern float blueShellSpeed;
extern float blueShellMinimumDiveDistance; //big because it's squared
extern float blueShellHomingSpeed;


}//namespace Item
#endif