#ifndef _HANACHAN_OBJECT_
#define _HANACHAN_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/Math/Vector.hpp>
#include <MarioKartWii/Route/Linked3DPoints.hpp>

namespace Objects {

//Specificities: bone must be named skl_root
class Hanachan;
class BossHanachanHead;
class HanachanPart;
class HanachanPart;

using namespace nw4r;

class UnkCycleParent { //extremely similar to CycleManager but vf_0xC does not return anything
public:
    virtual ~UnkCycleParent();
    virtual void vf_0xC(); //0xC 
    u16 unknown_0x4;
    u8 padding[2];
    u32 unknown_0x8;
    u32 frames; //resets when the object reaches the end of its route//its cycle
    u16 routePtmfsCount; //unsure
    u8 padding2[2];
    u16* idsArray; //0x14 ptmfs used
    CyclePtmfs* ptmfs; //0x18 808c5da0
    Object* parent; //0x1c
};

class HanachanPart : public ObjectCollidable {
public:

    ~HanachanPart() override; //806c7e68 vtable 808c4720
    void OnStart() override; //0xC 806c6b7c
    void Update() override; //0x14 806c6c10
    u32 GetPropertiesBitfield() override; //0x2c 806ccad0
    const char* GetSubFileName() const override; //0x38 806ccb88
    void LoadModels() override; //0x44 806c6b44
    void LoadRoute() override; //0x64 806ccacc
    void UpdateModelMatrix() override; //0x6c 806cca14
    bool vf_0x84() override; //0x84 0x84 806cca0c
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 806c6c94
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc4 806c6e40

    virtual void vf_0xec() = 0; //0xec 
    virtual void vf_0xf0() = 0; //0xf0 
    virtual void vf_0xf4(u32 r4) = 0; //0xf4 
    virtual void vf_0xf8() = 0; //0xf8 
    virtual void vf_0xfc() = 0; //0xfc 
    virtual void vf_0x100(u8 r4); //0x100 806c6c08
    virtual void vf_0x104(u8 r4); //0x104 806cca04
    virtual int vf_0x108() = 0; //0x108 

    u8 unknown_0xb0; //0xb0
    u32 unknown_0xb4;
    Vec3 unknown_0xB8;
    u8 unknown_0xc4[0xd4 - 0xc4];
    u32 unknown_0xd4;
    u8 unknown_0xd8[0xe4 - 0xd8];
}; //0xe4

class HanachanBody : public HanachanPart {
public:
    ~HanachanBody() override; //806ccad8 vtable 808c44e0
    void OnStart() override; //0xC 806c8878
    const char* GetSubFileName() const override; //0x38 806ccb80
    const char* GetShadowResName() const override; //0x40 806ccb74
    void LoadAnimations() override; //0x5c 806c87cc

    void vf_0xec() override; //0xec 806ccb4c
    void vf_0xf0() override; //0xf0 806ccb30
    void vf_0xf4(u32 r4) override; //0xf4 806ccb28
    void vf_0xf8() override; //0xf8 806ccb20
    void vf_0xfc() override; //0xfc 806ccb18
    int vf_0x108() override; //0x108 806ccb6c

    const char* mdlName; //0xe4
    u8 unknown_0xe8[0xfc - 0xe8];
}; //0xFC

class BossHanachanHead : public HanachanPart { //ObjectNum 0xf2 = 242 BossHanachanHead
public:
    class Handler {
    public:
        explicit Handler(BossHanachanHead* head); //inlined
        BossHanachanHead* head;
    };
    class CalcWorldCB : public ModelCalcBase, public EmptyModelCalcParent, public g3d::ICalcWorldCallback, public Handler {
    public:
        explicit CalcWorldCB(BossHanachanHead* head); //inlined
        //vtable 808c46f8 for empty, 808c4700 at 0x10
        ~CalcWorldCB() override; //thunk 806cce80 func 806cce38
        void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 806cce78 thunk 806c7cac
    }; //0x14
    explicit BossHanachanHead(const char* name); //806c7d74 inlined
    ~BossHanachanHead() override; //806ccb94 vtable 808c45ec
    void OnStart() override; //0xC 806c8204
    void Update() override; //0x14 806c82ac

    const char* GetBRRESName() const override; //0x34 806cce28
    void LoadAnimations() override; //0x5c 806ccda0
    void LoadCollision() override; //0x60 806c818c
    void UpdateShadow() override; //0x70 806ccd24
    void UpdateCollision() override; //0x74 806c8450

    void vf_0xec() override; //0xec 806ccca4
    void vf_0xf0() override; //0xf0 806ccc44
    void vf_0xf4(u32 r4) override; //0xf4 806ccbf8
    void vf_0xf8() override; //0xf8 806ccbf0
    void vf_0xfc() override; //0xfc 806ccbd4
    int vf_0x108() override; //0x108 806ccd98

    u8 unknown_0xe4[4];
    ModelDirector* hanachanAngry; //0xe4
    EGG::Effect* rk_hanaBlow; //0xE8
    EGG::Effect* rk_hanaPun; //0xEC
    CalcWorldCB* CalcWorldCB; //0xf0
    u8 unknown_0xf4[0x104 - 0xf4];

}; //0x104

class Hanachan : public ObjectCollidable, public UnkCycleParent { //ObjectNum 0xe2 = 226 Hanachan
public:
    explicit Hanachan(const KMP::Holder<GOBJ>& gobjHolder); //806c8a5c
    ~Hanachan() override; //806c9598 vtable 808c43b8
    void OnStart() override; //0xC 806c9630
    void Update() override; //0x14 806c9860
    void UpdateModel() override; //0x1c 806cc9ec
    u32 GetPropertiesBitfield() override; //0x2c 806cc9fc
    void LoadModels() override; //0x44 806cc9f8
    void LoadClipInfo() override; //0x58 806cc9f0
    void LoadCollision() override; //0x60 806cc9f4

    //UnkCycleParent vtable 808c44a4 at 0xB0 4 ptmfs
    //~Hanachan() override; thunk 806cce88
    void vf_0xC() override; //0xC 806ca24c

    u8 partCount; //0xd0 init at 7
    u8 padding[3];
    u32 bodyPartCount; //0xd4 init at 6

    BossHanachanHead* hanaHead; //0xd8
    HanachanBody* bodies; //0xdc
    HanachanPart* parts; //4xd0
    Linked3DPoints* partsGeometry;
    Linked3DPoints* partsGeometry2;
    float baseSpeed; //0xec setting 1
    float* distBtwParts; //0xf0 one per body part
    float* totalDistanceToHead; //0xf0, for each part
    u8 unknown_0xf8;
    Vec3* vecs; //0xfc d4 vectors
    float* float_0x100; //4xd4
    u8 unknown_0xd8[0x13c - 0x100];
}; //0x13c
size_assert(Hanachan, 0x13c);

} //namespace Objects
#endif