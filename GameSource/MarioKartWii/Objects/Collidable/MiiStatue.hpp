#ifndef _MIISTATUE_OBJECT_
#define _MIISTATUE_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/Mii/Mii.hpp>

namespace Objects {
//ObjectNum 0x166 = 358 MiiStatueM1, 0x186 = 390 MiiStatueL2, 0x187 = 391 MiiStatueD2, 0x188 = 392 MiiStatueP1, 
//0x2df = 735 MiiStatueM2, 0x2e1 = 737 MiiStatueL3, 0x2e3 = 739 MiiStatueBL1, 0x2e4 = 740 MiiStatueBD1

class MiiStatue : public ObjectCollidable {
public:
    static MiiCreationParams* params[4]; //809c44d0
    explicit MiiStatue(const KMP::Holder<GOBJ>& gobjHolder); //8082b63c
    ~MiiStatue() override; //8082ba18 vtable 808d8120

    void OnStart() override; //0xC 8082bae0
    void Update() override; //0x14 8082bce8
    u32 GetPropertiesBitfield() override; //0x2c 8082be0c

    u8 unknown_0xb0[4];
    Mii* miiUsed; //0xb4
    u8 unknown_0xb8[0xdc - 0xb8];
    u32 unknown_0xdc;
    float unknown_0xe0[6];
    u8 unknown_0xf8[0x138 - 0xf8];
    u32 unknown_0x138;
    u8 unknown_0x13c[4];
}; //0x140
} //namespace Objects
#endif