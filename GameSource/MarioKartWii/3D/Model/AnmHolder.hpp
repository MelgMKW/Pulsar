#ifndef _ANM_NOLDER_
#define _ANM_NOLDER_
#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/nw4r/snd/AnimSoundFile.hpp>
#include <core/nw4r/ut/List.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/


enum AnmType {
    ANMTYPE_EMPTY = -1,
    ANMTYPE_CHR = 0x0,
    ANMTYPE_CLR = 0x1,
    ANMTYPE_TEXSRT = 0x2,
    ANMTYPE_TEXPAT = 0x3,
    ANMTYPE_SHP = 0x4
};
using namespace nw4r;

class AnmHolder;

class AnmHolder {
public:
    AnmHolder(g3d::AnmObj* anmObjRes, snd::detail::AnimSoundFile* rawBRASD); //8055572c inlined
    virtual float GetFrameCount() const; //0x8 80557b28 vtable 808b44c8
    virtual float GetFrame() const; //0xc 80557954
    virtual void SetFrame(float frame); //0x10 80557fc8
    virtual void UpdateRateAndSetFrame(float frame); //0x14 80557fc4
    virtual float GetUpdateRate() const; //0x18 80557fb8
    virtual void SetUpdateRate(float rate); //0x1c 80557fb4
    virtual u32 IsLooped() const; //0x20 80557b20
    AnmType type; //-1 = empty anm holder
    u16 idx; //0x8 
    u8 padding[2];
    g3d::AnmObj* anmObjRes; //0xC AnmObjChrRes, AnmObjTexPatRes etc...
    ut::Link link; //0x10
    snd::detail::AnimSoundFile* rawBRASD; //0x18 nullptr for all but chr
}; //0x1c

class AnmChrHolder : public AnmHolder {
public:
    //ctor inlined
    float GetFrameCount() const override; //8055ae90 vtable 808b4430
    float GetFrame() const override; //8055adfc
    void SetFrame(float frame) override; //8055ae10
    void UpdateRateAndSetFrame(float frame) override; //8055ae24
    float GetUpdateRate() const override; //8055af78
    void SetUpdateRate(float rate) override; //8055af8c
    u32 IsLooped() const override; //8055af14
    g3d::AnmObjChrRes* anmObjRes2; //0x1C
};

class AnmShpHolder : public AnmHolder {
public:
    //ctor inlined
    float GetFrameCount() const override; //8055a800 vtable 808b42f0
    float GetFrame() const override; //8055a76c
    void SetFrame(float frame) override; //8055a780
    void UpdateRateAndSetFrame(float frame) override; //8055a794
    float GetUpdateRate() const override; //8055a8e8
    void SetUpdateRate(float rate) override; //8055a8fc
    u32 IsLooped() const override; //8055a884
    g3d::AnmObjShpRes* anmObjRes2; //0x1C
};

class AnmMatClrHolder : public AnmHolder {
public:
    //ctor inlined
    float GetFrameCount() const override; //8055acec vtable 808b43e0
    float GetFrame() const override; //8055ac58
    void SetFrame(float frame) override; //8055a66c
    void UpdateRateAndSetFrame(float frame) override; //8055ac80
    float GetUpdateRate() const override; //8055add4
    void SetUpdateRate(float rate) override; //8055ade8
    u32 IsLooped() const override; //8055ad70
    g3d::AnmObjMatClrRes* anmObjRes2; //0x1C
}; //0x20

class AnmTexPatHolder : public AnmHolder {
public:
    //ctor inlined
    float GetFrameCount() const override; //8055a9a4 vtable 808b4340
    float GetFrame() const override; //8055a910
    void SetFrame(float frame) override; //8055a924
    void UpdateRateAndSetFrame(float frame) override; //8055a938
    float GetUpdateRate() const override; //8055aa8c
    void SetUpdateRate(float rate) override; //8055aaa0
    u32 IsLooped() const override; //8055aa28
    g3d::AnmObjTexPatRes* anmObjRes2; //0x1C
};

class AnmTexSrtHolder : public AnmHolder {
public:
    //ctor inlined
    float GetFrameCount() const override; //8055ab48 vtable 808b4390
    float GetFrame() const override; //8055aab4
    void SetFrame(float frame) override; //8055aac8
    void UpdateRateAndSetFrame(float frame) override; //8055aadc
    float GetUpdateRate() const override; //8055ac30
    void SetUpdateRate(float rate) override; //8055ac44
    u32 IsLooped() const override; //8055abcc
    g3d::AnmObjTexSrtRes* anmObjRes2; //0x1C
};

class AnmBlendHolder {
public:
    virtual ~AnmBlendHolder(); //0x8 80556734 vtable 808b4480
    virtual void AttachNew(AnmHolder* newActive, AnmHolder* prev, bool changeUpdateRate) = 0; //0xc
    virtual void Attach(AnmHolder* obj, int idx) = 0; //0x10
    virtual bool ShouldDetachFromParent() = 0; //0x14
    virtual void DetachAll() = 0; //0x18
    virtual void DecrementWeight(float decrementBy) = 0; //0x1c
    virtual void SetWeight(int idx, float weight) = 0; //0x20
    virtual float GetWeight(int idx) const = 0; //0x24
    AnmType type;
    float weightDecrement; //0x8 how much weight decreases every frame, btw 0 and 1 (100%)
    g3d::AnmObj* anmBlend; //0xC AnmObjChrBlend, AnmObjTexPatOverride, etc..
    ut::Link link;
};

class AnmTexPatOverrideHolder : public AnmBlendHolder {
    ~AnmTexPatOverrideHolder() override; //80558794 vtable 808b4368
    void AttachNew(AnmHolder* first, AnmHolder* second, bool changeUpdateRate) override; //8055886c detaches old
    void Attach(AnmHolder* obj, int idx) override; //80558ab0
    bool ShouldDetachFromParent() override; //80558d00 potential better name, ResetAnm?
    void DetachAll() override; //80558ecc
    void DecrementWeight(float decrementBy) override; //80558bb0
    void SetWeight(int idx, float weight) override; //805587d4
    float GetWeight(int idx) const override; //8055881c
}; //0x18

class AnmChrBlendHolder : public AnmBlendHolder {
    ~AnmChrBlendHolder() override; //80559eec vtable 808b4458
    void AttachNew(AnmHolder* first, AnmHolder* second, bool changeUpdateRate) override; //8055a07c detaches old
    void Attach(AnmHolder* obj, int idx) override; //8055a2c0
    bool ShouldDetachFromParent() override; //8055a510 potential better name, ResetAnm?
    void DetachAll() override; //8055a6dc
    void DecrementWeight(float decrementBy) override; //8055a3c0
    void SetWeight(int idx, float weight) override; //80559f2c
    float GetWeight(int idx) const override; //80559fdc
}; //0x18

class AnmShpBlendHolder : public AnmBlendHolder {
    ~AnmShpBlendHolder() override; //80557fcc vtable 808b4318
    void AttachNew(AnmHolder* first, AnmHolder* second, bool changeUpdateRate) override; //805580a4 detaches old
    void Attach(AnmHolder* obj, int idx) override; //805582e8
    bool ShouldDetachFromParent() override; //80558538 potential better name, ResetAnm?
    void DetachAll() override; //80558704
    void DecrementWeight(float decrementBy) override; //805583e8
    void SetWeight(int idx, float weight) override; //8055800c
    float GetWeight(int idx) const override; //80558054
}; //0x18

class AnmTexSrtOverrideHolder : public AnmBlendHolder {
    ~AnmTexSrtOverrideHolder() override; //80558f5c vtable 808b43b8
    void AttachNew(AnmHolder* first, AnmHolder* second, bool changeUpdateRate) override; //80559034 detaches old
    void Attach(AnmHolder* obj, int idx) override; //80559278
    bool ShouldDetachFromParent() override; //805594c8 potential better name, ResetAnm?
    void DetachAll() override; //80559694
    void DecrementWeight(float decrementBy) override; //80559378
    void SetWeight(int idx, float weight) override; //80558f9c
    float GetWeight(int idx) const override; //80558fe4
}; //0x18

class AnmMatClrOverrideHolder : public AnmBlendHolder {
    ~AnmMatClrOverrideHolder() override; //80559724 vtable 808b4408
    void AttachNew(AnmHolder* first, AnmHolder* second, bool changeUpdateRate) override; //805597fc detaches old
    void Attach(AnmHolder* obj, int idx) override; //80559a40
    bool ShouldDetachFromParent() override; //80559c90 potential better name, ResetAnm?
    void DetachAll() override; //80559e5c
    void DecrementWeight(float decrementBy) override; //80559b40
    void SetWeight(int idx, float weight) override; //80559764
    float GetWeight(int idx) const override; //805597ac
}; //0x18
#endif