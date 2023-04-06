/*
 * Kamek Standard Library
 * Wii game patching engine
 * (c) Treeki 2010-2018
 */

#pragma gcc_extensions on
#ifndef __KAMEK_H
#define __KAMEK_H
#include <types.hpp>





#include <include/c_stdlib.h>
#include <include/c_math.h>
#include <include/c_stdio.h>
#include <include/c_wchar.h>
#include <include/c_string.h>
#include "hooks.hpp"

#include <game/Math/Matrix.hpp>
#include <game/Math/Vector.hpp>
#include <core/rvl/os/OS.hpp>
#include <core/nw4r/ut/List.hpp>
 //just for usability in other structs, so that you don't have to type EGG::type every time

template <class Subject, typename Ret>
struct Ptmf_0A {
    int this_delta;
    int vtableOffset;
    Ret(Subject:: *functionPointer)();
};//total size 0xc

template <class Subject, typename Ret, typename A1>
struct Ptmf_1A {
    int this_delta;
    int vtableOffset;
    Ret(Subject:: *functionPointer)(A1);
};//total size 0xc

template <class Subject, typename Ret, typename A1, typename A2>
struct Ptmf_2A {
    int this_delta;
    int vtableOffset;
    Ret(Subject:: *functionPointer)(A1, A2);
};//total size 0xc

template <class Subject, typename Ret, typename A1, typename A2, typename A3>
struct Ptmf_3A {
    int this_delta;
    int vtableOffset;
    Ret(Subject:: *functionPointer)(A1, A2, A3);
};//total size 0xc

template <typename Ret>
struct PtmfHolderBase_0A {
    virtual Ret operator()() = 0;
};

template <class Subject, typename Ret>
struct PtmfHolder_0A : PtmfHolderBase_0A<Ret> {
    Subject *subject;
    Ret(Subject:: *ptmf)();
    virtual Ret operator()() {
        return (subject->*ptmf)();
    }
};

template <typename Ret, typename A1>
struct PtmfHolderBase_1A {
    virtual Ret operator()(A1 a1) = 0;
};

template <class Subject, typename Ret, typename A1>
struct PtmfHolder_1A : PtmfHolderBase_1A<Ret, A1> {
    Subject *subject;
    Ret(Subject:: *ptmf)(A1);
    virtual Ret operator()(A1 a1) {
        return (subject->*ptmf)(a1);
    }
};

template <typename Ret, typename A1, typename A2>
struct PtmfHolderBase_2A {
    virtual Ret operator()(A1 a1, A2 a2) = 0;
};
template <class Subject, typename Ret, typename A1, typename A2>
struct PtmfHolder_2A : PtmfHolderBase_2A<Ret, A1, A2> {
    Subject *subject;
    Ret(Subject:: *ptmf)(A1, A2);
    virtual Ret operator()(A1 a1, A2 a2) {
        return (subject->*ptmf)(a1, a2);
    }
};

template <typename Ret, typename A1, typename A2, typename A3>
struct PtmfHolderBase_3A {
    virtual Ret operator()(A1 a1, A2 a2, A3 a3) = 0;
};
template <class Subject, typename Ret, typename A1, typename A2, typename A3>
struct PtmfHolder_3A : PtmfHolderBase_3A<Ret, A1, A2, A3> {
    Subject *subject;
    Ret(Subject:: *ptmf)(A1, A2, A3);
    virtual Ret operator()(A1 a1, A2 a2, A3 a3) {
        return (subject->*ptmf)(a1, a2, a3);
    }
};


#ifdef __INTELLISENSE__
#define NANDSZSLOADER 1
#define GHOSTLOADER 1
#define BOOTMENUS 1
#define MULTIGHOST 1
#define WIIMMFI 1
#define ENHANCEDREPLAY 1
#define BUFFBADKARTS 1
#define UMT 1
#define PANEL 1
#define INFODISPLAY 1
#define LECODE 1
#define LAPSPEED 1
#define CCMODIF 1
#define FILELOADING 1
#define DEBUG 1
#else
#endif

class SectionLoadHook {
private:
    typedef void (Func)();
    Func *mFunc;
    SectionLoadHook *mNext;

    static SectionLoadHook *sHooks;

public:
    SectionLoadHook(Func *f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (SectionLoadHook *p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};

class RaceLoadHook {
private:
    typedef void (Func)();
    Func *mFunc;
    RaceLoadHook *mNext;

    static RaceLoadHook *sHooks;

public:
    RaceLoadHook(Func *f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (RaceLoadHook *p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};

class RaceFrameHook {
private:
    typedef void (Func)();
    Func *mFunc;
    RaceFrameHook *mNext;

    static RaceFrameHook *sHooks;

public:
    RaceFrameHook(Func *f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (RaceFrameHook *p = sHooks; p; p = p->mNext) p->mFunc();
    }
};

class BootHook {
public:
    typedef void (Func)();
    Func *mFunc;
    nw4r::ut::Link link;
    static nw4r::ut::List list;

public:
    BootHook(Func *f, u16 position) {
        this->mFunc = f;
        Func *obj = (Func *)nw4r::ut::List_GetNth(&list, position);
        if (obj == NULL || position > list.count) nw4r::ut::List_Append(&list, this);
        else {
            nw4r::ut::List_Insert(&list, obj, this);
        }
    }

    static void exec() {
        BootHook *next = NULL;
        BootHook *cur = (BootHook *)nw4r::ut::List_GetNth(&list, 0);
        for (cur; cur != NULL; cur = next) {
            cur->mFunc();
            next = (BootHook *)nw4r::ut::List_GetNext(&list, cur);
        }
    }
};
#endif