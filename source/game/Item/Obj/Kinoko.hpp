#ifndef _ITEMOBJKINOKO_
#define _ITEMOBJKINOKO_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807a9dac
namespace Item {
class ObjKinoko: public Obj {
public:
    static Obj** CreateArray(u32 count); //807a9cc0
    void InitSelf() override; //0x8 807a9d90 vtable 808d1fb0
};
size_assert(ObjKinoko, 0x1a0);
}//namespace Item

#endif