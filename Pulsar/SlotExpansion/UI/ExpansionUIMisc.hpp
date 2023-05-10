#ifndef _EXPANSIONUIMISC_
#define _EXPANSIONUIMISC_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace UI {
int GetTrackBMG(PulsarId pulsarId);
int GetTrackBMGByRowIdx(u32 cupTrackIdx);
int GetCurTrackBMG();
}//namespace UI
}//namespace Pulsar
#endif