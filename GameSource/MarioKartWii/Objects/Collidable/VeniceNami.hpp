#ifndef _VENICENAMI_OBJECT_
#define _VENICENAMI_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class VeniceNami : public ObjectCollidable { //ObjectNum 0x4 = 4
public:
    explicit VeniceNami(const KMP::Holder<GOBJ>& gobjHolder); //8082e854
    ~VeniceNami() override; //8082f3c8 vtable 808d8a60
    void Update() override; //0x14 8082ef80
    u32 GetPropertiesBitfield() override; //0x2c 8082f3c0

    virtual const char* GetSubFileName() const; //0x38 8082f3ac
    void LoadModels() override; //0x44 8082e9f4
    virtual void LoadAnimations(); //0x5c 8082ebe8
    virtual void UpdateModelMatrix(); //0x6c 8082ec9c
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 8082f3b8

    float height; //0xb0

    float oddStageRisingSpeedPercent; //0xc4 setting0/100
    float eventStageRisingSpeedPercent; //0xc8 setting6/100
    u32 stage2FrameCount; //0xcc setting3
    u32 stage4FrameCount; //0xd0 setting5

    float stage1Height; //0xe0 setting2
    float stage3Height; //0xe4 setting4
    float stage5Height; //0xe8 setting1
    float curStageHeight; //0xec
}; //0xf0
} //namespace Objects
#endif