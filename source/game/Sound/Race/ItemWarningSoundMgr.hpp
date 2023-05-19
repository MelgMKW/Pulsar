#ifndef _ITEMWARNINGSOUNDMGR_
#define _ITEMWARNINGSOUNDMGR_
#include <kamek.hpp>
#include <game/Sound/Other/AudioValues.hpp>

class KartSound;

struct ItemWarningSound {
    ItemWarningSound(); //806f772c
    ~ItemWarningSound(); //806f7f70
    void PlayUntargetedWarning(float panValue, float volume); //806f7aa8 for megas, stars, bills etc.. pan value is moduled by the hudSlotId
    void PlayTargetedWarning(float panValue); //806f7828 for reds, blue shells etc..
    void PlayWarningOnWiimote(); //806f7ce0 inlined
    static float GetPan(u8 hudSlotId); //806f7698 essentially depends on which quadrant of the screen you are in
    void Init(u8 hudSlotId); //806f77d4 inlined

    u8 hudSlotId;
    u8 padding[3];
    KartSound* kartSound;
    AudioHandle handle;
}; //0xC

class ItemWarningSoundMgr {
public:
    static ItemWarningSoundMgr* sInstance; //809c2320
    static ItemWarningSoundMgr* GetStaticInstance(); //806f7ee8
    static void DestroyStaticInstance(); //806f7fcc
    ~ItemWarningSoundMgr(); //806f80ac
    void Init(); //806f8188
    void Shutdown(); //806f8204 sets playerCount to 0

    ItemWarningSound& GetItemWarningSound(u8 hudSlotId) const; //806f8210

    EGG::TDisposer< ItemWarningSoundMgr> disposer; //806f7d58 vtable 808c7860
    u8 localPlayerCount;
    u8 padding[3];
    ItemWarningSound itemWarningSounds[4]; //0x14
}; //0x44


#endif
