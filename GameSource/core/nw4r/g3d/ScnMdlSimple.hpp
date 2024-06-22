#ifndef _NW4R_G3D_SCNMDLSIMPLE_
#define _NW4R_G3D_SCNMDLSIMPLE_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/AnmChr.hpp>
#include <core/nw4r/g3d/AnmClr.hpp>
#include <core/nw4r/g3d/AnmTexSrt.hpp>
#include <core/nw4r/g3d/AnmTexPat.hpp>
#include <core/nw4r/g3d/CalcWorld.hpp>

namespace nw4r {
namespace g3d {

class ScnMdlSimple : public ScnLeaf {
public:
    enum OptID { //see scnleaf's enum for the rest
        OPTID_IGNORE_ANMCHR_TRANS  = 0x00020001
    };

    enum AnmObjType {
        ANMOBJTYPE_CHR = 0,
        ANMOBJTYPE_VIS,
        ANMOBJTYPE_MATCLR,
        ANMOBJTYPE_TEXPAT,
        ANMOBJTYPE_TEXSRT,
        ANMOBJTYPE_SHP
    };
    static ScnMdlSimple* Construct(G3dHeap* heap, u32* size, ResMdl mdl, int numbViews = 1); //80070d20

    ScnMdlSimple(G3dHeap* pHeap, ResMdl mdl, math::MTX34* worldMtxArray, u32* worldMtxAttribArray,
        math::MTX34* viewPosMtxArray, math::MTX33* viewNrmMtxArray, math::MTX34* viewTexMtxArray, int nView, int numViewMtx);

    bool IsDerivedFrom(TypeObj type) const override; //0x8 80072db0 vtable 80273200
    void G3dProc(u32 g3dproc, u32 param, void* info); //0xC 800714b0
    ~ScnMdlSimple() override; //0x10 80072c90
    TypeObj GetTypeObj() const override; //0x14 80072e50
    const char* GetTypeName() const override; //0x18 80072e20
    bool SetScnObjOption(u32 optionID, u32 value) override; //0x20 80071d40
    bool GetScnObjOption(u32 optionID, u32* value) const override; //0x24 80071d80
    virtual bool SetAnmObj(AnmObj* obj, AnmObjType type); //0x34 80071f00
    virtual bool RemoveAnmObj(AnmObj* obj); //0x38 80072510
    virtual AnmObj* RemoveAnmObj(AnmObjType type); //0x3c 80072690
    virtual AnmObj* GetAnmObj(AnmObjType type); //0x40 80072770
    virtual const AnmObj* GetAnmObj(AnmObjType type) const; //0x44 800727d0

    void ScnMdlSmpl_CalcPosture(u32 param, const math::MTX34* pParent); //80070ec0
    void EnableScnMdlCallbackTiming(Timing t); //800728f0
    ResMdl resMdl; //0xe8
    math::MTX34* worldMtxArray; //0xec
    u32* worldMtxAttribArray; //0xf0
    math::MTX34* viewPosMtxArray; //0xf4
    math::MTX33* viewNrmMtxArray; //0xf8
    math::MTX34* viewTexMtxArray; //0xfc
    u8 numView; //0x100
    u8 curView;
    u16 viewMtxCount; //0x102
    u32 flagScnMdlSimple; //0x104

    const u8* byteCodeCalc; //0x108
    const u8* byteCodeMix; //0x10c
    const u8* byteCodeDrawOpa; //0x110
    const u8* byteCodeDrawXlu; //0x114
    u32 renderingMode; //0x118
    ICalcWorldCallback calcWorldCb; //0x11c
    u8 callbackTiming; //0x120
    u8 callbackDeleteOption; //0x121
    u16 callbackNodeID; //0x122
    AnmObjChr* anmObjChr; //0x124
    void* unknown; //0x128
    AnmObjMatClr* anmObjMatClr; //0x12c
    AnmObjTexPat* anmObjTexPat; //0x130
    AnmObjTexSrt* anmObjTexSrt; //0x134
};


}//namespace g3d   
}//namespace nw4r


#endif