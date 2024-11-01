#include <kamek.hpp>


//SectionLoadHook* SectionLoadHook::sHooks = nullptr;
DoFuncsHook* RaceLoadHook::raceLoadHooks = nullptr;
DoFuncsHook* RaceFrameHook::raceFrameHooks = nullptr;

DoFuncsHook::DoFuncsHook(Func& f, DoFuncsHook** prev) : func(f) {
    next = *prev;
    *prev = this;
}

void DoFuncsHook::Exec(DoFuncsHook* first) {
    for(DoFuncsHook* p = first; p; p = p->next) {
        p->func();
    }
}

nw4r::ut::List BootHook::list ={ nullptr, nullptr, 0, offsetof(BootHook, link) };

//kmBranch(0x80001500, BootHook2::Exec);
kmCall(0x80543bb4, BootHook::Exec); //800074d4
kmBranch(0x80554728, RaceLoadHook::Exec);
kmBranch(0x8053369c, RaceFrameHook::Exec); //Raceinfo::Update()

//kmBranch(0x8063507c, SectionLoadHook::exec);

