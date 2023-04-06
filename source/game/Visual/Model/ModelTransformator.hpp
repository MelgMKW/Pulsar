#ifndef _MODEL_TRANSFORMATOR_
#define _MODEL_TRANSFORMATOR_
#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <game/System/Archive.hpp>
#include <game/Sound/Actors/RaceActor.hpp>
#include <game/Visual/ScnManager.hpp>
#include <game/Visual/Model/AnmHolder.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/
using namespace nw4r;

class ModelDirector;
class ModelTransformator { //animation stuff
public:
    explicit ModelTransformator(ModelDirector *parent); //80555750
    virtual void vf_0x8(); //80557fb0 vtable 808b44b8
    virtual void DetachHolderFromParent(int idx); //805573ac just calls g3dobj::detachfromparent
    void InitAnm(float initialFrame, float updateRate, u32 idx); //805573cc detaches from all, sets AnmObj to the scnMdl
    void Bind(); //80557bb8
    void Update(); //805578d8
    void LinkAnimation(u32 id, EGG::Heap *heap, EGG::Allocator *allocator, g3d::ResMdl rawMdl, g3d::ResFile rawBrres,
        const char *name, AnmType type, bool hasBlend, const char *brasd, ArchiveSource source, u8 kartArchiveIdx); //8055597c           
    //the args are named based on Director's LinkAnimation's args
    void LinkEmptyAnm(u32 animId); //805571a4 will create an empty AnmHolder, used for conditional animations to prevent NULL reads 

    AnmHolder *GetAnmHolderFromList(u32 listIdx); //80557234
    AnmHolder *GetAnmHolderFromArray(u32 idx); //80557340

    ut::List anmHolderList; //0x4
    ut::List anmBlendList; //0x10
    ModelDirector *parent; //0x1c
    g3d::ScnMdl *scnMdl; //0x20
    AnmHolder **animHolders; //0x24
    AnmHolder **animHolders2; //0x28
    AnmBlendHolder **anmBlendHolders; //0x2C
    LinkedRaceActor *soundActor; //0x30
    u32 unknown_0x34;
    u16 bitfield; //0x38
    u8 unknown_0x3A[2];
}; //0x3c

#endif