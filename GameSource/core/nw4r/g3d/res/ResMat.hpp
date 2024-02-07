#ifndef _NW4R_G3D_RESMAT_
#define _NW4R_G3D_RESMAT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResTex.hpp>
#include <core/nw4r/math.hpp>
#include <core/rvl/gx/GXStruct.hpp>

//https://wiki.tockdom.com/wiki/MDL0_(File_Format)#Section_8_-_Materials
namespace nw4r {
namespace g3d {

struct ResTexObjData {};
struct ResTlutObjData {};
struct ResTexSrtData {};
struct ResGenModeData {};
struct ResMatMiscData {};
struct ResPixDL {};
struct ResIndMtxAndScaleDL {};
struct ResTexCoordGenDL {};
struct ResTevData {};

struct ResTevColorDL {
    u8 tevKColor[4][10];
};

struct ResTexPlttInfoData { //https://wiki.tockdom.com/wiki/MDL0_(File_Format)#Layers
    s32 offsetToTexName;      //Offset from the start of the structure to the texture name
    s32 offsetToPlttName;     //0x4 Offset from the start of the structure to the palette name (0 if it doesn't exist)
    ResTexData* pTexData;     //0x8
    void* pPlttData;          //0xc
    GX::TexMapID mapID;       //0x10 GXTexMapID in which data is to be loaded (reflected in the array indices of ResMatData::texObj)
    GX::Tlut tlutID;          //0x14 Palette address in which data is to be loaded
    GX::TexWrapMode wrap_s;   //0x18 Set to GX::TexObj
    GX::TexWrapMode wrap_t;   //0x1c Set to GX::TexObj
    GX::TexFilter min_filt;   //0x20 Set to GX::TexObj
    GX::TexFilter mag_filt;   //0x24 Set to GX::TexObj
    float lod_bias;           //0x28 Set to GX::TexObj
    GX::Anisotropy max_aniso; //0x2c Set to GX::TexObj
    bool bias_clamp;          //0x30 Set to GX::TexObj
    bool do_edge_lod;         //0x31 Set to GX::TexObj
    u8 padding[2];
};

struct ResChanData {
    struct Chan {
        u32 flag;
        GX::Color matColor;
        GX::Color ambColor;
        u32 paramChanCtrlC;
        u32 paramChanCtrlA;
    } chan[2];
};

struct ResMatData { //this is very wrong, but too lazy to fix it for v11
    u32 size;                           //0x0
    s32 offsetToMdlData;                //0x4
    s32 offsetToName;                   //0x8
    u32 id;                             //0xc
    u32 flags;                          //0x10
    u32 genMode; //tex gens, etc...     //0x14
    u32 cullMode;                       //0x18
    u8 alphaFunction;                   //0x1c
    u8 lightSet;
    u8 fogSet;
    u8 padding;
    u8 indirectMethods[4];              //0x20
    u8 normalMapRef[4];                 //0x24
    s32 offsetToShader;                 //0x28
    u32 texCount;                       //0x2c
    s32 offsetToLayer;                  //0x30
    s32 offsetToFurData;                //0x34
    s32 offsetToDisplayList;            //0x38
    s32 offsetToDisplayList2;           //0x3c

    u32 texSrtData;
    ResChanData chan; //0x3F0
};

struct TexSrtTypedef {
    enum TexMatrixMode {
        TEXMATRIXMODE_MAYA = 0,
        TEXMATRIXMODE_XSI = 1,
        TEXMATRIXMODE_3DSMAX = 2
    };
    enum MappingMethod {
        TEXCOORD = 0x00,
        ENV_CAMERA = 0x01,
        PROJECTION = 0x02,
        ENV_LIGHT = 0x03,
        ENV_SPEC = 0x04,

        NUM_BUILTIN_MAPPING_METHOD
    };
};

class ResMat : public ResCommon<ResMatData> {};

class ResMatTevColor : public ResCommon<ResTevColorDL> {};

class ResMatMisc : public ResCommon<ResMatMiscData> {};

class ResTexObj : public ResCommon<ResTexObjData> {};
class ResTexSrt : public ResCommon<ResTexSrtData>, public TexSrtTypedef {};

class ResTev : public ResCommon<ResTevData> {};

class ResTlutObj : public ResCommon<ResTlutObjData> {};

class ResMatChan : public ResCommon<ResChanData> {};

class ResGenMode : public ResCommon<ResGenModeData> {};

class ResMatPix : public ResCommon<ResPixDL> {};

class ResMatIndMtxAndScale : public ResCommon<ResIndMtxAndScaleDL> {};
class ResMatTexCoordGen : public ResCommon<ResTexCoordGenDL> {};

}//namespace g3d
}//namespace nw4r


#endif