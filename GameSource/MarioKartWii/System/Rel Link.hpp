#ifndef _REL_LINK_
#define _REL_LINK_

struct RelEndFuncLink { //list of static functions to be called by rel_end, a function that is effectively never called
    static RelEndFuncLink* cur; //809c4c88
    static void AddEntry(void (*func)(void*, int), void* funcArgs, RelEndFuncLink* memLocation); //8088f334
    static void ExecFuncs(); //8088f350²
    RelEndFuncLink* prev;
    void (*func)(void*, int);
    void* funcArgs;
};

void rel_start(); //8055531c calls all the static ctors
void rel_end(); //80555368 calls all the static dtors
void rel_main(); //80543b10

#endif