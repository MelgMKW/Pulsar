#ifndef _OBJECT_
#define _OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/File/Tables/GeoHitTable.hpp>
#include <MarioKartWii/Audio/Actors/ObjectActor.hpp>
#include <MarioKartWii/Route/RouteController.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/3D/Model/ShadowModelDirector.hpp>
#include <MarioKartWii/Entity/EntityManager.hpp>
#include <MarioKartWii/3D/ClipInfoMgr.hpp>
#include <core/egg/Effect/Effect.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/
enum ObjectType {
    OBJECT_TYPE_NORMAL = 0x0,
    OBJECT_TYPE_SPECIAL = 0x2
};

class Object;
struct CyclePtmfs {
    u16 id;
    u8 padding[2];
    Ptmf_0A<Object, void> ptmfs[2];
}; //0x1c


class Object {
public:
    explicit Object(const KMP::Holder<GOBJ>& gobj); //8081f828
    Object(u16 objId, const Vec3& position, const Vec3& rotation, const Vec3& scale); //8081f9bc
    Object(const char* name, const Vec3& position, const Vec3& rotation, const Vec3& scale, u32 r8); //8081fb04 used for sub objects

    virtual ~Object(); //8067e3c4 vtable 808d6ecc
    virtual void OnStart(); //0xC 8081fc68
    virtual void vf_0x10(); //0x10 806807dc just a blr
    virtual void Update(); //0x14 806bf448
    virtual void vf_0x18(); //0x18 0x18 806807d8 just a blr
    virtual void UpdateModel(); //0x1c 808217b8
    virtual void Init() = 0; //0x20
    virtual u16 GetID() const; //0x24 80572574
    virtual const char* GetName() const; //0x28 80680784
    virtual u32 GetPropertiesBitfield(); //0x2c 806bf434 1 : isUpdating
    virtual ClipInfo* GetClipInfo() const; //0x30 8067da54
    virtual const char* GetBRRESName() const; //0x34 80680730
    virtual const char* GetSubFileName() const; //0x38 806806dc completely identical to the one above, but for other objects can be MDL, KCL, BREFF etc...
    virtual void* vf_0x3c(); //0x3c 806806d4
    virtual const char* GetShadowResName() const; //0x40 806806cc
    virtual void LoadModels(); //0x44 8081fcec calls loadgraphics
    virtual void LoadModels(void* r4); //0x48 8081fd00 same
    virtual void LoadGraphics(void* r4); //0x4c 8081fd10
    virtual void LoadShadow(); //0x50 808205dc
    virtual void LoadSound(); //0x54 80820360
    virtual void LoadClipInfo(); //0x58 80821070
    virtual void LoadAnimations(); //0x5c 8082072c
    virtual void LoadCollision() = 0; //0x60
    virtual void LoadRoute(); //0x64 80820980
    virtual void ToggleVisible(bool isVisible); //0x68 808216c0
    virtual void UpdateModelMatrix(); //0x6c 80821a9c
    virtual void UpdateShadow(); //0x70 80821974
    virtual void UpdateCollision() = 0; //0x74
    virtual void UpdateModelScale(); //0x78 8068065c called by UpdateModel
    virtual void UpdateShadowScale(); //0x7c 80680630
    virtual u8 GetShadowListIdx(); //0x80 80680628
    virtual bool vf_0x84(); //0x84 80680620
    virtual void vf_0x88(); //0x88 80821db8
    virtual void vf_0x8c(); //0x8c 80821dd8
    virtual void DisableCollision(); //0x90 80821dec for example when you destroy a create
    virtual void EnableCollision(); //0x94 80821e00
    virtual const Entity& GetEntity() const; //0x98 80680618
    virtual Vec3& GetPosition(); //0x9c 80681598
    virtual float GetCollisionDiameter() const; //0xa0 8080bdc0 
    virtual bool IsLodDisbled(); //0xa4 80680610
    virtual void vf_0xa8(); //0xa8 80680608
    virtual bool DoCalcShadowMtx(); //0xac 80680600 if false, just copies the main model's mtx
    virtual u32 GetDrawType() const = 0; //0xb0

    void LoadAnimationByType(u32 idx, AnmType type); //80820a90
    void LinkAnimations(char** brasd, char** idk, u32 brsadCount, u32 idkCount); //80820eb8
    void UpdateMatrix(); //80821640
    Audio::Handle* StartSoundLimited(u32 soundId, float volume); //808204fc
    Audio::Handle* HoldSoundLimited(u32 soundId); //8082051c
    Audio::Handle* StartNewSoundLimited(u32 soundId, float volume); //no overlap, if sound already started, does nothing
    bool StartSound(u32 soundId); //8082055c
    bool HoldSound(u32 soundId); //8082057c
    void StopAllSound(int fadeOutFrames); //8052059c 
    void StopSound(int fadeOutFrames); //808205bc
    void LinkSound(u16 objId); //808204b8 if objId == 0, uses own id
    void CalcYAxisTransMtx(const Vec3& dir); //808218b0 calculates the trans mtx using the position as the translation, and a YAxisRotMtx based on dir

    ObjectType type;
    ModelDirector* mdlDirector; //0x8
    ModelDirector* mdlLodDirector; //0xc
    ShadowModelDirector* shadowDirector; //0x10
    nw4r::g3d::ResFile rawBrres; //0x14
    Audio::LinkedRaceActor* objectActor; //0x18 see object actor class
    ClipInfo* clipInfo; //0x1c
    RouteController* routeController; //0x20
    Entity* entity; //0x24
    const char* shadowResName; //0x28
    u16 flags; //0x2c bitfield
    /*
    1: update mtx pos
    2: update mtx rt
    3: update matrix on model update
    4: update model srt
    8: update model scale
    */
    u8 padding[2];
    Vec3 position; //0x30
    Vec3 scale; //0x3c
    Vec3 rotation; //0x48
    u8 unknown_0x54[4];
    Mtx34 transformationMtx; //0x58
    u16 objId; //0x88
    u8 padding_0x8a[2];
    const char* name; //0x8c unsure, read by vf_0x3c
    u8 lodFlags; //0x90 1 = has lod
    u8 padding2[3];
    const char* lodResName; //0x94
    u8 unknown_0x98[3];
    bool isVisible; //0x9b
    u8 unknown_0x9c[4];
    const KMP::Holder<GOBJ>& gobj; //0xa0
    u32 holderIdx; //0xa4
    bool unknown_0xA8;
    u8 padding3[3];
}; //total size 0xac
size_assert(Object, 0xaC);

class ObjectCycleManager {
    static CyclePtmfs cyclePtmfs;
    virtual ~ObjectCycleManager();
    //virtual int vf_0xC() = 0; //0xC this might be wrong since kart_truck has no such function 
    u16 curPtmfArrayIdx;
    u8 padding[2];
    u32 nextPtmfArrayIdx; //0x8 
    //set to -1 initially, setting it to 1 resets the route, for example a HeyHoBallGBA gets rethrown
    //works similar to a state, where the specific object decides when to set the state
    u32 frames; //resets when the object reaches the end of its route//its cycle
    u16 cyclePtmfsCount; //unsure
    u8 padding2[2];
    u16* idsArray; //0x14 ptmfs used
    CyclePtmfs* ptmfs; //0x18 808c5da0
    Object* parent; //0x1c
}; //0x20

class ObjectEffect : public EGG::Effect {
public:
    ~ObjectEffect() override; //806805a8 vtable 808c1010
};

template<class T>
class SubObjectArray { //for example w_itembox
public:
    static_assert(is_base_of<Object, T>::value, "Not a child of object");
    virtual ~SubObjectArray();
    virtual void CreateArray(u32 boxCount, u32 unused);
    virtual void CreateArray(u32 boxCount, EGG::Heap* heap);
    virtual void vf_0x14(u32 r4);
    virtual void vf_0x18();

    u32 arrayCount; //0x4
    T** subObjects; //0x8
}; //0xc

#endif