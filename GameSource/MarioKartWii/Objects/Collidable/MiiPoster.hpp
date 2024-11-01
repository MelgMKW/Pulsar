#ifndef _MIIPOSTER_OBJECT_
#define _MIIPOSTER_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Mii/MiiCreationParams.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

//ObjectNum 0x16b = 363 

class MiiPoster : public ObjectCollidable {
    explicit MiiPoster(const KMP::Holder<GOBJ>& gobjHolder); //807736c8
    ~MiiPoster() override; //807738f0 vtable 808cf8f0
    void OnStart() override; //0xC 80773708
    u32 GetPropertiesBitfield() override; //0x2c 807738e8
    void LoadModels() override; //0x44 80773714
    u8 unknown_0xb0[4];
}; //0xb4
} //namespace Objects
#endif