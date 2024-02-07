#ifndef _ITEMOBJTHUNDER_
#define _ITEMOBJTHUNDER_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

//_sinit_ at 807b7d74
namespace Item {
class ObjThunder : public Item::Obj {
public:
    static Item::Obj** CreateArray(u32 count); //807b7b00
    void InitSelf() override; //0x8 807b7c04 vtable 808d2770
};
size_assert(ObjThunder, 0x1a0);
}//namespace Item

#endif