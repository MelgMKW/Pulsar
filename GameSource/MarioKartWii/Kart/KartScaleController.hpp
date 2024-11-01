#ifndef _KARTSCALECONTROLLER_
#define _KARTSCALECONTROLLER_

//Formerly PlayerSub10
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>

namespace Kart {

class Pointers;

//_sinit_ at 8056b5e8
struct ResAnmChrNulld : g3d::ResAnmChr { //just a resanmchr with a ctor that nulls the ptr
    ResAnmChrNulld(); //8056b630
};

class ScaleAnmController : public Link {
public:
    static void LoadAnimations(); //8056ab6c item scale anms for thunder/kinoko
    static void GetAnmScale(Vec3& scaleDest, u8 anmIdx); //8056ac9c see names for the idx
    static void GetPressUpAnmScale(Vec3& scaleDest); //8056acf4
    static ResAnmChrNulld scaleAnms[5]; //809c18a0
    static float anmFrameCount[5]; //809c18b8
    static const char* scaleAnmNames[5]; //808b5098 thunder_scale_up, down, kinoko_scale_up, down then press_scale_up

    ScaleAnmController(const Values& values); //8056ad44

    void Reset(); //8056af10
    void Update(); //8056b218

    void RequestScaleChange(bool isGrowing); //8056afb4 otherwise shrinking
    void RequestEndScale(bool isEndingGrow); //8056b168


    enum Status {
        SCALE_STATUS_GROWING_THUNDER,
        SCALE_STATUS_SHRINKING_THUNDER,
        SCALE_STATUS_GROWING_KINOKO,
        SCALE_STATUS_SHRINKING_KINOKO,
    };

    virtual ~ScaleAnmController(); //8056b5a8 vtable 808b50d0

    Status status;
    Vec3 scaleIncrement; //0x14 how much scale increases every frame
    Vec3 unknown_0x20;
    Vec3 curScale; //0x2c
    bool hasRequest; //0x38
    u8 padding[3];
    float curAnmFrame; //0x3c

    //from Stats
    float megaScale; //0x40
    float unknown_0x44[2];
    float vertical_tilt; //0x4c
    float unknown_0x50;
    float megaScale2; //0x54
    float vertical_tilt; //0x58 
    float unknown_0x5c;

    u32 unknown_0x60;
    u8 unknown_0x64;
    float unknown_0x68[4];

}; //0x78

}//namespace kart

#endif