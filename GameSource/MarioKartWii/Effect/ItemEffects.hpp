#ifndef _ITEMEFFECT_
#define _ITEMEFFECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectCreator.hpp>
#include <core/egg/Effect/EffectManager.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <core/egg/mem/Heap.hpp>

//duplicated effects are for each side/wheels
//https://wiki.tockdom.com/wiki/BREFF_(File_Format)

namespace Effects {

class Items {
    Items(); //8068cedc
    void Init(); //8068d274

    void FadeKouraTailGEffect(u32 idx); //8068d3f0
    void FadeKouraTailREffect(u32 idx); //8068d41c
    void FadeKouraTailBEffect(u32 idx); //8068d448

    void KillKouraTailGEffect(u32 idx); //8068d474
    void KillKouraTailREffect(u32 idx); //8068d4a0
    void KillKouraTailBEffect(u32 idx); //8068d4cc

    //lifeframes = how long since it's started, playerIdx only needed if updateVelocity true as it uses the player's velocity
    void CreateKouraTailGEffect(u32 idx, const Vec3& translation, const Vec3& rotationAngle, u32 lifeFrames, bool enable,
        float scale); //8068d284
    void CreateKouraTailREffect(u32 idx, const Vec3& translation, const Vec3& rotationAngle, u32 lifeFrames, bool enable,
        float scale); //8068d2d8
    void CreateKouraTailBEffect(u32 idx, const Vec3& translation, const Vec3& rotationAngle, u32 lifeFrames, bool enable,
        const Mtx34& transMtx, bool updatePtclLifeAndVelocity, u32 playerIdx, float scale); //8068d32c

    void CreateKouraTailEffect(EGG::Effect* effect, const Vec3& translation, const Vec3& rotationAngle, u32 lifeFrames, bool useExtMtx,
        bool enable, const Mtx34& extMtx, bool updatePtclLifeAndVelocity, u32 playerIdx, float scale); //8068dd08 calcs Mtx using pos and angle except if useExtMtx is true

    void CreateHaneKouraEffect(const Vec3& position); //8068d748 Blue shell explosion

    void CreateBananaEffect(const Mtx34& transMtx, float scale); //8068d848

    void KillBombHeiSparkEffect(u32 idx); //8068d81c
    void CreateBombHeiSparkEffect(u32 idx, const Mtx34& transMtx); //8068d784
    void CreateBombHeiEffect(const Vec3& pos, u32 type, float scale); //8068d608 normal, Red, Blue and then checks 0x30 for S versions like rk_BombHeiS

    void CreateItemVanEffect(); //8068d5e8
    void CreateKouraBrkGEffect(); //8068d4f8
    void CreateKouraBrkREffect(); //8068d570 brk = break, red shell breaks

    void KillKaminariGumoPreEffect(u32 idx); //8068dad8
    void CreateKaminariGumoPreEffect(u32 idx, const Vec3& pos, const Vec3& scale); //8068d9e8
    void CreateKaminariGumoVanEffect(u32 idx); //8068daf4
    void UpdateKaminariGumoVanEffect(u32 idx, const Vec3& translation, u32 playerId); //8068db8c

    EGG::Effect** rk_kouraTailG; //length capacity 8068cfb8
    EGG::Effect** rk_kouraTailR; //length capacity
    EGG::Effect** rk_kouraTailB; //0x8 length capacity
    EGG::Effect** rk_bombHeiSpark; //length capacity 0xC
    EGG::Effect** rk_kaminariGumoPre; //length capacity 0x10
    EGG::Effect** rk_kaminariGumoVan; //length capacity 0x14
    EGG::Effect** rk_kaminariGumoVanS; //length capacity 0x18
    u32 greenShellCapacity; //0x1C
    u32 redShellCapacity;
    u32 blueShellCapacity; //+4 if online gamemode
    u32 bombCapacity; //0x28
    u32 tcCapacity; //0x2C
    bool moreThan2Screens; //0x30 screenCount >= 2, this implies the game uses rk_XS versions for example rk_BombHeiS
    bool moreThan3Screens; //0x31
    bool unknown_0x32;
    bool isDisabled; //0x33
    float float_0x34[2];
    u16 unknown_0x3C; //8068d210
    u8 unknown_0x3E[2]; //padding?
    virtual ~Items(); //8068d234 vtable 808c1ec0
}; //total size 0x44

}//namespace Effects





#endif