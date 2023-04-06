#ifndef _KARTBODY_
#define _KARTBODY_

#include <kamek.hpp>
#include <game/Race/Kart/KartPart.hpp>

class KartPhysicsHolder;

class KartBody : public KartPart { //tentative name
public:
    KartBody(); //8056c394 
    ~KartBody() override; //8056cd84 vtable 808b53c0
    UnkType GetWheelMatrixBike(Mtx34 *wheelMatrix, u32 wheelIdx); //8056dd54
    u8 unknown_0x8c[0x90 - 0x8c];
    KartPhysicsHolder *kartPhysicsHolder;
    float unknown_0x94;
    Vec3 unknown_0x98;
    u8 unknown_0xa4[0xa8 - 0xa4];
    Mtx34 unknown_0xa8;
    Mtx34 unknown_0xd8;
    u8 unknown_0x108[0x168 - 0x108];
    Mtx34 unknown_0x168;
    Mtx34 unknown_0x198;
    u8 unknown_0x1c8[0x230 - 0x1c8];
    float wheelForwardRotationSpeed; //from KartPartsDispParam/BikePartsDispParam
    float wheelBackwardRotationSpeed; //same
    u8 unknown_0x238[0x360 - 0x238];
}; //Total size 0x360

class KartBodyBike : public KartBody {
    KartBodyBike(); //8056d858
    ~KartBodyBike() override; //8056e2bc vtable 808b5268
};
#endif