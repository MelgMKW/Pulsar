#ifndef _NW4R_G3D_SCNMDL_
#define _NW4R_G3D_SCNMDL_
#include <types.hpp>
#include <core/nw4r/g3d/ScnMdlSimple.hpp>
#include <core/nw4r/g3d/AnmShp.hpp>
#include <core/nw4r/g3d/res/ResVtx.hpp>

namespace nw4r {
namespace g3d {

struct DrawResMdlReplacement {
    u32  flag;    //0
    u8* visArray; //0x4
    ResTexObjData* texObjDataArray; //0x8
    ResTlutObjData* tlutObjDataArray; //0xc
    ResTexSrtData* texSrtDataArray; //0x10
    ResChanData* chanDataArray; //0x14
    ResGenModeData* genModeDataArray; //0x18
    ResMatMiscData* matMiscDataArray; //0x1c
    ResPixDL* pixDLArray; //0x20
    ResTevColorDL* tevColorDLArray; //0x24
    ResIndMtxAndScaleDL* indMtxAndScaleDLArray; //0x28
    ResTexCoordGenDL* texCoordGenDLArray; //0x2c
    ResTevData* tevDataArray; //0x30
    ResVtxPosData** vtxPosTable; //0x34
    ResVtxNrmData** vtxNrmTable; //0x38
    ResVtxClrData** vtxClrTable; //0x3c
}; //0x40

//same as ScnMdlSimple, but with possibility for a shape animation and copies of model res used for animation via CopyMatAccess
//this allows the possibility to execute animations separately even if multiple ScnMdl share the same ResMdl
class ScnMdl : public ScnMdlSimple {
public:
    enum OptID { //see scnmdlsimple's enum for the rest
        OPTID_REFRESH_VISIBILITY = 0x00030001
    };
    enum AnmObjType {
        ANMOBJTYPE_CHR = 0,
        ANMOBJTYPE_UNKNOWN,
        ANMOBJTYPE_MATCLR,
        ANMOBJTYPE_TEXPAT,
        ANMOBJTYPE_TEXSRT,
        ANMOBJTYPE_SHP
    };
    enum BufferOption {
        BUFFER_RESTEXOBJ = 0x00000001,
        BUFFER_RESTLUTOBJ = 0x00000002,
        BUFFER_RESTEXSRT = 0x00000004,
        BUFFER_RESCHAN = 0x00000008,
        BUFFER_RESGENMODE = 0x00000010,
        BUFFER_RESMATMISC = 0x00000020,
        BUFFER_VIS = 0x00000040,
        BUFFER_RESPIX = 0x00000080,
        BUFFER_RESTEVCOLOR = 0x00000100,
        BUFFER_RESINDMTXANDSCALE = 0x00000200,
        BUFFER_RESTEXCOORDGEN = 0x00000400,
        BUFFER_RESTEV = 0x00000800,
        BUFFER_VTXPOS = 0x00001000,
        BUFFER_VTXNRM = 0x00002000,
        BUFFER_VTXCLR = 0x00004000,
        ALWAYS_BUFFER_ANM_SHP = 0x01000000,
        ANM_MATCLR = BUFFER_RESTEVCOLOR | BUFFER_RESCHAN,
        ANM_TEXPAT = BUFFER_RESTEXOBJ | BUFFER_RESTLUTOBJ,
        ANM_TEXSRT = BUFFER_RESTEXSRT | BUFFER_RESINDMTXANDSCALE,
        ANM_VIS = BUFFER_VIS,
        ANM_SHP = BUFFER_VTXPOS | BUFFER_VTXNRM | BUFFER_VTXCLR,
        ANM_VTX = ANM_SHP,
        ANM_ALL = ANM_MATCLR | ANM_TEXPAT | ANM_TEXSRT | ANM_VIS | ANM_VTX
    };
    //access a copy of a given material
    class CopiedMatAccess {
    public:
        CopiedMatAccess(ScnMdl* scnMdl, u32 id); //800730b0
        ResTexObj GetResTexObj(bool bMarkDirty); //80072e60
        ResMatTevColor GetResMatTevColor(bool bMarkDirty); //80072e60
        ResTexSrt GetResTexSrtEx(); //80072f00
        ResMatMisc GetResMatMiscEx(); //80072f60
        ResMatTevColor GetResMatTevColorEx(); //80072fc0
        ResTev GetResTevEx(); //8007230b0

        ScnMdl* scnMdl; //0x0
        u32 matID;      //0x4
        ResTexObj            texObj; //0x8
        ResTlutObj           tlutObj; //0xc
        ResTexSrt            texSrt; //0x10
        ResMatChan           chan; //0x14
        ResGenMode           genMode; //0x18
        ResMatMisc           matMisc; //0x1c
        ResMatPix            pix; //0x20
        ResMatTevColor       tevColor; //0x24
        ResMatIndMtxAndScale indMtxAndScale; //0x28
        ResMatTexCoordGen    texCoordGen; //0x2c
        ResTev               tev; //0x30
    };
    static ScnMdl* Construct(G3dHeap* heap, u32* size, ResMdl mdl, u32 bufferOption, int nView = 1); //80073470
    bool IsDerivedFrom(TypeObj type) const override; //0x8 800757f0 vtable 80273248
    void G3dProc(u32 g3dproc, u32 param, void* info); //0xC 80074770
    ~ScnMdl() override; //0x10 80075780
    TypeObj GetTypeObj() const override; //0x14 800758a0
    const char* GetTypeName() const override; //0x18 80075870
    bool SetScnObjOption(u32 optionID, u32 value) override; //0x20 80074c20
    bool GetScnObjOption(u32 optionID, u32* value) const override; //0x24 80074c60
    virtual bool SetAnmObj(AnmObj* obj, AnmObjType type); //0x34 80075380
    virtual bool RemoveAnmObj(AnmObj* obj); //0x38 800754f0
    virtual AnmObj* RemoveAnmObj(AnmObjType type); //0x3c 800756f0
    virtual AnmObj* GetAnmObj(AnmObjType type); //0x40 80075740
    virtual const AnmObj* GetAnmObj(AnmObjType type) const; //0x44 80075760

    void ScnMdl_G3DPROC_CALC_MAT(u32 param, void* info); //80074000

    AnmObjShp* anmObjShp; //0x138
    u32 flagVisBuffer; //0x13c
    u32* matBufferDirtyFlag; //0x140
    DrawResMdlReplacement replacement; //0x144
    u32 replacementFlag; //0x184
};


}//namespace g3d   
}//namespace nw4r


#endif