#ifndef _CONTROLGROUP_
#define _CONTROLGROUP_
#include <kamek.hpp>

class UIControl;
class Page;

class ControlGroupAction {
    virtual void Calc(UIControl* control) = 0;
};

class ControlGroup {
public:
    ControlGroup(); //805C23E4
    ~ControlGroup(); //805c2400

    void Init(UIControl& parentControl, u32 controlCount); //805c2460
    void Init(Page& parentPage, u32 controlCount); //805c2620
    void SetControl(u8 index, UIControl& control, u32 zIdx); //805c27dc
    void InitControls(); //805c2868
    void Update(); //805c28d8
    void Draw(u32 zIdx); //805c2948
    void ResetControlsPosition(); //805c2a5c
    UIControl* GetControl(u32 index) const; //805c2ac0
    void DoAction(ControlGroupAction& action); //805c2ad0


    template<class T>
    inline T* GetControl(u32 index) const { return static_cast<T*>(GetControl(index)); }
    template <class T>
    inline T* GetParentPage() const { return static_cast<T*>(parentPage); }


    UIControl** controlArray; //pointer to the array of controls
    UIControl** zIdxOrderedArray; //pointer to the array of controls, of length controlCount, idk what is the difference look the same in game
    UIControl* parentControl; //0x8
    Page* parentPage;
    u32 controlCount; //0x10
};//Total Size 0x14

size_assert(ControlGroup, 0x14);



#endif