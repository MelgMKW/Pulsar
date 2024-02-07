#ifndef _NW4R_SNDTHREAD_
#define _NW4R_SNDTHREAD_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/AxManager.hpp>
#include <core/rvl/OS/thread.hpp>
#include <core/rvl/OS/Message.hpp>
#include <core/rvl/OS/Mutex.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class SoundThread {
public:
    class SoundFrameCallback {
    public:
        ut::LinkListNode link;
        virtual ~SoundFrameCallback();
        virtual void OnBeginSoundFrame();
        virtual void OnEndSoundFrame();
    };
    class PlayerCallback {
    public:
        ut::LinkListNode link;
        virtual ~PlayerCallback();
        virtual void OnUpdateFrameSoundThread();
        virtual void OnUpdateVoiceSoundThread(); //80096260
        virtual void OnShutdownSoundThread();
    };

    static SoundThread instance; //802dceb0
    static SoundThread& GetInstance(); //800a4530
    ~SoundThread(); //800a4600
    bool Create(s32 priority, void* stack, u32 stackSize); //800a4670
    void Shutdown(); //800a47b0
    static void AxCallbackFunc(); //800a48b0 
    static void* SoundThreadFunc(void* arg); //800a49c0 OsThread Run func
    void RegisterPlayerCallback(PlayerCallback* callback); //800a4a20
    void UnregisterPlayerCallback(PlayerCallback* callback); //800a4a90
    void FrameProcess(); //800a4af0

    OS::Thread thread;
    OS::ThreadQueue threadQueue; //0x318
    OS::MessageQueue msgQueue; //0x320
    OS::Message msgBuffer[4]; //0x340
    u32* stackEnd; //0x350
    OS::Mutex mutex; //0x354

    AxManager::CallbackListNode axCallbackNode; //0x36c

    ut::LinkList<SoundFrameCallback, offsetof(SoundFrameCallback, link)> soundFrameCallbackList; //0x378
    ut::LinkList<PlayerCallback, offsetof(PlayerCallback, link)> playerCallbackList; //0x384

    u32 processTick; //0x390

    bool createFlag; //0x394
    bool pauseFlag; //0x395
    u8 padding[2];
}; //total size 0x2C

}//namespace detail
}//namespace snd
}//namespace nw4r

#endif