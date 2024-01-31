#include <kamekLoader.hpp>
#include <core/nw4r/ut/Misc.hpp>


struct KBHeader {
    u32 magic1; //0x0
    u16 magic2; //0x2
    u16 version; //0x4
    u32 bssSize; //0x8
    u32 codeSize; //0xc
    u32 ctorStart; //0x10
    u32 ctorEnd; //0x14
    u32 length; //0x18
    u32 padding; //0x1c
};


#define kAddr32 1
#define kAddr16Lo 4
#define kAddr16Hi 5
#define kAddr16Ha 6
#define kRel24 10
#define kWrite32 32
#define kWrite16 33
#define kWrite8 34
#define kCondWritePointer 35
#define kCondWrite32 36
#define kCondWrite16 37
#define kCondWrite8 38
#define kBranch 64
#define kBranchLink 65


void DisplayError(const LoaderFunctions* funcs, const char* str) {
    u32 fg = 0xFFFFFFFF, bg = 0;
    funcs->OSFatal(&fg, &bg, str);
}


static inline u32 resolveAddress(u32 text, u32 address) {
    if(address & 0x80000000)
        return address;
    else
        return text + address;
}


#define kCommandHandler(name) \
	static inline const u8 *kHandle##name(const u8 *input, u32 text, u32 address)
#define kDispatchCommand(name) \
	case k##name: input = kHandle##name(input, text, address); break

kCommandHandler(Addr32) {
    u32 target = resolveAddress(text, *(const u32*)input);
    *(u32*)address = target;
    return input + 4;
}
kCommandHandler(Addr16Lo) {
    u32 target = resolveAddress(text, *(const u32*)input);
    *(u16*)address = target & 0xFFFF;
    return input + 4;
}
kCommandHandler(Addr16Hi) {
    u32 target = resolveAddress(text, *(const u32*)input);
    *(u16*)address = target >> 16;
    return input + 4;
}
kCommandHandler(Addr16Ha) {
    u32 target = resolveAddress(text, *(const u32*)input);
    *(u16*)address = target >> 16;
    if(target & 0x8000)
        *(u16*)address += 1;
    return input + 4;
}
kCommandHandler(Rel24) {
    u32 target = resolveAddress(text, *(const u32*)input);
    u32 delta = target - address;
    *(u32*)address &= 0xFC000003;
    *(u32*)address |= (delta & 0x3FFFFFC);
    return input + 4;
}
kCommandHandler(Write32) {
    u32 value = *(const u32*)input;
    *(u32*)address = value;
    return input + 4;
}
kCommandHandler(Write16) {
    u32 value = *(const u32*)input;
    *(u16*)address = value & 0xFFFF;
    return input + 4;
}
kCommandHandler(Write8) {
    u32 value = *(const u32*)input;
    *(u8*)address = value & 0xFF;
    return input + 4;
}
kCommandHandler(CondWritePointer) {
    u32 target = resolveAddress(text, *(const u32*)input);
    u32 original = ((const u32*)input)[1];
    if(*(u32*)address == original)
        *(u32*)address = target;
    return input + 8;
}
kCommandHandler(CondWrite32) {
    u32 value = *(const u32*)input;
    u32 original = ((const u32*)input)[1];
    if(*(u32*)address == original)
        *(u32*)address = value;
    return input + 8;
}
kCommandHandler(CondWrite16) {
    u32 value = *(const u32*)input;
    u32 original = ((const u32*)input)[1];
    if(*(u16*)address == (original & 0xFFFF))
        *(u16*)address = value & 0xFFFF;
    return input + 8;
}
kCommandHandler(CondWrite8) {
    u32 value = *(const u32*)input;
    u32 original = ((const u32*)input)[1];
    if(*(u8*)address == (original & 0xFF))
        *(u8*)address = value & 0xFF;
    return input + 8;
}
kCommandHandler(Branch) {
    *(u32*)address = 0x48000000;
    return kHandleRel24(input, text, address);
}
kCommandHandler(BranchLink) {
    *(u32*)address = 0x48000001;
    return kHandleRel24(input, text, address);
}


inline void cacheInvalidateAddress(register u32 address) {
    asm(dcbst 0, address;);
    asm(sync;);
    asm(icbi 0, address;);
}

void LoadKamekBinary(LoaderFunctions* funcs, const void* binary, u32 binaryLength, bool isDol) {

    static u32 text = 0;
    const KBHeader* header = (const KBHeader*)binary;
    if(header->magic1 != 'Kame' || header->magic2 != 'k\0')
        DisplayError(funcs, "FATAL ERROR: Corrupted file, please check your game's Kamek files");
    if(header->version != 3) {
        char err[512];
        funcs->sprintf(err, "FATAL ERROR: Incompatible file (version %d), please upgrade your Kamek Loader", header->version);
        DisplayError(funcs, err);
    }

    funcs->OSReport("header: bssSize=%u, codeSize=%u, ctors=%u-%u\n",
        header->bssSize, header->codeSize, header->ctorStart, header->ctorEnd);

    u32 textSize = header->codeSize + header->bssSize;

    EGG::ExpHeap* heap = funcs->rkSystem->EGGSystem;
    if(isDol) text = (u32)heap->alloc(textSize, 0x20);
    if(!text) DisplayError(funcs, "FATAL ERROR: Out of code memory");

    const u8* input = ((const u8*)binary) + sizeof(KBHeader);
    const u8* inputEnd = ((const u8*)binary) + binaryLength;
    u8* output = (u8*)text;

    if(isDol) {
        // Create text + bss sections
        for(u32 i = 0; i < header->codeSize; ++i) {
            *output = *(input++);
            cacheInvalidateAddress((u32)(output++));
        }
        for(u32 i = 0; i < header->bssSize; ++i) {
            *output = 0;
            cacheInvalidateAddress((u32)(output++));
        }
    }

    while(input < inputEnd) {
        u32 cmdHeader = *((u32*)input);
        input += 4;

        u8 cmd = cmdHeader >> 24;
        u32 address = cmdHeader & 0xFFFFFF;
        if(address == 0xFFFFFE) {
            // Absolute address
            address = *((u32*)input);
            if(address < 0x80510238 && !isDol) continue;
            else if(address >= 0x80510238 && isDol) continue;
            input += 4;
        }
        else {
            if(!isDol) continue;
            // Relative address
            address += text;
        }

        switch(cmd) {
            case kAddr32:
                input = kHandleAddr32(input, text, address);
                break;
            case kAddr16Lo:
                input = kHandleAddr16Lo(input, text, address);
                break;
            case kAddr16Hi:
                input = kHandleAddr16Hi(input, text, address);
                break;
            case kAddr16Ha:
                input = kHandleAddr16Ha(input, text, address);
                break;
            case kRel24:
                input = kHandleRel24(input, text, address);
                break;
            case kWrite32:
                input = kHandleWrite32(input, text, address);
                break;
            case kWrite16:
                input = kHandleWrite16(input, text, address);
                break;
            case kWrite8:
                input = kHandleWrite8(input, text, address);
                break;
            case kCondWrite32:
                input = kHandleCondWrite32(input, text, address);
                break;
            case kCondWrite16:
                input = kHandleCondWrite16(input, text, address);
                break;
            case kCondWrite8:
                input = kHandleCondWrite8(input, text, address);
                break;
            case kCondWritePointer:
                input = kHandleCondWritePointer(input, text, address);
                break;
            case kBranch:
                input = kHandleBranch(input, text, address);
                break;
            case kBranchLink:
                input = kHandleBranchLink(input, text, address);
                break;
            default:
                funcs->OSReport("Unknown command: %d\n", cmd);
        }

        cacheInvalidateAddress(address);
    }
    asmVolatile(sync;);
    asmVolatile(isync;);

    typedef void (*Func)();
    if(!isDol) {
        for(Func* f = (Func*)(text + header->ctorStart); f < (Func*)(text + header->ctorEnd); f++) {
            (*f)();
        }
    }
}


void LoadKamekBinaryFromDisc(LoaderFunctions* funcs, Region region)
{
    static void* codePulBuf = nullptr;
    static u32 fileLength = 0;
    funcs->OSReport("{Kamek by Treeki}\nLoading Kamek binary");

    bool isDol = false;
    EGG::ExpHeap* heap = funcs->rkSystem->EGGSystem;

    if(codePulBuf == nullptr) {
        const char* path = "/Binaries/Code.pul";
        int entrynum = funcs->DVDConvertPathToEntrynum(path);
        if(entrynum < 0) {
            char err[512];
            funcs->sprintf(err, "FATAL ERROR: Failed to locate file on the disc: %s", path);
            DisplayError(funcs, err);
        }

        DVDFileInfo fileInfo;
        if(!funcs->DVDFastOpen(entrynum, &fileInfo)) DisplayError(funcs, "FATAL ERROR: Failed to open file!");
        funcs->OSReport("DVD file located: addr=%p, size=%d\n", fileInfo.startAddr, fileInfo.length);

        alignas(0x20) KBHeader header;
        u32 roundedHeaderLength = nw4r::ut::RoundUp(sizeof(KBHeader), 32);
        funcs->DVDReadPrio(&fileInfo, &header, roundedHeaderLength, 0, 2);

        fileLength = header.length;
        u32 length = header.length;
        u32 roundedLength = nw4r::ut::RoundUp(length, 32);

        isDol = true;
        codePulBuf = heap->alloc(roundedLength, -0x20);
        if(!codePulBuf) DisplayError(funcs, "FATAL ERROR: Out of file memory");
        funcs->DVDReadPrio(&fileInfo, codePulBuf, roundedLength, length * region, 2);
        funcs->DVDClose(&fileInfo);
    }

    LoadKamekBinary(funcs, codePulBuf, fileLength, isDol);
    if(!isDol) heap->free(codePulBuf);
}
