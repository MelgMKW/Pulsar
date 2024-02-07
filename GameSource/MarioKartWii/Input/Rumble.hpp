#ifndef _RUMBLE_
#define _RUMBLE_
#include <kamek.hpp>
#include <MarioKartWii/File/KRM.hpp>

namespace Input {

class RumbleManager { //name based on RequestRumble extensively loading class fields
    //no ctor
    virtual ~RumbleManager(); //80525204 vtable 808b30fc
    void Init(const KRM& vibrationKRM); //805250c8
    KRM* rawKRM;
    void** krmEntries; //
    void** krmEntries2; //0xc
};
size_assert(RumbleManager, 0x10);

}//namespace Input
#endif