#ifndef _ITEMOBJ_
#define _ITEMOBJ_
#include <kamek.hpp>
#include <MarioKartWii/Item/ItemPlayer.hpp>
#include <MarioKartWii/Item/Obj/ItemEVENT.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/3D/ClipInfoMgr.hpp>
#include <MarioKartWii/Entity/EntityManager.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/3D/Model/ShadowModelDirector.hpp>
#include <MarioKartWii/3D/Model/ModelCalc.hpp>
#include <MarioKartWii/Audio/Actors/ItemActor.hpp>
#include <MarioKartWii/KCL/Collision.hpp>
#include <MarioKartWii/RKNet/EVENT.hpp>

namespace Item {
class ObjMiddle;
class ObjHolder;
class Player;

class Collision {
    //normals stuff
    u8 unknown[0x5c];
};
size_assert(Collision, 0x5c);
//some of these functions are obviously part of ObjMiddle, but it's very hard to tell and it doesn't matter since there is only one instance of an Obj that isn't an ObjMiddle (the one in ItemManager)

class Obj {
public:
    Obj(); //8079d8bc

    class CalcWorldCB : public ModelCalcBase, public EmptyModelCalcParent, public g3d::ICalcWorldCallback {
        //vtable 808d19b0, 808D19A8 for empty
        ~CalcWorldCB() override; //thunk 807a3a1c func 807a39d4
        void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807a3a14 func 8079d84c
        Vec3* position;
    }; //0x14 used to set ScnMdlSimple's cb
    struct AnmParam { //808d1d20 for example
        const char* name;
        AnmType type;
    };

    virtual void RemoveFromScn();  //0x8 8079e300 vtable 808d19f0
    virtual void InitSelf(); //0xc 8079d804
    virtual void UpdateModelPosition();  //0x10 807a05d0
    //called when an active object is very far or out of sight (info obtained from clipinfo's bitfield)
    virtual void UpdateModelPositionNoClip(); //0x14 807a05f4 

    virtual void SpawnModel(); //0x18 8079d9fc
    virtual void PrepareLight(); //0x1c 8079da9c acquires and sets light
    virtual bool SetInitialPosition(PlayerObj& playerObj);; //0x20 8079dcb4 returns 1 if it's a forward throw
    virtual int OnKill(); //0x24 8079dcbc
    virtual void OnTetherBreak(); //0x28 8079dd6c just a blr, called when a tether breaks (for example you trail a green and hit an obj)
    virtual void OnFinishKill(); //0x2c 8079dd70
    virtual void vf_0x30(); //0x30 8079dee4
    virtual void vf_0x34(); //0x34 8079e1f0

    //EVENT
    static void AddUseEVENTEntry(ItemObjId itemObjId, u8 playerId); //8079c220
    static void AddShootEVENTEntry(ItemObjId itemObjId); //8079c2e4
    static void AddHitFreeEVENTEntry(ItemObjId itemObjId, u32 type, u8 playerIdOfCollision, u16 eventBitfield); //8079c3c4 id to 12 if nothing
    static void AddHitDraggedEVENTEntry(ItemObjId itemObjId); //8079c498 assumes packet is already prefilled, inlined in SendOrExtractHitDraggedEVENT
    static void AddTCLostPassEVENTEntry(ItemObjId itemObjId, u8 playerId); //8079c554 by passing the TC
    static void AddAction6EVENTEntry(ItemObjId itemObjId, u16 playerId); //8079c620
    static void AddTCLostEndEVENTEntry(ItemObjId itemObjId, u8 playerId, u8 r5, u16 eventBitfield, u32 kumo1a8, u32 r8); //8079C6E4 by the TC ending, playerId always 12?
    static void AddDropEVENTEntry(ItemObjId itemObjId); //8079c7c4
    //These functions can either prepare and send the packet (if the bool is true, in which case packet can be nullptr), 
    //or extract data from a packet (if the bool is false)
    //often the game first prepares and sends the packet, then it calls the same func with the packet to extract its data into Obj
    //returns the packet
    static void* SendOrExtractShootEVENT(void* packet, Obj* obj, bool extractOrSend); //807a3370
    static void* SendOrExtractHitDraggedEVENT(void* packet, Obj* obj, bool extractOrSend); //8079c960
    void ProcessRecvShootEVENT(ItemObjId itemObjId, const EVENTBuffer::Entry& entry, bool isBreak, bool isDrop, u8 playerUsedItemId); //8079de34
    void PrepareShootEVENTPacket(); //807a31c0

    //Load
    void LoadGraphics(const char* brresName, const char* mdlName, const char* shadowSrc, u8 whichShadowListToUse, AnmParam* anmParam,
        g3d::ScnMdl::BufferOption option, void* funcPtr, u32 directorBitfield); //807a0040
    void LoadGraphicsImplicitBRRESNoFunc(const char* mdlName, const char* shadowSrc, AnmParam* anmParam,
        g3d::ScnMdl::BufferOption option, u32 directorBitfield); // 8079ff5c brresName will be deduced from mdlName, shadow list always 0
    void LoadGraphicsDefault(const char* brresName, const char* mdlName, const char* shadowSrc, AnmParam* param); //8079ffa4
    void LoadGraphicsImplicitBRRES(const char* mdlName, const char* shadowSrc, u8 whichShadowListToUse, AnmParam* anmParam,
        g3d::ScnMdl::BufferOption option, void* funcPtr); //8079ffdc
    //calls loadGraphics with brresName == nullptr which causes it to be copied from mdlName
    void LoadItemLight(); //807a0380 only for teams

    void Init(u32 idx, u16 effectIdx, ItemObjId id); //8079e224
    void Spawn(ItemObjId objId, u8 playerId, const Vec3& position, bool r7); //8079e550
    void Set(ItemObjId objId); //8079e5f4

    //Update
    void Update(bool r4); //8079efec
    void UpdateWithClipping(); //807a25b0
    void UpdateModelFromQuat(Mtx34* transMtxCopy = nullptr); //807a0cd4 will copy the calculated transMtx into the arg if not null
    void UpdateModelFromVecs(Mtx34* transMtxCopy = nullptr); //807a07b8 will copy the calculated transMtx into the arg if not null
    void UpdateShadow(Mtx34& transMtx); //807a0a68

    //Kill
    int KillObj(u32 r4); //807a6328 might be objthrowable
    void UpdateKillThunk(); //807a38e4 as the obj is getting killed, plays the animation etc...
    void UpdateKill(); //807a6700

    //Collision
    void OnPlayerCollision(Kart::Player& player, bool isRemote); //807a3790
    void OnObjCollision(Item::Obj& other);
    void UnregisterEntity(); //8079eecc
    void RegisterEntity(bool usePropertiesSmallRadius); //8079ee30
    //result: 0 the obj survives with no effect, 1 the obj bounces off the other entity, 2 kill the obj
    void ProcessOtherCollision(u32 result, const Vec3& otherPos, const Vec3& otherSpeed); //807a18fc a green runs into a green, a green runs into an Object like a goomba
    void KillFromPlayerCollision(bool sendBreakEVENT, u8 playerIdOfCollision); //807a6614
    void KillFromOtherCollision(bool sendBreakEVENT); //807a6560 for example a bomb makes objs disappear, or a green has bounced too many times with a wall
    bool CanDisappearFromDuration() const; //8079feb4 inlined in TryKill if has been active for over 300 frames
    void TryDisappearDueToExcess(); //8079fe30 when too many of this type exist on the map
    void DisappearDueToExcess(bool sendBreakEVENT); //807a6c14
    void CheckOtherObjsCollision(); //807a1c94
    bool CheckKartCollision(Kart::Player* kartPlayer, u32 r5); //807a14d4

    void FinishKill(); //8079e884 removes entity and calls OnFinishKill

    ItemObjId itemObjId;
    u16 idx; //0x8
    u16 effectIdx; //0xa see item effects
    u16 eventBitfield; //0xc bitfield calculated and sent via EVENT packets for use/shoot
    u8 unknown_0xe[2];
    Quat quaternion; //0x10
    Vec3 unknown_0x20[3];
    Vec3 position; //0x44
    //Mtx34 transMtx; //0x20, so curPosition is at 0x44
    Vec3 speed; //0x50
    Vec3 scale; //0x5c
    float scaleFactor; //0x68
    u8 playerUsedItemId; //0x6c player id of who used the item in the 1st place
    u8 playerCollisionId; //0x6d player id of who collided with the obj
    u8 unknown_0x6d[0x74 - 0x6e];
    u32 bitfield74;
    /*
    0x1 : isKilled
    0x8 : finished throw (only for obj throwable)
    */
    u32 bitfield78; //0x78
    /*
    0x40 : no movement?
    */
    u32 bitfield7c; //0x7c
    /*

    0x20 : isOnline
    */
    Vec3 initialPosition; //0x80 the position it spawned on
    Vec3 positionRelativeToPlayer; //0x8c only updated while the item is tethered (including during the throw anm)
    Vec3* curPosition; //0x98 there's likely a substruct here else why would this ptr be needed
    ModelDirector* modelDirector; //0x9c
    ShadowModelDirector* shadowMdlDirector; //0xa0
    ClipInfo* clipInfo; //0xa4
    ModelDirector* item_light; //0xa8 only in teams, it's the coloured halo around the item
    Light* light; //0xac
    Entity* entity; //0xb0
    float unknown_0xb4[2];
    Vec3 lastPosition; //0xbc
    u8 unknown_0xc8[0xd4 - 0xc8];
    KCLTypeHolder kclType; //0xd4
    Collision collision; //0xd8
    void* unknown_0x134;
    u8 unknown_0x138[0x160 - 0x138];
    u32 duration; //0x160   
    u8 unknown_0x164[4]; //0x164
    Ptmf_0A<Obj, void> updatePtmf; //0x168 Update, UpdateKill
    u8 unknown_0x174[0x180 - 0x174];
    Audio::ItemActor* sound; //0x180
    u8 unknown_0x184[0x188 - 0x184];


};//Total Size 0x188
size_assert(Obj, 0x188); //where to cut the class and decide the rest is part of "ObjMiddle" was done through analyzing the size of the obj in ItemManager, which can only be up to 0x188

class ObjMiddle : public Obj { //the vtable of base has a ton of copies in memory so there could be in btw classes
public:
    ObjMiddle(); //807a6928
    //vtable 808d1c50

    u8 unknown_0x188[4];
    Vec3 unknown_0x18c;
    u8 unknown_0x198;
    u8 padding[3];
    u32 killTimer; //0x19c check by update kill
}; //total size 0x1A0
size_assert(ObjMiddle, 0x1A0);

}//namespace Item
#endif