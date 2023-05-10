#include <kamek.hpp>


nw4r::ut::List BootHook::list ={ nullptr, nullptr, 0, offsetof(BootHook, link) };
//SectionLoadHook* SectionLoadHook::sHooks = nullptr;
DoFuncsHook* RaceLoadHook::raceLoadHooks = nullptr;
DoFuncsHook* RaceFrameHook::raceFrameHooks = nullptr;

DoFuncsHook::DoFuncsHook(Func& f, DoFuncsHook** prev) : func(f) {
    next = *prev;
    *prev = this;
}

void DoFuncsHook::exec(DoFuncsHook* first) {
    for(DoFuncsHook* p = first; p; p = p->next) {
        p->func();
    }
}


kmBranch(0x800074d4, BootHook::exec);
kmBranch(0x80554728, RaceLoadHook::exec);
kmBranch(0x8053369c, RaceFrameHook::exec); //RaceInfo::Update()

//kmBranch(0x8063507c, SectionLoadHook::exec);

