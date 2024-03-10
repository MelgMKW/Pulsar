#ifndef _LAKITUMANAGER_
#define _LAKITUMANAGER_

#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/Lakitu/LakituPlayer.hpp>

namespace Lakitu {

class Manager {
public:
    static Manager* sInstance; //809c28b8
    static Manager CreateInstance(); //8071e270
    static void DestroyInstance(); //8071e2fc
    Manager(); //8071e330 inlined
    void Init(); //8071e638
    void CreatePlayers(); //8071e480
    void Update(); //8071e6c0
    void ToggleVisible(u8 playerId, bool isVisible); //8071e7ac has to be called every frame because camera does it on non-rear view
    void DoEnableRespawnAction(u8 playerId); //8071e734
    void StartCountdownAnm(); //8071e8a4
    int GetCountdownStartFrame(int armSwipeEndFrame) const; //8071e984, this is used to sync the anm with the actual countdown, especially the numbers; the 1st arm swipe ends when the 3 appears
    EGG::TDisposer<Manager> disposer; //8071e1d8 vtable 808c94bc
    virtual ~Manager(); //8071e390 vtable 808c94b0 at 0x10
    Player* lakituPlayers[4]; //0x14 lakitu player, one per local player
    u32 localPlayerCount; //8071e610
}; //total size 0x28

}//namespace Lakitu
#endif