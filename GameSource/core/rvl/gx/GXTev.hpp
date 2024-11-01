#ifndef _GXTEV_
#define _GXTEV_

#include <types.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace GX {
void SetTevColorIn(TevStageID stage, TevColorArg a, TevColorArg b, TevColorArg c, TevColorArg d); //80171ce0
void SetTevColorOp(TevStageID stage, TevOp op, TevBias bias, TevScale scale, BOOL clamp, TevRegID out_reg); //80171d60 how should the inputs be combined

void SetTevAlphaIn(TevStageID stage, TevAlphaArg a, TevAlphaArg b, TevAlphaArg c, TevAlphaArg d); //80171d20 how should the inputs be combine
void SetTevAlphaOp(TevStageID stage, TevOp op, TevBias bias, TevScale scale, BOOL clamp, TevRegID out_reg); //80171db8 how should the inputs be combined


/*
outReg =[d +- (a * (1 - c) + b * c) + bias] * scale then clamped, IF TevOP is Sub or Add
outReg = d + (a OP b ? c : 0) if TevOP is a COMP; a and b are compared and c or 0 are used based on the result


for example
GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_KONST, GX_CC_TEXC, GX_CC_C2);
GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVREG2);
leads to REG2 = textureColor + REG2; a is 0, b is 1, c is texColor, d is reg2

GXSetTevColorIn(GX_TEVSTAGE0, GX_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
leads to REGPPREV = textureColor - rasterizerColor

*/




}//namespace GX
#endif