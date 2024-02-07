#ifndef _NW4R_G3D_RES_ANMSCN_
#define _NW4R_G3D_RES_ANMSCN_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResLightSet.hpp>
#include <core/nw4r/g3d/res/ResAnmAmbLight.hpp>
#include <core/nw4r/g3d/res/ResAnmLight.hpp>
#include <core/nw4r/g3d/res/ResAnmCamera.hpp>
#include <core/nw4r/g3d/res/ResAnmFog.hpp>
#include <core/nw4r/math.hpp>

namespace nw4r {
namespace g3d {

struct ResAnmScnInfoData { //+0x34
    u16 frameCount;  //0
    u16 specularLightCount; //0x2
    u32 policy; //0x4
    u16 resLightSetDataCount; //0x8
    u16 resAnmAmbLightDataCount; //0xa
    u16 resAnmLightDataCount; //0xc
    u16 resAnmFogDataCount; //0xe
    u16 resAnmCameraDataCount; //0x10
    u8 padding[2];
};

struct ResAnmScnData { //https://wiki.tockdom.com/wiki/SCN0_(File_Format)
    ResBlockHeaderData header;
    u32 revision; //0x8
    s32 offsetToResFileData; //0xC
    s32 offsetToScnTopLevelDic; //0x10
    s32 offsetToResLightSetDataArray; //0x14
    s32 offsetToResAnmAmbLightDataArray; //0x18
    s32 offsetToResAnmLightDataArray; //0x1c
    s32 offsetToResAnmFogDataArray; //0x20
    s32 offsetToResAnmCameraDataArray; //0x24
    s32 offsetToResUserData; //0x28
    s32 name; //0x2c
    s32 originalPath; //0x30
    ResAnmScnInfoData info; //0x34
};

class ResAnmScn : public ResCommon<ResAnmScnData> {

    bool HasResAnmAmbLight() const; //800562e0
    bool HasResAnmLight() const; //80056340
    u32 GetResLightSetNumEntries() const;


    u32 GetResAnmAmbLightNumEntries() const; //80056560
    ResAnmAmbLight GetResAnmAmbLight(const ResName n) const; //80056420
    ResAnmAmbLight GetResAnmAmbLight(u32 idx) const; //800564b0


    ResAnmLight GetResAnmLight(const ResName n) const; //800565e0
    ResAnmLight GetResAnmLight(u32 idx) const; //80056670
    u32 GetResAnmLightNumEntries() const; //80056720

    ResAnmFog GetResAnmFog(u32 idx) const; //800567a0
    u32 GetResAnmFogNumEntries() const; //80056850

    ResAnmCamera GetResAnmCamera(u32 idx) const; //800568d0
    u32 GetResAnmCameraNumEntries() const; //80056980

    ResLightSet GetResLightSetByRefNumber(u32 refNumber) const; //80056a00
    ResLightSet GetResLightSetByRefNumber(int refNumber) const; //80056a50
    ResAnmAmbLight GetResAnmAmbLightByRefNumber(u32 refNumber) const; //80056aa0
    ResAnmLight GetResAnmLightByRefNumber(u32 refNumber) const; //80056af0
    ResAnmFog GetResAnmFogByRefNumber(u32 refNumber) const; //80056b40
    ResAnmCamera GetResAnmCameraByRefNumber(u32 refNumber) const; //80056b90
    ResAnmCamera GetResAnmCameraByRefNumber(int refNumber) const; //80056be0

    bool Bind(const ResAnmScn other); //80056c30





};

}//namespace g3d
}//namespace nw4r


#endif