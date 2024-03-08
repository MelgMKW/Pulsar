#include <MarioKartWii/Item/ItemManager.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <MarioKartWii/Item/Obj/Gesso.hpp>
#include <MarioKartWii/CourseMgr.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/Driver/DriverManager.hpp>
#include <Info.hpp>


namespace Pulsar {
namespace Race {
//Credit CLF78 and Stebler, this is mostly a port of their version with slightly different hooks and proper arguments naming since this is C++
void UseFeather(Item::Player& itemPlayer) {
    const Kart::Pointers* pointers = itemPlayer.kartPointers;
    pointers->kartMovement->specialFloor |= 0x4; //JumpPad

    Kart::Status* status = pointers->kartStatus; //Hijacking bitfield1 14th bit to create a feather state
    u32 type = 0x7;
    if((status->bitfield1 & 0x4000) != 0) type = 0x2; //if already in a feather, lower vertical velocity (30.0f instead of 50.0 for type 7)
    status->jumpPadType = type;
    status->trickableTimer = 0x4;

    itemPlayer.inventory.RemoveItems(1);

    if(DriverMgr::isOnlineRace && itemPlayer.isRemote) Item::Obj::AddEVENTEntry(OBJ_BLOOPER, itemPlayer.id);
}

void UseBlooperOrFeather(Item::Player& itemPlayer) {
    if(Info::IsFeather()) UseFeather(itemPlayer);
    else itemPlayer.UseBlooper();
};
kmWritePointer(0x808A5894, UseBlooperOrFeather);
//kmBranch(0x807a81b4, UseBlooperOrFeather); //replaces UseBlooper



void ReplaceBlooperUseOtherPlayers(Item::GessoMgr& gessoMgr, u8 id) {
    if(Info::IsFeather()) {
        UseFeather(Item::Manager::sInstance->players[id]);
    }
    else gessoMgr.DeployBlooper(id);

}
kmCall(0x80796d8c, ReplaceBlooperUseOtherPlayers); //replaces the small blooper model when someone uses a blooper with a feather use




//kmWrite32(0x805b68d8, 0x7DE97B78); //mr r9, r15 to get playercollision
static bool ConditionalIgnoreInvisibleWalls(float radius, CourseMgr& mgr, const Vec3& position, const Vec3& prevPosition,
    KCLBitfield acceptedFlags, CollisionInfo* info, KCLTypeHolder& kclFlags)
{
    if(Info::IsFeather()) {
        register Kart::Collision* collision;
        asm(mr collision, r15;);
        Kart::Status* status = collision->link.pointers->kartStatus;
        if(status->bitfield0 & 0x40000000 && status->jumpPadType == 0x7) {
            acceptedFlags = static_cast<KCLBitfield>(acceptedFlags & ~(1 << KCL_INVISIBLE_WALL));
        }
        //to remove invisible walls from the list of flags checked, these walls at flag 0xD and 2^0xD = 0x2000*
    }
    return mgr.IsCollidingAddEntry(position, prevPosition, acceptedFlags, info, &kclFlags, 0, radius);
}
kmCall(0x805b68dc, ConditionalIgnoreInvisibleWalls);

u8 ConditionalFastFallingBody(const Kart::Sub& sub) {
    if(Info::IsFeather()) {
        const Kart::PhysicsHolder& physicsHolder = sub.link.GetPhysicsHolder();
        const Kart::Status* status = sub.link.pointers->kartStatus;
        if(status->bitfield0 & 0x40000000 && status->jumpPadType == 0x7 && status->airtime >= 2 && (!status->bool_0x97 || status->airtime > 19)) {
            Input::ControllerHolder& controllerHolder = sub.link.GetControllerHolder();
            float input = controllerHolder.inputStates[0].stick.z <= 0.0f ? 0.0f :
                (controllerHolder.inputStates[0].stick.z + controllerHolder.inputStates[0].stick.z);
            physicsHolder.physics->gravity -= input * 0.39f;
        }
    }
    return sub.link.GetPlayerIdx();
}
kmCall(0x805967ac, ConditionalFastFallingBody);


void ConditionalFastFallingWheels(float unk_float, Kart::WheelPhysicsHolder* wheelPhysicsHolder, Vec3& gravityVector, const Mtx34& wheelMat) {
    if(Info::IsFeather()) {
        Kart::Status* status = wheelPhysicsHolder->link.pointers->kartStatus;
        if(status->bitfield0 & 0x40000000 && status->jumpPadType == 0x7) {
            if(status->airtime == 0) status->bool_0x97 = ((status->bitfield0 & 0x80) != 0) ? true : false;
            else if(status->airtime >= 2 && (!status->bool_0x97 || status->airtime > 19)) {
                const Input::ControllerHolder& controllerHolder = wheelPhysicsHolder->link.GetControllerHolder();
                float input = controllerHolder.inputStates[0].stick.z <= 0.0f ? 0.0f :
                    (controllerHolder.inputStates[0].stick.z + controllerHolder.inputStates[0].stick.z);
                gravityVector.y -= input * 0.39f;
            }
        }
    }
    wheelPhysicsHolder->Update(gravityVector, wheelMat, unk_float);
}
kmCall(0x805973b4, ConditionalFastFallingWheels);


s32 HandleGroundFeatherCollision(const Kart::Collision& collision) {
    if(Info::IsFeather()) {
        Item::Player& itemPlayer = Item::Manager::sInstance->players[collision.link.GetPlayerIdx()];
        itemPlayer.inventory.currentItemCount += 1;
        UseFeather(itemPlayer);
    }
    return -1;
}
kmWritePointer(0x808b54e8, HandleGroundFeatherCollision);

static u32 ConditionalBlooperTimer(u32 timer) {
    if(Info::IsFeather()) timer = 0;
    else timer--;
    return timer;
}
kmCall(0x807bba64, ConditionalBlooperTimer);

/* for spraying, useless
void ConditionalFeatherBRRES(g3d::ResFile& file, ArchiveSource type, const char* brresName) {
    if(Info::IsFeather()) brresName = "feather.brres";
    ModelDirector::BindBRRES(file, type, brresName);
}
kmCall(0x807a84c8, ConditionalFeatherBRRES);
*/

void LoadCorrectFeatherBRRES(Item::ObjGesso& objKumo, const char* mdlName, const char* shadowSrc, u8 whichShadowListToUse,
    Item::ObjBase::AnmParam* anmParam) {
    if(Info::IsFeather()) objKumo.LoadGraphics("feather.brres", mdlName, shadowSrc, 0, 0,
        static_cast<nw4r::g3d::ScnMdl::BufferOption>(0), nullptr, 0);
    else objKumo.LoadGraphicsImplicitBRRESNoFunc(mdlName, shadowSrc, 0, static_cast<nw4r::g3d::ScnMdl::BufferOption>(0), 0);
}
kmBranch(0x807a8390, LoadCorrectFeatherBRRES);

void ConditionalNoBlooperAnimation(ModelDirector* mdl, u32 id, g3d::ResFile& brres, const char* name, AnmType type, bool hasBlend,
    const char* brasd, ArchiveSource source, u8 kartArchiveIdx) {
    if(!Info::IsFeather()) {
        mdl->LinkAnimation(id, brres, name, type, hasBlend, brasd, source, kartArchiveIdx);
    }
}
kmCall(0x807a854c, ConditionalNoBlooperAnimation);
kmCall(0x807a857c, ConditionalNoBlooperAnimation);
kmCall(0x807a85ac, ConditionalNoBlooperAnimation);


void ConditionalObjProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel) {
    new (dest) Item::ObjProperties(rel);
    if(Info::IsFeather()) {
        dest->limit = 4;
        dest->canFallOnTheGround = true;
        dest->canFallOnTheGround2 = true;
    }
}
kmCall(0x80790bc4, ConditionalObjProperties);

//Kept as is because it's almost never used and that guarantees ghost sync
kmWrite32(0x808b5c24, 0x42AA0000); //increases min, max speed of jump pad type 0x7 as well as its vertical velocity
kmWrite32(0x808b5c28, 0x42AA0000);
kmWrite32(0x808b5c2C, 0x42960000);
}//namespace Race
}//namespace Pulsar