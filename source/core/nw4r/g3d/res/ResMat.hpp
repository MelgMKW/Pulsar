#ifndef _NW4R_G3D_RESMAT_
#define _NW4R_G3D_RESMAT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResTex.hpp>
#include <core/nw4r/math/math.hpp>
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
    s32 offsetToTexName;             // Offset from the start of the structure to the texture name
    s32 offsetToPlttName;            // Offset from the start of the structure to the palette name (0 if it doesn't exist)
    ResTexData *pTexData;
    void *pPlttData;
    GXTexMapID mapID;               // GXTexMapID in which data is to be loaded (reflected in the array indices of ResMatData::texObj)
    GXTlut tlutID;              // Palette address in which data is to be loaded
    GXTexWrapMode wrap_s;              // Set to GXTexObj
    GXTexWrapMode wrap_t;              // Set to GXTexObj
    GXTexFilter min_filt;            // Set to GXTexObj
    GXTexFilter mag_filt;            // Set to GXTexObj
    float lod_bias;            // Set to GXTexObj
    GXAnisotropy max_aniso;           // Set to GXTexObj
    bool bias_clamp;          // Set to GXTexObj
    bool do_edge_lod;         // Set to GXTexObj
    u8 padding[2];
};

struct ResChanData {
    struct Chan {
        u32 flag;
        GXColor matColor;
        GXColor ambColor;
        u32 paramChanCtrlC;
        u32 paramChanCtrlA;
    } chan[2];
};

struct ResMatData { //this is very wrong, but too lazy to fix it for v11
    u32 size;
    s32 offsetToMdlData;
    s32 offsetToName;
    u32 id;
    u32 flags;
    u32 genMode; //tex gens, etc...
    u32 cullMode;
    u8 alphaFunction;
    u8 lightSet;
    u8 fogSet;
    u8 padding;
    u8 indirectMethods[4];
    u8 normalMapRef[4];
    s32 offsetToShader;
    u32 texCount;
    s32 offsetToLayer;
    s32 offsetToFurData;
    s32 offsetToDisplayList;
    s32 offsetToDisplayList2;

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

class ResMat : public ResCommon<ResMatData> {
public:

};

class ResMatTevColor : public ResCommon<ResTevColorDL> {
public:

};

}//namespace g3d
}//namespace nw4r


#endif