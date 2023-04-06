#ifndef _EGG_LIGHT_
#define _EGG_LIGHT_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/egg/Math/Vector.hpp>
#include <core/egg/3D/Texture.hpp>

namespace EGG {
//https://wiki.tockdom.com/wiki/BLIGHT_(File_Format)
//https://wiki.tockdom.com/wiki/BLMAP_(File_Format)

struct BinaryLightHeader {
    char magic[4]; //LGHT
    u32 fileSize;
    u8 version;
    u8 padding[3];
    u32 unknown_0xC;
};

struct BinaryLIGHTInfo {
    u16 lightObjectCount;
    u16 ambLightsCount;
    GXColor ambBlackColor;
    u8 padding[16]; //alignment
};

struct BinaryLIGHTObject {
    BinaryLightHeader header; //LOBJ
    u8 attenuationFalloffFuncType; //0x10
    u8 attenuationDistanceFuncType;
    u8 coordSystem;
    u8 lightType; //0x13
    u16 ambLightIdx;
    u16 bitfield;
    Vector3f origin;
    Vector3f dest;
    float width;
    GXColor color;
    GXColor ambBLMAPColor;
    float spotlightCutoffAngle;
    float attenuationRefDistance;
    float attenuatioNRefBrightness;
    u32 unknown_0x48;
    u16 lightObjIdx;
    u8 padding[2];
}; //0x50

struct BinaryAmbLight {
    GXColor color;
    u32 unknown_0x4;
};

struct BinaryLightMAPInfo {
    u16 ltexCount;
    u8 padding[14];
};

struct BinaryLightTexEntry {
    float intensity;
    u8 gradient;
    u8 padding[3];
};
struct BinaryLightTex {
    BinaryLightHeader header; //LTEX
    u16 subObjectsCount;
    char lm_TexName[32];
    u8 type;
    u8 padding[3];
    u32 activatedBitfield;
    //BinaryLightTexEntry entries;
};

struct BLIGHT {
    BinaryLightHeader header;
    BinaryLIGHTInfo info;
    //BinaryLIGHTObject objects;
    //BinaryAmbLight lights;
};

struct BLMAP {
    BinaryLightHeader header;
    BinaryLightMAPInfo info;
    //BinaryLightTex objects;
};



class ScnMdlEx;
class LightMapBinary;
class LightMgr;


class LightTextureBinary { //probably not abstract, can't find the vtable
    void Mount(BinaryLightTex *raw); //8022f3e8
    virtual void MountImpl() = 0;
    virtual void SaveImpl() = 0;
    virtual char *GetMagic() = 0;
    virtual void vf_0x14() = 0;
    virtual void vf_0x18(); //8022e780
    virtual void vf_0x1c(); //8022e77c
    u8 unknown_0x4[0x58 - 0x4];
    u8 unknown_0x[2];
    u16 gradLimit;
    Vector3f unknown_0x8;
    u16 gradientsEnabled;
    u16 gradientsEnabledHi;
    u16 unknown_0x18;
    u8 unknown_0x1a[2];
    u32 type;
    float *clrIntensityArr;
    int *gradientRefs;
    char name[32]; //0x28
    LightMapBinary *lmap; //0x48
    u8 status; //0x4c
    u8 tevStageCount;
    u8 indStageCount;
    u8 padding;
    u16 curTevStage; //0x50
    u16 srcLeft;
    u16 srcTop;
    u8 padding2[2];
}; //0x58

class CapTexture : public MatTexture, public LightTextureBinary {
    CapTexture(u16 r4, const char *name, LightMapBinary *lightMapBinary); //8022d730

    //CPUTexture vtable 802a3148 at 0x10
    ~CapTexture() override; //8022d9ac
    void Configure() override; //8022da48

    //LightTextureBinary
    void MountImpl() override;  //thunk 8022e79c func 8022e4d4 vtable 802a315c
    void SaveImpl() override;   //thunk 8022e7a4 func 8022e6dc
    char *GetMagic() override;  //thunk 8022e7ac func 8022e4c4
    void vf_0x14() override;    //thunk 8022e7b4 func 8022e788
}; //0x80

class LightMapBinary {
    explicit LightMapBinary(LightMgr *mgr); //8022e7bc
    virtual void Mount(BLMAP *raw); //8022f2a8 vtable 802a3190
    virtual void Save(); //8022f358
    virtual char *GetMagic(); //8022f298
    virtual void vf_0x14(); //8022f708
    virtual void vf_0x18(); //8022f3e0
    virtual void vf_0x1c(); //8022f3dc
    void CreateCapTexturesByPrefix(const char *prefix, ScnMdlEx *scnMdlEx); //8022eaa4
    u8 unknown_0x4[0x6 - 0x4];
    u16 ltexCount; //0x6
    CapTexture **capTextures; //0x8
    LightMgr *mgr; //0xC
    u8 unknown_0x10[0x2C - 0x10];
}; //0x2C

class LightObject {
    LightObject(); //8022b6d4
    virtual void LoadImpl(BinaryLIGHTObject *raw); //8022c2b4 vtable 802a3128
    virtual void Save(); //8022c958
    virtual void *GetLobjPtr(); //8022c2a4
    virtual void vf_0x14(); //8022b664
    virtual void vf_0x18(); //8022d0f0
    virtual void DoubleMount(); //8022ca4c
    void Load(BinaryLIGHTObject *raw); //8022b414
    u16 ambLightIdx; //0x4
    u16 unknown_0x6;
    Vector3f dest; //0x8
    Vector3f origin; //0x14
    Vector3f position; //0x20
    GXColor color; //0x2C
    float width; //0x30
    u32 coordSystem; //0x34
    float distanceToOrigin; //0x38
    GXColor ambBLMAPColor; //0x3C
    u32 lightType; //0x40
    float spotlightCutoffAngle; //0x44
    float attenuationRefDistance; //0x48
    float attenuatioNRefBrightness; //0x4C
    u8 unknown_0x50[0x68 - 0x50];
    u32 attenuationFalloffFuncType; //0x68 probably enums now
    u32 attenuationDistanceFuncType; //0x6C
    u8 unknown_0x70[0x76 - 0x70];
    u16 bitField; //0x76
    u8 unknown_0x78[0xb0 - 0x78];
}; //0xB0

class AmbientLight {
    GXColor color;
    u32 unknown_0x4;
};

class LightMgr {
    LightMgr(u16 lightObjCount, u16 ambLightCount, u8 pageCount); //8022a38c
    virtual void Mount(BLIGHT *rawBLIGHT); //8022a8f0 vtable 802a3100
    virtual void Save(); //8022aee4
    virtual BLIGHT *GetStaticBLIGHT(); //8022a8e0
    virtual void vf_0x14(); //8022b6ac
    virtual void vf_0x18(); //8022b6cc
    virtual void DoubleMount(); //8022afd8
    virtual ~LightMgr(); //8022b66c
    void InitAmbientLights(); //8022a4a8
    void SetMaxCounts(u16 maxLightObj, u16 maxAmbLight); //8022a49c
    u16 lightObjCount; //0x4
    u16 ambLightCount;
    u16 maxLightObjCount; //0x8
    u16 maxAmbLightCount; //0xA
    LightObject **lightObjs; //0xC
    AmbientLight *ambientLights; //0x10
    GXColor ambBlackColor; //0x14
    u8 unknown_0x18[0x20 - 0x18];
    LightMapBinary binary; //0x20
    u8 unknown_0x24[0x2C - 0x24];
};
}//namespace EGG

#endif