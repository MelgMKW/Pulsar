#ifndef _FILTEREFFECT_
#define _FILTEREFFECT_

#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/nw4r/ut.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

using namespace nw4r;

//color is the same for all screens, at 0x808B3D70
class FilterEffect : public StatePtmfTrigger<FilterEffect> {
public:
    FilterEffect(u32 idx); //8054ce90 inlined
    ~FilterEffect() override; //8054d7ac vtable 808b3e4c entries 808b3cc8
    void Update(); //8054d13c inlined
    void Draw(); //8054d388 inlined
    float intensity; //0x20
    u32 idx; //0x24
    float screenWidth; //0x28
    float screenHeight; //0x2c
    u8 unknown_0x30[8];
}; //0x38

class FilterEffectMgr { //https://imgur.com/SLNAest
public:
    FilterEffectMgr(u32 screenCount); //8054d488 inlined
    virtual ~FilterEffectMgr(); //8054d6f4 vtable 808b3e40
    static void SetColor(ut::Color color); //8054d114
    void Update(); //8054d814 inlined
    void Draw(); //8054d908 inlined
    FilterEffect** filters; //0x4 arr size screenCount
    u32 screenCount; //0x8
}; //0xC

//every entity is "in front" of the filter
class CourseFilterEffect : public StatePtmfTrigger<CourseFilterEffect> {
public:
    enum Filters {
        WHITE_ALPHA210PREPARE,
        WHITE_ALPHA210, //only active for 3 frames
        BLACK_ALPHA150, //active for 50 frames
        ALPHA_FADEOUT, //active until alpha becomes 0, -5 alpha per frame
        NONE,
    };
    CourseFilterEffect(u32 idx); //8054dc44 inlined
    ~CourseFilterEffect() override; //8054e480 vtable 808b3e28
    void Update(); //8054de88 inlined
    void Draw(); //8054e098 inlined
    void OnWhiteFilterPrepareStart(); //8054df6c
    void WhiteFilterPrepareUpdate(); //8054df90
    void OnWhiteFilterStart(); //8054dfe4
    void WhiteFilterUpdate(); //8054dfe8
    void OnBlackFilterStart(); //8054e000
    void BlackFilterUpdate(); //8054e020
    void OnAlphaFadeoutStart(); //8054e038
    void AlphaFadeoutUpdate(); //8054e03c
    void OnNoFilterStart(); //8054df5c
    ut::Color color; //0x20 alpha unused
    float alpha; //0x24 alpha of the color
    u32 idx; //0x28
    float screenWidth; //0x2c
    float screenHeight; //0x30
    u8 unknown_0x34[4];
}; //0x38

class CourseFilterEffectMgr {
public:
    CourseFilterEffectMgr(u32 screenCount); //8054e198 inlined
    virtual ~CourseFilterEffectMgr(); //8054e3c8 vtable 808b3e1c
    void Update(); //8054e4e8 inlined
    void Draw(); //8054e5dc inlined
    CourseFilterEffect** filters; //0x4 arr size screenCount
    u32 screenCount; //0x8
}; //0xC

#endif