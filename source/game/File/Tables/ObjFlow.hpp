#ifndef _OBJFLOW_
#define _OBJFLOW_
#include <game/File/Tables/Table.hpp>

//https://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/ObjFlow.bin
//Objects params
enum ObjectClippingMethod {
    OBJ_CLIPPING_NONE = 0x0,
    OBJ_CLIPPING_DEFAULT_ENABLED = 0x1, //disabled outside draw distance
    OBJ_CLIPPING_DEFAULT_DISABLED = 0x2, //enabled inside draw distance
    OBJ_CLIPPING_DEFAULT_ENABLED_AREA = 0x8,
    OBJ_CLIPPING_DEFAULT_ENABLED_AREA_RECALCULATE = 0x9,
    OBJ_CLIPPING_DEFAULT_DISABLED_AREA = 0xA,
    OBJ_CLIPPING_DEFAULT_DISABLED_AREA_RECALCULATE = 0xB
};

struct ObjFlowEntry {
    u16 objId;
    char name[0x20];
    char neededFiles[0x40]; //separated by a ; such as koopaFirebar; WLfirebarGC
    u16 param0; //0x62
    s16 objectClipping; //0x64 see enum
    s16 backwardDrawDistance; //0x66
    s16 forwardDrawDistance; //0x68
    u16 solidityType; //0x6a if not null, is solid
    s16 solidityParams[3]; //0x6c value used depends on solidity type
    u16 unknown_0x72; //0x72
}; //total size 0x74
size_assert(ObjFlowEntry, 0x74);

struct ObjFlow {
    TableBinaryHeader header;
    ObjFlowEntry entries; //number = objCount
    //IndexToIDTable idxToID;
};

#endif