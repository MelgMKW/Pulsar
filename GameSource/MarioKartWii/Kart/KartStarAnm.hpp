#ifndef _KARTSTARANM_
#define _KARTSTARANM_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/3D/Model/ShadowModelDirector.hpp>
#include <MarioKartWii/Kart/KartBRRESHandle.hpp>

namespace Kart {

class StarAnmMgr {
public:
    static void LoadAnm(); //8056b63c star.clr0 in driver.brres
    StarAnmMgr(); //8056b8a8
    static float frameCount; //809c18d0
    static nw4r::g3d::ResAnmClrAnmData* matAnmData; //809c18cc
    static s16 totalDuration; //809c18d4
    Link link;
    virtual void SetModelColors(ModelDirector& dest); //0x8 8056c030 vtable 808b5120
    virtual ~StarAnmMgr(); //0xc 8056c034

    void Reset(); //8056bbcc
    void Activate(); //8056b8ec
    void Update(); //8056b910
    void SetModelColorsImpl(ModelDirector& dest); //0x8 8056be20
    void StartEnding(); //8056bbac
    void End(); //8056bbc0

    float frame; //used to get the AnmColor 
    ut::Color color; //0x14
    float colorDivider; //0x18 increases by 0.1 every frame until it gets to 1
    u8 unknown_0x1c[2]; //0x1c used to control flickering of the star through a sinusoidal pattern
    bool isEnding; //0x1e
    bool hasEnded;
    u8 unknown_0x1e[2];
    u16 frameCounter;
}; //Total size 0x24

}//namespace kart

#endif