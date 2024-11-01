#ifndef _ITEMOBJTHUNDER_
#define _ITEMOBJTHUNDER_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

//_sinit_ at 807b7d74
namespace Item {
class ObjThunder : public ObjMiddle {
public:
    static Obj** CreateArray(u32 count); //807b7b00

    void InitSelf() override; //0x8 807b7c04 vtable 808d2770
    static void ApplyToPlayers(u8 srcPlayerId); //807b7c20 applies to all but src
};
size_assert(ObjThunder, 0x1a0);
}//namespace Item

#endif