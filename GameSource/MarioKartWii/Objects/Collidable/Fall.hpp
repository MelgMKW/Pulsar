#ifndef _FALL_OBJECT_
#define _FALL_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class Fall : public ObjectCollidable { //ObjectNum 0x2da = 730 Fall_T
public:
    explicit Fall(const KMP::Holder<GOBJ>& gobjHolder); //8077d9d8
    ~Fall() override; //8077dd10 vtable 808d11a0
    void OnStart() override; //0xC 8077dd50
    void Update() override; //0x14 8077dd54
    u32 GetPropertiesBitfield() override; //0x2c 8077df1c

    u8 unknown_0xb0[4]; //0xb0
    EGG::Effect* effect; //0xb4
    bool isEnabled; //0xb8 disabled for ObjectNum 734 and 735 on 2/3/4P
    u8 padding4[3];
}; //0xbc
} //namespace Objects
#endif