
#ifndef _EFFECT_MENU_
#define _EFFECT_MENU_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectCreator.hpp>
#include <core/egg/Effect/EffectManager.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <core/egg/mem/Heap.hpp>

//duplicated effects are for each side/wheels
//https://wiki.tockdom.com/wiki/BREFF_(File_Format)

namespace Effects {
class Menus {
    Menus(); //806ec7c8
    virtual ~Menus(); //806ec914 vtable 808c7668
    EGG::Effect* GetEffectByIdx(u32 idx); //806ec994
    EGG::EffectResource* menuEffects; //0x4
    EGG::Effect* rk_cursors[4]; //0x8 has RKMenu BREFF and BREFT, EGG::Effects for all the relevant rk_ emitters
    EGG::Effect* effects[10];
}; //total size 0x58
}//namespace Effects



#endif