#ifndef _NW4R_DB_EXCEPTION_
#define _NW4R_DB_EXCEPTION_
#include <types.hpp>
#include <core/rvl/os/thread.hpp>

namespace nw4r {
namespace db {
struct Exception {
    static Exception sInstance; //802a70b8
    static void Init(); //800023150
    u8 unknown[0x360];
}; //total size 0x360



struct ExceptionCallbackParam {
    u16 error; //see OSError
    u8 padding[2];
    OSContext *context;
    u32 dsisr;
    u32 dar;
};

// prints message to NW4R console
void DirectPrint_ChangeXfb(void *frameBuffer, u16 width, u16 height);
void DirectPrint_DrawString(u32 xCoord, u32 yCoord, bool hasWrapping, const char *string);
void DirectPrint_StoreCache();
void Exception_Printf_(const char *, ...);
void PrintContext_(u16 error, const OSContext *context, u32 dsisr, u32 dar);
void DumpException_(const ExceptionCallbackParam *param);
}//namespace db
}//namespace nw4r
#endif