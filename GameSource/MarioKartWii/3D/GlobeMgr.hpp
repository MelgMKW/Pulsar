#ifndef _GLOBE_MGR_
#define _GLOBE_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/Mii/MiiHeadsModel.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

class GlobeMii {
public:
    GlobeMii(); //80750aac
    virtual void Init(); //0x8 8075102c vtable 808cbe88
    virtual void Update(); //0xc 80751144
    virtual void SetMii(const Mii& mii); //0x10 80751208
    virtual void DisplayMii(u32 globeZoomState); //0x14 80751540
    virtual void Reset(); //0x18 807518bc
    virtual const Vec3& GetTranslation() const; //0x1c 8074f208
    void IsFemaleMii(const Mii& mii); //80751528

    ModelDirector* ma_mii_m; //0x4
    ModelDirector* ma_mii_f; //0x8
    MiiHeadsModel* headsModel; //0xC
    u32 isFemale; //0x10
    Mii mii; //0x14
    Mii mii2; //0xCC

    Random* random; //0x184
    u8 unknown_0x188[4];
    Vec3 translation; //0x18c
    EGG::Effect* rk_miiHamon; //0x198
    u8 unknown_0x19c; //related to head size
    u8 padding[3];
    u32 unknown_0x1a0;
    u32 animationLength; //0x1a4 initiated when animation starts, decreased by 1 every frame
};
size_assert(GlobeMii, 0x1a8);

class EarthModel : public StatePtmfTrigger<EarthModel> {
public:
    EarthModel(); //8074d700
    ~EarthModel() override; //8074dcc8 vtable 808cbdb0

    ModelDirector* earth; //0x20 earth.mdl0 of dummy_tex.brres below
    ModelDirector* ef_galaxy; //0x24 mdl0 of galaxy.brres
    ModelDirector* blackBoard; //0x28 of same name brres
    Mtx34 matrix_0x2c;
    float unknown_0x5c[3]; //0x5c
    u8 unknown_0x68[0xf4 - 0x68]; //mostly floats
    nw4r::g3d::ResFile earth_with_dummy_tex; //0xf4
    u8 unknown_0xf8;
    bool isMiiShown; //0xf9
    u8 unknown_0xfa[0x104 - 0xfa];
    GlobeMii* globeMii; //0x104
    u8 unknown_0x108[0x110 - 0x108];
};
size_assert(EarthModel, 0x110);


class GlobeMgr {
public:
    static GlobeMgr* sInstance; //809c2cb8
    static GlobeMgr* CreateInstance(); //8074d650
    static void DestroyInstance(); //8074d6cc
    GlobeMgr(); //8074fe3c
    void Init(u32 earthModelCount); //8074ff54
    void Update(); //80750344
    void SetPosition(u32 zoomState, float position); //80750808 also hides the mii temporarily
    void SetMii(const Mii& mii); //807509a0
    void DisplayMii(); //807509b4
    bool IsMiiShown(); //807507fc
    void ResetGlobeMii(); //807509d0
    EGG::TDisposer<GlobeMgr> disposer; //8074d5b8 vtable 808cbdd4
    virtual ~GlobeMgr(); //0x10 8074fe8c vtable 808cbdc8
    EarthModel* earthmodel; //0x14 array of 1 in this case
    nw4r::g3d::ResFile earthBrres; //0x18 in globe.arc
    nw4r::g3d::ResFile earthBrres2; //0x1c after checking it's 32 aligned?
    float unknown_0x20[2];
    u8 unknown_0x24[0x8];
    u8 unknown_0x30[2];
    bool hasEarthBrres; //0x32
    u8 padding; //0x33
    GlobeMii* globeMii; //0x34
    u8 unknown_0x38[4];
    u32 zoomState; //0x3c 2 = max zoom, unsure
};
size_assert(GlobeMgr, 0x40);

#endif