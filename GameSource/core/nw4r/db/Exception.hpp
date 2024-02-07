#ifndef _NW4R_DB_EXCEPTION_
#define _NW4R_DB_EXCEPTION_
#include <types.hpp>
#include <core/rvl/os/Message.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/gx/GX.hpp>
#include <core/nw4r/db/Console.hpp>

namespace nw4r {
namespace db {
typedef bool (*ExceptionUserCallback)(detail::ConsoleHead* console, void* arg);

struct ExceptionHead {
    static ExceptionHead mInstance; //802a70b8
    static void Init(); //800023150
    OS::Thread exceptionThread; //0x0
    OS::MessageQueue msgQueue; //0x318
    void* frameBuffer; //0x338
    u32 sp; //0x33c
    detail::ConsoleHead* console; //0x340
    const void* render; //0x344
    ExceptionUserCallback callback; //0x348
    void* callbackArgs; //0x34c
    u32 msr; //0x350
    u32 fpscr; //0x354 
    u16 displayedInfo; //0x358
    u8 padding[6];
}; //total size 0x360
size_assert(ExceptionHead, 0x360);

struct ExceptionCallbackParam {
    u16 error; //see OS::Error
    u8 padding[2];
    OS::Context* context;
    u32 dsisr;
    u32 dar;
};



// prints message to NW4R console
void DirectPrint_ChangeXfb(void* frameBuffer, u16 width, u16 height); //80021e30
void DirectPrint_DrawString(u32 xCoord, u32 yCoord, bool hasWrapping, const char* string); //80021e90
void DirectPrint_StoreCache(); //80021e70
void Exception_Printf_(const char*, ...); //800235a0
void PrintContext_(u16 error, const OS::Context* context, u32 dsisr, u32 dar); //80023680
void Exception_SetUserCallback(ExceptionUserCallback callback, void* args); //800240a0
void DumpException_(const ExceptionCallbackParam* param); //80023410

}//namespace db
}//namespace nw4r
#endif