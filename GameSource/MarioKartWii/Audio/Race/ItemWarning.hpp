#ifndef _ITEMWARNING_
#define _ITEMWARNING_
#include <kamek.hpp>
#include <MarioKartWii/Audio/Other/AudioValues.hpp>

namespace Audio {
class KartActor;

struct ItemWarning {
    ItemWarning(); //806f772c
    ~ItemWarning(); //806f7f70
    void PlayUntargetedWarning(float panValue, float volume); //806f7aa8 for megas, stars, bills etc.. pan value is moduled by the hudSlotId
    void PlayTargetedWarning(float panValue); //806f7828 for reds, blue shells etc..
    void PlayWarningOnWiimote(); //806f7ce0 inlined
    static float GetPan(u8 hudSlotId); //806f7698 essentially depends on which quadrant of the screen you are in
    void Init(u8 hudSlotId); //806f77d4 inlined

    u8 hudSlotId;
    u8 padding[3];
    KartActor* kartActor;
    Handle handle;
}; //0xC

class ItemWarningMgr {
public:
    static ItemWarningMgr* sInstance; //809c2320
    static ItemWarningMgr* CreateInstance(); //806f7ee8
    static void DestroyInstance(); //806f7fcc
    ~ItemWarningMgr(); //806f80ac
    void Init(); //806f8188
    void Shutdown(); //806f8204 sets playerCount to 0

    ItemWarning& GetItemWarning(u8 hudSlotId) const; //806f8210

    EGG::TDisposer< ItemWarningMgr> disposer; //806f7d58 vtable 808c7860
    u8 localPlayerCount;
    u8 padding[3];
    ItemWarning itemWarningSounds[4]; //0x14
}; //0x44
}//namespace Audio

#endif
