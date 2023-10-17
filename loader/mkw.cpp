#include <kamekLoader.hpp>

void loadIntoMKW();

struct loaderFunctionsEx {
    LoaderFunctions base;
};

loaderFunctionsEx functions_p ={
    {(OSReport_t)0x801A25D0,
    (OSFatal_t)0x801A4EC4,
    (DVDConvertPathToEntrynum_t)0x8015DF4C,
    (DVDFastOpen_t)0x8015E254,
    (DVDReadPrio_t)0x8015E834,
    (DVDClose_t)0x8015E568,
    (sprintf_t)0x80011A2C,
    (RKSystem*)0x802A4080}
};
loaderFunctionsEx functions_e ={
    {(OSReport_t)0x801A2530,
    (OSFatal_t)0x801A4E24,
    (DVDConvertPathToEntrynum_t)0x8015DEAC,
    (DVDFastOpen_t)0x8015E1B4,
    (DVDReadPrio_t)0x8015E794,
    (DVDClose_t)0x8015E4C8,
    (sprintf_t)0x80010ECC,
    (RKSystem*)0x8029fd00}
};
loaderFunctionsEx functions_j ={
    {(OSReport_t)0x801A24F0,
    (OSFatal_t)0x801A4DE4,
    (DVDConvertPathToEntrynum_t)0x8015DE6C,
    (DVDFastOpen_t)0x8015E174,
    (DVDReadPrio_t)0x8015E754,
    (DVDClose_t)0x8015E488,
    (sprintf_t)0x80011950,
    (RKSystem*)0x802a3a00}
};
loaderFunctionsEx functions_k ={
    {(OSReport_t)0x801A292C,
    (OSFatal_t)0x801A5220,
    (DVDConvertPathToEntrynum_t)0x8015DFC4,
    (DVDFastOpen_t)0x8015E2CC,
    (DVDReadPrio_t)0x8015E8AC,
    (DVDClose_t)0x8015E5E0,
    (sprintf_t)0x80011A94,
    (RKSystem*)0x80292080}
};


void LoadIntoMKW() {
    u8 region = *(u8*)(0x80000003);

    LoaderFunctions* funcs = nullptr;
    switch(region) {
        case 'P': funcs = &functions_p.base; break;
        case 'E': funcs = &functions_e.base; break;
        case 'J': funcs = &functions_j.base; break;
        case 'K': funcs = &functions_k.base; break;
    }

    char path[64];
    funcs->sprintf(path, "/Binaries/%c.bin", region);
    LoadKamekBinaryFromDisc(funcs, path);
}
