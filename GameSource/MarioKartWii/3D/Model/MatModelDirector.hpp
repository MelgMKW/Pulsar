#ifndef _MATMATMODELDIRECTOR_
#define _MATMATMODELDIRECTOR_
#include <kamek.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>


//ModelDirector with hardcoded material names
//These material names are hardcoded because it allows the user to fetch them at run time and using ScnMdl::CopiedMatAccess, to modify various effects
//The actual use in MKWii is the torch effect on MH (MHModelDirector) where the hardcoded mat TEV Colors are used to simulate a torch effect by clamping the texture
//The devs could have used GetResMat(idx) instead of GetResMat(name) but then it would have hardcoded the orders of the materials

class MatModelDirector : public ModelDirector, public EGG::Disposer {
public:

    MatModelDirector(u32 scnObjDrawOptionsIdx, ClipInfo* clipInfo, u32 bitfield); //805b90c8
    MatModelDirector(u32 scnObjDrawOptionsIdx, u32 bitfield); //805b9010
    MatModelDirector(u32 scnMgrIdx, u32 scnObjDrawOptionsIdx, u32 bitfield); //805b906c

    ~MatModelDirector() override; //805b9124 vtable 808b7368
    void AppendToScnMgr() override; //0x24 805b918c
    virtual void SetMatsTEVColors(u32 screenIdx) = 0; //8078de60
    void CopyMaterialsTevColors(); //805b91e0 copies ALL the materials' tev colors
    void SetMaterialNames(const char** names, u16 matCount, bool r6); //805b91d0
    void ReplaceDefaultScnMdlTevColorDL(u32 screenIdx); //805b92c8

    //DisposerVtable 808b7390 at 0x4c
    //~MatModelDirector() override; //thunk 805b92f8 func 805b9124

    ut::Link scnMgrMatMdlDirectorLink; //0x5c
    g3d::ResTevColorDL** matsResTevColorCopy; //0x64 array of array of tevColors, one array per screen
    const char** matNames; //0x68
    u8 unknown_0x6c[4]; //0x6c
    u16 matCount; //0x70
    bool r6; //0x72
    u8 padding;
}; //total size 0x74
size_assert(MatModelDirector, 0x74);

class MHModelDirector : public MatModelDirector {
public:
    static const char* matNames[12]; //808d1860
    static ut::Color torchColor; //808a4b5c
    MHModelDirector(u32 scnObjDrawOptionsIdx);  //8078de04 ctor inlined
    ~MHModelDirector() override; //80790a68 vtable 808d1890
    //DisposerVtable 808d18b8 at 0x4c
    //~MatModelDirector() override; //thunk 80790ad0 func 80790a68
    void SetMatsTEVColors(u32 screenIdx) override; //8078de60 torch effect
    u32 unknown_0x74[4];
}; //0x84

#endif