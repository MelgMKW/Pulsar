#ifndef _LAKITUMANAGER_
#define _LAKITUMANAGER_

#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/Lakitu/LakituPlayer.hpp>

namespace Lakitu {

class Manager {
public:
    static Manager* sInstance;
    static Manager CreateInstance(); //8071e270
    static void DestroyInstance(); //8071e2fc
    Manager(); //8071e330 inlined
    void Init(); //8071e638
    void CreatePlayers(); //8071e480
    void Update(); //8071e6c0

    EGG::TDisposer<Manager> disposer; //8071e1d8 vtable 808c94bc
    virtual ~Manager(); //8071e390 vtable 808c94b0 at 0x10
    Player* lakituPlayers[4]; //lakitu player, one per local player
    u32 localPlayerCount; //8071e610
}; //total size 0x28

}//namespace Lakitu
#endif