#ifndef _EXPANSIONUIMISC_
#define _EXPANSIONUIMISC_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace UI {
int GetTrackBMGId(PulsarId pulsarId);

inline void GetTrackBMG(wchar_t* dest, PulsarId id) {
    const wchar_t* name = UI::GetCustomMsg(GetTrackBMGId(id));
    const wchar_t* ptrSlash = wcschr(name, L'\\');

    int realLength;
    if(ptrSlash == nullptr) realLength = wcslen(name);
    else {
        const wchar_t* ptrSpace = wcschr(name, L'\\') - sizeof(L' ');
        realLength = (ptrSpace - name) / sizeof(wchar_t);
    }
    wcsncpy(dest, name, realLength);
}
int GetTrackBMGByRowIdx(u32 cupTrackIdx);
int GetCurTrackBMG();
}//namespace UI
}//namespace Pulsar
#endif