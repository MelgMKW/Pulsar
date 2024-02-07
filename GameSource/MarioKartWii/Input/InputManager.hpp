/*
Manager is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#ifndef _INPUTMANAGER_
#define _INPUTMANAGER_
#include <kamek.hpp>
#include <MarioKartWii/Input/Controller.hpp>
#include <MarioKartWii/Input/ControllerHolder.hpp>
#include <MarioKartWii/Input/Rumble.hpp>
#include <MarioKartWii/System/Ghost.hpp>

namespace Input {

class Manager {
public:
    static Manager* sInstance; //809bd70c
    static Manager* GetInstance(); //8052313c
    static void DestroyInstance(); //8052318c
    Manager(); //805232f0
    virtual ~Manager(); //805231dc vtable 808b2fc8

    void SetFSStickClamp(s8 min, s8 max); //80522358
    static void InitKPAD(); //80522690
    void SyncSimpleCallBack(s32  result, s32 num); //805230e0
    void Init(); //80523690 called everytime a game scene is created
    void UpdateControllers(u8 isPaused); //805237e8
    void Update(); //805238f0
    static int ConvertType(ControllerType type); //80523a58 if wiimote based, returns 0, gcn returns 1, other returns 3
    void ResetDummyController(); //80523eac
    void UpdateGCNInputs(u8 id, PAD::Status* status);
    void ResetRealController(u8 id); //80524264
    void InitControllerHolders(); //805242d8
    void InitGhostController(u8 id, const RKGInputs* rawInputs, bool isAuto); //8052453c
    void StartGhostReading(); //80524580
    void EndGhostWriting(u8 hudSlotId); //805245cc
    void InitRumble(); //805246c0
    bool SyncWiimotes(); //80524788 returns true if all wiimotes are connected

    RealControllerHolder realControllerHolders[4]; //0x4 Stores inputs from a real controller at the same console
    AIControllerHolder virtualControllerHolders[12]; //0x3b4 Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
    ControllerHolder controllerHolder; //0x15b4 dummy?


    u32 unknown_0x168c;
    DummyController dummyController; //0x1690
    WiiController wiiControllers[4]; //0x1720
    GCNController gcnControllers[4]; //0x3ba0
    GhostController ghostControllers[4]; //0x3e60
    RumbleManager rumbleManager;
    u8 unknown_0x4110[0x4154 - 0x4110];
    bool isPaused; //0x4154
    bool isMirror; //0x4155
    u8 padding[2];
    u32 wiimotesSyncStatus; //0x4158 2 = not all wiimotes are synced
}; //Total size 0x415c
size_assert(Manager, 0x415c);
}//namespace Input
#endif