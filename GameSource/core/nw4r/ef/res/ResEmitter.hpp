#ifndef _NW4R_EF_EMITTERRESOURCE_
#define _NW4R_EF_EMITTERRESOURCE_
#include <types.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/ef/res/ResTexture.hpp>
#include <core/nw4r/ef/res/ResAnimCurve.hpp>

namespace nw4r {
namespace ef {

void BreffRelocate(EffectProject*);

struct EmitterInheritSetting {
    enum EmitterInheritSettingFlag {
        FLAG_FOLLOW_EMITTER = 1,
        FLAG_INHERIT_ROTATE = 2
    };
    s16 speed;
    u8 scale;
    u8 alpha;
    u8 color;
    u8 weight;
    u8 type;
    u8 flag;
    u8 alphaFuncPri;
    u8 alphaFuncSec;
}; //0x12

struct EmitterDrawSetting {
    struct TevStageColor {
        u8 a;
        u8 b;
        u8 c;
        u8 d;
    };
    struct TevStageAlpha {
        u8 a;
        u8 b;
        u8 c;
        u8 d;
    };
    struct TevStageColorOp {
        u8 op;
        u8 bias;
        u8 scale;
        u8 clamp;
        u8 outReg;
    };
    struct BlendMode {
        u8 type;
        u8 srcFactor;
        u8 dstFactor;
        u8 op;
    };
    struct Lighting {
        u8 mode;
        u8 type;
        GX::Color ambient;
        GX::Color diffuse;
        float radius;
        math::VEC3 position;
    };
    struct ColorInput {
        u8 rasColor;
        u8 tevColor[3];
        u8 tevKColor[4];
    };

    u16 flags;
    u8 alphaCmpComp0;
    u8 alphaCmpComp1;
    u8 alphaCmpOp;
    u8 tevsCount;
    u8 flagClamp;
    u8 indirectTargetStage;
    u8 tevTexture[4];
    TevStageColor tevColor[4];
    TevStageColorOp tevColorOp[4];
    TevStageAlpha tevAlpha[4];
    TevStageColorOp tevAlphaOp[4];
    u8 tevKColorSel[4];
    u8 tevKAlphaSel[4];
    BlendMode blendMode;
    ColorInput colorInput;
    ColorInput alphaInput;
    u8 zCompareFunc;
    u8 alphaFlickType;
    u16 alphaFlickCycle;
    u8 alphaFlickRandom;
    u8 alphaFlickAmplitude;
    Lighting lighting;
    float indTexOffsetMtx[2][3];
    s8 indTexScaleExp;
    s8 pivotX;
    s8 pivotY;
    u8 padding;
    u8 ptcltype;
    u8 typeOption;
    u8 typeDir;
    u8 typeAxis;
    u8 typeOption0;
    u8 typeOption1;
    u8 typeOption2;
    u8 padding4;
    float zOffset;
};


struct ParticleParameterDesc {
    GX::Color color[2][2];
    nw4r::math::VEC2 size;
    nw4r::math::VEC2 scale;
    nw4r::math::VEC3 rotate;

    nw4r::math::VEC2 textureScale[3];
    float textureRotate[3];
    nw4r::math::VEC2 textureTranslate[3];

    TextureData* texture[3];
    u16 textureWrap;
    u8 textureReverse;

    u8 alphaCmpRef0;
    u8 alphaCmpRef1;

    u8 rotateOffsetRandom[3];
    float rotateOffset[3];


    u8 textureNames[1];
};

struct EmitterResource {
    char* name;
    u32 headersize;

    //lwzu 8 + 4 + lwz 4 = GetPtclTrack(i), which is a animCurveData used for ResAnimCurve
};

class ResEmitter {
public:
    ResAnimCurve GetEmitTrack(u16 num); //8004bc80 often inlinted in egg
    EmitterResource* data;
};

}
}
#endif