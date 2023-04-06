#ifndef _GLOBESCENE_
#define _GLOBESCENE_
#include <game/Scene/BaseScene.hpp>

class GlobeScene : public GameScene {
public:
    GlobeScene(); //80553850
    ~GlobeScene() override; //80553894 vtable 808b41c0
    void OnCalc() override; //0x30 80553b10
    void OnExit() override; //0x34 80553ac8
    void OnEnter() override; //0x38 805538ec
    void OnEnterEnd() override; //0x3c 80553a88
    void CreateAndInitInstances() override; //0x44 805539b8
}; //0x254c


#endif