#ifndef _TICO_
#define _TICO_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/3D/Model/ModelDirector.hpp>

class DriverController;

//TICO = LUMA
class TicoModel {
public:

    TicoModel(DriverController* controller); //807d9b98   
    void Update(); //807d9d64
    void UpdateKartPosition(); //807da578 inlined

    ModelDirector* tico; //0x0
    Vec3 vec_0x4; //0x4
    Vec3 kartPosition; //0x10
    float unknown_0x1c[10]; //0x18
    DriverController* controller; //0x40
    float unknown_0x44[5]; //0x44
}; //0x58


#endif