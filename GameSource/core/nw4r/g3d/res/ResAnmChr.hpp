#ifndef _NW4R_G3D_RES_ANMCHR_
#define _NW4R_G3D_RES_ANMCHR_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/math.hpp>

namespace nw4r {
namespace g3d {



struct ChrAnmResult {
    void GetScale(math::VEC3* scale) const; //800555c0
    enum Flag {};
    u32 flags;
    math::VEC3 ratio;
    math::VEC3 rotation;
    math::MTX34 rotTranslation;
};

struct ResAnmChrInfoData { //"CHR0 header"
    enum ScalingRule {
        SCALINGRULE_STANDARD = 0,
        SCALINGRULE_SOFTIMAGE = 1,
        SCALINGRULE_MAYA = 2
    };
    u16 frameCount; //0x20
    u16 nodeCount; //0x22
    u32 isLooped; //0x24
    ScalingRule scalingRule;
};

struct ResAnmChrData { //https://wiki.tockdom.com/wiki/CHR0_(File_Format)
    ResBlockHeaderData header;
    u32 version; //0x8
    s32 offsetToBRRES; //0xc
    s32 toChrDataDic;  //0x10
    s32 offsetToResUserData; //0x14
    s32 offsetToName; //0x18
    s32 offsetToPath; //0x1c
    ResAnmChrInfoData fileInfo; //0x20
    //data
};

struct ResAnmChrNodeData {
    s32 nameOffset;
    union AnmData {
        s32 offsetToResAnmChrAnmData;
        float    constValue;
    } anms[1];
};

typedef void (*FuncGetAnmResult)(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame);



class ResAnmChr : public ResCommon<ResAnmChrData> {
    static const FuncGetAnmResult gGetAnmResultTable[8]; //802474a0
    static void GetAnmResult_(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //80055130
    static void GetAnmResult_S(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //80055250
    static void GetAnmResult_R(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //800551e0
    static void GetAnmResult_SR(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //80055340
    static void GetAnmResult_T(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //80055150
    static void GetAnmResult_ST(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //800553e0
    static void GetAnmResult_RT(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //80055290
    static void GetAnmResult_SRT(ChrAnmResult* result, const ResAnmChrInfoData& info, const ResAnmChrNodeData* nodeAnm, float frame); //80055480




    void GetAnmResult(ChrAnmResult* result, u32 anmIdx, float frame) const; //80055540
};

}//namespace g3d
}//namespace nw4r


#endif