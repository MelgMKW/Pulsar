#include <kamek.hpp>
#include <Debug/Debug.hpp>

namespace Debug {
const OSContext *crashContext = NULL;
u16 crashError = 0;


void LaunchSoftware() { //If dolphin, restarts game, else launches Riivo->HBC->OHBC->WiiMenu
    s32 result = Pulsar::Open("/dev/dolphin", IOS::MODE_NONE);
    if (result >= 0) {
        IOS::Close(result);
        SystemManager::RestartGame();
        return;
    }
    result = Pulsar::Open("/title/00010001/52494956/content/title.tmd\0", IOS::MODE_NONE); //Riivo
    if (result >= 0) {
        ISFS::Close(result);
        OSLaunchTitle(0x00010001, 0x52494956);
        return;
    }
    result = Pulsar::Open("/title/00010001/4c554c5a/content/title.tmd\0", IOS::MODE_NONE); //OHBC
    if (result >= 0) {
        ISFS::Close(result);
        OSLaunchTitle(0x00010001, 0x4c554c5a);
        return;
    }
    result = Pulsar::Open("/title/00010001/48424330/content/title.tmd\0", IOS::MODE_NONE); // If HBC can't be found try OHBC
    if (result >= 0) {
        ISFS::Close(result);
        OSLaunchTitle(0x00010001, 0x48424330);
        return;
    }
    OSLaunchTitle(0x1, 0x2); // Launch Wii Menu if channel isn't found
}

//Credit Star and Riidefi
//Data Shown
kmWrite16(0x802A7410, 0x00000023);
//Show Handler
kmWrite32(0x802A7404, 0x00000000);
//Show StackTrace
kmWrite32(0x80023948, 0x281e0007);
//Max number of lines
kmWrite32(0x80009324, 0x38800068);
//Lines on the screen and x-pos
void SetConsoleParams() {
    nw4r::db::detail::ConsoleHead *console = EGG::Exception::console;
    console->viewLines = 0x16;
    console->viewPosX = 0x10;
}
BootHook ConsoleParams(SetConsoleParams, 3);


ExceptionFile::ExceptionFile(const OSContext *context) {
    magic = 0x50554C44;
    this->srr0.name = 0x73727230;
    this->srr0.gpr = context->srr0;
    this->srr1.name = 0x73727231;
    this->srr1.gpr = context->srr1;
    this->msr.name = 0x6D73723A;
    this->msr.gpr = PPCMfmsr();
    this->cr.name = 0x63723A20;
    this->cr.gpr = context->cr;
    this->lr.name = 0x6C723A20;
    this->lr.gpr = context->lr;
    for (int i = 0; i < 32; i++) {
        this->gprs[i].Set(context, i);
        this->fprs[i].Set(context, i);
    }
    this->fpscr.name = 0x66736372;
    this->fpscr.fpr = context->fpscr;
    u32 *sp = (u32 *)context->gpr[1];
    for (int i = 0; i < 10; i++) {
        if (sp == NULL || (u32)sp == 0xFFFFFFFF) break;
        this->frames[i].sp = (u32)sp;
        this->frames[i].lr = sp[1];
        sp = (u32 *)*sp;
    }
}

//Can't get the file to be created on all threads therefore shelving this for now
void DumpContextToFile(u16 error, const OSContext *context, u32 dsisr, u32 dar) {
    crashError = error;
    crashContext = context;
    nw4r::db::PrintContext_(error, context, dsisr, dar);
}
kmCall(0x80023484, DumpContextToFile);


void CreateCrashFile() {
    PulsarIO::File *fileHandler = PulsarIO::File::sInstance;
    if (fileHandler != NULL) { //should always exist if the crash is after strap 
        const OSContext *context = crashContext;
        OSDetachThread((OSThread *)context);
        OSCancelThread((OSThread *)context);

        register u32 *addressPtr = (u32 *)(context->srr0 + 4);
        s32 diff = (u8 *)&LaunchSoftware - (u8 *)addressPtr; //b to launch software just in case something goes wrong
        u32 instruction = 0x48000000;
        if (diff < 0) instruction = 0x4B000000;
        *addressPtr = instruction + (diff & 0x00FFFFFF);
        asm{
            ASM(
            dcbst 0, addressPtr;
            sync;
            icbi 0, addressPtr;
            )
        }

        ExceptionFile *file = new(RKSystem::mInstance.EGGSystem, 0x20) ExceptionFile(context);
        file->error = (OSError)crashError;
        char path[IPCMAXPATH];
        snprintf(path, IPCMAXPATH, "%s/Crash.bin", Pulsar::sInstance->GetModFolder());
        fileHandler->CreateAndOpen(path, IOS::MODE_READ_WRITE);
        fileHandler->Overwrite(sizeof(ExceptionFile), file);
        fileHandler->Close();
        delete(file);
    }
    LaunchSoftware();
}

void OnCrashEnd() {
    PulsarIO::File *fileHandler = PulsarIO::File::sInstance;
    if (fileHandler != NULL) { //should always exist if the crash is after strap 
        register u32 *addressPtr = (u32 *)(crashContext->srr0 + 4);
        s32 diff = (u8 *)&CreateCrashFile - (u8 *)addressPtr;
        u32 instruction = 0x48000000;
        if (diff < 0) instruction = 0x4B000000;
        *addressPtr = instruction + (diff & 0x00FFFFFF) + 1;
        asm{
            ASM(
            dcbst 0, addressPtr;
            sync;
            icbi 0, addressPtr;
            )
        }
        OSThread::current = (OSThread *)crashContext;
        SelectThread(0);

    }
    else LaunchSoftware();
}


kmBranch(0x802265f0, CreateCrashFile);
}//namespace Debug



