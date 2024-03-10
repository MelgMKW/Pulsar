#ifndef _MISCSOUND_
#define _MISCSOUND_

#include <kamek.hpp>
#include <core/nw4r/snd.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <MarioKartWii/Audio/SinglePlayer.hpp>

namespace Pulsar {
namespace Sound {

snd::SoundStartable::StartResult PlayExtBRSEQ(snd::SoundStartable& startable, Audio::Handle& handle, const char* fileName, const char* labelName, bool hold);

}//namespace Audio
}//namespace Pulsar

#endif