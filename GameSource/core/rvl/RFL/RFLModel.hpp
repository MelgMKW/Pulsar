#ifndef _RFLMODEL_
#define _RFLMODEL_
#include <types.hpp>
#include <core/rvl/RFL/RFLTypes.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/rvl/gx/GXEnum.hpp>

//Revolution Face Library
namespace RFL {

struct CharModel {
    Mtx viewMtx; //0x0
    Mtx invertedViewMtx; //0x30
    u8 dummy[0x88 - 0x60]; //0x60
}; //0x88

struct DrawSetting {
    bool lightEnable;
    u32 lightMask;
    GX::DiffuseFn diffFn;
    GX::AttnFn attnFn;
    GX::Color ambientColor;
    bool zCompLoc;
};

struct DrawCoreSetting {
    u8 txcGenNum;
    GX::TexCoordID	txcID;
    GX::TexMapID texMapID;
    u8 tevStageNum;
    GX::TevSwapSel	tevSwapTable;
    GX::TevKColorID	tevKColorID;
    GX::TevRegID tevOutRegID;
    GX::PosNrmMtx posNrmMtxID;
    bool reverseCulling;
};


GX::Color GetFavoriteColor(FavoriteColor favoriteColor); //800c0ad0
u32 GetModelBufferSize(Resolution resolution, u32 expressionFlag); //inlined in ScnRfl::Construct 8024451c
void SetMtx(CharModel* charModel, const Mtx viewMtx); //800c0a70
void DrawOpa(const CharModel* charModel); //800c0e10
void DrawOpa(const CharModel* charModel); //800c0e20
void DrawOpaCore(const CharModel* charModel, const DrawCoreSetting* setting); //800c0f90
void DrawXluCore(const CharModel* charModel, const DrawCoreSetting* setting); //800c14a0
void LoadDrawSetting(const DrawSetting* setting); //800c0b20

void SetExpression(CharModel* charModel); //800c0ac0
}//namespace RFL



#endif