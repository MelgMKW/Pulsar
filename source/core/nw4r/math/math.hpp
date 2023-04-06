#ifndef _NW4R_MATH_
#define _NW4R_MATH_
#include <types.hpp>
#include <include/c_math.h>
#include <core/rvl/mtx/mtx.hpp>

namespace nw4r {
namespace math {
namespace detail {
float FExp(float);
float FLog(float);
}//namespace detail

inline float FExp(float value) { return detail::FExp(value); }
inline float FLog(float value) { return (value > 0.0f) ? detail::FLog(value) : NAN; }
float FrSqrt(float);


float SinFIdx(float fidx);
float CosFIdx(float fidx);
void SinCosFIdx(float *pSin, float *pCos, float fidx);
float Atan2FIdx(float y, float x);
u16 Atan2Idx(float y, float x);

typedef struct VEC2 {
    float x, z;
};

struct VEC3 : Vec {
    void Report(bool addNewLine, const char *prefixText = 0);
};

VEC2 *VEC2Maximize(VEC2 *dest, const VEC2 *src1, const VEC2 *src2); //80085580
VEC2 *VEC2Minimize(VEC2 *dest, const VEC2 *src1, const VEC2 *src2); //800855c0
VEC3 *VEC3Maximize(VEC3 *dest, const VEC3 *src1, const VEC3 *src2);
VEC3 *VEC3Minimize(VEC3 *dest, const VEC3 *src1, const VEC3 *src2);

struct QUAT {
    float x, y, z, w;
}; // total size 0x10

typedef struct { s16 x, y, z; } S16Vec3;
typedef float Mat[3][4];
typedef Mat Mat34;
typedef float Mat44[4][4];
typedef float Mat43[4][3];



struct MTX33 {
    union {
        struct {
            float n00, n01, n02;
            float n10, n11, n12;
            float n20, n21, n22;
        };
        float element[3][3];
        float member[9];
    };
};

struct MTX34 {
    union {
        struct {
            float n00, n01, n02, n03;
            float n10, n11, n12, n13;
            float n20, n21, n22, n23;
        };
        float element[3][4];
        float member[12];
        Mat mtx;
    };
};

struct MTX44 {
    union {
        struct {
            float n00, n01, n02, n03;
            float n10, n11, n12, n13;
            float n20, n21, n22, n23;
            float n30, n31, n32, n33;
        };
        float element[4][4];
        float member[16];
        Mat44 mtx;
    };
};

struct MTX43 {
    union {
        struct {
            float n00, n01, n02;
            float n10, n11, n12;
            float n20, n21, n22;
            float n30, n31, n32;
        };
        float element[4][3];
        float member[12];
        Mat43 mtx;
    };
};

void MTX33Identity(MTX33 *mtx);
void MTX34ToMTX33(MTX33 *dest, const MTX34 *source);
void MTX34Zero(MTX34 *mtx);
void MTX34Add(MTX34 *dest, const MTX34 *sourceA, const MTX34 *sourceB);
void MTX34Scale(MTX34 *dest, const MTX34 *sourceMatrix, const VEC3 *sourceVector);
void MTX34Trans(MTX34 *dest, const MTX34 *sourceMatrix, const VEC3 *sourceVector);
void MTX34RotAxisFIdx(MTX34 *dest, const VEC3 *vector, float fidx);
void MTX34RotXYZFIdx(MTX34 *dest, float x, float y, float z);
void VEC3TransformNormal(VEC3 *dest, const MTX34 *sourceMatrix, const VEC3 *sourceVector);
void MTX44Identity(MTX44 *mtx);
void MTX44Copy(MTX44 *dest, const MTX44 *source);

struct PLANE {
    VEC3 vector;
    float constant;

    void Set(const VEC3 *a, const VEC3 *b, const VEC3 *c);
}; // Total size 0x10

struct AABB {
    VEC3 minPoint, maxPoint;

    void Set(const VEC3 *pointArray, u32 pointCount);
    void Set(const AABB *otherAABB, const MTX34 *matrix);
}; // Total size 0x18

struct FRUSTUM {
    MTX34 matrix;
    PLANE left, right, top, bottom;
    float near, far;
    AABB aabb;
    PLANE planes[6];

    void Set(float fovy, float aspect, float near, float far, const MTX34 &matrix);
    void Set(float top, float bottom, float left, float right, float near, float far, const MTX34 &matrix);
    int IntersectAABB_Ex(const AABB *otherAabb);
}; // Total size 0xf0

struct SEGMENT3 { VEC3 a, b; };
struct LINE3 { VEC3 point, direction; };
struct SPHERE { VEC3 point; float radius; };

float DistSqSegment3ToSegment3(const SEGMENT3 *a, const SEGMENT3 *b, float *pOut1, float *pOut2);
int IntersectionLine3Sphere(const LINE3 *a, const SPHERE *b, float *pOut1, float *pOut2);
int IntersectionSegment3Sphere(const SEGMENT3 *a, const SPHERE *b, float *pOut1, float *pOut2);
bool IntersectionAABB(const AABB *a, const AABB *b);
}//namespace math
}//namespace nw4r

#endif
