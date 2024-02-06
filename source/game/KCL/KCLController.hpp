#ifndef _KCLHANDLER_
#define _KCLHANDLER_
#include <kamek.hpp>
#include <game/File/KCL.hpp>
#include <game/KCL/Collision.hpp>

class ObjectKCL;
struct CollisionInfo { //match = matches the "accepted" kcl types bitfield
    struct ObjInfo { //if you are an entity containing this struct, which objectKCL are you colliding with, if any, and what is your distance to it
        void Init(); //807bd7b4
        void Reset(); //807bd930
        void Set(ObjectKCL* obj, float yDistance); //807bd7d8
        bool AreItemsAllowedOnObj() const; //807bd850
        void CalcInitialDistance(const Vec3& otherInitialPosition); //807bd88c for ex S_Itembox
        void Update(Vec3& otherPosition); //807bd8e8 updates otherPosition using internal distance + object's
        void UpdateWithRot(Vec3& otherPosition, Vec3& otherDir); //807bd908 updates otherPosition using internal distance + object's
        void SetDistanceCalcBit(); //807bd864

        u32 bitfield; // 1 has obj, 20 hasDistanceCalc'd, 40 hasDistanceWithRot, 100 test specific object before looping through all
        ObjectKCL* object; //0x4
        Vec3 distance; //0x8 once calc'd this is a constant so that the entity always stays at the same distance 
    };
    void Init(); //807c2660
    Vec3 minDistInAllDir; //0x0 minimize(dir of all matches), ie furthest potential dist into -x -y -z
    Vec3 maxDistInAllDir; //0xc maximize(dir of all matches)
    Vec3 dirToClosestTri; //0x18 normal of closest match
    Vec3 dirToClosestFloorTri; //0x24 normalized, only filled if floor AND inputed floorDist < dist to match 
    Vec3 dirToClosestWallTri; //0x30  normalized, only filled if wall 
    Vec3 unknown_0x3c; //0x3c doesn't seem to be used?
    float minDistToFloorTri; //0x48
    float minDistToWallTri; //0x4c
    float unknown_0x50; //0x50 dist of 0x3c
    //smallest dot product of two wall tris normals, the smaller the number, the bigger the angle btw 2 tris planes
    float smallestProjOfDifferentWallTris; //0x54 
    ObjInfo* objInfo; //0x58
}; //0x5c

class KCLController {
public:
    explicit KCLController(const KCL& raw); //807bdc5c
    ~KCLController(); //807bddbc
    void GetTrianglesList(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, float radius); //807c1bb4
    void GetTrianglesListReuse(const Vec3& pos, const Vec3& prevPos, KCLBitfield accepted, float radius); //807c1de8
    u16* FindTrianglesList(const Vec3& position); //807be030
    void FindTrianglesListAndProcessNewRadius(const Vec3& position, Ptmf_0A<KCLController, bool>* isColliding, float radius); //807be12c

    //These increment the triangle list until a match is found or the list is exhausted
    bool IsColliding(float* distance, Vec3* normal, u16* flag); //807c2410
    bool IsCollidingImplInfY(float* distance, Vec3* normal, u16* flag); //807c1514 if position.y == infinity
    bool IsCollidingImpl(float* distance, Vec3* normal, u16* flag); //807c0884
    bool IsCollidingFromCurCopyPosition(float* distance, Vec3* normal, u16* flag); //807c0f00 Only checks triangles after curCopyPosition

    //will find a new trianglesList if needed
    void Update(const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale, float radius);

    //Is radius < lastMaxRadius && dist(position, lastPosition) < (lastMaxRadius - radius)
    static bool CanReuseLastTrianglesList(const Vec3& pos, const Vec3& prevPos, float radius, float lastMaxRadius); //8051a07c

    Vec3* vertices; //0
    Vec3* normals; //4
    KCLTriangle* trianglesMinus0x10; //8 because it is 1-indexed in the octree
    u32* octree; //0xc
    float thickness; //0x10
    Vec3 firstCoord; //0x14 spatial grid first coordinate
    u32 xWidthMask; //0x20
    u32 yWidthMask; //0x24
    u32 zWidthMask; //0x28
    u32 coordShift; //0x2c = max octree depth
    u32 yShift; //0x30
    u32 zShift; //0x34
    float maximumRadius; //0x38

    Vec3 position;  //0x3c
    Vec3 prevPosition; //0x48
    Vec3 positionDifference; //0x54
    float radius; //0x60
    KCLBitfield flags; //0x64

    //to avoid searching the octree for every process collision func/call, the game checks if it can reuse the list pointed to by 0x290
    //that ptr points to a copy of the last octree list that was obtained through a search
    u16* triangleList; //0x68 obtained from the octree

    u32 triangleCount; //0x6c determined via the length of the triangleArray
    KCLTriangle* triangles; //0x70
    u8 unknown_0x74[0x80 - 0x74];
    Vec3 firstVertice; //0x80
    u16 curTriangle; //0x8c
    u16 trianglesIdx[0xFF]; //0x8e copy of the last used triangle list, to prevent searching the octree many times; always ends with a 0000
    u16* curCopyTriangleListPosition; //0x28c points to the nextPosition to be copied from triangleList to the idx array
    u16* lastTriangleList; //0x290
    Vec3 lastPosition; //0x294
    float lastMaxRadius; //0x2a0 of the 
};
size_assert(KCLController, 0x2a4);
#endif