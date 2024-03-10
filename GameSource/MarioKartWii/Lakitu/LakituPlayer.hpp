#ifndef _LAKITUPLAYER_
#define _LAKITUPLAYER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/Lakitu/LakituActions.hpp>

/*
Contributors:
-Melg
*/

namespace Kart {
class Player;
}
class ModelDirector;
class ShadowModelDirector;
class ObjectActor;

namespace Lakitu {

//no idea what this sub does
struct ParamsSubSubSub {
    ParamsSubSubSub(); //8074bfa0
    float unknown[2];
    Ptmf_0A<ParamsSubSubSub, void> ptmf;
}; //0x14

struct ParamsSubSub {
    explicit ParamsSubSub(u32 subSubSubCount); //8074bf28
    virtual ~ParamsSubSub(); //0x8 8074bfd0 vtable 808cbc80
    void Reset(float initialValue); //8074c048
    void Set(u32 ptmfFuncIdx, float value, float value2); //8074c0b4

    ParamsSubSubSub* subsubsubArray; //0x4
    u32 lastUpdatedSubSubSub;

}; //0xC

struct ParamsSub {
    ParamsSubSub* sub1;
    ParamsSubSub* sub2;
    ParamsSubSub* sub3;
    float unknown_0xC[4];
    u8 unknown_0x1C;
    u8 padding[3];
};//0x20

class Movement {
    Movement(const Kart::Player& kartPlayer); //8071e9b4
    static void UpdateScale(ParamsSub* sub, Mtx& scaleMtx); //80720a20
    void Reset(); //8071eb6c
    void SetPosition(const Vec3& position, bool r5); //8071efa8
    void SetBasePosition(const Vec3& position); //8071efd8

    void Update(); //8071f404
    void UpdateExtMtx(Mtx& extMtx); //807202bc
    void UpdateRotation(Mtx& rotationMtx); //80720024
    Vec3 CalcOscillation(Mtx& extMtx); //807201b0 uses floats at 0xE8

    const Kart::Player& kartPlayer; //0x0
    Vec3 position;
    Vec3 translation; //0x10 3rd column of transfoMtx, translation relative to what? if norm > 2000, lakitu flies away
    Vec3 basePosition; //0x1c around which lakitu moves
    //1st is position + ext params like a thwomp squishing lakitu, 2nd is rotation, 3rd is scale; kept as an array because of game code
    Mtx34 matrix[3]; //0x28 
    Mtx34 transfoMtx; //0xb8 = product of all other matrixes

    float xOscillation; //0xe8 +0.04 every frame which moves lakitu in a sinusoidal movement
    float yOscillation; //0xec same but adds 0.08 and on the Y axis

    bool isOscillating; //0xf0 lakitu will not oscillate in a sinusoidal movement if false
    u8 padding[3];
    Vec3 kartPosition; //0xF4

    float unknown_0x100[0xF]; //0x100
    float unknown_0x13c; //0x13c
    float unknown_0x140[4]; //0x100
    u8 unknown_0x150;
    u8 unknown_0x151;
    u8 padding2[2];
    u32 unknown_0x154[2];
    float unknown_0x15c[2];

    ParamsSub* sub; //0x164
}; //0x168

class PlayerBase {
    PlayerBase(); //80720f44 inlined
    virtual ~PlayerBase(); //80720f8c vtable 808c9740
    virtual void Init(); //8072101c
    virtual void Update(); //80721024
    void ToggleModelsScreenVisibility(bool disable); //80721090
    //For example, r5 == 5 means reverse will be visible (and so will the rod that comes with it)
    //r6 == 8 will make the lamp model visible, this is mostly used for hair/lamp
    void SetModelsVisibility(bool areNotAllInvisible, u32 visibleModelIdx, u32 visibleModelIdx2); //80721128

    ModelDirector* lakituModel; //0x4
    ModelDirector* rodModel; //0x8
    ModelDirector* signalModel; //0xc
    ModelDirector* lapModel;  //0x10
    ModelDirector* finalLapModel; //0x14
    ModelDirector* reverseModel; //0x18
    ModelDirector* flagModel; //0x1c
    ModelDirector* hair; //0x20
    ModelDirector* lamp; //0x24
    ShadowModelDirector* shadow; //0x28 ends at 2c
    Mtx34 transformationMtx;
    u8 unknown_0x5C; //ctor'd at 1
    u8 screenId;
    u8 padding[2];
}; //0x60


class Player : public PlayerBase, public AI::Base {
    enum ActionState {
        STARTING,
        ACTIVATING,
        ACTIVE,
        ENDING
    };

    explicit Player(const Kart::Player& kartPlayer); //80721514

    //PlayerBase vtable 808c96a0
    ~Player() override; //80721d2c
    void Init() override; //80722100
    void Update() override; //807221c4

    //AIBase vtable 808c96b4 at 0x94
    //~Player() override; //thunk 807259e4 func 80721d2c
    virtual void OnStartIdle();       //0x18 80723458 from start: 0x2c
    virtual void UpdateIdle();        //0x1c 807234a4 from start: 0x30
    virtual void OnStartCountdown();  //0x20 80723598 from start: 0x34
    virtual void UpdateCountdown();   //0x24 807237ac from start: 0x38
    virtual void OnEndCountdown();    //0x28 80723c20 from start: 0x3c
    virtual void OnStartLap();        //0x2c 80723c7c from start: 0x40
    virtual void UpdateLap();         //0x30 80723ec0 from start: 0x44
    virtual void OnStartRespawn();    //0x34 807242f4 from start: 0x48
    virtual void UpdateRespawn();     //0x38 80724430 from start: 0x4c
    virtual void OnStartBackwards();  //0x3c 80724794 from start: 0x50
    virtual void UpdateBackwards();   //0x40 80724880 from start: 0x54
    virtual void OnEndBackwards();    //0x44 80724f70 from start: 0x58
    virtual void OnStartEnding();     //0x48 80725060 from start: 0x5c
    virtual void UpdateEnding();      //0x4c 80725170 from start: 0x60
    virtual void OnEndEnding();       //0x50 80725424 from start: 0x64
    virtual void OnStartUnknown();    //0x54 807254a0 from start: 0x68
    virtual void UpdateUnknown();     //0x58 807254c0 from start: 0x6c

    u8 GetPlayerIdx() const; //8072239c
    void StarteRespawnAction(); //807223a4
    void DStartCountdownAction(); //807223bc
    void LoadGraphics(); //80722504 loads jugemu.brres, rod.brres, links anims
    void CreateEnableActions(); //80721ec0
    u16 GetCountdownArmSwipeDuration; //8072240c

    //For example as countdown is happening, lakitu's base position is (0,250,320) offset from the player (with Z being forwards)
    //That is mapped to the world euclidean space
    Vec3 MapToWorldSpace(const Vec3& relativeLakituPosition); //807230d4 relative to the player

    //Because of multiple inheritance, these are "from start" offsets
    Action idle;        //0x98  vf 0x2c/0x30/none
    Action countdown;   //0xc4  vf 0x34/0x38/0x3c
    Action lap;         //0xf0  vf 0x40/0x44/none
    Action respawn;     //0x11c vf 0x48/0x4c/none
    Action backwards;   //0x148 vf 0x50/0x54/0x58
    Action ending;      //0x174 vf 0x5c/0x60/0x64
    Action unknown;     //0x1A0 vf 0x68/0x6c/none

    const Kart::Player& kartPlayer; //0x1CC
    u32 mode; //0x1d0 0 = TT, 1 = battle, 2 = others
    Vec3 position; //0x1d4
    bool hasNonPlayerScreen; //from raceCameraMge
    u8 unknown_0x1E1[3]; //seems to be padding
    ActionState curActionState; //0x1e4
    u32 frames; //0x1e8
    u32 curActionAnimationIdx; //0x1ec 2 seems to be the arm animation for most actions
    u32 curActionAnimationLength; //0x1f0 used by backwards to know where to transition from the head shaking animation

    //all of these actions are checked by 807234a4, which only runs when the current actionHandler is "idle"
    EnableCountdownAction* enableCountdownAction; //0x1f4 
    EnableDisplayLapAction* enableDisplayLapAction; //0x1f8
    EnableRespawnAction* enableThirdAction; //0x1fc
    EnableBackwardsAction* enableBackwardsAction; //0x200
    EnableEndingAction* enableEndingAction; //0x204

    Movement* movement;
    void* lightStruct;
    ParamsSubSub* subsub; //8074bf28 ctor
    ObjectActor* sound; //0x214
};//total size 0x218

}//namespace Lakitu
#endif