#include <kamek.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <core/rvl/pad.hpp>
#include <core/rvl/kpad.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>
#include <PulsarSystem.hpp>

extern char gameID[4];
namespace Pulsar {
namespace Debug {

OS::Thread* crashThread = nullptr;
static u16 crashError = 0;

using namespace nw4r;


void FatalError(const char* string) {
    GX::Color fg;
    fg.rgba = 0xFFFFFFFF;
    GX::Color bg ={ 0 };
    OS::Fatal(fg, bg, string);
}

#pragma suppress_warnings on
void LaunchSoftware() { //If dolphin, restarts game, else launches Riivo->HBC->OHBC->WiiMenu
    s32 result = IO::OpenFix("/dev/dolphin", IOS::MODE_NONE);
    if(result >= 0) {
        IOS::Close(result);
        SystemManager::Shutdown();
        return;
    }
    result = IO::OpenFix("/title/00010001/52494956/content/title.tmd\0", IOS::MODE_NONE); //Riivo
    if(result >= 0) {
        ISFS::Close(result);
        OS::LaunchTitle(0x00010001, 0x52494956);
        return;
    }
    result = IO::OpenFix("/title/00010001/4c554c5a/content/title.tmd\0", IOS::MODE_NONE); //OHBC
    if(result >= 0) {
        ISFS::Close(result);
        OS::LaunchTitle(0x00010001, 0x4c554c5a);
        return;
    }
    result = IO::OpenFix("/title/00010001/48424330/content/title.tmd\0", IOS::MODE_NONE); // If HBC can't be found try OHBC
    if(result >= 0) {
        ISFS::Close(result);
        OS::LaunchTitle(0x00010001, 0x48424330);
        return;
    }
    OS::LaunchTitle(0x1, 0x2); // Launch Wii Menu if channel isn't found
}
#pragma suppress_warnings reset

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
static void SetConsoleParams() {
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

static void WriteHeaderCrash(u16 error, const OS::Context* context, u32 dsisr, u32 dar) {
    crashError = error;
    crashThread = const_cast<OS::Thread*>(reinterpret_cast<const OS::Thread*>(context));
    db::ExceptionHead& exception = db::ExceptionHead::mInstance;
    exception.displayedInfo = 0x23;
    exception.callbackArgs = nullptr;

    //char endMsg[512];
    //snprintf(endMsg, 512, "Press A%s and send a clip\nof the crash or the crash.pul file to the pack\ncreator to help fix the bug.\n", outcome);

    db::Exception_Printf_("Press A to exit. Send crash.pul to the creator.");
    db::PrintContext_(error, context, dsisr, dar);

}
kmCall(0x80023484, WriteHeaderCrash);


static void CreateCrashFile(s32 channel, KPAD::Status buff[], u32 count) {

    IO* io = IO::sInstance;;
    bool exit = false;
    if(io == nullptr) exit = true; //should always exist if the crash is after strap 
    else {
        KPAD::Read(channel, buff, count);
        u8 wiimoteExtension = buff[0].extension;
        if(buff[0].error == WPAD::WPAD_ERR_NONE && wiimoteExtension < WPAD::WPAD_DEV_FUTURE &&
            (wiimoteExtension == WPAD::WPAD_DEV_CLASSIC && buff[0].extStatus.cl.trig & WPAD::WPAD_CL_BUTTON_A
                || buff[0].trig & WPAD::WPAD_BUTTON_A)) exit = true;
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

            /* failsafe, but bad for ISI
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
            */

            alignas(0x20) ExceptionFile exception(thread->context);
            exception.error = static_cast<OS::Error>(crashError);
            char path[IOS::ipcMaxPath];
            const System* system = System::sInstance;
            snprintf(path, IOS::ipcMaxPath, "%s/Crash.pul", system->GetModFolder());
            io->CreateAndOpen(path, IOS::MODE_READ_WRITE);
            io->Overwrite(sizeof(ExceptionFile), &exception);
            io->Close();
        }
    }
    if(exit) LaunchSoftware();
}
kmCall(0x80226610, CreateCrashFile);

/*
static void OnCrashEnd() {
    IO* io = IO::sInstance;;
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


