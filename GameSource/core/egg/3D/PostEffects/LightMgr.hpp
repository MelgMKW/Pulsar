#ifndef _EGG_LIGHT_MGR_
#define _EGG_LIGHT_MGR_

#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/egg/Math/Vector.hpp>
#include <core/egg/3D/Texture.hpp>
#include <core/egg/3D/PostEffects/LightObject.hpp>
#include <core/egg/3D/PostEffects/LightTexture.hpp>

namespace EGG {
//https://wiki.tockdom.com/wiki/BLIGHT_(File_Format)
//https://wiki.tockdom.com/wiki/BLMAP_(File_Format)

struct BinaryLIGHTInfo {
    u16 lightObjectCount;
    u16 ambLightsCount;
    GX::Color ambBlackColor;
    u8 padding[16]; //alignment
};

struct BinaryAmbLight {
    GX::Color color;
    u32 unknown_0x4;
};

class LightMgr : public IBinary<LightMgr> {
    LightMgr(u16 lightObjCount, u16 ambLightCount, u8 screenCount); //8022a38c

    struct BLIGHT : public IBinary::Binary {
        //BinaryHeader header;
        BinaryLIGHTInfo info;
        //BinaryLIGHTObject objects;
        //BinaryAmbLight lights;
    };

    void SetBinaryImpl(const IBinary::Binary& rawBlight) override; //0x8 8022a8f0 vtable 802a3100
    void GetBinaryImpl(IBinary::Binary* blightDest) const override; //0xc 8022aee4
    const char* GetBinaryType() const override; //0x10 8022a8e0
    u32 GetBinarySize() const override; //0x14 8022b6ac
    u8 GetVersion() const override; //0x18 8022b6cc
    void DoubleMount() override; //0x1c 8022afd8
    virtual ~LightMgr(); //0x20 8022b66c

    void InitAmbientLights(); //8022a4a8
    void SetMaxCounts(u16 maxLightObj, u16 maxAmbLight); //8022a49c

    u16 lightObjCount; //0x4 same as ScnRoot's LightSetting in mkwii
    u16 ambLightCount;
    u16 maxLightObjCount; //0x8
    u16 maxAmbLightCount; //0xA
    LightObject** lightObjs; //0xC
    BinaryAmbLight* ambientLights; //0x10
    GX::Color ambBlackColor; //0x14
    u8 unknown_0x18[0x20 - 0x18];
    LightMap* binary; //0x20
    u8 unknown_0x24[0x2C - 0x24];
};
}//namespace EGG

#endif