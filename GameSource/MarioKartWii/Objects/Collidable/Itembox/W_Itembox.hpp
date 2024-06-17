#ifndef _W_ITEMBOX_
#define _W_ITEMBOX_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/Objects/Collidable/Itembox/Itembox.hpp>

namespace Objects {

/*
SubObjectArray<W_Itembox::Box>
    ~SubObjectArray<W_Itembox::Box>() override; //8076c9c8 vtable 808cec5c
    void CreateArray(u32 boxCount, u32 unused) override; //8076cf78
    void CreateArray(u32 boxCount, EGG::Heap* heap) override; //8076cfc8
    void vf_0x14(u32 r4) override; //8076d040
    void vf_0x18() override; //8076ca40

*/

class W_Itembox : public ObjectCollidable { //ObjectNum 0xd3 = 211
    class Box : public Itembox { //one box of the line
    public:
        explicit Box(const KMP::Holder<GOBJ>& gobjHolder); //8076ccc8 inlined
        ~Box() override; //8076cd04 vtable 808cec78
        void OnStart() override; //0xc 8076cd44
        void Update() override; //0x14 8076cdb8
        u32 GetPropertiesBitfield() override; //0x2c 8076cf70
        const char* GetBRRESName() const override; //0x34 8076cf58
        const char* GetSubFileName() const override; //0x38 8076cf64
        ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 8076cefc
        ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
            ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) const override; //0xc4 8076cf34

        u32 hasSpawned; //0xc8 0 unspawned, 1 spawned
    }; //0xcc
    explicit W_Itembox(const KMP::Holder<GOBJ>& gobjHolder); //8076c85c
    ~W_Itembox() override; //8076ca44 vtable 808ceb70
    void OnStart() override; //0xc 8076cac4
    void Update() override; //0x14 8076cb08
    void UpdateModel() override; //0x1c 8076cf3c
    u32 GetPropertiesBitfield() override; //0x2c 8076cf50
    void LoadModels() override; //0x44 8076cf4c
    void LoadClipInfo() override; //0x58 8076cf40
    void LoadAnimations() override; //0x5c 8076cf48
    void LoadCollision() override; //0x60 8076cf44

    SubObjectArray<Box> array; //0xb0
    u32 boxCount; //0xbc setting6, if 0 then 5
    u32 frameCounter; //0xc0 init at start delay = setting5 and then -1 every frame and reset to time btw 2 boxes = setting6
    u32 numberOfBoxesSpawned; //0xc4 starts at 0, then +1 every time the counter reaches 0, until boxCount - 1 when it resets to 0
}; //0xc8


}//namespace Objects



#endif