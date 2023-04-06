#include <kamek.hpp>

nw4r::ut::List BootHook::list = { 0,0,0,offsetof(BootHook, link) };
SectionLoadHook *SectionLoadHook::sHooks = NULL;
RaceLoadHook *RaceLoadHook::sHooks = NULL;
RaceFrameHook *RaceFrameHook::sHooks = NULL;

kmBranch(0x800074d4, BootHook::exec);
kmBranch(0x805320d0, RaceLoadHook::exec);
kmBranch(0x8053369c, RaceFrameHook::exec); //RaceInfo::Update()
kmBranch(0x8063507c, SectionLoadHook::exec);

