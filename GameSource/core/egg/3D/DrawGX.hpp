#ifndef _EGG_DRAWGX_
#define _EGG_DRAWGX_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/3D/ScreenEffect.hpp>
#include <core/egg/Math/Matrix.hpp>

namespace EGG {


class DrawGX {

    struct ZModes {
        bool compare_enable;
        u8 padding[3];
        GX::Compare func;
        bool update_enable;
        u8 padding2[3];
    }; //0xC

    struct BlendModes {
        GX::BlendMode type;
        GX::BlendFactor src_factor;
        GX::BlendFactor dst_factor;
        GX::LogicOp op;
    }; //0x10

    static ZModes zModes; //80257558
    /*
    false GX_ALWAYS false //0
    true  GX_LEQUAL true  //1
    true  GX_LEQUAL false //2
    true  GX_ALWAYS true  //3
    */
    static BlendModes blendModes; //80257588
    /*
    GX_BM_BLEND    GX_BL_SRCALPHA     GX_BL_INVSRCALPHA GX_LO_CLEAR //0
    GX_BM_BLEND    GX_BL_INVSRCALPHA  GX_BL_SRCALPHA    GX_LO_CLEAR //1
    GX_BM_BLEND    GX_BL_ONE          GX_BL_ONE         GX_LO_CLEAR //2
    GX_BM_BLEND    GX_BL_SRCALPHA     GX_BL_ONE         GX_LO_CLEAR //3
    GX_BM_BLEND    GX_BL_SRCCLR       GX_BL_ONE         GX_LO_CLEAR //4
    GX_BM_BLEND    GX_BL_INVSRCCLR    GX_BL_ONE         GX_LO_CLEAR //5
    GM_BM_SUBTRACT GX_BL_ONE          GX_BL_ONE         GX_LO_CLEAR //6
    GX_BM_BLEND    GX_BL_ZERO         GX_BL_SRCCLR      GX_LO_CLEAR //7
    GX_BM_BLEND    GX_BL_ZERO         GX_BL_INVSRCCLR   GX_LO_CLEAR //8
    GX_BM_BLEND    GX_BL_ONE          GX_BL_ZERO        GX_LO_CLEAR //9
    GX_BM_BLEND    GX_BL_DSTALPHA     GX_BL_INVDSTALPHA GX_LO_CLEAR //a
    GX_BM_BLEND    GX_BL_INVDSTALPHA  GX_BL_DSTALPHA    GX_LO_CLEAR //b
    GM_BM_NONE     GX_BL_ONE          GX_BL_ONE         GX_LO_CLEAR //c
    GM_BM_LOGIC    GX_BL_INVSRCALPHA  GX_BL_INVDSTALPHA GX_LO_AND   //d
    */

    struct DisplayList {
        u8* list; //0x0
        u32 size; //0x4
    };

    static DisplayList lists[18]; //803840b0 16 = postEffect

    static void Initialize(EGG::Heap* heap); //8021a4d8

    static GX::TexMapID GetDefaultTexMap(); //8021a580
    static void BeginDrawCircleZ(u32 colorChanType, u32 zModesIdx); //8021a588


    static void ClearEfb(const Matrix34f& posMtx, bool colorUpdate, bool alphaUpdate, bool useTexture, GX::Color tevColor, bool vtxTypeRelated); //8021ad78
    static void SetMatChannels(u32 colorChanType); //8021afe4
    static void SetMatTexGen(u32 texGenType); //8021b0b8
    static void SetMatIndirect(); //8021b134
    static void SetMatTev(GX::TevStageID stage, u32 tevType); //8021b13c
    static void SetMatPE(u32 zModesIdx, u32 blendModesIdx); //8021b29c
    static void SetVtxState(u32 type); //8021b300
    static void InitDL(); //8021af5c
    static void DrawDL(u32 idx, const Matrix34f& posMtx); //8021bff0
    static void DrawDL(u32 idx, const Matrix34f& posMtx, GX::Color matColor); //8021c058
    static void SetZMode(u32 zModesIdx); //8021c0f8
    static void SetBlendMode(u32 blendModesIdx); //8021c118
    static void SetupTranslucent(bool cullFrontFaces); //8021c13c will cull back faces otherwise
    static void SetCull(bool cullBack); //8021c1b8 otherwise cullback

    static void BeginDrawScreen(u8 vtxTypeSomething, bool setupMat, bool disableAlphaSomething); //8021a600
};

}//namespace EGG
#endif