#ifndef _KARTMODELSMGR_
#define _KARTMODELSMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Camera.hpp>
#include <game/System/Timer.hpp>
#include <game/Visual/Model/KartModel.hpp>

class KartModelsMgr {
public:
    static KartModelsMgr *sInstance; //809c2f38
    static KartModelsMgr *GetStaticInstance(); //8079c9e8
    static void DestroyStaticInstance(); //8078ca38
    KartModelsMgr(); //8078ca5c
    ~KartModelsMgr(); //8078ce24
    void Update(); //8078d824
    void SetKartModel(u8 playerIdx, KartModel *model); //8078cf4c

    static void SetParams(); //807bd1d0
    static void InitiateKartModelBoneNames(); //807c71d8 stores a bunch of pointers to strings, too lazy to declare them
    static u8 playerCount; //809c38b8
    static bool isOnlineRace; //809c38b9
    static bool isVSRace; //809c38ba
    static bool isBattle; //809c38bb
    static bool isTT; //809c38bc
    static bool isTeams; //809c38bd
    static float unknown_float; //809c38d0 only on gcn cookie gba battle course 3snes battle course 4 block plaza, read by KartModel
    static bool isDKJP; //809c38d4
    EGG::TDisposer<KartModelsMgr> disposer; //8078c960 vtable 808d1850
    KartModel *models[12]; //8078cf4c stored by KartModel::Init
    //Position3D positions[12]; //0x40
    Vec3 *targetingItemPosition[12]; //related to items 8078da90
    u32 frameCounter[12]; //0x100 related to something about the model
    u32 invertedFrameCounter[12]; //0x130  decrements
    bool isAwardLoss; //0x160
    u8 racePositions[12]; //0x161

    u8 unknown_0x16D[0x170 - 0x16D]; //padding?

    u32 unknown_0x170; //8078cd14
    u8 unknown_0x174[4];
    u32 unknown_0x178[12]; //8078cde0

    bool hasTime[5]; //0x1A8
    u8 unknown_0x1AD[0x1B0 - 0x1AD]; //padding?
    Timer top5[5]; //0x1B0, personal top 5 on the track
    u8 maxPlayerCount; //init at 12, unsure
    u8 unknown_0x1ED[3]; //padding
    //0x10
}; //total size 0x1F0
#endif