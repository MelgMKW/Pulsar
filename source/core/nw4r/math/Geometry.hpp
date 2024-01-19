#ifndef _NW4R_MATH_GEOMETRY_
#define _NW4R_MATH_GEOMETRY_
#include <types.hpp>
#include <include/c_math.h>
#include <core/nw4r/math/types.hpp>
#include <core/rvl/mtx/mtx.hpp>

namespace nw4r {
namespace math {

enum IntersectionResult {
    INTERSECTION_NONE = 0,
    INTERSECTION_1 = 1,
    INTERSECTION_2 = 2,

    INTERSECTION_LINE3_ON_PLANE = 2,

    INTERSECTION_OUTSIDE = 0,
    INTERSECTION_INSIDE = 1,
    INTERSECTION_INTERSECT = 2
};

struct SEGMENT3 { VEC3 a, b; };
struct LINE3 { VEC3 point, direction; };
struct SPHERE { VEC3 point; float radius; };

struct PLANE {
    VEC3 vector;
    float constant;

    void Set(const VEC3* a, const VEC3* b, const VEC3* c);
}; // Total size 0x10

struct AABB { //axis-aligned bounding boxes, box of minimum volume within which point array is within AND whose edges are parallel to xyz
    VEC3 minPoint, maxPoint;

    void Set(const VEC3* pointArray, u32 pointCount);
    void Set(const AABB* otherAABB, const MTX34* matrix);
}; // Total size 0x18

class FRUSTUM {
public:
    FRUSTUM(); //empty
    void Set(float fovy, float aspect, float near, float far, const MTX34& camera); //80085e70
    void Set(float top, float bottom, float left, float right, float near, float far, const MTX34& camera); //80085f30
    // AABB is in world coordinate system
    IntersectionResult IntersectAABB_Ex(const AABB* B) const; //80086610

    //view
    MTX34 camera;
    PLANE left, right, top, bottom;
    float near;
    float far;

    //world
    AABB box;
    PLANE planes[6]; //left right near far up down
};

float DistSqSegment3ToSegment3(const SEGMENT3* a, const SEGMENT3* b, float* pOut1, float* pOut2);
int IntersectionLine3Sphere(const LINE3* a, const SPHERE* b, float* pOut1, float* pOut2);
int IntersectionSegment3Sphere(const SEGMENT3* a, const SPHERE* b, float* pOut1, float* pOut2);
bool IntersectionAABB(const AABB* a, const AABB* b);

}//namespace math
}//namespace nw4r

#endif
