#ifndef _W_ITEMBOX_LINE_
#define _W_ITEMBOX_LINE_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/Objects/Collidable/Press.hpp>
#include <MarioKartWii/Objects/Collidable/Itembox/Itembox.hpp>

namespace Objects {

/*

SubObjectArray<W_Itemboxline::Box>
    ~SubObjectArray<W_Itemboxline::Box>() override; //8076d460 vtable 808cee80
    void CreateArray(u32 boxCount, u32 unused) override; //8076eb14
    void CreateArray(u32 boxCount, EGG::Heap* heap) override; //8076eb64
    void vf_0x14(u32 r4) override; //8076ebdc
    void vf_0x18() override; //8076d554


SubObjectArray<W_Itemboxline::Block>
    ~SubObjectArray<W_Itemboxline::Block>() override; //8076d4d8 vtable 808cee64
    void CreateArray(u32 boxCount, u32 unused) override; //8076ea48
    void CreateArray(u32 boxCount, EGG::Heap* heap) override; //8076ea98
    void vf_0x14(u32 r4) override; //8076eb10
    void vf_0x18() override; //8076d550
*/


class W_Itemboxline : public ObjectCollidable { //ObjectNum 0xd5 = 213
public:
    class Press;
    class Block;

    class Box : public Itembox { //one box on the belt
    public:
        ~Box() override; //8076da48 vtable 808ceea0
        void OnStart() override; //0xc 8076da88
        void Update() override; //0x14 8076daf4
        u16 GetID() const override; //0x24 8076e9e4
        u32 GetPropertiesBitfield() override; //0x2c 8076e9c4
        ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 8076e0bc

        u8 unknown_0xc8[4];
        Press* press; //0xcc
        Block* block; //0xd0
        EGG::Effect* rk_pressItemB; //0xd8
    }; //0xdc

    class Press : public Objects::Press {
    public:
        explicit Press(const KMP::Holder<GOBJ>& gobjHolder); //8076e7ac
        ~Press() override; //8076e818 vtable 808cf07c
        u16 GetID() const override; //0x24 8076ea28
        u32 GetPropertiesBitfield() override; //0x2c 8076ea20
        const char* GetBRRESName() const override; //0x34 8076ea30
        const char* GetSubFileName() const override; //0x38 8076ea3c 
        void TryFall() override; //0xec 8076e870
        void UpdateEffect() override; //0xf0 8076e8b0

        EGG::Effect* rk_pressSenko;
    };

    class Block : public ObjectCollidable {
    public:
        ~Block() override; //8076e164 vtable 808cef90
        void OnStart() override; //0xc 8076e1a4
        void Update() override; //0x14 8076e2c0
        u32 GetPropertiesBitfield() override; //0x2c 8076e9ec
        const char* GetBRRESName() const override; //0x34 8076e9f4
        const char* GetSubFileName() const override; //0x38 8076ea00 
        ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 8076e4e8
        ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
            ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) const override; //0xc4 8076e5d8

        u8 unknown_0xb0[8];
        EGG::Effect* rk_block; //0xb8
        u8 unknown_0xb4[4];
    }; //0xc0


    explicit W_Itemboxline(const KMP::Holder<GOBJ>& gobjHolder); //8076d044
    ~W_Itemboxline() override; //8076d558 vtable 808ced78
    void OnStart() override; //0xc 8076d604
    void Update() override; //0x14 8076d64c
    void UpdateModel() override; //0x1c 8076e9a8
    u32 GetPropertiesBitfield() override; //0x2c 8076e9bc
    void LoadModels() override; //0x44 8076e9b8
    void LoadClipInfo() override; //0x58 8076e9ac
    void LoadAnimations() override; //0x5c 8076e9b4
    void LoadCollision() override; //0x60 8076e9b0

    SubObjectArray<Box> boxesArray; //0xb0
    SubObjectArray<Block> blockArray; //0xbc

    Press* press; //0xc8
    u32 boxCount; //0xcc
    u32 frameCounter; //0xd0 init at start delay = setting5 and then -1 every frame and reset to time btw 2 boxes = setting6
    u32 unknown_0xd4;
    u32 unknown_0xd8;
}; //0xdc


}//namespace Objects



#endif