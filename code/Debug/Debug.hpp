#ifndef _Debug_
#define _Debug_
#include <core/System/SystemManager.hpp>
#include <core/RK/RKSystem.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <core/rvl/base/ppc.hpp>
#include <core/rvl/devfs/isfs.hpp>
#include <core/rvl/os/OS.hpp>
#include <core/rvl/os/Error.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/egg/Exception.hpp>
#include <File/File.hpp>
#include <Pulsar.hpp>

namespace Debug {
void LaunchSoftware();
struct GPR {
    void Set(const OSContext *context, u8 idx) {
        gpr = context->gpr[idx];
        name = 0x7230303a + ((idx / 10) % 10) * 0x10000 + (idx % 10) * 0x100;
    }
    u32 name;
    u32 gpr;
};

struct FPR {
    void Set(const OSContext *context, u8 idx) {
        fpr = context->fpr[idx];
        name = 0x6630303a + ((idx / 10) % 10) * 0x10000 + (idx % 10) * 0x100;
    }
    u32 name;
    f64 fpr;
};

struct StackFrame {
    StackFrame(): spName(0x73703A20), sp(0), lrName(0x6C723A20), lr(0) {};
    u32 spName;
    u32 sp;
    u32 lrName;
    u32 lr;
};

struct ExceptionFile {
    explicit ExceptionFile(const OSContext *context);

    u32 magic;
    OSError error;
    GPR srr0;
    GPR srr1;
    GPR msr;
    GPR cr;
    GPR lr;
    GPR gprs[32];
    FPR fprs[32];
    FPR fpscr;
    StackFrame frames[10];
};

}//namespace Debug


#endif