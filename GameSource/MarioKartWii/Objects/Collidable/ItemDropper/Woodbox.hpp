#ifndef _WOODBOX_OBJECT_
#define _WOODBOX_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ItemDropper/ItemDropper.hpp>

namespace Objects {

class Woodbox : public ItemDropper { //ObjectNum 0x70 = 112
public:
    static u32 respawnTimer; //808d1290
    explicit Woodbox(const KMP::Holder<GOBJ>& gobjHolder); //8077e5e4
    ~Woodbox() override; //8077e620 vtable 808d14b4
    void OnStart() override; //0xc 8077e678
    u32 GetPropertiesBitfield() override; //0x2c 8077edac
    const char* GetBRRESName() const override; //0x34 8077ed70
    const char* GetSubFileName() const override; //0x38 8077ed7c
    virtual void UpdateCollision() override; //0x74 8077ebb8
    virtual void InitEntity(float maxSpeed) override; //0xe0 8077ece4

    void LoadEffects() override; //0xec 8077e6b8
    void Respawn() override; //0xf4 8077e750
    void DropItem(u8 playerId, const Vec3& speed) override; //0xf8 8077e704
    void UpdateRespawn() override; //0xfc 8077e7b0 

    void OnNormalCollision(const Kart::Player& kartPlayer) override; //0x104 8077e928
    void OnImperviousCollision(const Kart::Player& kartPlayer) override; //0x108 8077e9c0
    void OnNormalItemCollision(const Kart::Player& kartPlayer, const Vec3& itemSpeed) override; //0x10c 8077ea6c
    void OnImperviousItemCollision(const Kart::Player& kartPlayer, const Vec3& itemSpeed) override; //0x110 8077eb08

    void UpdateRespawnImpl(); //8077e7e0
    u8 unknown_0xc0[0x8];
    float initialRespawnHeight; //0xc0 init at KMP YPos
    float curRespawnHeight; //0xc4 negative while respawning, then updated to its value on "fall"
}; //0xc8


/*
SubObjectArray<Temp>
    ~SubObjectArray<W_Itembox::Box>() override; //8077e0a4 vtable 808d1384
    void CreateArray(u32 boxCount, u32 unused) override; //8077edb4
    void CreateArray(u32 boxCount, EGG::Heap* heap) override; //8077ee04
    void vf_0x14(u32 r4) override; //8077ee7c
    void vf_0x18() override; //8077e11c
*/


class W_Woodbox : public ObjectCollidable { //ObjectNum 0xd3 = 211
public:
    class Box : public Woodbox {
    public:
        explicit Box(const KMP::Holder<GOBJ>& gobjHolder); //8077e34c inlined
        ~Box() override; //8077e388 vtable 808d13a0
        void OnStart() override; //0xc 8077e3e4
        void Update() override; //0x14 8077e49c
        u32 GetPropertiesBitfield() override; //0x2c 8077eda4
        void RespawnImpl() override; //0xf0 8077e444

    };
    //this is essentially a dummy object so all the load funcs are blr'd
    explicit W_Woodbox(const KMP::Holder<GOBJ>& gobjHolder); //8077df24
    ~W_Woodbox() override; //8077e120 vtable 808d1298
    void OnStart() override; //0xc 8077e1a0
    void Update() override; //0x14 8077e1e4
    void UpdateModel() override; //0x1c 8077ecc8
    u32 GetPropertiesBitfield() override; //0x2c 8077ecdc
    void LoadModels() override; //0x44 8077ecd8
    void LoadClipInfo() override; //0x58 8077eccc
    void LoadAnimations() override; //0x5c 8077ecd4
    void LoadCollision() override; //0x60 8077ecd0

    SubObjectArray<Box> array; //0xb0
    u32 boxCount; //0xbc setting7
    u32 timeUntilNextBox; //0xc0 init at start delay (if not 0) setting5, then reset to time btw 2 boxes, setting6
    u32 unknown_0xc4;
}; //0xc8

} //namespace Objects
#endif