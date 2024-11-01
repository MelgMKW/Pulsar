#ifndef _KARTMATTEVHANDLER_
#define _KARTMATTEVHANDLER_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>
#include <MarioKartWii/Driver/DriverController.hpp>

class RaceCamera;

namespace Kart {

//bad name, but it simply calls SetTevSwapMode/SetTevColorOp on all kart models mats, changing the swap mode of the texture color input
class MatTEVHandler : public Link {
public:
    MatTEVHandler(); //8056a5ec
    static void SetPartTEVSwapMode(Part& part); //8056a5dc a CallOnAllPartsFunc
    virtual void SetModelTEVSwapMode(ModelDirector& model); //8056aa28 vtable 808b5048 TEVStage1, called with driver model, but any model will do
    virtual ~MatTEVHandler(); //8056ab2c

    //only the middle one is ever called, hence why the simpler name for it
    void SelTexSwapModeAndSetTEVSwapModes(bool doSwap); //8056a630 "adds" the bool to the u16, ie if the bool is true the texture swap mode will be 1
    void SetTEVSwapModes(bool doSwap); //8056a6d8 "removes" the bool from the u16, ie if it was mode 1 it becomes mode 0
    void SetTEVSwapModesNoTexModeUpdate(); //8056a998

    void SetModelTEVSwapMode(ModelDirector& model, bool onTEVStage1); //8056a780 otherwise on tevStage0

    void SetModelTevColorOp(ModelDirector& model); //8056a89c

    u16 textureColorInputSwapMode; //0x10
    /*
    1 : GXTevSwapSel for the texture, ie textureColorInputSwapMode, 0 or 1 ofc since it's a bit
    2 : GXTevOP, Add or Sub
    */
    u8 padding[2];
}; //0x14


}//namespace kart

#endif