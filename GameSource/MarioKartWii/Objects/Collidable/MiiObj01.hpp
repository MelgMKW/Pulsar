#ifndef _MIIOBJ01_OBJECT_
#define _MIIOBJ01_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class MiiObj01 : public ObjectCollidable { //ObjectNum 0x14d = 333
public:
    explicit MiiObj01(const KMP::Holder<GOBJ>& gobjHolder); //807730d4
    ~MiiObj01() override; //80773114 vtable 808cf800
    void OnStart() override; //0xC 80773180
    u32 GetPropertiesBitfield() override; //0x2c 807736c0
    void LoadModels() override; //0x44 8077318c
    u32 unknown_0xb0;
}; //0xb4
} //namespace Objects
#endif