#ifndef _STATEPTMFTRIGGER_
#define _STATEPTMFTRIGGER_
#include <kamek.hpp>

#include <MarioKartWii/Race/RaceData.hpp>


//this has a state variable, which should not be changed, and a next state, which can;
//the next state is checked every frame, and if it not -1, the state is updated to next, and the corresponding ptmf is called
//Update func is always inlined, but the snippet of code from 806cee7c to 806cef20 or from 8054bb40 to 8054bbe4 is its body:

//the state are almost always (except for one camera class and earthmodel) related to the cycle of an object
template<class T>
class StatePtmfTrigger {
public:
    struct Entry {
        u16 id;
        u8 padding[2];
        Ptmf_0A<T, void> onStateBegin; //0x4
        Ptmf_0A<T, void> stateUpdate; //0x10
    }; //0x1c
    static Entry entryArray;
    virtual ~StatePtmfTrigger();
    /*
    void Update() {
        s32 next = this->nextState;
        StatePtmfTrigger<Racedata>::Entry* entry;
        if(next >= 0) {
            this->curState = next;
            this->nextState = -1;
            this->curStateframes = 0;
            u16 id = this->idsArray[this->curState];
            entry = &this->entries[id];
            Ptmf_0A<Racedata, void>& ptmf = entry->onStateBegin;
            if(ptmf_test(ptmf) == true) {
                (this->subject->*ptmf.ptr)();
            }
        }
        else {
            this->curStateframes++;
            u16 id = this->idsArray[this->curState];
            entry = &this->entries[id];
        }
        Ptmf_0A<Racedata, void>& ptmf = entry->stateUpdate;
        if(ptmf_test(ptmf) == true) {
            (this->subject->*ptmf.ptr)();
        }
    };*/ //inlined always

    u16 curState;
    u8 padding[2];
    s32 nextState; //0x8 
    //set to -1 initially, setting it to 1 resets the route, for example a HeyHoBallGBA gets rethrown
    //works similar to a state, where the specific object decides when to set the state
    u32 curStateframes; //resets when the object reaches the end of its route//its cycle
    u16 cyclePtmfsCount; //unsure
    u8 padding2[2];
    u16* idsArray; //0x14 to be accessed via curState
    Entry* entries; //0x18 808c5da0
    T* subject; //0x1c
}; //0x20
size_assert(StatePtmfTrigger<u32>, 0x20);


#endif

