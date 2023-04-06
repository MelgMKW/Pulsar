#ifndef _OBJECT_
#define _OBJECT_
#include <kamek.hpp>
#include <game/KMP/Controller.hpp>
#include <game/File/Tables/GeoHitTable.hpp>
#include <game/Sound/Actors/ObjectSound.hpp>
#include <game/Route/RouteController.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Visual/Model/ShadowModelDirector.hpp>
#include <game/Collision/Entity/EntityHolder.hpp>
#include <game/Visual/ClipInfoMgr.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/
enum ObjectType {
    OBJECT_TYPE_NORMAL = 0x0,
    OBJECT_TYPE_SPECIAL = 0x2,
};


class Object;
struct CyclePtmfs {
    u16 id;
    u8 padding[2];
    Ptmf_0A<Object, void> ptmfs[2];
};


class Object {
public:
    explicit Object(KMP::GOBJHolder *gobj); //8081f828
    Object(const char *name, Vec3 *position, Vec3 *rotation, Vec3 *scale, u32 r8); //8081fb04 used for sub objects
    virtual ~Object(); //8067e3c4 vtable 808d6ecc
    virtual void OnStart(); //0xC 8081fc68
    virtual void vf_0x10(); //0x10 0x10 806807dc just a blr
    virtual void Update(); //0x14 806bf448
    virtual void vf_0x18(); //0x18 0x18 806807d8 just a blr
    virtual void UpdateModel(); //0x1c 808217b8
    virtual void Init() = 0; //0x20
    virtual int GetID() const; //0x24 80572574
    virtual const char *GetName() const; //0x28 80680784
    virtual bool HasLod(); //0x2c 806bf434
    virtual ClipInfo *GetClipInfo() const; //0x30 8067da54
    virtual char *GetBRRESName() const; //0x34 80680730
    virtual char *GetSubFileName() const; //0x38 806806dc completely identical to the one above, but for other objects can be KCL, BREFF etc...
    virtual void *vf_0x3c(); //0x3c 806806d4
    virtual char *GetShadowResName() const; //0x40 806806cc
    virtual void LoadModels(); //0x44 8081fcec calls loadgraphics
    virtual void LoadModels(void *r4); //0x48 8081fd00 same
    virtual void LoadGraphics(void *r4); //0x4c 8081fd10
    virtual void LoadShadow(); //0x50 808205dc
    virtual void LoadSound(); //0x54 80820360
    virtual void LoadRenderer(); //0x58 80821070
    virtual void LoadAnimations(); //0x5c 8082072c
    virtual void LoadCollision() = 0; //0x60
    virtual void LoadRoute(); //0x64 80820980
    virtual void InitModels(bool r4); //0x68 808216c0
    virtual void UpdateModelMatrix(); //0x6c 80821a9c
    virtual void UpdateShadow(); //0x70 80821974
    virtual void UpdateCollision() = 0; //0x74
    virtual void UpdateModelScale(); //0x78 8068065c called by UpdateModel
    virtual void UpdateShadowScale(); //0x7c 80680630
    virtual bool vf_0x80(); //0x80 0x80 80680628
    virtual bool vf_0x84(); //0x84 0x84 80680620
    virtual void vf_0x88(); //0x88 0x88 80821db8
    virtual void vf_0x8c(); //0x8c 0x8c 80821dd8
    virtual void DisableCollision(); //0x90 80821dec for example when you destroy a create
    virtual void EnableCollision(); //0x94 0x94 80821e00
    virtual int *GetDrawInfo() const; //0x98 80680618
    virtual Vec3 *GetPosition() const; //0x9c 80681598
    virtual float GetCollisionDiameter() const; //0xa0 8080bdc0 
    virtual bool IsLodDisbled(); //0xa4 80680610
    virtual void vf_0xa8(); //0xa8 0xa8 80680608
    virtual void vf_0xac(); //0xac 0xa8 80680600
    virtual u32 GetDrawType() const = 0; //0xb0

    void LoadAnimationByType(u32 idx, AnmType type); //80820a90
    void LinkAnimations(char **brasd, char **idk, u32 brsadCount, u32 idkCount); //80820eb8
    AudioHandle *UpdateMatrix(); //80821640
    AudioHandle *StartSoundLimited(u32 soundId, float volume); //808204fc
    AudioHandle *HoldSoundLimited(u32 soundId); //8082051c
    AudioHandle *StartNewSoundLimited(u32 soundId, float volume); //no overlap, if sound already started, does nothing
    bool StartSound(u32 soundId); //40 8082055c
    bool HoldSound(u32 soundId); //44 8082057c
    void StopAllSound(int fadeOutFrames); //0x8082059c 
    void StopSound(int fadeOutFrames); //0x48 808205bc


    ObjectType type;
    ModelDirector *mdlDirector; //0x8
    ModelDirector *mdlLodDirection; //0xc
    ShadowModelDirector *shadowDirector; //0x10
    nw4r::g3d::ResFileData *rawBrres; //0x14
    LinkedRaceActor *objectSound; //0x18 see object sound class
    ClipInfo *clipInfo; //0x1c
    RouteController *routeController; //0x20
    Entity *entity; //0x24
    const char *shadowResName; //0x28
    u16 flags; //0x2c 1: update mtx pos, 2: update mtx rt, 4: update model srt, 8: update model scale
    u8 padding[2];
    Vec3 position; //0x30
    Vec3 scale; //0x3c
    Vec3 rotation; //0x48
    u8 unknown_0x54[4];
    Mtx34 transformationMtx; //0x58
    u16 objId; //0x88
    const char *name; //0x8c unsure, read by vf_0x3c
    u8 lodFlags; //0x90 1 = has lod
    u8 padding2[3];
    const char *lodResName; //0x94
    u8 unknown_0x98[8];
    KMP::GOBJHolder *gobj; //0xa0
    u32 holderIdx;
    bool unknown_0xA8;
    u8 padding3[3];
}; //total size 0xac
size_assert(Object, 0xaC);

class ObjectCycleManager {
    static CyclePtmfs routePtmfs;
    virtual ~ObjectCycleManager();
    virtual int vf_0xC() = 0; //0xC 
    u16 unknown_0x4;
    u8 padding[2];
    u32 unknown_0x8;
    u32 frames; //resets when the object reaches the end of its route//its cycle
    u16 routePtmfsCount; //unsure
    u8 padding2[2];
    u16 *idsArray; //ptmfs used
    CyclePtmfs *ptmfs; //808c5da0
    Object *parent; //0x1c
}; //0x20

#endif