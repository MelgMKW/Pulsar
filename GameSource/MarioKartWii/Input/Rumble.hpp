#ifndef _RUMBLE_
#define _RUMBLE_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <MarioKartWii/File/KRM.hpp>

namespace Input {

using namespace nw4r;
class ControllerHolder;

struct KRMEntry {
    u8 type; //0 or 1
    u8 unknown_0x1[0x4 - 0x1];
    union {
        char* type0Params;
        u16 type1Params[2];
    }params; //0x4
}; //0x8

class Rumble {
    virtual ~Rumble(); //80525c78 vtable 808b3108
    void Init(); //80525278 inlined
    void Request(const char* krmEntry0, s32 duration); //805252a4 inlined
    void Request(u32 duration, float f1); //805252e8 inlined
    int Update(); //80525334 0: disabled, 1: enabled, 3: stop
    const char* krmEntry0; //0x4
    const char* curKRMEntry0; //0x8
    u8 unknown_0xc[4];
    s32 duration; //0x10
    float requestArg;
    float unknown_0x18;
    u8 bitfield; //0x1c
    u8 unknown_0x1d[0x2c - 0x1d];
}; //0x2c

class RumbleController {
public:
    RumbleController(); //80525498
    virtual ~RumbleController(); //80525c38 vtable 808b30f0
    void Init(u32 subsCount, ControllerHolder* holder); //80525508
    void Update(); //8052570c
    void Stop(); //805255bc
    void DeactivateRumble(Rumble* rumble); //8052564c
    Rumble* Request(const char* krmEntry0, s32 duration, bool replaceActiveIfNoFreeRumble); //80525974
    void Request(u32 duration, bool replaceActiveIfNoFreeRumble, float f1); //80525a74
    Rumble* GetFreeRumble(bool replaceActiveIfNoFreeRumble); //80525b8c inlined the returned is considered active

    ut::List activeRumbles; //0x4
    ut::List freeRumbles; //0x10
    ControllerHolder* parent; //0x1c
    u8 unknown_0x20[0x10]; //0x20

}; //0x30



class KRMMgr { //name based on RequestRumble extensively loading class fields
    //no ctor
    virtual ~KRMMgr(); //80525204 vtable 808b30fc
    void Init(const KRM* vibrationKRM = nullptr); //805250c8
    KRM* rawKRM; //0x4
    KRMEntry** oddKRMEntries; //0x8
    KRMEntry** evenKRMEntries; //0xc
};
size_assert(KRMMgr, 0x10);

}//namespace Input
#endif