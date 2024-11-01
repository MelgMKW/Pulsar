#include <kamekLoader.hpp>
#include <core/rvl/OS/OSBootInfo.hpp>

static void loadIntoMKW();


LoaderParams paramsPAL ={
    (OSReport_t)0x801A25D0,
    (OSFatal_t)0x801A4EC4,
    (DVDConvertPathToEntrynum_t)0x8015DF4C,
    (DVDFastOpen_t)0x8015E254,
    (DVDReadPrio_t)0x8015E834,
    (DVDClose_t)0x8015E568,
    (sprintf_t)0x80011A2C,
    (RKSystem*)0x802A4080,
    PAL,
    0x80510238
};
LoaderParams paramsNTSC_U ={
    (OSReport_t)0x801A2530,
    (OSFatal_t)0x801A4E24,
    (DVDConvertPathToEntrynum_t)0x8015DEAC,
    (DVDFastOpen_t)0x8015E1B4,
    (DVDReadPrio_t)0x8015E794,
    (DVDClose_t)0x8015E4C8,
    (sprintf_t)0x80010ECC,
    (RKSystem*)0x8029fd00,
    NTSC_U,
    0x8050bf50,

};
LoaderParams paramsNTSC_J ={
    (OSReport_t)0x801A24F0,
    (OSFatal_t)0x801A4DE4,
    (DVDConvertPathToEntrynum_t)0x8015DE6C,
    (DVDFastOpen_t)0x8015E174,
    (DVDReadPrio_t)0x8015E754,
    (DVDClose_t)0x8015E488,
    (sprintf_t)0x80011950,
    (RKSystem*)0x802a3a00,
    NTSC_J,
    0x8050fc50,
};
LoaderParams paramsNTSC_K ={
    (OSReport_t)0x801A292C,
    (OSFatal_t)0x801A5220,
    (DVDConvertPathToEntrynum_t)0x8015DFC4,
    (DVDFastOpen_t)0x8015E2CC,
    (DVDReadPrio_t)0x8015E8AC,
    (DVDClose_t)0x8015E5E0,
    (sprintf_t)0x80011A94,
    (RKSystem*)0x80292080,
    NTSC_K,
    0x804fe2f0
};



static void LoadIntoMKW() {
    const u8 regionMem = OS::BootInfo::mInstance.diskID.gameName[3];

    LoaderParams* params = nullptr;
    switch(regionMem) {
        case 'P':
            params = &paramsPAL;
            break;
        case 'E':
            params = &paramsNTSC_U;
            break;
        case 'J':
            params = &paramsNTSC_J;
            break;
        case 'K':
            params = &paramsNTSC_K;
            break;
    }

    LoadKamekBinaryFromDisc(params);
}
