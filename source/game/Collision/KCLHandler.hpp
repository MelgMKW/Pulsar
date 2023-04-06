#ifndef _KCLHANDLER_
#define _KCLHANDLER_
#include <kamek.hpp>
#include <game/File/KCL.hpp>

class KCLHandler {
public:
    explicit KCLHandler(KCL *raw); //807bdc5c
    Vec3 *vertices; //0
    Vec3 *normals; //4
    Vec3 *trianglesMinus0x10; //8
    u32 *octree; //0xc
    float thickness; //0x10
    Vec3 firstCood; //0x14
    u32 xMask; //0x20
    u32 yMask; //0x24
    u32 zMast; //0x28
    u32 coordShift; //0x2c
    u32 yShift; //0x30
    u32 zShift; //0x34
    float maximumRadius; //0x38
    u8 unknown_0x3C[0x6c - 0x3C];
    u32 triangleCount; //determined via the length of the triangleArray
    KCLTriangle *triangles;
    u8 unknown_0x74[0x80 - 0x74];
    Vec3 firstVertice; //0x80
    u8 unknown_0x8c[0x2A4 - 0x8c];
};
size_assert(KCLHandler, 0x2a4);
#endif