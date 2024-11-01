#ifndef _DRIVERMGR_
#define _DRIVERMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/3D/Camera/Camera.hpp>
#include <MarioKartWii/System/Timer.hpp>
#include <MarioKartWii/Driver/DriverController.hpp>

enum FinishType { //used for the fanfare and the animation
    FINISH_TYPE_FIRST, //1st
    FINISH_TYPE_GOOD, //in a 12p room, 2nd to 5th
    FINISH_TYPE_BAD, //in a 12p room, 6th to 12th
    FINISH_TYPE_NOT_FINISHED = 4,
};
struct Timers {
    u32 raceFrames; //809c38c0 copied from raceinfo
    u32 raceFramesLastBit; //809c38c4
    u32 raceFramesLast2Bits; //809c38c8
    u32 raceFramesLast3Bits; //809c38cc
};

class DriverMgr {
public:
    static DriverMgr* sInstance; //809c2f38
    static DriverMgr* CreateInstance(); //8079c9e8
    static void DestroyInstance(); //8078ca38
    static Random* GetRaceinfoRandom(); //807bd718
    static bool IsPlayerComputer(u8 playerId); //807bd5bc
    static Timers* timers; //809c38c0
    static FinishType localFinishType; //808d1818
    DriverMgr(); //8078ca5c
    ~DriverMgr(); //8078ce24
    void InitAwards(); //8078d7e8
    void Update(); //8078d824
    void SetController(u8 playerIdx, DriverController* model); //8078cf4c
    static void ChangeFocusedPlayer(u8 playerIdx); //8078dde4
    static u8 GetFocusedPlayer(); //8078ddf4
    static FinishType CalcFinishType(u8 playerIdx); //8078cfa4
    static void SetParams(); //807bd1d0
    static void InitiateKartModelBoneNames(); //807c71d8 stores a bunch of pointers to strings, too lazy to declare them


    static bool IsHomeMenuON(); //8078ddb4

    ut::Color GetMiiFavoriteColor(RFL::FavoriteColor color) const; //8078cf38

    void SetControllerModelsFloats(DriverController& controller); //8078cf5c
    void SetLocalFinishType(FinishType type); //8078d4c0
    static u8 playerCount; //809c38b8
    static bool isOnlineRace; //809c38b9
    static bool isVSRace; //809c38ba
    static bool isBattle; //809c38bb
    static bool isTT; //809c38bc
    static bool isTeams; //809c38bd
    static float unknown_float; //809c38d0 only on gcn cookie gba battle course 3snes battle course 4 block plaza, read by KartModel
    static bool isDKJP; //809c38d4
    EGG::TDisposer<DriverMgr> disposer; //8078c960 vtable 808d1850
    DriverController* models[12]; //8078cf4c stored by KartModel::Init
    //Position3D positions[12]; //0x40
    Vec3* targetingItemPosition[12]; //related to items 8078da90
    u32 frameCounter[12]; //0x100 related to something about the model
    u32 invertedFrameCounter[12]; //0x130  decrements
    bool isAwards; //0x160
    u8 racePositions[12]; //0x161

    u8 unknown_0x16D[0x170 - 0x16D]; //padding?

    u32 unknown_0x170; //8078cd14
    u8 unknown_0x174[4];
    u32 unknown_0x178[12]; //8078cde0

    bool hasTime[5]; //0x1A8
    u8 unknown_0x1AD[0x1B0 - 0x1AD]; //padding?
    Timer top5[5]; //0x1B0, personal top 5 on the track
    u8 focusedPlayer; //init at 12, unsure
    u8 unknown_0x1ED[3]; //padding
    //0x10
}; //total size 0x1F0
#endif