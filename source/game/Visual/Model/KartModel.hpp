#ifndef _KART_MODEL_
#define _KART_MODEL_
#include <kamek.hpp>
#include <core/nw4r/g3d/res/ResNode.hpp>
#include <game/Race/Kart/KartBase.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Visual/Mii.hpp>
#include <game/Sound/Actors/CharacterSound.hpp>
using namespace nw4r;
class IKParams { //Inverse kinematics
public:
    IKParams(u8 playerId); //8078b5d0 calls Load, if returns false, gets params from IKParam.ikp in the driver szs
    bool Load(u8 playerId); //8078b7ac loads from DiverIKParam.bin 
    u8 unk[0x11c]; //IKParam.ikp
}; //0x11c

class KartModelBones {
    static char **boneNames; //809c3db8
    KartModelBones(); //807c708c
    ~KartModelBones(); //807c70f4
    void SetBoneName(u8 idx); //807c7134
    void SetNode(g3d::ResNode resNode); //807c7158
    KartModelBones *prev;
    KartModelBones *next;
    KartModelBones *unk_0x8;
    u32 unknown_0xC;
    u32 idx;
    char *name; //0x14
    g3d::ResNode resNode; //raw bone
    u32 matId; //0x1c
    bool unknown_0x20;
    u8 unknown_0x21[3];
    Mtx34 mtxRT; //0x24 RotTrans of Chr
    Vec3 translation; //0x54 from the mtx
    //0x54
}; //0x60

class KartModel {
public:
    static char **characterNames; //808d6c58 "M Mii AM" for medium mii male outfit A
    KartModel(); //807c7364
    void Init(); //807c8758
    void InitBones(); //807c7e7c
    void Update(); //807cb360
    KartBase base;
    CharacterSound *characterSound; //0xC
    u8 unknown_0x10;
    u8 unknown_0x11[3];
    u32 unknown_0x14;
    u32 unknown_0x18;
    virtual ~KartModel(); //807cdd08 vtable 808d2ad8
    u8 unknown_0x24[0x38 - 0x24];
    u32 trickType;
    u32 trickDirection;
    u8 unknown_0x40[0x68 - 0x40];
    g3d::ResFile driverModelBRRES; //0x68
    ModelDirector *driverModel; //0x6c linked to mdl0 of the brres above
    ModelDirector *driverModel_lod; //0x70 linked to mdl0_lod of the brres above
    UnkType *opacityRelatedStruct;
    Mtx modelTransMtx; //0x78
    bool isCpu;
    u8 unknown_0xa9[0xB8 - 0xA9];
    ClipInfo *clipInfo; //0xb8
    Vec3 unknown_0xBC;
    bool isTT;
    u8 unknown_0xC9[0xCC - 0xC9];
    UnkType *unknown_0xCC[2];
    u8 unknown_0xD4[2];
    bool isNotFocusedInLiveView;
    u8 unknown_0xD7[2];
    ModelDirector mdlDirectors[6]; //array of all the mdlDirectors used (driver, driver_lod, miiHeads, luma etc..)
    u32 mdlDirectorsCount; //0xF0
    u8 unknown_0xE0[0xfa - 0xf4];
    u16 currentAnimation;
    u16 lastAnimation;
    u8 unknown_0xFe[0x100 - 0xfe];
    MiiHeadsModel *miiHeads; //0x100 0x807c795c
    KartModelBones *bonesArray; //0x104 size 36
    KartModelBones *firstBone; //0x108 one whose prev == NULL
    char *characterName; //0x10c
    u8 unknown_0x110[4];
    Mtx34 kartTimesModelMtx; //0x114
    u8 unknown_0x144[0x2a4 - 0x144];
    IKParams *ikParams; //0x2a4;
    u8 unknown_0x2a8[0x6e4 - 0x2a8];
};//total size 0x6e4

class KartModelBike : public KartModel {
public:
    KartModelBike(); //807cdccc
    ~KartModelBike() override; //807d3f58 vtable 808d2ab0
};//total size 0x6e4
#endif