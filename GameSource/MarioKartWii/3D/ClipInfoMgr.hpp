#ifndef _CLIP_INFO_MGR_
#define _CLIP_INFO_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>


//classes responsible with determining whether a subject (items, karts, objects etc...) should be rendered for a given screen (for exemple if the subject is far and behind, it's useless to render it)
//ClipInfo's bitfield is updated every frame according to the area render type (whether it should check for 8/9 disabling) and the subject's position
//Clip Info can then be bound to a ModelDirector (via one ctor), which possesses a function that checks the bitfield to toggle the model on/off 


//80787950 is where the AREA8 and 9 groupIds check occurs
enum AREARenderType {
    AREA_RENDERTYPE_CAN_DISABLE = 0, //will be disabled using AREA8/9
    AREA_RENDERTYPE_CAN_DISABLE_AND_RECALCULATE = 1,
    AREA_RENDERTYPE_NONE = 2
};


class ClipInfo { //as with entity, used by items, karts, objects...
    ClipInfo(); //80787bd8
    ~ClipInfo(); //80787be4
    void Init(Vec3* position, bool isDefaultyEnabled, u16 area8GroupIds, AREARenderType type, u32 r7, u32 r8,
        float near, float maxSpeed, float farDistance); //80787c24

    Vec3* position; //0
    float nearDistance; //0x4
    float farDistanceSquared; //0x8
    float unknown_0xC[4]; //0xC
    u16 area8GroupIds; //0x1C
    u8 areaRenderType; //0x1E
    u8 padding;
    u32 bitfield; //0x20 if every 8th bit is set, the subject will NOT  be rendered
    /*
    0x1         0
    0x2         1
    0x4         2
    0x8         3
    0x10        4
    0x20        5
    0x40        6
    0x80        7
    0x100       8
    0x200       9
    0x400       10
    0x800       11
    0x1000      12
    0x2000      13
    0x8000      15
    0x10000     16
    0x40000     18
    0x80000     19
    0x100000    20
    0x800000    23
    0x1000000   24
    0x2000000   26
    0x8000000   27
    0x10000000  28 disabled
    0x20000000  29
    0x40000000  30
    0x80000000  31

    */
}; //0x24

struct ClipScreenInfo { //essentially used to control whether a player (a screen) is in AREA type 9 and which objects in AREA8 with matching groupIDs should be clipped
    ClipScreenInfo(); //8078768c
    ~ClipScreenInfo(); //80787690


    float invViewMtxForwX;
    float invViewMtxForwY;
    float invViewMtxForwZ; //0x8

    float screenNear; //0xc
    Vec3 directionInCameraSpace; //0x10 x = -cos(fovy), y = 0, z = sin(fovy) * (screenWidth/screenHeight), transformed into the camera space via the viewMtx and normalized
    u8 unknown_0x1c[0xc];
    Vec3 directionInCameraSpace2; //0x28 x = cos(fovy), y = 0, z = sin(fovy) * (screenWidth/screenHeight), transformed into the camera space via the viewMtx and normalized 

    u8 unknown_0x34[0x5c - 0x34];
    float fovyDiv55Squared; //0x58

    u16 area9GroupIds; //0x5c
    u8 padding[2];
    u8 unknown[0x60];
};

class ClipInfoMgr {
    static ClipInfoMgr* sInstance; //809c2ef8
    static ClipInfoMgr* CreateInstance(); //8078746c
    static void DestroyInstance(); //80787538

    //"GetAreaReferencesByType", this function can be used with any area and will return a bitfield of setting1s of all areaType AREAs the position is inside of
    static int GetArea8And9GroupIDs(const Vec3& position, u32 areaType); //80786fc0
    static bool NormalizeVector(Vec3& dest, const Vec3& src); //807872c0 only if non-null vec
    static void UpdateScreenInfo(ClipScreenInfo& info, const GameScreen& screen); //8078707c
    static void CalcAreaType8Refs(ClipInfo& dest); //80787ba0 stores the refs in dest
    ClipInfoMgr(); //807875ec inlined
    ~ClipInfoMgr(); //807876d0
    void Update(); //80787774
    ClipInfo* Insert(Vec3* position, bool isDefaultyEnabled, AREARenderType type, u32 r7, u32 r8,
        float nearDistance, float maxSpeed, float farDistance); //80787ab8 maxSpeed unused

    EGG::TDisposer<ClipInfoMgr> disposer; //0x0 //80787340 vtable 808d17f8
    ClipInfo* clipInfoArray; //0x10 array size 512
    u32 maxClipInfoCount; //0x14
    u32 clipInfoCount; //0x18 increment by insert
    ClipScreenInfo* screenInfos; //0x1c array size4, one per screen

}; //0x20
size_assert(ClipInfoMgr, 0x20);




#endif