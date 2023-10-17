#ifndef _KARTBRRESHANDLE_
#define _KARTBRRESHANDLE_
#include <kamek.hpp>
#include <game/3D/Scn/Light.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/3D/Model/ShadowModelDirector.hpp>

namespace Kart {

class BRRESHandle {
public:
    BRRESHandle(Light* light, bool isGhost, u8 playerId); //80576b3c "ApplyTransparency"
    ~BRRESHandle(); //80576c54

    void LoadKartBRRES(u8 playerId); //80576d8c
    void LoadDriverBRRES(u8 playerIdx, bool isBike); //80576e90

    void LoadDriverModels(ModelDirector** driver, ModelDirector** driver_lod, DriverController& controller); //805778ac
    void LoadKartShadowModel(ShadowModelDirector& shadow); //80577d7c
    void LoadKillerModels(const nw4r::g3d::ResFile&, ModelDirector& kartKillerModel, ShadowModelDirector& kartKillerShadowModel); //80577e00

    bool LoadBodyModel(ModelDirector& dest, void* unknown); //80577064
    bool LoadArmModel(u32 idx, ModelDirector& dest, bool* r6); //805776d4
    bool LoadSuspensionsModel(ModelDirector& dest); //805775d0

    bool LoadLeftBackWheelModel(ModelDirector& dest); //80577460
    bool LoadLeftFrontWheelModel(ModelDirector& dest); //805772f0
    bool LoadRightBackWheelModel(ModelDirector& dest); //80577518
    bool LoadRightFrontWheelModel(ModelDirector& dest); //805773a8

    bool LoadBikeFrontWheelModel(ModelDirector& dest); //80577a9c
    bool LoadBikeBackWheelModel(ModelDirector& dest); //80577b54
    bool LoadBikeHandleModel(ModelDirector& dest); //8057791c
    bool LoadBikeSwingArmModel(ModelDirector& dest); //805779e4
    bool LoadBikeSuspensionsModel(ModelDirector& dest); //80577c0c

    nw4r::g3d::ResFile brres; //kart or driver
    nw4r::g3d::ResFile brres2;
    u32 unknown_0x8;
    Light* light; //0xC
    bool isTransparent; //0x10
    bool is4thNonPlayerScreen; //0x11
    bool has2ndKartModel;
    u8 playerId; //0x13
    bool isLocal; //0x14
    u8 padding[3];
}; //Total size 0x18

}//namespace kart

#endif