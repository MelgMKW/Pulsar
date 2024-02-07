#ifndef _EGG_EFFECTMANAGER_
#define _EGG_EFFECTMANAGER_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/nw4r/ef.hpp>

namespace EGG {

class EffectCreator;

class EffectManager {
public:
    struct EffectArg {
        EGG::Heap* heap;
        int maxEffects;
        int maxEmitters;
        int maxParticleManagers;
        int maxParticles;
    }; //0x14

    static EffectManager* sInstance; //80386E30
    static EffectManager* Create(u32, EGG::Heap* heap); //802246ec
    EffectManager(u32, EGG::Heap* heap); //80225224

    void CreateMemoryManager(EffectArg* args); //80224768
    void SetCreator(EffectCreator* creator, int idx); //8022501c
    void ResetCreator(int idx); //8022502c
    void ResetAllCreator(); //80225040
    void StopAllEffect(); //80225070
    void CalcEffect(int creatorIdx); //802250e0

    void GarbageCollection(); //802251a8 unofficial
    void Draw(const nw4r::ef::DrawInfo& drawInfo, int creatorIdx, int groupID); //802251dc
    void CreateEffect(const char* name, int creatorIdx); //80225208

    u32 maxGroupID; //0x0
    u32 maxEffectsCount; //0x4
    char unknown_0x8[0x20];
    EffectCreator** creators; //0x28
    void* memoryBlock; //used for ef::memoryManager

}; //total size 0x30
size_assert(EffectManager, 0x30);
}//namespace EGG
#endif