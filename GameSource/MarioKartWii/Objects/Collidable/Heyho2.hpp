#ifndef _HEYHO2_OBJECT_
#define _HEYHO2_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

//lifts work in pairs; the first half doesn't create its own rider, instead only the latter half does  

class Heyho2 : public ObjectCollidable { //ObjectNum 0x149 = 329
public:
    static u32 liftCount; //808d7cb0 set to 14 on boot, set to 10 if >1screen, never reset
    class Lift;
    class Rider : public ObjectCollidable {
    public:
        Rider(Lift& initial, Lift& opposite, u32 side); //80829d68 1 = right, 2 = left
        ~Rider() override; //8082a274 vtable 808d7e90
        void OnStart() override; //0xC 80829ed4
        void Update() override; //0x14 8082a010
        u32 GetPropertiesBitfield() override; //0x2c 8082a26c
        const char* GetBRRESName() const override; //0x34 8082a214
        const char* GetSubFileName() const override; //0x38 8082a220
        void LoadAnimations() override; //0x5c 8082a00c
        void LoadRoute() override; //0x64 8082a208
        bool IsMat1Shp1() override; //0xa8 8082a20c

        u8 unknown_0xb0[4];
        u32 randVal; //0xb4
        Vec3 sideOffset; //0xb8
        Lift* initial; //0xc4
        Lift* opposite; //0xc8
    }; //0xcc

    class Lift : public ObjectCollidable {
    public:
        Lift(const KMP::Holder<GOBJ>& gobjHolder, Heyho2& parent, u32 idx); //80829764
        ~Lift() override; //8082a1c8 vtable 808d7da4
        void OnStart() override; //0xC 808298dc
        void Update() override; //0x14 80829aa4
        u32 GetPropertiesBitfield() override; //0x2c 8082a1b8
        const char* GetBRRESName() const override; //0x34 8082a18c
        const char* GetSubFileName() const override; //0x38 8082a198
        void UpdateModelMatrix() override; //0x6c 80829c98
        bool IsMat1Shp1() override; //0xa8 8082a1c0

        Rider* riders[2]; //0xb0 stored for both halves, but same instances
        bool useK_chairlift01; //0xb8 setting0
        u8 unknown_0xb9[3];
        u8 randVal; //0xbc
        u8 unknown_0xbd[3];
        u32 idx; //0xc0
        float unknown_0xc4;
    }; //0xc8
    explicit Heyho2(const KMP::Holder<GOBJ>& gobjHolder); //8082963c
    ~Heyho2() override; //8082a14c vtable 808d7cb8
    void OnStart() override; //0xC 808296f8
    void Update() override; //0x14 8082a138
    u32 GetPropertiesBitfield() override; //0x2c 8082a144
    void LoadModels() override; //0x44 8082a13c
    void LoadAnimations() override; //0x5c 8082a140
    void LoadRoute() override; //0x64 8082a134

    Lift* lifts[20];
}; //0x100
} //namespace Objects
#endif