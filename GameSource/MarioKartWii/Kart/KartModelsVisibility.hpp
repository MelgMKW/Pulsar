#ifndef _KARTMODELSVISIBILITY_
#define _KARTMODELSVISIBILITY_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartValues.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

namespace Kart {

class ModelsVisibility : public Link { //controls visibility of kart models
public:
    ModelsVisibility(); //8056a264

    virtual void SetModelDraw(ModelDirector& direction); //8056a580 vtable 808b5028 calls model's enabledraw
    virtual ~ModelsVisibility(); //0xc 8056a59c

    void SetModelsVisibility(bool isVisible); //8056a300
    void SetInvisible(); //8056a2f0 will NOT update models visibility
    void UpdateModelsVisibility(); //8056a470

    u16 unknown_0x10;
    bool areModelsVisible; //0x12
    u8 padding;

}; //Total size 0x14

}//namespace kart

#endif