#ifndef _ITEMOBJGESSO_
#define _ITEMOBJGESSO_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>
#include <game/Sound/Actors/ItemSound.hpp>
#include <game/Visual/Model/ModelDirector.hpp>

//_sinit_ at 807a9a58
class ItemObjGesso : public ItemObj {
public:
    static ItemObj **CreateArray(u32 count); //807a8138
    void InitSelf() override; //0x8 807a8378 vtable 808d1e48
};
size_assert(ItemObjGesso, 0x1a0);

class GessoPage { //one per Page
    GessoPage(u32 pageId); //807a8460
    ~GessoPage(); //807a85f4
    u32 unknown_0x0;
    ModelDirector *gessoModel; //0x4
    u32 pageId; //0x8
    u8 unknown_0xc[0x1c - 0xc];
    bool isTwilightHouse;
    u8 padding[3];
    GessoSound sound; //0x20
    u8 unknown_0xc8[8]; //0xc8
}; //0xd0
size_assert(GessoPage, 0xd0);

class GessoMgr {
public:
    static GessoMgr *sInstance; //809c3648
    static GessoMgr *GetStaticInstance(); //807a8f04
    static void DestroyStaticInstance(); //807a8fa0
    GessoMgr(); //807a90a0 inlined
    void DeployBlooper(u8 playerId); //807a9128 that player used a blooper which will deploy the blooper model from the character
    u32 pageCount; //0x0
    u8 unknown_0x4[0x44 - 0x4];
    GessoPage *gessoPages[4]; //0x44
};//Total Size 0x54
size_assert(GessoMgr, 0x54);



#endif