#include <kamek.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <core/rvl/pad.hpp>
#include <core/rvl/kpad.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>
#include <IO/File.hpp>
#include <PulsarSystem.hpp>

extern char gameID[4];
namespace Pulsar {
namespace Debug {

OS::Thread* crashThread = nullptr;
u16 crashError = 0;

using namespace nw4r;


void FatalError(const char* string) {
    GXColor fg;
    fg.rgba = 0xFFFFFFFF;
    GXColor bg ={ 0 };
    OS::Fatal(fg, bg, string);
}

void LaunchSoftware() { //If dolphin, restarts game, else launches Riivo->HBC->OHBC->WiiMenu
    s32 result = IO::Open("/dev/dolphin", IOS::MODE_NONE);
    if(result >= 0) {
        IOS::Close(result);
        SystemManager::RestartGame();
        return;
    }
    result = IO::Open("/title/00010001/52494956/content/title.tmd\0", IOS::MODE_NONE); //Riivo
    if(result >= 0) {
        ISFS::Close(result);
        OS::LaunchTitle(0x00010001, 0x52494956);
        return;
    }
    result = IO::Open("/title/00010001/4c554c5a/content/title.tmd\0", IOS::MODE_NONE); //OHBC
    if(result >= 0) {
        ISFS::Close(result);
        OS::LaunchTitle(0x00010001, 0x4c554c5a);
        return;
    }
    result = IO::Open("/title/00010001/48424330/content/title.tmd\0", IOS::MODE_NONE); // If HBC can't be found try OHBC
    if(result >= 0) {
        ISFS::Close(result);
        OS::LaunchTitle(0x00010001, 0x48424330);
        return;
    }
    OS::LaunchTitle(0x1, 0x2); // Launch Wii Menu if channel isn't found
}

//Credit Star and Riidefi

//Data Shown
//kmWrite16(0x802A7410, 0x00000023);
//Show Handler
//kmWrite32(0x802A7404, 0x00000000);
//Show StackTrace
kmWrite32(0x80023948, 0x281e0007);
//Max number of lines
//kmWrite32(0x80009324, 0x38800068);

//Lines on the screen and x-pos
void SetConsoleParams() {
    db::detail::ConsoleHead* console = EGG::Exception::console;
    console->viewLines = 0x16;
    console->viewPosX = 0x10;
}
BootHook ConsoleParams(SetConsoleParams, 1);


ExceptionFile::ExceptionFile(const OS::Context& context) : magic('PULD'), region(*reinterpret_cast<u32*>(gameID)), reserved(-1) {
    this->srr0.name = 'srr0';
    this->srr0.gpr = context.srr0;
    this->srr1.name = 'srr1';
    this->srr1.gpr = context.srr1;
    this->msr.name = 'msr:';
    this->msr.gpr = PPCMfmsr();
    this->cr.name = 'cr: ';
    this->cr.gpr = context.cr;
    this->lr.name = 'lr: ';
    this->lr.gpr = context.lr;
    for(u32 i = 0; i < 32; ++i) {
        this->gprs[i].gpr = context.gpr[i]; //r00: //r01:
        this->fprs[i].fpr = context.fpr[i];
        const u32 tens = i / 10U;
        const u32 units = i - tens * 10U;
        const u32 regValue = units * 0x100U + tens * 0x10000U;
        this->gprs[i].name = 'r00:' + regValue;
        this->fprs[i].name = 'f00:' + regValue;
    }
    this->fpscr.name = 'fscr';
    this->fpscr.fpr = context.fpscr;
    u32* sp = (u32*)context.gpr[1];
    for(int i = 0; i < 10; ++i) {
        if(sp == nullptr || (u32)sp == 0xFFFFFFFF) break;
        this->frames[i].sp = (u32)sp;
        this->frames[i].lr = sp[1];
        sp = (u32*)*sp;
    }
}

void DumpContextToFile(u16 error, const OS::Context* context, u32 dsisr, u32 dar) {
    crashError = error;
    crashThread = const_cast<OS::Thread*>(reinterpret_cast<const OS::Thread*>(context));
    db::ExceptionHead& exception = db::ExceptionHead::mInstance;
    exception.displayedInfo = 0x23;
    exception.callbackArgs = nullptr;
    const char* outcome = "";
    IO::File* file = IO::File::sInstance;
    if(file != nullptr) {
        IO::IOType type = file->type;
        outcome = " to restart the game";
        if(type != IO::IOType_DOLPHIN) outcome = " to go back to Riivolution";
    }
    //char endMsg[512];
    //snprintf(endMsg, 512, "Press A%s and send a clip\nof the crash or the crash.bin file to the pack\ncreator to help fix the bug.\n", outcome);

    db::Exception_Printf_("Press A%s and send a clip\nof the crash or the crash.bin file to the pack\ncreator to help fix the bug.\n",
        outcome);
    db::PrintContext_(error, context, dsisr, dar);



}
kmCall(0x80023484, DumpContextToFile);


void CreateCrashFile(s32 channel, KPAD::Status buff[], u32 count) {

    IO::File* file = IO::File::sInstance;
    bool exit = false;
    if(file == nullptr) exit = true; //should always exist if the crash is after strap 
    else {
        KPAD::Read(channel, buff, count);
        u16 wiimoteExtension = buff[0].extension;
        u32 buttonsPressed = buff[0].trig;
        if(wiimoteExtension < WPAD::WPAD_DEV_FUTURE && buff[0].error == WPAD::WPAD_ERR_NONE &&
            (wiimoteExtension == WPAD::WPAD_DEV_CLASSIC && buttonsPressed & WPAD::WPAD_CL_BUTTON_A
                || buttonsPressed & WPAD::WPAD_BUTTON_A)) exit = true;
        else {
            PAD::Status padStatus[4];
            PAD::Read(&padStatus[0]);
            for(int channel = 0; channel < 4; ++channel) {
                if(padStatus[channel].error == PAD::PAD_ERR_NONE) {
                    if(padStatus[channel].buttons & PAD::PAD_BUTTON_A) {
                        exit = true;
                        break;
                    }
                }
            }
        }
        if(exit) {
            OS::Thread* thread = crashThread;
            OS::DetachThread(thread);
            OS::CancelThread(thread);

            register u32* const addressPtr = (u32*)(thread->context.srr0 + 4);
            const s32 diff = static_cast<int>(reinterpret_cast<u32>(&LaunchSoftware) - reinterpret_cast<u32>(addressPtr));
            u32 instruction = 0x48000000;
            if(diff < 0) instruction = 0x4B000000;
            *addressPtr = instruction + (diff & 0x00FFFFFF);
            asm{
                ASM(
                dcbst 0, addressPtr; //update main memory from data cache so that it contains the correct instruction at addressPtr
                sync;                //memory barrier, ie wait for dcbst to complete
                icbi 0, addressPtr;  //invalidate instruction cache block at addressPtr so that the instruciton is fetched from the (updated) main memory
                isync;               //discard prefetched instructions in case the update addressPtr was prefetched
                )
            }

            alignas(0x20) ExceptionFile exception(thread->context);
            exception.error = static_cast<OS::Error>(crashError);
            char path[IOS::ipcMaxPath];
            const System* system = System::sInstance;
            snprintf(path, IOS::ipcMaxPath, "%s/Crash.bin", system->GetModFolder());
            file->CreateAndOpen(path, IOS::MODE_READ_WRITE);
            file->Overwrite(sizeof(ExceptionFile), &exception);
            file->Close();
        }
    }
    if(exit) LaunchSoftware();
}
kmCall(0x80226610, CreateCrashFile);

/*
void OnCrashEnd() {
    IO::File* file = IO::File::sInstance;
    if(file != nullptr) { //should always exist if the crash is after strap
        register u32* const addressPtr = (u32*)(crashThread->context.srr0 + 4);
        const s32 diff = static_cast<int>(reinterpret_cast<u32>(&LaunchSoftware) - reinterpret_cast<u32>(addressPtr));
        u32 instruction = 0x48000000;
        if(diff < 0) instruction = 0x4B000000;
        *addressPtr = instruction + (diff & 0x00FFFFFF) + 1;
        asm{
            ASM(
            dcbst 0, addressPtr;
            sync;
            icbi 0, addressPtr;
            )
        }
        OS::Thread::current = crashThread;
        OS::SelectThread(0);

    }
    else LaunchSoftware();
}
*/


}//namespace Debug
}//namespace Pulsar


