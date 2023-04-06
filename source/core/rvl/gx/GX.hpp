#ifndef _GX_
#define _GX_

#include <types.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/os/thread.hpp>

extern "C" {
    void GXSetVtxDesc(GXAttr attr, GXAttrType type);
    void GXClearVtxDesc();
    void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
    void GXSetNumTexGens(u8 nr);
    void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
    void GXSetCullMode(GXCullMode mode);
    void GXSetNumChans(u8 nChans);
    void GXSetChanCtrl(GXChannelID chan, bool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
    void GXSetChanMatColor(GXChannelID chan, GXColor color);
    void GXSetTevOp(GXTevStageID id, GXTevMode mode);
    void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
    void GXSetAlphaUpdate(bool enable);
    void GXSetColorUpdate(bool enable);
    void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID IDcolor);
    void GXSetNumTevStages(u8 num);
    void GXSetFog(GXFogType type, float startz, float endz, float nearz, float farz, GXColor color);
    void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
    void GXSetZMode(bool compare_enable, GXCompare func, bool update_enable);
    void GXSetZCompLoc(bool before_tex);
    void GXSetProjection(const float mtx[4][4], GXProjectionType type);
    void GXLoadPosMtxImm(const float mtx[3][4], u32 pnidx);
    void GXSetCurrentMtx(u32 mtx);
    void GXLoadPosMtxIndx(u32 indx);
    OSThread *GetCurrentGXThread(); //8016d39c
    void GXSetDrawSync(u16 token); //sets a token, which will be stored in a reg when it reaches the end of the pipeline
    u16 GXReadDrawSync(); //if matches token set with, geometry has been rendered
}
#endif