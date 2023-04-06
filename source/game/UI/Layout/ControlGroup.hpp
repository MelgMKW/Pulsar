#ifndef _CONTROLGROUP_
#define _CONTROLGROUP_
#include <kamek.hpp>

class UIControl;
class Page;

class ControlGroupAction {
    virtual void Calc(UIControl *control) = 0;
};

class ControlGroup {
public:
    ControlGroup(); //0x805C23E4
    ~ControlGroup(); //0x805c2400

    void Init(UIControl *parentControl, u32 controlCount); //0x805c2460
    void Init(Page *parentPage, u32 controlCount); //0x805c2620
    void SetControl(u8 index, UIControl *control, u32 isOpaque); //0x805c27dc
    void InitControls(); //0x805c2868
    void Update(); //0x805c28d8
    void Draw(u32 isOpaque); //805c2948
    void ResetControlsPosition(); //805c2a5c
    UIControl *GetControl(u8 index); //805c2ac0
    void DoAction(ControlGroupAction *action); //805c2ad0

    UIControl **controlArray; //pointer to the array of controls
    UIControl **controlArray2; //pointer to the array of controls, of length controlCount, idk what is the difference look the same in game
    UIControl *parentControl; //0x8
    Page *parentPage;
    u32 controlCount; //0x10
};//Total Size 0x14

size_assert(ControlGroup, 0x14);



#endif