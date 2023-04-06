#ifndef _MENUSCENE_
#define _MENUSCENE_
#include <game/Scene/BaseScene.hpp>

class MenuScene : public GameScene {
public:
    MenuScene(); //80554fa4
    ~MenuScene() override; //80554fe8 vtable 808b4280
    void OnCalc() override; //0x30 805552c8
    void OnExit() override; //0x34 80555298
    void OnEnter() override; //0x38 80555040
    void OnEnterEnd() override; //0x3c 80555264
    void CreateAndInitInstances() override; //0x44 80555154
}; //0x254c


#endif