#ifndef _REL_LINK_
#define _REL_LINK_

struct RelEndFuncLink { //list of static functions to be called by rel_end, a function that is effectively never called
    static RelEndFuncLink* cur; //809c4c88
    static void AddEntry(void (*func)(void*, int), void* funcArgs, RelEndFuncLink* memLocation); //8088f334
    static void ExecFuncs(); //8088f350
    RelEndFuncLink* prev;
    void (*func)(void*, int);
    void* funcArgs;
};

void RelProlog(); //8055531c calls all the static ctors
void RelEpilog(); //80555368 calls all the static dtors
void RelUnresolvedSection(); //805553b0

#endif