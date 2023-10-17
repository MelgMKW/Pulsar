#ifndef _ELINEMANAGER_
#define _ELINEMANAGER_
#include <kamek.hpp>
#include <game/KMP/KMPManager.hpp>

/* Temporal chaining of elines:Every "frames until next controller", the game switches to the next controller, meaning it is the one used;
That means the "enter/do not enter" flag can be switched at will that way */

class ElineController {
public:
    KMP::Holder<GOBJ>* gobjHolder;
    ElineController* next;
    u16 frameCounter; //0x8
    u8 ENPHsection; //0xa
    u8 unknown_0xb;
    u16 framesUntilNextController; //0xc settings * framerate
    u8 padding[2];
}; //0x10

class ElineManager {
public:
    ElineManager(); //8052d46c
    void Update(); //8052d888
    ElineController** initialControllers; //0x0 those whose ENPH section (setting 8) is not -1
    u16 eline_controlCount; //0x4 count of the object in the KMP
}; // Total size 0x8
#endif