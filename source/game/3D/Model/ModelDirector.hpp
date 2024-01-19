#ifndef _MODEL_DIRECTOR_
#define _MODEL_DIRECTOR_
#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <game/Archive/ArchiveRoot.hpp>
#include <game/3D/Scn/ScnManager.hpp>
#include <game/3D/Scn/Light.hpp>
#include <game/3D/Model/ModelTransformator.hpp>
#include <game/3D/Model/ModelCalc.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/
class ClipInfo;
class Mii;
using namespace nw4r;

class ModelDirector {
public:
    static g3d::ResFile GetBRRES(ArchiveSource type, const char* brresName); //8055b5fc
    static void BindBRRES(g3d::ResFile& file, ArchiveSource type, const char* brresName); //8055b618
    static void BindBRRESFallback(g3d::ResFile& file, ArchiveSource type, const char* brresName, const g3d::ResFile& fallBack); //8055b6a4
    //if brresName does not have MDL0s, it'll fallback on the provided 2nd BRRES and use it for mdl0s
    static void RipAndBindBRRES(g3d::ResFile& file, const char* brresName, EGG::ExpHeap* heap, bool allocFromHead); //8055b754
    //Rips the BRRES instead of getting it from ArchiveRoot
    static void BindBRRESImpl(g3d::ResFile& main, const char* name, const g3d::ResFile& fallback, u32 unused); //8055b7f8
    //the actual binding, the other 2 merely call this 3rd one. both name and unused are...unused

    static bool BRRESExists(ArchiveSource type, const char* brresName); //8055ba00
    static g3d::ResMdl GetResMdl(const char* mdlName, const g3d::ResFile& brres); //8055ba44
    static g3d::ResMdl GetResMdl(int idx, const g3d::ResFile& brres); //8055ba54
    static bool MdlExists(const char* mdlName, const g3d::ResFile& brres); //8055ba64
    static bool HasResMdl(const g3d::ResFile& brres); //8055ba9c

    ModelDirector(u32 scnObjDrawOptionsIdx, ClipInfo* clipInfo, u32 bitfield); //0x8055b298 
    ModelDirector(u32 scnObjDrawOptionsIdx, u32 bitfield); //0x8055b50c
    ModelDirector(u32 scnMgrIdx, u32 scnObjDrawOptionsIdx, u32 bitfield); //8055b558
    virtual ~ModelDirector(); // 8055b5bc vtable 808b47f0
    virtual void ToggleVisible(bool insert);  //0xc 8055c9f0 inserts/remove from ScnGroup, easy way to make a model invisible for everyone
    virtual void EnableDraw(bool enable); //0x10 8055cb08
    virtual void SetScale(const Vec3& scale); //0x14 8055b05c
    virtual void SetScale(float scale); //0x18 8055f894
    virtual void GetScale(Vec3& scale) const; //0x1c 8055f848
    // best used aftr calling Enable/Disable Screen as this selectively makes a model visible/invisible for a specific hudSlotId
    //(since the ScnMdl will match that id and so will isVisible, calculated from the bitfield)
    virtual void SetScnOptions(g3d::ScnMdl* scnMdl, bool isVisible, bool doNotCalcWorldMatVtx); //0x20 8055cd68
    virtual void AppendToScnManager(); //0x24 8055bed4

    void Init(ScnType type, g3d::ScnMdl::BufferOption option, Light* light, Mii* mii, u32 miiScnStrE8, s32 r9); //8055baa0
    void InitG3D(ScnType type, g3d::ScnMdl::BufferOption option, Mii* mii, ScnMgr* scnMgr,
        u32 scnObjDrawOptionsIdx, u32 miiScnStr0xE8, s32 r10); //8055bd00
    g3d::ScnLeaf* CreateScn(ScnType type, g3d::ScnMdl::BufferOption option, Mii* mii, ScnMgr* scnMgr,
        u32 miiScnStrE8, s32 r9, u8 idx); //8055bf10

    //Constructs a ScnMdl
    void LoadWithAnm(const char* mdlName, g3d::ResFile& brres, Light* light); //8055c0e8 name without extension also calls init
    void LoadWithAnm(int mdlIdx, g3d::ResFile& brres, Light* light); //8055c1d0

    //Constructs a ScnMdlSimple
    void LoadNoAnm(const char* mdlName, g3d::ResFile& brres, Light* light); //8055c2b8
    void LoadNoAnm(int mdlIdx, g3d::ResFile& brres, Light* light); //8055c318

    //Constructs a ScnMdl (so supports anims) with a specified Option
    void LoadWithOption(const char* mdlName, g3d::ResFile& brres, g3d::ScnMdl::BufferOption option, Light* light); //8055c378
    void LoadWithOption(int mdlIdx, g3d::ResFile& brres, g3d::ScnMdl::BufferOption option, Light* light); //8055c44c

    //Constructs a ScnMdl1Mat1Shp (single shape, single material), this is for example used for Kart shadows
    void LoadScnMdl1Mat1SHp(const char* mdlName, g3d::ResFile& brres, Light* light); //8055c520

    void UpdateVisibility(u8 hudSlotId); //8055cc0c calls ToggleVisible
    void EnableScreen(u32 screenIdx); //8055cce0 the model will be visible on that screen
    void DisableScreen(u32 screenIdx); //8055ccf8
    bool IsVisibleOnScreen(u32 screenIdx); //8055cd10

    void Update(u32 scnMdlIdx); //8055d23c
    ModelTransformator* CreateTransformator(); //8055d9f0 mostly inlined
    void SetSoundActor(LinkedRaceActor& actor); //8055dce4 

    void LinkEmptyAnm(u32 animId); //8055e274 will create an empty AnmHolder, used for conditional animations to prevent nullptr reads 
    void LinkAllAnimations(g3d::ResFile& brres); //8055eae0 gets the ResNames and then constructs (if needed) a Transformator and binds all to it
    void LinkAnimation(u32 id, g3d::ResFile& brres, const char* name, AnmType type, bool hasBlend,
        const char* brasd, ArchiveSource source, u8 kartArchiveIdx); //8055ddec     

    void SetLight(void* lightStruct); //8055f2b4
    ScnMgr* GetScnManager() const; //8055f2c4 often inlined
    void UpdateDrawPriority(u32 scnObjDrawOptionsIdx); //8055f4c4
    void ChangeTransformator(ModelTransformator* newTransformator, bool disableAllAnms); //8055f7d8
    void PrepareAllAnms(); //8055f1e4

    //Keeps the model insert in the ScnGroup, but toggles drawXLU/OPA
    void ToggleTransparent(bool isTransparent); //8055f34c used to prevent this https://imgur.com/hUjHk6b

    u32 bitfield; //0x4
    /*
    24: removed from ScnGroups
    20: last ToggleFromScn isVisible value
    16-19: if set, model is visible on screen (bit idx - 16)
    8: register in the scn manager
    */
    u32 unknown_0x8;
    g3d::ResMdlData* rawMdl; //0xC
    EGG::ScnMdlEx* curScnMdlEx; //0x10 chooses which one to use based on 1st bit of bitfield
    EGG::ScnMdlEx* scnMdlEx[2]; //0x14
    g3d::ScnGroup* groups[2]; //0x1c
    u32 scnObjDrawOptionsIdx; //0x24 0x1 to make transparent
    ModelTransformator* modelTransformator; //0x28
    u8 unknown_0x2c[0x3C - 0x2c];
    u32 scnMgrIdx; //0 or 1
    Light* light; //0x40
    ClipInfo* clipInfo; //0x44
    u8 unknown_0x48[4];
}; //total size 0x4c
size_assert(ModelDirector, 0x4c);

#endif