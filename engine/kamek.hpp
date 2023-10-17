/*
 * Kamek Standard Library
 * Wii game patching engine
 * (c) Treeki 2010-2018
 */

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
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/ut/List.hpp>
 //just for usability in other structs


/*
CW implements ptmfs with this pseudo-struct:
struct Ptmf{
    u32 passedArgDelta; (this + subject is the arg passed into the func)
    s32 offsetToVtable; (offset to the vtable of the subject, also serves to specify if the call is virtual (set to -1 if it isn't)
    u32 funcData; (if the member func is not virtual, this is its address; if the func is virtual, this is its offset in the vtable)
};*/

template <class Subject, typename Ret>
struct Ptmf_0A {
    template <class FromSubject, typename FromRet>
    void operator=(FromRet(FromSubject::* const& src)()) {
        this->ptr = static_cast<Ret(Subject::*)()>(src);
    }
    Ret(Subject::* ptr)();
};//total size 0xc

template <class Subject, typename Ret, typename A1>
struct Ptmf_1A {
    template <class FromSubject, typename FromRet, typename FromA1>
    void operator=(FromRet(FromSubject::* const& src)(FromA1)) {
        this->ptr = static_cast<Ret(Subject::*)(FromA1)>(src);
    }
    Ret(Subject::* ptr)(A1);
};//total size 0xc

template <class Subject, typename Ret, typename A1, typename A2>
struct Ptmf_2A {
    template <class FromSubject, typename FromRet, typename FromA1, typename FromA2>
    void operator=(FromRet(FromSubject::* const& src)(FromA1, FromA2)) {
        this->ptr = static_cast<Ret(Subject::*)(FromA1, FromA2)>(src);
    }
    Ret(Subject::* ptr)(A1, A2);
};//total size 0xc

template <class Subject, typename Ret, typename A1, typename A2, typename A3>
struct Ptmf_3A {
    template <class FromSubject, typename FromRet, typename FromA1, typename FromA2, typename FromA3>
    void operator=(FromRet(FromSubject::* const& src)(FromA1, FromA2, FromA3)) {
        this->ptr = static_cast<Ret(Subject::*)(FromA1, FromA2, FromA3)>(src);
    }
    Ret(Subject::* ptr)(A1, A2, A3);
};//total size 0xc

template <typename Ret>
struct PtmfHolderBase_0A {
    virtual Ret operator()() const = 0;
};

template <class Subject, typename Ret>
struct PtmfHolder_0A : PtmfHolderBase_0A<Ret> {
    virtual Ret operator()() const {
        return (subject->*ptmf.ptr)();
    }
    Subject* subject;
    Ptmf_0A<Subject, Ret> ptmf;
    template <class ToSubject, typename ToRet>
    operator PtmfHolder_0A<ToSubject, ToRet>& () {
        return reinterpret_cast<PtmfHolder_0A<ToSubject, ToRet>&>(*this);
    }

    template <class ToSubject, typename ToRet>
    operator const PtmfHolder_0A<ToSubject, ToRet>& () const {
        return reinterpret_cast<const PtmfHolder_0A<ToSubject, ToRet>&>(*this);
    }
};

template <typename Ret, typename A1>
struct PtmfHolderBase_1A {
    virtual Ret operator()(A1 a1) const = 0;
};

template <class Subject, typename Ret, typename A1>
struct PtmfHolder_1A : PtmfHolderBase_1A<Ret, A1> {
    virtual Ret operator()(A1 a1) const {
        return (subject->*ptmf.ptr)(a1);
    }
    Subject* subject;
    Ptmf_1A<Subject, Ret, A1> ptmf;
    template <class ToSubject, typename ToRet, typename ToA1>
    operator PtmfHolder_1A<ToSubject, ToRet, ToA1>& () {
        return reinterpret_cast<PtmfHolder_1A<ToSubject, ToRet, ToA1>&>(*this);
    }

    template <class ToSubject, typename ToRet, typename ToA1>
    operator const PtmfHolder_1A<ToSubject, ToRet, ToA1>& () const {
        return reinterpret_cast<const PtmfHolder_1A<ToSubject, ToRet, ToA1>&>(*this);
    }
};

template <typename Ret, typename A1, typename A2>
struct PtmfHolderBase_2A {
    virtual Ret operator()(A1 a1, A2 a2) const = 0;
};
template <class Subject, typename Ret, typename A1, typename A2>
struct PtmfHolder_2A : PtmfHolderBase_2A<Ret, A1, A2> {
    virtual Ret operator()(A1 a1, A2 a2) const {
        return (subject->*ptmf.ptr)(a1, a2);
    }
    Subject* subject;
    Ptmf_2A<Subject, Ret, A1, A2> ptmf;

    template <class ToSubject, typename ToRet, typename ToA1, typename ToA2>
    operator PtmfHolder_2A<ToSubject, ToRet, ToA1, ToA2>& () {
        //static_cast<const ToSubject *>((const Subject *)nullptr);
        return reinterpret_cast<PtmfHolder_2A<ToSubject, ToRet, ToA1, ToA2>&> (*this);
    }

    template <class ToSubject, typename ToRet, typename ToA1, typename ToA2>
    operator const PtmfHolder_2A<ToSubject, ToRet, ToA1, ToA2>& () const {
        //static_cast<const ToSubject *>((const Subject *)nullptr);
        return reinterpret_cast<const PtmfHolder_2A<ToSubject, ToRet, ToA1, ToA2>&> (*this);
    }

};

template <typename Ret, typename A1, typename A2, typename A3>
struct PtmfHolderBase_3A {
    virtual Ret operator()(A1 a1, A2 a2, A3 a3) const = 0;
};
template <class Subject, typename Ret, typename A1, typename A2, typename A3>
struct PtmfHolder_3A : PtmfHolderBase_3A<Ret, A1, A2, A3> {
    virtual Ret operator()(A1 a1, A2 a2, A3 a3) const {
        return (subject->*ptmf.ptr)(a1, a2, a3);
    }
    Subject* subject;
    Ptmf_3A<Subject, Ret, A1, A2, A3> ptmf;
    template <class ToSubject, typename ToRet, typename ToA1, typename ToA2, typename ToA3>
    operator PtmfHolder_3A<ToSubject, ToRet, ToA1, ToA2, ToA3>& () {
        return reinterpret_cast<PtmfHolder_3A<ToSubject, ToRet, ToA1, ToA2, ToA3>&> (*this);
    }
    template <class ToSubject, typename ToRet, typename ToA1, typename ToA2, typename ToA3>
    operator const PtmfHolder_3A<ToSubject, ToRet, ToA1, ToA2, ToA3>& () const {
        return reinterpret_cast<const PtmfHolder_3A<ToSubject, ToRet, ToA1, ToA2, ToA3>&> (*this);
    }
};

class DoFuncsHook {
protected:
    typedef void (Func)();
    Func& func;
    DoFuncsHook* next;
    DoFuncsHook(Func& f, DoFuncsHook** prev);

    static void exec(DoFuncsHook* first);
};

class RaceLoadHook : public DoFuncsHook {
    static DoFuncsHook* raceLoadHooks;
public:
    RaceLoadHook(Func& f) : DoFuncsHook(f, &raceLoadHooks) {}
    static void exec() { DoFuncsHook::exec(raceLoadHooks); }
};

class RaceFrameHook : public DoFuncsHook {
    static DoFuncsHook* raceFrameHooks;
public:
    RaceFrameHook(Func& f) : DoFuncsHook(f, &raceFrameHooks) {}
    static void exec() { DoFuncsHook::exec(raceFrameHooks); }
};

/*
class SectionLoadHook {
private:
    typedef void (Func)();
    Func* mFunc;
    SectionLoadHook* mNext;

    static SectionLoadHook* sHooks;

public:
    SectionLoadHook(Func* f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for(SectionLoadHook* p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};
*/


class BootHook {
public:
    typedef void (Func)();
    Func* mFunc;
    nw4r::ut::Link link;
    static nw4r::ut::List list;

public:
    BootHook(Func* f, u16 position) {
        this->mFunc = f;
        Func* obj = (Func*)nw4r::ut::List_GetNth(&list, position);
        if(obj == nullptr || position > list.count) nw4r::ut::List_Append(&list, this);
        else {
            nw4r::ut::List_Insert(&list, obj, this);
        }
    }

    static void exec() {
        BootHook* next = nullptr;
        BootHook* cur = (BootHook*)nw4r::ut::List_GetNth(&list, 0);
        for(cur; cur != nullptr; cur = next) {
            cur->mFunc();
            next = (BootHook*)nw4r::ut::List_GetNext(&list, cur);
        }
    }
};


#endif