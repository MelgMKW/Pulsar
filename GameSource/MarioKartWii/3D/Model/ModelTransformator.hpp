#ifndef _MODEL_TRANSFORMATOR_
#define _MODEL_TRANSFORMATOR_
#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <MarioKartWii/Archive/ArchiveMgr.hpp>
#include <MarioKartWii/3D/Scn/ScnMgr.hpp>
#include <MarioKartWii/3D/Model/AnmHolder.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/
using namespace nw4r;
namespace Audio {
class LinkedRaceActor;
}//namespace Audio

class ModelDirector;
class ModelTransformator { //animation stuff
public:
    explicit ModelTransformator(ModelDirector* parent); //80555750
    ~ModelTransformator(); //80556774
    virtual void vf_0x8(u32 listIdx, float frame, float rate); //80557fb0 vtable 808b44b8
    virtual void DetachHolderFromParent(AnmType type); //805573ac just calls g3dobj::detachfromparent

    void AppendAnmHolder(AnmHolder* holder); //8055585c inlined
    void AppendAnmBlend(AnmBlendHolder* holder); //80555864 inlined
    void SetBlendWeightDecrement(AnmType type); //8055586c
    float GetBlendWeightDecrement(AnmType type) const; //80555890
    void DecrementBlendWeight(AnmType type, float decrementBy); //805558bc
    void DetachAllAnmFromBlend(AnmType type); //805558ec
    void DetachAllAnmFromBlend(u32 listIdx); //8055591c

    //the args are named based on Director's LinkAnimation's args
    void LinkAnimationByName(u32 idx, EGG::Heap* heap, EGG::Allocator* allocator, g3d::ResMdl& rawMdl, g3d::ResFile& rawBrres,
        const char* name, AnmType type, bool hasBlend, const char* brasd, ArchiveSource sourceOfBRASD, u8 playerIdForBRASD); //8055597c           
    //for example, the 2nd SRT of the brres would be brresAnmTypeIdx == 2, type == 2 
    void LinkAnimationByBRRESIdx(u32 idx, EGG::Heap* heap, EGG::Allocator* allocator, g3d::ResMdl& rawMdl, g3d::ResFile& rawBrres,
        u32 brresAnmTypeIdx, AnmType type); //805567b4
    void LinkChrAnmToBone(u32 idx, EGG::Heap* heap, EGG::Allocator* allocator, g3d::ResMdl& rawMdl, g3d::ResFile& rawBrres,
        const char* name, AnmType type, const char* boneToAnimate, bool bindNonSpecifiedBones); //80556f10
    void LinkEmptyAnm(u32 animId); //805571a4 will create an empty AnmHolder, used for conditional animations to prevent nullptr reads 

    snd::detail::AnimSoundFile* GetBRASD(AnmType type, const char* anmName, const char* brasd, ArchiveSource sourceOfBRASD, u8 playerIdForBRASD); //805570ec inlined
    AnmHolder* GetAnmHolderByIdx(u32 listIdx) const; //80557234
    g3d::AnmObj* GetAnmObjByIdx(u32 listIdx) const; //8055723c
    void AddAnmToScnMdlAndSetupBRASD(u32 anmIdx); //80557264
    void AddAnmToScnMdl(g3d::AnmObj* anm); //805572f0
    void OverwriteAnm(AnmType type, AnmHolder* holder); //80557308 replaces animHolders[idx] with specified holder
    void RestoreAnm(AnmType type); //800557328 replaces animHolders[idx] with prevAnimHolders[idx]
    AnmHolder* GetAnmHolderByType(AnmType type) const; //80557340
    AnmHolder* GetPrevAnmHolderByType(AnmType type) const; //80557350
    bool IsTypeActive(AnmType type) const; //80557360
    bool IsTypeInPrev(AnmType type) const; //8055737c
    g3d::AnmObj* GetAnmObjByType(AnmType type); //80557398

    void AddAnmBlendToScnMdl(AnmType type); //80557650

    //puts currently active (of the same type as listIdx's) into prev, puts listIdx into active, detaches currently active, attaches listIdx, etc... 
    //the sole difference is the first does blending, the former detaches all from the blendHolder
    void PlayAnmWithBlend(u32 listIdx, bool changeUpdateRate, float initialFrame, float updateRate); //80557684
    void PlayAnmNoBlend(u32 listIdx, float initialFrame, float updateRate); //805573cc detaches from all, sets AnmObj to the scnMdl
    void AttachToBlendAndPlayAnm(u32 listIdx, int blendArrIdx, float initialFrame, float updateRate); //80557548 inlined, attaches the anm to the blend of the same AnmType with the specified idx

    void CreateAnmBlendArray(bool hasBlend); //80557b34
    void StopAnmType(AnmType type); //80557830
    void UpdateBRASDAndBlend(); //805578d8
    void UpdateBlend(); //80557960
    void UpdateActiveAnms(g3d::ScnMdl& scnMdl); //80557c10 sets scnMdl, detaches/sets anmObjs (including blend) based on the current state of the array (idx matching etc...)
    void Bind(); //80557bb8


    static bool IsG3dObj(const g3d::G3dObj::TypeObj obj); //returns true if r4 is G3dObj's typeObj 802476c8, seems completely useless


    ut::List anmHolderList; //0x4
    ut::List anmBlendList; //0x10
    ModelDirector* parent; //0x1c
    g3d::ScnMdl* scnMdl; //0x20
    AnmHolder** activeAnms; //0x24 one per type, use type to access
    AnmHolder** prevAnimHolders; //0x28 when the first array is updated, 2nd copies what the modified idx contained
    AnmBlendHolder** activeAnmBlends; //0x2C
    Audio::LinkedRaceActor* audioActor; //0x30
    u32 unknown_0x34;
    u16 bitfieldActiveAnmTypes; //0x38
    u8 padding[2];
}; //0x3c

class ModelTransformatorAddedCHRs : public ModelTransformator { //animation stuff
public:
    ModelTransformatorAddedCHRs(ModelDirector* parent, u8 additionalCHRCount); //80557cf8
    ~ModelTransformatorAddedCHRs(); //80557d90
    void vf_0x8(u32 listIdx, float frame, float rate) override; //80557dd0 vtable 808b44a8
    void DetachHolderFromParent(AnmType type) override; //80557ef4
    AnmChrHolder** additionalCHRs; //0x3c
    u8 additionalCHRCount; //0x40
    u8 padding2[3];
}; //0x44
#endif