#ifndef _NW4R_G3D_RESNODE_
#define _NW4R_G3D_RESNODE_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResTex.hpp>
#include <core/nw4r/g3d/res/ResAnmChr.hpp>
#include <core/nw4r/math.hpp>
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
    u32 id; //0xC
    u32 matId; //0x10
    u32 flags; //0x14
    Billboard billboardMode; //0x18
    u32 padding; //0x1c
    math::VEC3 scale; //0x20
    math::VEC3 rotation; //0x2c
    math::VEC3 translation; //0x38
    math::VEC3 minVolume; //0x44
    math::VEC3 maxVolume; //0x50
    s32 offsetToParent; //0x5C
    s32 offsetTo1stChild; //0x60
    s32 offsetToNextSibling; //0x64
    s32 offsetToPrevSibling; //0x68
    s32 offsetToResUserData; //0x6c next section
    math::MTX34 modelMtx; //0x70
    math::MTX34 invModelMtx; //0xA0
}; //0xD0

class ResNode : public ResCommon<ResNodeData> {
public:
    void PatchChrAnmResult(ChrAnmResult* result) const; //80052af0
    void CalcChrAnmResult(ChrAnmResult* result) const; //80052c90
    void SetScale(float x, float y, float z); //80052e00
    void SetTranslate(float x, float y, float z); //80052eb0
    void SetRotate(float x, float y, float z); //80052f40
};




}//namespace g3d
}//namespace nw4r


#endif