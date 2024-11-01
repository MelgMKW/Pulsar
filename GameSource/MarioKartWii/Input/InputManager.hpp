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

//_sinit_ at 0x805230b0
class Manager {
public:
    static Manager* sInstance; //809bd70c
    static Manager* GetInstance(); //8052313c
    static void DestroyInstance(); //8052318c
    Manager(); //805232f0
    virtual ~Manager(); //805231dc vtable 808b2fc8

    void SetFSStickClamp(s8 min, s8 max); //80522358
    static void ResetKPAD(); //80522690
    void SyncSimpleCallBack(s32  result, s32 num); //805230e0
    void Init(); //80523520 just a blr
    void Prepare(); //80523690
    void UpdateControllers(u8 isPaused); //805237e8
    void Update(); //805238f0
    static int ConvertType(ControllerType type); //80523a58 if wiimote based, returns 0, gcn returns 1, other returns 3
    void ResetDummyController(); //80523eac
    bool TrySetController(u32 hudSlotId, void* r5 = nullptr); //80523ebc controller is set if A is pressed
    void UpdateGCNInputs(u8 id, PAD::Status* status);
    void ResetRealController(u8 id); //80524264
    void InitControllerHolders(); //805242d8
    void InitGhostController(u8 id, const RKGInputs* rawInputs, bool isAuto); //8052453c
    void StartGhostReading(); //80524580
    void EndGhostWriting(u8 hudSlotId); //805245cc
    void EndAllGhostWriting(); //805245dc
    void InitRumble(); //805246c0
    void ResetRumble(); //80524718
    bool SyncWiimotes(); //80524788 returns true if all wiimotes are connected
    void ResetSelfWiiAndGCNControllers(); //80523724
    static void RequestRumbleByDuration(u8 hudSlotId, u32 duration, bool replaceActiveIfNoFreeRumble, float f1); //0x805249b0
    void EnableAllPointers(bool* prevStatus); //80524840
    void ToggleAllPointers(const bool* statusOfEach); //805248d8
    int CopyPADStatus(u32 channel, PAD::Status* dest); //80524628 returns value based on error

    void DisableGhostReading(); //80524568
    void PrepareRealControllerHolderForRace(u8 hudSlotId); //80524558
    void ResetIdleFrameCounter(); //805235ac

    RealControllerHolder realControllerHolders[4]; //0x4 Stores inputs from a real controller at the same console
    AIControllerHolder virtualControllerHolders[12]; //0x3b4 Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
    ControllerHolder controllerHolder; //0x15b4 dummy?


    u32 unknown_0x168c;
    DummyController dummyController; //0x1690
    WiiController wiiControllers[4]; //0x1720
    GCNController gcnControllers[4]; //0x3ba0
    GhostController ghostControllers[4]; //0x3e60
    KRMMgr krmManager; //0x4100
    u8 unknown_0x4110[0x10];
    PAD::Status padStatuses[4]; //0x4120
    u8 unknown_0x4150[4];
    bool isPaused; //0x4154
    bool isMirror; //0x4155
    bool unknown_0x4156;
    u8 padding;
    u32 wiimotesSyncStatus; //0x4158 2 = not all wiimotes are synced
}; //Total size 0x415c
size_assert(Manager, 0x415c);
}//namespace Input
#endif