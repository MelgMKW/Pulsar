#ifndef _NW4R_G3D_SCNMDL_
#define _NW4R_G3D_SCNMDL_
#include <types.hpp>
#include <core/nw4r/g3d/ScnMdlSimple.hpp>
#include <core/nw4r/g3d/AnmShp.hpp>
#include <core/nw4r/g3d/res/ResVtx.hpp>

namespace nw4r {
namespace g3d {

struct DrawResMdlReplacement
{
    enum Flag {
        IGNORE_BUFFER_ANM_SHP = 0x00000001
    };

    u32  flag;
    u8 *visArray;
    ResTexObjData *texObjDataArray;
    ResTlutObjData *tlutObjDataArray;
    ResTexSrtData *texSrtDataArray;
    ResChanData *chanDataArray;
    ResGenModeData *genModeDataArray;
    ResMatMiscData *matMiscDataArray;

    ResPixDL *pixDLArray;
    ResTevColorDL *tevColorDLArray;
    ResIndMtxAndScaleDL *indMtxAndScaleDLArray;
    ResTexCoordGenDL *texCoordGenDLArray;
    ResTevData *tevDataArray;
    ResVtxPosData **vtxPosTable;
    ResVtxNrmData **vtxNrmTable;
    ResVtxClrData **vtxClrTable;
};

class ScnMdl : public ScnMdlSimple {
public:
    enum AnmObjType {
        ANMOBJTYPE_CHR = 0,
        ANMOBJTYPE_UNKNOWN,
        ANMOBJTYPE_MATCLR,
        ANMOBJTYPE_TEXPAT,
        ANMOBJTYPE_TEXSRT,
        ANMOBJTYPE_SHP,
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
    class CopiedMatAccess {
    private:
        ScnMdl *scnMdl; //0x0
        u32 matID;
        u8 unknown_0x8[0x30 - 0x8];
        CopiedMatAccess(ScnMdl *scnMdl, u32 id); //800730b0
    };
    static ScnMdl *Construct(G3dHeap *heap, u32 *size, ResMdl mdl, u32 bufferOption, int nView = 1); //80073470
    bool IsDerivedFrom(TypeObj type) const override; //0x8 800757f0 vtable 80273248
    void G3dProc(u32 r4, u32 r5, void *info); //0xC 80074770
    ~ScnMdl() override; //0x10 80075780
    TypeObj GetTypeObj() const override; //0x14 800758a0
    const char *GetTypeName() const override; //0x18 80075870
    bool SetScnObjOption(u32 optionID, u32 value) override; //0x20 80074c20
    bool GetScnObjOption(u32 optionID, u32 *value) const override; //0x24 80074c60
    virtual bool SetAnmObj(AnmObj *obj, AnmObjType type); //0x34 80075380
    virtual bool RemoveAnmObj(AnmObj *obj); //0x38 800754f0
    virtual AnmObj *RemoveAnmObj(AnmObjType type); //0x3c 800756f0
    virtual AnmObj *GetAnmObj(AnmObjType type); //0x40 80075740
    virtual const AnmObj *GetAnmObj(AnmObjType type) const; //0x44 80075760

    void ScnMdl_G3DPROC_CALC_MAT(u32 param, void *info); //80074000

    AnmObjShp *anmObjShp;
    u32 unknown; //0x13c
    u32 *matBufferDirtyFlag;
    DrawResMdlReplacement replacement;
    u32 replacementFlag;
};


}//namespace g3d   
}//namespace nw4r


#endif