#ifndef _NW4R_G3D_RESNODE_
#define _NW4R_G3D_RESNODE_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResTex.hpp>
#include <core/nw4r/g3d/res/ResAnmChr.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/gx/GXStruct.hpp>

//https://wiki.tockdom.com/wiki/MDL0_(File_Format)#Section_8_-_Materials
namespace nw4r {
namespace g3d {


struct ResNodeData { //BONES https://wiki.tockdom.com/wiki/MDL0_(File_Format)#Section_1_-_Bones
    enum Billboard
    {
        BILLBOARD_OFF = 0,
        BILLBOARD_STD,
        BILLBOARD_PERSP_STD,
        BILLBOARD_ROT,
        BILLBOARD_PERSP_ROT,
        BILLBOARD_Y,
        BILLBOARD_PERSP_Y,
        NUM_BILLBOARD
    };
    u32 size;
    s32 offsetToMdlData;
    s32 offsetToName;
    u32 id;
    u32 matId; //0x10
    u32 flags;
    Billboard billboardMode;
    u32 padding;
    math::VEC3 scale;
    math::VEC3 rotation;
    math::VEC3 translation;
    math::VEC3 minVolume;
    math::VEC3 maxVolume;
    s32 offsetToParent;
    s32 offsetTo1stChild;
    s32 offsetToNextSibling;
    s32 offsetToPrevSibling;
    s32 offsetToResUserData; //next section
    math::MTX34 modelMtx;
    math::MTX34 invModelMtx;
}; //0xD0

class ResNode : public ResCommon<ResNodeData> {
public:
    void PatchChrAnmResult(ChrAnmResult *result) const; //80052af0
    void CalcChrAnmResult(ChrAnmResult *result) const; //80052c90
    void SetScale(f32 x, f32 y, f32 z); //80052e00
    void SetTranslate(f32 x, f32 y, f32 z); //80052eb0
    void SetRotate(f32 x, f32 y, f32 z); //80052f40
};




}//namespace g3d
}//namespace nw4r


#endif