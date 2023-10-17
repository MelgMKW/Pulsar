#ifndef _CHARACTERAI_
#define _CHARACTERAI_
#include <kamek.hpp>
#include <game/AI/AIBase.hpp>
#include <game/Input/InputState.hpp>
#include <game/Kart/KartLink.hpp>


class KartAIController;
namespace AI {
class Inputs;

class Character;

//AI::Actions<Character> ~CharacterActions() override; //80736218 vtable 808caf58
//AI::Actions<Character> void OnStart() override; //0xc 80738cf8
//AI::Actions<Character> void Update() override; //0x10 80738d40
//AI::Actions<Character> void OnEnd() override; //0x14 80738d70

typedef Actions<Character> CharacterActions;

class Character : public Base { //for example, controls the character (miis) looking at the camera at the end of a race
public:
    Character(Inputs& inputs); //80735948
    ~Character() override; //80736258 vtable 808caec0
    virtual void Init();         //0x18 807362dc
    virtual void Update();         //0x1c 807363c0
    virtual void vf_0x20();         //0x20 80736400
    virtual void StartDriving();    //0x24 80736480
    virtual void OnStartAction0();  //0x28 80736d24
    virtual void UpdateAction0();   //0x2c 80736d30
    virtual void OnStartAction1();  //0x30 80736d8c
    virtual void UpdateAction1();   //0x34 80736d90
    virtual void OnStartAction2();  //0x38 80736ec4
    virtual void UpdateAction2();   //0x3c 80736ec8
    virtual void OnEndAction2();    //0x40 8073700c
    virtual void OnStartAction3();  //0x44 80737048
    virtual void UpdateAction3();   //0x48 80737054
    virtual void OnStartAction4();  //0x4c 807371a8
    virtual void UpdateAction4();   //0x50 807372e4
    virtual void OnEndAction4();    //0x54 807373a8
    virtual void OnStartAction5();  //0x58 807373e4
    virtual void UpdateAction5();   //0x5c 807373f8
    virtual void OnEndAction5();    //0x60 80737600
    virtual void OnStartAction6();  //0x64 8073763c
    virtual void UpdateAction6();   //0x68 80737798
    virtual void OnEndAction6();    //0x6c 80737888
    virtual void OnStartAction7();  //0x70 807378c4
    virtual void UpdateAction7();   //0x74 807378d4
    virtual void OnEndAction7();    //0x78 80737934
    virtual void OnStartLookAhead();  //0x7c 80737970
    virtual void UpdateLookAhead();   //0x80 807379ac just a blr obviously
    virtual void OnStartLookAtCamera();  //0x84 807379b0
    virtual void UpdateLookAtCamera();   //0x88 807379bc
    virtual bool vf_0x8c(const KartAIController& other);         //0x8c 807369bc
    virtual bool ArePlayersClose(const KartAIController& controller, float maxDistance);  //0x90 80736764
    virtual void vf_0x94();         //0x94 80736ca0


    CharacterActions actions0; //0x38
    CharacterActions actions1; //0x64
    CharacterActions actions2; //0x90
    CharacterActions actions3; //0xbc
    CharacterActions actions4; //0xe8
    CharacterActions actions5; //0x114 also missions
    CharacterActions actions6; //0x140
    CharacterActions action7; //0x16c
    CharacterActions lookAhead; //0x198
    CharacterActions lookAtCamera; //0x1c4
    Inputs& inputs;
    u8 unknown_0x1f0[0x204 - 0x1f4];
    u32 otherPlayerIdx; //0x204
    u8 unknown_0x208[0x21c - 0x208];
}; //0x21c

class CharacterBattle : public Character {
public:
    CharacterBattle(Inputs& inputs); //80738558
    ~CharacterBattle() override; //80738594 vtable 808cae28
    void Init() override; //0x18 807385ec
    void OnStartAction1() override; //0x30 80738624
    void UpdateAction1() override;  //0x34 80738628
};

class CharacterAwards : public Character {
public:
    CharacterAwards(Inputs& inputs); //80738664
    ~CharacterAwards() override; //807386A0 vtable 808cad90
    void Init() override; //0x18 807386f8
    void OnStartAction1() override;  //0x30 80738730
    void UpdateAction1() override;   //0x34 80738734
    void vf_0x94() override; //0x94 80738cf0
};
}

#endif