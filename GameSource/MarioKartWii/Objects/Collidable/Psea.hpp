#ifndef _PSEA_OBJECT_
#define _PSEA_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class Psea1sand : public ObjectCollidable {
public:
    ~Psea1sand() override; //8082ca98 vtable 808d86c0
    const char* GetName() const override; //0x28 8082ca78
    u32 GetPropertiesBitfield() override; //0x2c 8082ca90
    const char* GetSubFileName() const override; //0x38 8082ca84
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 8082ca70
    float height; //0xb0
}; //0xb4

class Psea2dark : public ObjectCollidable {
public:
    ~Psea2dark() override; //8082ca30 vtable 808d85d4
    const char* GetName() const override; //0x28 8082ca10
    u32 GetPropertiesBitfield() override; //0x2c 8082ca28
    const char* GetSubFileName() const override; //0x38 8082ca1c
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 8082ca08
    float height; //0xb0
}; //0xb4

class Psea3nami : public ObjectCollidable {
public:
    ~Psea3nami() override; //8082c9c8 vtable 808d84e8
    const char* GetName() const override; //0x28 8082c9a8
    u32 GetPropertiesBitfield() override; //0x2c 8082c9c0
    const char* GetSubFileName() const override; //0x38 8082c9b4
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 8082c9a0
    float height; //0xb0
}; //0xb4

class Psea4tex : public ObjectCollidable {
public:
    ~Psea4tex() override; //8082c960 vtable 808d83fc
    const char* GetName() const override; //0x28 8082c940
    u32 GetPropertiesBitfield() override; //0x2c 8082c958
    const char* GetSubFileName() const override; //0x38 8082c94c
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 8082c938
    float height; //0xb0
}; //0xb4

class Psea5spc : public ObjectCollidable {
public:
    ~Psea5spc() override; //8082c8f8 vtable 808d8310
    const char* GetName() const override; //0x28 8082c8d8
    u32 GetPropertiesBitfield() override; //0x2c 8082c8f0
    const char* GetSubFileName() const override; //0x38 8082c8e4
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 8082c8d0
    float height; //0xb0
}; //0xb4

class Psea : public ObjectCollidable { //ObjectNum 0x2 = 2
public:
    explicit Psea(const KMP::Holder<GOBJ>& gobjHolder); //8082c234
    ~Psea() override; //8082c890 vtable 808d8224
    void Update() override; //0x14 8082c634
    u32 GetPropertiesBitfield() override; //0x2c 8082c888
    void LoadModels() override; //0x44 8082c884

    Psea1sand* _1sand; //0xb0
    Psea2dark* _2dark; //0xb4
    Psea3nami* _3nami; //0xb8
    Psea4tex* _4tex; //0xbc
    Psea5spc* _5spc; //0xc0
    u16 unknown_0xc4[2];
    float unknown_0xc8[2];
    u8 unknown_0xd0[4];
}; //0xd4
} //namespace Objects
#endif