#ifndef _EGG_LIGHT_OBJECT_
#define _EGG_LIGHT_OBJECT_

#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/egg/Math/Vector.hpp>
#include <core/egg/3D/Texture.hpp>
#include <core/egg/Binary.hpp>

namespace EGG {
//https://wiki.tockdom.com/wiki/BLIGHT_(File_Format)
//https://wiki.tockdom.com/wiki/BLMAP_(File_Format)



class LightObject : public IBinary<LightObject> {
    struct BinaryLIGHTObject : IBinary::Binary {
        //BinaryHeader header; //LOBJ
        u8 attenuationFalloffFuncType; //0x10
        u8 attenuationDistanceFuncType;
        u8 coordSystem;
        u8 lightType; //0x13
        u16 ambLightIdx;
        u16 bitfield;
        Vector3f origin;
        Vector3f dest;
        float width;
        GX::Color color;
        GX::Color ambBLMAPColor;
        float spotlightCutoffAngle;
        float attenuationRefDistance;
        float attenuatioNRefBrightness;
        u32 unknown_0x48;
        u16 lightObjIdx;
        u8 padding[2];
    }; //0x50

    LightObject(); //8022b6d4

    void SetBinaryImpl(const IBinary::Binary& rawLOBJ) override; //0x8 8022c2b4 vtable 802a3128
    void GetBinaryImpl(IBinary::Binary* lobjDest) const override; //0xc 8022c958
    const char* GetBinaryType() const override; //0x10 8022c2a4
    u32 GetBinarySize() const override; //0x14 8022b664
    u8 GetVersion() const override; //0x18 8022d0f0
    void DoubleMount() override; //0x1c 8022ca4c


    void Load(const BinaryLIGHTObject& raw); //8022b414
    void CalcDestination(); //8022c260
    void CalcDir(); //8022c1bc

    u16 ambLightIdx; //0x4
    u16 unknown_0x6;
    Vector3f dest; //0x8
    Vector3f origin; //0x14
    Vector3f position; //0x20
    GX::Color color; //0x2C
    float width; //0x30
    u32 coordSystem; //0x34
    float distanceToOrigin; //0x38
    GX::Color ambBLMAPColor; //0x3C
    u32 lightType; //0x40
    float spotlightCutoffAngle; //0x44
    float attenuationRefDistance; //0x48
    float attenuatioNRefBrightness; //0x4C
    u8 unknown_0x50[0x68 - 0x50];
    u32 attenuationFalloffFuncType; //0x68 probably enums now
    u32 attenuationDistanceFuncType; //0x6C
    float shininess;
    u8 unknown_0x74[2];
    u16 bitField; //0x76
    u8 unknown_0x78[4];
    Vector3f colorDir; //0x7c
    GX::Color color2; //0x88
    Vector3f viewLightOri; //0x8c
    Vector3f viewLightDest; //0x98
    Vector3f viewLightDir; //0xa4
}; //0xB0



}//namespace EGG

#endif