#ifndef _GX_
#define _GX_

#include <types.hpp>
#include <core/rvl/GX/GXEnum.hpp>
#include <core/rvl/GX/GXStruct.hpp>
#include <core/rvl/os/thread.hpp>

namespace GX {

FifoObj* Init(void* buffer, u32 size);
void SetVtxDesc(Attr attr, AttrType type);
void ClearVtxDesc();
void SetVtxAttrFmt(VtxFmt vtxfmt, Attr attr, CompCnt cnt, CompType type, u8 frac);
void SetNumTexGens(u8 nr);
void Begin(Primitive type, VtxFmt vtxfmt, u16 nverts);
void SetCullMode(CullMode mode);
void SetNumChans(u8 nChans);
void SetChanCtrl(ChannelID chan, bool enable, ColorSrc amb_src, ColorSrc mat_src, u32 light_mask, DiffuseFn diff_fn, AttnFn attn_fn);
void SetChanMatColor(ChannelID chan, Color color);
void SetTevOp(TevStageID id, TevMode mode);
void SetAlphaCompare(Compare comp0, u8 ref0, AlphaOp op, Compare comp1, u8 ref1);
void SetAlphaUpdate(bool enable);
void SetColorUpdate(bool enable);
void SetTevOrder(TevStageID stage, TexCoordID coord, TexMapID map, ChannelID IDcolor);
void SetNumTevStages(u8 num);
void SetFog(FogType type, float startz, float endz, float nearz, float farz, Color color);
void SetBlendMode(BlendMode type, BlendFactor src_factor, BlendFactor dst_factor, LogicOp op);
void SetZMode(bool compare_enable, Compare func, bool update_enable);
void SetZCompLoc(bool before_tex);
void LoadPosMtxImm(const float mtx[3][4], u32 pnidx);
void SetCurrentMtx(u32 mtx);
void LoadPosMtxIndx(u32 indx);
OS::Thread* GetCurrentThread(); //8016d39c
void SetDrawSync(u16 token); //sets a token, which will be stored in a reg when it reaches the end of the pipeline
u16 ReadDrawSync(); //if matches token set with, geometry has been rendered
void SetLineWidth(u8 width, TexOffset offset);

}//namespace GX
#endif