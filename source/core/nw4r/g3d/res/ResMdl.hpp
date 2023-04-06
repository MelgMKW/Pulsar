#ifndef _NW4R_G3D_RESMDL_
#define _NW4R_G3D_RESMDL_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/g3d/res/ResNode.hpp>
#include <core/nw4r/g3d/res/ResTexPlttInfo.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {


struct ResMdlInfoDataTypedef {
    enum ScalingRule {
        SCALINGRULE_STANDARD = 0,
        SCALINGRULE_SOFTIMAGE = 1,
        SCALINGRULE_MAYA = 2
    };
    enum TexMatrixMode {
        TEXMATRIXMODE_MAYA = 0,
        TEXMATRIXMODE_XSI = 1,
        TEXMATRIXMODE_3DSMAX = 2
    };

    enum EnvelopeMatrixMode {
        EVPMATRIXMODE_NORMAL = 0,
        EVPMATRIXMODE_APPROX = 1,
        EVPMATRIXMODE_EXACT = 2
    };
};

struct ResMdlInfoData : public ResMdlInfoDataTypedef
{
    u32 size;
    s32 offsetToMdlData;
    ScalingRule scalingRule;
    TexMatrixMode texMtxMode;
    s32 vertexSize;
    s32 triangleSize;
    s32 offsetToOriginalPath;
    u32 numViewMtx;
    u8 needNrmMtxArray;
    u8 needTexMtxArray;
    bool isValidVolume;
    u8 envelopeMtxMode;
    s32 toMtxIDToNodeID;
    math::VEC3 minVolume;
    math::VEC3 maxVolume;
};

struct ResMdlData {
    ResBlockHeaderData header;  //"MDL0"
    u32 version; //0x8
    s32 offsetToBRRES; //0xc
    s32 offsetToByteCodeDic; //0x10
    s32 offsetToNodeDic; //0x14
    s32 offsetToVtxPosDic; //0x18
    s32 offsetToVtxNrmDic; //0x1c
    s32 offsetToVtxClrDic; //0x20 
    s32 offsetToVtxTexCoordDic; //0x24
    s32 offsetToVtxFurVecDic; //0x28
    s32 offsetToVtxFurPosDic; //0x2c
    s32 offsetToMatDic; //0x30
    s32 offsetToTevDic; //0x34
    s32 offsetToShpDic; //0x38
    s32 offsetToTexNameToTexPlttInfoDic; //0x3c
    s32 offsetToPlttNameToTexPlttInfoDic; //0x40
    s32 offsetToUserData;    //0x44
    s32 offsetToName; //0x48
    ResMdlInfoData info;// Includes ResMdlInfoData
    // Data in the model (the entire set of dictionaries, nodes, and so on) and user data continues below
};

class ResMdl : public ResCommon<ResMdlData> {
public:
    ResMat GetResMat(const char *name) const; //8004e8f0
    ResMat GetResMat(const ResName resName) const; //8004e940
    ResMat GetResMat(int idx) const; //8004e990 offset to Dic = ResDic->ResMat, same for all the get
    ResMat GetResMat(u32 idx) const; //8004e9f0

    u32 GetResMatNumEntries() const; //8004ea50

    ResNode GetResNode(const char *name) const; //8004e2a4 
    ResNode GetResNode(const ResName resName) const; //8004e2f0 
    ResNode GetResNode(int idx) const; //8004e340
    ResNode GetResNode(u32 idx) const; //8004e340
    u32 GetResNodeNumEntries() const; //8004e400


    ResTexPlttInfoOffset GetResTexPlttInfoOffsetFromTexName(u32 idx) const; //8004eb90 "Mdl0::RawTextureLinkByID"
    u32 GetResTexPlttInfoOffsetFromTexNameNumEntries() const; //8004ebf0 "GetTextureLinkCount"
};

}//namespace g3d   
}//namespace nw4r


#endif