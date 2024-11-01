#ifndef _MIIOBJ_OBJECT_
#define _MIIOBJ_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Mii/MiiCreationParams.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

//ObjectNum 0x14d = 333 MiiObj01,   ObjectNum 0x14e = 334 MiiObj02,   ObjectNum 0x14f = 335 MiiObj03
//ObjectNum 0x167 = 359 ShMiiObj01, ObjectNum 0x168 = 360 ShMiiObj02, ObjectNum 0x169 = 361 ShMiiObj03 
//ObjectNum 0x2e8 = 744 MiiObjD01,  ObjectNum 0x2e9 = 745 MiiObjD02,  ObjectNum 0x2ea = 746 MiiObjD03

class MiiObj : public ObjectCollidable {
public:
    static MiiCreationParams* miiCreationParams; //809c2da0
    static Mii** miis; //809c2da8
    static u32* processedMiisCount; //809c2dac
    explicit MiiObj(const KMP::Holder<GOBJ>& gobjHolder); //807730d4
    ~MiiObj() override; //80773114 vtable 808cf800
    void OnStart() override; //0xC 80773180
    u32 GetPropertiesBitfield() override; //0x2c 807736c0
    void LoadModels() override; //0x44 8077318c
    u32 unknown_0xb0;
}; //0xb4
} //namespace Objects
#endif