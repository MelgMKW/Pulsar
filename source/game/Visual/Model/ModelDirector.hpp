#ifndef _MODEL_DIRECTOR_
#define _MODEL_DIRECTOR_
#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <game/System/Archive.hpp>
#include <game/Visual/ScnManager.hpp>
#include <game/Visual/Model/ModelTransformator.hpp>
#include <game/Visual/ClipInfoMgr.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/

using namespace nw4r;

class ModelDirector {
public:
    static g3d::ResFile GetBRRES(ArchiveSource type, const char *brresName); //8055b5fc
    static void BindBRRES(g3d::ResFile &file, ArchiveSource type, const char *brresName); //8055b618
    static void BindBRRESFallback(g3d::ResFile &file, ArchiveSource type, const char *brresName, g3d::ResFile *fallBack); //8055b6a4
    //if brresName does not have MDL0s, it'll fallback on the provided 2nd BRRES and use it for mdl0s
    static void RipAndBindBRRES(g3d::ResFile &file, const char *brresName, EGG::ExpHeap *heap, bool allocFromHead); //8055b754
    //Rips the BRRES instead of getting it from ArchiveRoot
    static void BindBRRESImpl(g3d::ResFile main, const char *name, g3d::ResFile *fallback, u32 unused); //8055b7f8
    //the actual binding, the other 2 merely call this 3rd one. both name and unused are...unused

    static bool BRRESExists(ArchiveSource type, const char *brresName); //8055ba00
    static g3d::ResMdl GetResMdl(const char *mdlName, g3d::ResFile *brres); //8055ba44
    static g3d::ResMdl GetResMdl(int idx, g3d::ResFile *brres); //8055ba54
    static bool MdlExists(const char *mdlName, g3d::ResFile *brres); //8055ba64
    static bool HasResMdl(g3d::ResFile *brres); //8055ba9c


    ModelDirector(u32 isTransparent, ClipInfo *clipInfo, u32 bitfield); //0x8055b298 
    ModelDirector(u32 isTransparent, u32 bitfield); //0x8055b50c
    ModelDirector(u32 gfxMgrIdx, u32 isTransparent, u32 bitfield); //8055b558
    virtual ~ModelDirector(); // 8055b5bc vtable 808b47f0
    virtual void RemoveFromScn();  //0xc  8055c9f0
    virtual void EnableDraw(bool enable); //0x10 8055cb08
    virtual void SetScale(Vec3 *scale); //0x14 8055b05c
    virtual void SetScale(float scale); //0x18 8055f894
    virtual void GetScale(Vec3 &scale) const; //0x1c 8055f848
    virtual void SetScnMdlOptions(g3d::ScnMdl *scnMdl, bool enableOptions, bool doNotCalcWorldMatVtx); //0x20 8055cd68 see OptID 
    virtual void AppendToScnManager(); //0x24 8055bed4

    void Init(ScnType type, g3d::ScnMdl::BufferOption option, u32 r6, u32 r7, u32 r8, u32 r9); //8055baa0
    void InitG3D(ScnType type, g3d::ScnMdl::BufferOption option, u32 r6, ScnManager *gfxMgr, u32 r8, u32 r9, u32 r10); //8055bd00
    g3d::ScnLeaf *CreateScn(ScnType type, g3d::ScnMdl::BufferOption option, u32 r6, ScnManager *gfxMgr, u32 r8, u32 r9, u8 idx); //8055bf10

    void LoadScnTypeMdl(const char *mdlName, g3d::ResFile *brres, UnkType *r6); //8055c0e8 name without extension also calls init
    void LoadScnTypeMdl(int mdlIdx, g3d::ResFile *brres, UnkType *r6); //8055c1d0
    void LoadNoAnmScnTypeMdlSimple(const char *mdlName, g3d::ResFile *brres, UnkType *r6); //8055c2b8
    void LoadNoAnmScnTypeMdlSimple(int mdlIdx, g3d::ResFile *brres, UnkType *r6); //8055c318
    void LoadWithOption(const char *mdlName, g3d::ResFile *brres, g3d::ScnMdl::BufferOption option, UnkType *r7); //8055c378
    void LoadWithOption(int mdlIdx, g3d::ResFile *brres, g3d::ScnMdl::BufferOption option, UnkType *r7); //8055c44c
    void LoadNoAnmScnTypeMdlShp(const char *mdlName, g3d::ResFile *brres, UnkType *r6); //8055c520

    void Update(u32 scnMdlIdx); //8055d23c
    void SetSoundActor(LinkedRaceActor *actor); //8055dce4 
    void LinkAnimation(u32 id, g3d::ResFile *brres, const char *name, AnmType type, bool hasBlend,
        const char *brasd, ArchiveSource source, u8 kartArchiveIdx); //8055ddec     
    void LinkEmptyAnm(u32 animId); //8055e274 will create an empty AnmHolder, used for conditional animations to prevent NULL reads          
    ScnManager *GetScnManager() const; //8055f2c4 often inlined


    u32 unk_bitfield;
    /*
    0x8 = register in the gfx manager
    */
    u32 unknown_0x8;
    g3d::ResMdlData *rawMdl; //0xC
    EGG::ScnMdlEx *curScnMdlEx; //0x10 chooses which one to use based on 1st bit of bitfield
    EGG::ScnMdlEx *scnMdlEx[2]; //0x14
    u32 unknown_0x1c[2];
    u32 isTransparent;
    ModelTransformator *modelTransformator; //0x28
    u8 unknown_0x2c[0x3C - 0x2c];
    u32 gfxMgrIdx; //0 or 1
    u8 unknown_0x40[8];
    ClipInfo *clipInfo;
}; //total size 0x4c
size_assert(ModelDirector, 0x4c);

#endif