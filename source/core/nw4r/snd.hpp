#ifndef _NW4R_SND_
#define _NW4R_SND_
#include <types.hpp>
#include <core/nw4r/snd/AnimSound.hpp>
#include <core/nw4r/snd/AnimSoundFile.hpp>
#include <core/nw4r/snd/BasicPlayer.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/DisposeCallbackManager.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>
#include <core/nw4r/snd/FrameHeap.hpp>
#include <core/nw4r/snd/FxParam.hpp>
#include <core/nw4r/snd/FxReverbHiDpl2.hpp>
#include <core/nw4r/snd/InstancePool.hpp>
#include <core/nw4r/snd/MmlSeqTrackAllocator.hpp>
#include <core/nw4r/snd/PlayerHeap.hpp>
#include <core/nw4r/snd/SeqPlayer.hpp>
#include <core/nw4r/snd/SeqSound.hpp>
#include <core/nw4r/snd/SeqSoundHandle.hpp>
#include <core/nw4r/snd/Sound3DActor.hpp>
#include <core/nw4r/snd/Sound3DEngine.hpp>
#include <core/nw4r/snd/Sound3DListener.hpp>
#include <core/nw4r/snd/Sound3DManager.hpp>
#include <core/nw4r/snd/SoundActor.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>
#include <core/nw4r/snd/SoundArchiveFile.hpp>
#include <core/nw4r/snd/SoundArchivePlayer.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/SoundHeap.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/SoundPlayer.hpp>
#include <core/nw4r/snd/SoundStartable.hpp>
#include <core/nw4r/snd/SoundSystem.hpp>
#include <core/nw4r/snd/StrmChannel.hpp>
#include <core/nw4r/snd/StrmFile.hpp>
#include <core/nw4r/snd/StrmPlayer.hpp>
#include <core/nw4r/snd/StrmSound.hpp>
#include <core/nw4r/snd/StrmSoundHandle.hpp>
#include <core/nw4r/snd/Util.hpp>

enum SoundType {
    SOUND_TYPE_INVALID,
    SOUND_TYPE_SEQ,
    SOUND_TYPE_STRM,
    SOUND_TYPE_WAVE
};

#endif