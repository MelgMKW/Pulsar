#ifndef _MTX_
#define _MTX_
#include <types.hpp>
#ifdef __cplusplus
extern "C" {
#endif


    /* MTX Module */

    typedef float Mtx[3][4];
    typedef struct { float x, y, z, w; } Quaternion;
    typedef struct { float x, y, z; } Vec;
    typedef float Mtx44[4][4];

    void PSMTXIdentity(Mtx matrix);
    void PSMTXCopy(const Mtx source, Mtx dest);
    void PSMTXConcat(const Mtx sourceA, const Mtx sourceB, Mtx dest);
    void PSMTXConcatArray(const Mtx sourceA, const Mtx *sourcesB, Mtx *destsB, int count);
    u32 PSMTXInverse(const Mtx source, Mtx dest);
    u32 PSMTXInvXpose(const Mtx source, Mtx dest);
    void PSMTXRotRad(Mtx matrix, u8 axis, float radians);
    void PSMTXRotTrig(Mtx matrix, u8 axis, float sin, float cos);
    void PSMTXRotAxisRad(Mtx matrix, Vec *axis, float radians);
    void PSMTXTrans(Mtx matrix, float x, float y, float z);
    void PSMTXTransApply(const Mtx source, Mtx dest, float x, float y, float z);
    void PSMTXScale(Mtx matrix, float x, float y, float z);
    void PSMTXScaleApply(const Mtx source, Mtx dest, float x, float y, float z);
    void PSMTXQuat(Mtx dest, const Quaternion *quat);
    void C_MTXLookAt(Mtx dest, const Vec *cameraPos, const Vec *cameraUp, const Vec *target);
    void C_MTXLightFrustum(Mtx dest, float top, float bottom, float left, float right, float near, float scaleS, float scaleT, float transS, float transT);
    void C_MTXLightPerspective(Mtx dest, float fovy, float aspect, float scaleS, float scaleT, float transS, float transT);
    void C_MTXLightOrtho(Mtx dest, float top, float bottom, float left, float right, float scaleS, float scaleT, float transS, float transT);
    void PSMTXMultVec(const Mtx matrix, const Vec *source, Vec *dest);
    void C_MTXFrustum(Mtx44 dest, float top, float bottom, float left, float right, float near, float far);
    void C_MTXPerspective(Mtx44 dest, float fovy, float aspect, float near, float far);
    void C_MTXOrtho(Mtx44 dest, float top, float bottom, float left, float right, float near, float far);
    void PSVECAdd(const Vec *sourceA, const Vec *sourceB, Vec *dest);
    void PSVECSubtract(const Vec *sourceA, const Vec *sourceB, Vec *dest);
    void PSVECScale(const Vec *source, Vec *dest, float scale);
    void PSVECNormalize(const Vec *source, Vec *dest);
    float PSVECMag(const Vec *Vec);
    float PSVECDotProduct(const Vec *sourceA, const Vec *sourceB);
    void PSVECCrossProduct(const Vec *sourceA, const Vec *sourceB, Vec *dest);
    void C_VecHalfAngle(const Vec *sourceA, const Vec *sourceB, Vec *dest);
    float PSVECSquareDistance(const Vec *sourceA, const Vec *sourceB);
    void C_QUATMtx(Quaternion *dest, const Mtx source);
    void C_QUATSlerp(const Quaternion *sourceA, const Quaternion *sourceB, Quaternion *dest, float value);

#define MTXIdentity PSMTXIdentity
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXConcatArray PSMTXConcatArray
#define MTXInverse PSMTXInverse
#define MTXInvXpose PSMTXInvXpose
#define MTXRotRad PSMTXRotRad
#define MTXRotTrig PSMTXRotTrig
#define MTXRotAxisRad PSMTXRotAxisRad
#define MTXTrans PSMTXTrans
#define MTXTransApply PSMTXTransApply
#define MTXScale PSMTXScale
#define MTXScaleApply PSMTXScaleApply
#define MTXQuat PSMTXQuat
#define MTXLookAt C_MTXLookAt
#define MTXLightFrustum C_MTXLightFrustum
#define MTXLightPerspective C_MTXLightPerspective
#define MTXLightOrtho C_MTXLightOrtho
#define MTXMultVec PSMTXMultVec
#define MTXFrustum C_MTXFrustum
#define MTXPerspective C_MTXPerspective
#define MTXOrtho C_MTXOrtho
#define VecAdd PSVECAdd
#define VecSubtract PSVECSubtract
#define VecScale PSVECScale
#define VecNormalize PSVECNormalize
#define VecMag PSVECMag
#define VecDotProduct PSVECDotProduct
#define VecCrossProduct PSVECCrossProduct
#define VecHalfAngle C_VecHalfAngle
#define VecSquareDistance PSVECSquareDistance
#define QUATMtx C_QUATMtx
#define QUATSlerp C_QUATSlerp

    // TODO: GX, CX, IOS ... and then of course NW4R

#ifdef __cplusplus
}
#endif
#endif