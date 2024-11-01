#ifndef _NW4R_G3D_RESSHP_
#define _NW4R_G3D_RESSHP_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResVtx.hpp>

namespace nw4r {
namespace g3d {

struct ShpAnmVtxSet {
    ResVtxPos   resVtxPos;
    ResVtxNrm   resVtxNrm;
    ResVtxClr   resVtxClr;
};

struct ShpAnmResult {
    struct BlendVtx {
        ShpAnmVtxSet    vtxSet;
        float             weight;
    };
    u32 flags;
    u32             numKeyShape;
    ShpAnmVtxSet    baseShapeVtxSet;
    float             baseShapeWeight;
    BlendVtx keyShape[32];
};

struct ResMtxSetUsed {
    u32 numMtxID; // Number of matrix IDs stored in vecMtxID
    u16 vecMtxID[2]; // There are a number of these equal to numMtxID
};

struct ResShpData {
    u32 size;
    s32 offsetToResMdlData;
    s32 curMtxIdx;
    u8 cacheData[12];
    ResTagDLData tagPrePrimDL;
    ResTagDLData tagPrimDL;
    u32 vcdBitmap;
    u32 flags;
    s32 offsetToName;
    u32 id;
    u32 numVtx;
    u32 numPolygon;
    s16 idVtxPosition;
    s16 idVtxNormal;
    s16 idVtxColor[2];
    s16 idVtxTexCoord[8];
    s16 idVtxFurVec;
    s16 idVtxFurPos;
    s32 offsetToMtxSetUsed;
    ResMtxSetUsed msu;
};

class ResShp : public ResCommon<ResShpData> {
public:
    void GetAnmResult(ShpAnmResult* result, u32 anmId, float frame, const ShpAnmVtxSet* shpArray) const; //80056da0
};

}//namespace g3d 
}//namespace nw4r


#endif