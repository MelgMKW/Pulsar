#ifndef _ITEMOBJ_
#define _ITEMOBJ_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/Visual/ClipInfoMgr.hpp>
#include <game/Collision/Entity/EntityHolder.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Visual/Model/ShadowModelDirector.hpp>
#include <game/Visual/Model/ModelWorldCalc.hpp>
#include <game/Sound/Actors/ItemSound.hpp>
#include <game/Collision/Collision.hpp>

namespace Item {
class Obj;
class ObjHolder;
class Player;

struct ObjProperties {
    static ObjProperties objProperties[15]; //809c2f48

    ObjProperties(const ObjProperties& rel); //80790e7c copy constructor from rodata's static array "copyFromRel"
    Obj** (*CreateArray)(u32 count);
    u32 limit; //0x4
    u32 competitionLimit;
    u32 capacity; //0xc
    u32 capacity2;
    u8 unknown_0x14[0x30 - 0x14];
    float backwardDrawDistance; //0x30
    float forwardDrawDistance;
    float unknown_0x38[7];
    u8 unknown_0x54[0x58 - 0x54];
    bool canFallOnTheGround; //0x58
    bool canFallOnTheGround2; //0x59
    bool unknown_0x5a[2];
    u8 unknown_0x5b[0x6c - 0x5b];
    float unknown_0x6c;
    bool unknown_0x70;
    u8 unknown_0x71[0x74 - 0x71];
}; // Total size 0x74
extern float greenShellSpeed;
extern float redShellInitialSpeed;
extern float redShellSpeed;
extern float blueShellSpeed;
extern float blueShellMinimumDiveDistance; //big because it's squared
extern float blueShellHomingSpeed;

void CopyObjPropertiesFromRelToTable();



class Collision {
    //normals stuff
    u8 unknown[0x5c];
};
size_assert(Collision, 0x5c);

class ObjBase {
public:
    ObjBase(); //8079d8bc

    class CalcWorld : public ModelWorldCalc {
        ~CalcWorld() override; //807a3c1c vtable 808d19b0, 808D19A8 for empty
        void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //807a3a14
        virtual void vf_0x18(); //807a39d4
        virtual void vf_0x1c(); //8079d84c
    }; //used to set ScnMdlSimple's cb
    struct AnmParam { //808d1d20 for example
        const char* name;
        AnmType type;
    };

    virtual void RemoveFromScn();  //8079e300 vtable 808d19f0
    virtual void InitSelf(); //0x8 8079d804
    virtual void UpdateModelPosition();  //0x10 807a05d0
    virtual void vf_0x14(); //0x14 807a05f4
    virtual void SpawnModel(); //0x18 8079d9fc
    virtual void vf_0x1c(); //0x1c 8079da9c
    virtual bool SetInitialPosition(Player& player); //0x20 8079dcb4 returns 1 if it's a forward throw
    virtual void OnCollision(); //0x24 8079dcbc
    virtual void vf_0x28(); //0x28 8079dd6c
    virtual void vf_0x2c(); //0x2c 8079dd70
    virtual void vf_0x30(); //0x30 8079dee4
    virtual void vf_0x34(); //0x34 8079e1f0
    void Update(bool r4); //8079efec
    static void GetQuatFromMat(Quat* dest, const Mtx34& src); //807b9dd4 probably global or another class
    static void AddEVENTEntry(ItemObjId itemObjId, u8 playerId);
    ItemObjId itemObjId;
    u16 idx; //0x8
    u16 r5; //0xa
    u8 unknown_0xc[0x10 - 0xc];
    Quat quaternion; //0x10
    Vec3 unknownVec_0x20[2];
    Vec3 basePosition; //0x38
    Vec3 curPosition; //0x44
    Vec3 speed; //0X50
    float unknown_0x5c;
    u8 unknown_0x60[0x6c - 0x60];
    u8 playerUsedItemId; //0x6c player id of who used the item in the 1st place
    u8 unknown_0x6d[0x8c - 0x6d];
    Vec3 translation; //0x8c just a copy of position for most items?
    u8 unknown_0x98[4];
    ModelDirector* modelDirector; //0x9c
    ShadowModelDirector* shadowMdlDirector; //0xa0
    ClipInfo* clipInfo; //0xa4
    ModelDirector* item_light; //0xa8 only in teams, it's the coloured halo around the item
    u8 unknown_0xac[4];
    Entity* entity; //0xb0
    u8 unknown_0xb4[8];
    Vec3 lastPosition; //0xbc
    u8 unknown_0xc8[0xd4 - 0xc8];
    KCLTypeHolder kclType; //0xd4
    Collision collision; //0xd8
    void* unknown_0x134;
    u8 unknown_0x138[0x174 - 0x138];
};//Total Size 0x174
size_assert(ObjBase, 0x174);

class Obj : public ObjBase {
public:
    Obj(); //807a6928
    //808d1c50 somehow has a different vtable
    void Init(u32 idx, u32 r5, ItemObjId id); //8079e224
    void Set(ItemObjId objId); //8079e5f4
    void Spawn(ItemObjId objId, u8 playerId, const Vec3& position, bool r7); //8079e550

    bool CheckKartCollision(Kart* kart, u32 r5); //807a14d4
    void LoadGraphics(const char* brresName, const char* mdlName, const char* shadowSrc, u8 whichShadowListToUse, AnmParam* anmParam,
        g3d::ScnMdl::BufferOption option, void* funcPtr, u32 directorBitfield); //807a0040
    void LoadGraphicsImplicitBRRESNoFunc(const char* mdlName, const char* shadowSrc, AnmParam* anmParam,
        g3d::ScnMdl::BufferOption option, u32 directorBitfield); // 8079ff5c brresName will be deduced from mdlName, shadow list always 0
    void LoadGraphicsDefault(const char* brresName, const char* mdlName, const char* shadowSrc, AnmParam* param); //8079ffa4
    void LoadGraphicsImplicitBRRES(const char* mdlName, const char* shadowSrc, u8 whichShadowListToUse, AnmParam* anmParam,
        g3d::ScnMdl::BufferOption option, void* funcPtr); //8079ffdc
    //calls loadGraphics with brresName == nullptr which causes it to be copied from mdlName
    void LoadItemLight(); //807a0380 only for teams


    u8 unknown_0x174[0x180 - 0x174];
    ItemSound* sound; //0x180
    u8 unknown_0x184[0x1a0 - 0x184];
}; //total size 0x1A0
size_assert(Obj, 0x1A0);

class ObjHolder { //one instance per objID
public:

    void Init(ItemObjId id, u32* initialIdx); //80795ccc
    void Spawn(u32 quantity, ItemObj* usedObj, u8 playerId, const Vec3& playerPos, bool r8); //80795e04 usedObj is filled by the function
    ItemObjId itemObjId;
    Obj** itemObj;
    u32 capacity; //unsure what the diff is with limit
    u32 capacity2;
    u32 bodyCount; //count on the track, including trailing/spinning
    u32 spawnedCount; //0x14
    u8 unknown_0x18[4];
    u32 limit;
    u8 unknown_0x20[0x24 - 0x20];
};//Total Size 0x24
size_assert(ObjHolder, 0x24);
}//namespace Item
#endif