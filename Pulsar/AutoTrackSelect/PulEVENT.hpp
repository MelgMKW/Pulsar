#include <game/Race/RaceData.hpp>
#include <game/RKNet/EVENT.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace Network {

struct PulEVENT {
    PulsarId nextTrack;
};

}//namespace Network
}//namespace Pulsar