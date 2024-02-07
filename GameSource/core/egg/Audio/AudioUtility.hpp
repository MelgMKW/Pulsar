#ifndef _EGGAUDIOUTILITY_
#define _EGGAUDIOUTILITY_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/os/message.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/Audio/AudioMgr.hpp>

using namespace nw4r;
namespace EGG {
namespace AudioUtility {
namespace HBM {

typedef void(*Callback)(bool); //called by enter with bool = 0, by exit with bool = 1
extern SimpleAudioMgr<>* simpleAudioMgr; //80386DBC
extern Callback cb; //80386DC4
extern int fadeFrames; //80385F68

void init(SimpleAudioMgr<>* mgr, Callback cb, int fadeFrames); //80214350
void enter(); //80214360
void exit(bool r3); //80214490

}//namespace HBM
}//namespace AudioUtility
}//namespace EGG

#endif