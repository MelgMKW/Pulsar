#ifndef _KCL_
#define _KCL_
#include <kamek.hpp>

//https://wiki.tockdom.com/wiki/KCL_(File_Format)
struct KCLHeader {
    u32 offsetToVertices;
    u32 offsetToNormals; //4
    u32 offsetToTris; //8
    u32 offsetToSpatialOctree; //0xc
    float thickness; //0x10
    Vec3 firstCoord; //0x14
    u32 xMask; //0x20
    u32 yMask; //0x24
    u32 zMast; //0x28
    u32 coordShift; //0x2c
    u32 yShift; //0x30
    u32 zShift; //0x34
    float maximumRadius; //0x38
}; //total size 0x3c

struct KCLTriangle {
    float length;
    u16 posIdx; //4
    u16 dirIdx; //6
    u16 normalAIdx; //8
    u16 normalBIdx; //a
    u16 normalCIdx; //c
    u16 flag; //d
};

struct KCL {
    KCLHeader header;
    Vec3 vertices; //array
    //Vec3 normals;
    //KCLTriangle triangles;
    //Octree
};

#endif