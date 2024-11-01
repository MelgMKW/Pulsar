#ifndef _MTX_
#define _MTX_
#include <types.hpp>

typedef float Mtx[3][4];
struct Quaternion { float x, y, z, w; };
struct Vec2D { float x, z; };
struct Vec { float x, y, z; };
typedef float Mtx44[4][4];

namespace MTX {

void PSMTXIdentity(Mtx matrix);                                   //80199d04 sets a matrix to identity
void PSMTXCopy(const Mtx source, Mtx dest);                       //80199d30
void PSMTXConcat(const Mtx sourceA, const Mtx sourceB, Mtx dest); //80199d64 dest = A * B works even if dest is sourceA or B
void PSMTXConcatArray(const Mtx sourceA, const Mtx* sourcesB, Mtx* destsB, u32 count); //80199e30 destsB[i] = A * sourcesB[i]

//only works for mtx with (0,0,0,1) 4th row, returns true on success
/*
    M = ( A  B ) where A is the upper 3x3 submatrix
        ( 0  1 )

INV(M)     = ( inv(A) (inv(A)) * (-B) )
             (  0           1         )*/
BOOL PSMTXInverse(const Mtx source, Mtx dest); //80199fc8

//Inverse then transpose
/* for normal transform matrices:
if you transform a space to another and scaling is applied to each axis, the inverse of that scaling should be applied to the normals:
https://paroj.github.io/gltut/Illumination/Tut09%20Normal%20Transformation.html*/
BOOL PSMTXInvXpose(const Mtx source, Mtx dest); //8019a0c0 


void PSMTXRotRad(Mtx matrix, u8 axis, float radians); //8019a188 creates a rot matrix about an axis from an axis and an angle: angle positive for counter-clockwise, axis is a char, 'x', 'y', 'z'
void PSMTXRotTrig(Mtx matrix, u8 axis, float sin, float cos); //8019a204 same as above but sin/cos of the angle instead of radians
void PSMTXRotAxisRad(Mtx matrix, Vec* axis, float radians); //8019a364 creates a rot matrix about an axis and a rot angle
void PSMTXTrans(Mtx matrix, float x, float y, float z); //8019a3e0 creates a translation matrix
void PSMTXTransApply(const Mtx source, Mtx dest, float x, float y, float z); //8019a414 dest = src + xyz translation vector column 3 ie adds the translation to src
void PSMTXScale(Mtx matrix, float x, float y, float z); //8019a460 creates a scaling matrix
void PSMTXScaleApply(const Mtx source, Mtx dest, float x, float y, float z); // dest = src * xyz scaling on the diagonal ie adds the scaling to src
void PSMTXQuat(Mtx dest, const Quaternion* quat); //8019a4e0 creates a rot mtx from a quat

//creates a transform matrix to the camera space using camera position, camera up direction and camera aim point
void C_MTXLookAt(Mtx dest, const Vec* cameraPos, const Vec* cameraUp, const Vec* target); //8019a584
//creates a transform matrix to project texture, see frustum.hpp as it's essentially the same principle
void C_MTXLightFrustum(Mtx dest, float top, float bottom, float left, float right, float near, float scaleS, float scaleT, float transS, float transT); //8019a584
//same as above but this time using fovy and aspect
void C_MTXLightPerspective(Mtx dest, float fovy, float aspect, float scaleS, float scaleT, float transS, float transT); //8019a79c
//orthographic projection
void C_MTXLightOrtho(Mtx dest, float top, float bottom, float left, float right, float scaleS, float scaleT, float transS, float transT); //8019a894

void PSMTXMultVec(const Mtx matrix, const Vec* source, Vec* dest); //8019a91c dest = matrix * source
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst); //8019a970 dest = matrix (only scaling and rot) * source

void C_MTXFrustum(Mtx44 dest, float top, float bottom, float left, float right, float near, float far); //8019a9c4
void C_MTXPerspective(Mtx44 dest, float fovy, float aspect, float near, float far); //8019aa60
void C_MTXOrtho(Mtx44 dest, float top, float bottom, float left, float right, float near, float far); //8019ab4c


void PSVECAdd(const Vec* sourceA, const Vec* sourceB, Vec* dest); //8019abe4
void PSVECSubtract(const Vec* sourceA, const Vec* sourceB, Vec* dest); //8019ac08
void PSVECScale(const Vec* source, Vec* dest, float scale); //8019ac08
void PSVECNormalize(const Vec* source, Vec* dest); //8019ac24
float PSVECMag(const Vec* Vec); //8019ac68 norm
float PSVECDotProduct(const Vec* sourceA, const Vec* sourceB); //8019acac
void PSVECCrossProduct(const Vec* sourceA, const Vec* sourceB, Vec* dest); //8019accc
void C_VecHalfAngle(const Vec* sourceA, const Vec* sourceB, Vec* dest); //8019ad08 vector halfway between 2 vectors
float PSVECSquareDistance(const Vec* sourceA, const Vec* sourceB); //8019ade0 (x1 - x2)² + (y1 - y2)² + (z1 - z2)²


void C_QUATMtx(Quaternion* dest, const Mtx source); //8019af48 mtx to quat
void C_QUATLerp(const Quaternion* p, const Quaternion* q, Quaternion* r, float t); //8019b114 linear interpolation of two quat
void C_QUATSlerp(const Quaternion* sourceA, const Quaternion* sourceB, Quaternion* dest, float value); //8019b178 spherical linear interpolation


void __PSMTXRotAxisRadInternal(register Mtx m, const register Vec* axis, register float sinT, register float cosT); //8019a2b4
}//namespace MTX

#endif