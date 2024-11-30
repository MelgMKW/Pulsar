#ifndef _PULSAR_OTT_
#define _PULSAR_OTT_
#include <kamek.hpp>

namespace Pulsar {
namespace OTT {

//Combo after vote
enum VoteState {
    COMBO_NONE,
    COMBO_SELECTION,
    COMBO_SELECTED,
    WAITING_FOR_START,
    HOST_START,
    SELECT_READY,
};

void AddGhostToVS();

}//namespace OTT
}//namespace Pulsar

#endif
