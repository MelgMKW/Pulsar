#ifndef _MODEL_TRANSFORMATOR_
#define _MODEL_TRANSFORMATOR_
#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <MarioKartWii/3D/Scn/ScnManager.hpp>
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
    virtual void vf_0x8(); //80557fb0 vtable 808b44b8
    virtual void DetachHolderFromParent(AnmType type); //805573ac just calls g3dobj::detachfromparent

    void AppendAnmHolder(AnmHolder* holder); //8055585c inlined
    void AppendAnmBlend(AnmBlendHolder* holder); //80555864 inlined
    void DetachAllAnmFromBlend(AnmType type); //805558ec

    //the args are named based on Director's LinkAnimation's args
    void LinkAnimationByName(u32 idx, EGG::Heap* heap, EGG::Allocator* allocator, g3d::ResMdl& rawMdl, g3d::ResFile& rawBrres,
        const char* name, AnmType type, bool hasBlend, const char* brasd, ArchiveSource source, u8 kartArchiveIdx); //8055597c           
    //for example, the 2nd SRT of the brres would be brresAnmTypeIdx == 2, type == 2 
    void LinkAnimationByBRRESIdx(u32 idx, EGG::Heap* heap, EGG::Allocator* allocator, g3d::ResMdl& rawMdl, g3d::ResFile& rawBrres,
        u32 brresAnmTypeIdx, AnmType type); //805567b4
    void LinkChrAnmToBone(u32 idx, EGG::Heap* heap, EGG::Allocator* allocator, g3d::ResMdl& rawMdl, g3d::ResFile& rawBrres,
        const char* name, AnmType type, const char* boneToAnimate, bool bindNonSpecifiedBones); //80556f10
    void LinkEmptyAnm(u32 animId); //805571a4 will create an empty AnmHolder, used for conditional animations to prevent nullptr reads 

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
    void PrepareAnm(AnmType type, float initialFrame, float updateRate); //805573cc detaches from all, sets AnmObj to the scnMdl
    void AddAnmBlendToScnMdl(AnmType type); //80557650
    //will replace newIdxToUse currently active anm (of the same type as newIdx) by list's newIdxToUse
    void SetActiveAnm(u32 newIdxToUse, bool changeUpdateRate, float f1, float updateRate); //80557684
    void DisableAnmType(AnmType type); //80557830

    void Bind(); //80557bb8
    void UpdateBRASDAndBlend(); //805578d8
    void UpdateActiveAnm(g3d::ScnMdl& scnMdl); //80557c10 sets scnMdl, detaches/sets anmObjs based on the current state of the array (idx matching etc...)

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

#endif