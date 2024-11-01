#ifndef _EGG_LIGHT_TEXTURE_
#define _EGG_LIGHT_TEXTURE_

#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/egg/Math/Vector.hpp>
#include <core/egg/3D/Texture.hpp>
#include <core/egg/Binary.hpp>

namespace EGG {
//https://wiki.tockdom.com/wiki/BLIGHT_(File_Format)
//https://wiki.tockdom.com/wiki/BLMAP_(File_Format)

class LightMgr;
class ScnMdlEx;
class LightMap;

struct BinaryLightTexEntry {
    float intensity;
    u8 gradient;
    u8 padding[3];
};

struct BinaryLightMAPInfo {
    u16 ltexCount;
    u8 padding[14];
};

class LightTexture : public CapTexture, public IBinary<LightTexture> {
public:
    struct BinaryLightTex : IBinary::Binary {
        //BinaryHeader header; //LTEX
        u16 subObjectsCount;
        char lm_TexName[32];
        u8 type;
        u8 padding[3];
        u32 activatedBitfield;
        //BinaryLightTexEntry entries;
    };

    LightTexture(u16 r4, const char* name, LightMap* lightMapBinary); //8022d730

    //CapTexture vtable 802a3148 at 0x10
    ~LightTexture() override; //8022d9ac
    void Configure() override; //8022da48

    //IBinary vtable 802a315c at 0x28
    void SetBinaryImpl(const IBinary::Binary& rawLTEX) override;     //0x8  thunk 8022e79c func 8022e4d4 vtable 802a315c
    void GetBinaryImpl(IBinary::Binary* ltexDest) const override;    //0xc  thunk 8022e7a4 func 8022e6dc
    const char* GetBinaryType() const override;                        //0x10 thunk 8022e7ac func 8022e4c4
    u32 GetBinarySize() const override;                                //0x14 thunk 8022e7b4 func 8022e788
    u8 GetVersion() const override;                                    //0x18 8022e780
    void DoubleMount() override;                                            //0x1c 8022e77c

    u8 unknown_0x2a[2]; //0x2a
    u16 gradLimit; //0x2e
    Vector3f unknown_0x30; //0x30
    u16 gradientsEnabled; //0x3c
    u16 gradientsEnabledHi; //0x3e
    u16 unknown_0x40; //0x40
    u8 unknown_0x42[2]; //0x42
    u32 type; //0x44
    float* clrIntensityArr; //0x48
    int* gradientRefs; //0x4c
    char name[32]; //0x50
    LightMap* lmap; //0x70
    u8 status; //0x74
    u8 tevStageCount;
    u8 indStageCount;
    u8 padding;
    u16 curTevStage; //0x78
    u16 srcLeft; //0x7a
    u16 srcTop; //0x7c
    u8 padding2[2];
}; //0x80

class LightMap : public IBinary<LightMap> {
public:
    struct BLMAP : IBinary::Binary {
        //BinaryHeader header; //BLMAP
        BinaryLightMAPInfo info;
        LightTexture::BinaryLightTex objects;
    };
    explicit LightMap(LightMgr* mgr); //8022e7bc

    void SetBinaryImpl(const IBinary::Binary& rawBLMAP) override;    //0x8  8022f2a8 vtable 802a3190
    void GetBinaryImpl(IBinary::Binary* blmapDest) const override;   //0xc  8022f358
    const char* GetBinaryType() const override;                        //0x10 8022f298
    u32 GetBinarySize() const override;                                //0x14 8022f708
    u8 GetVersion() const override;                            //0x18 8022f3e0
    void DoubleMount() override;     //0x1c 8022f3dc


    void CreateCapTexturesByPrefix(const char* prefix, ScnMdlEx* scnMdlEx); //8022eaa4

    u8 unknown_0x4[0x6 - 0x4];
    u16 ltexCount; //0x6
    LightTexture** lightTextures; //0x8
    LightMgr* mgr; //0xC
    u8 unknown_0x10[0x2C - 0x10];
}; //0x2C

} //namespace EGG

#endif