#ifndef _ITEMOBJTARGETING_
#define _ITEMOBJTARGETING_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

namespace Item {
class ObjTargeting : public Obj {
public:
    //vtable 808d2280 idk why it has a vtable of its own
    u8 unknown_0x1a0[0x1ec - 0x1a0];
    Vec3ZeroInit unknown_vec3s[8]; //0x1ec
};
size_assert(ObjTargeting, 0x24c);
}//namespace Item

#endif