#ifndef _LENSFLARE_
#define _LENSFLARE_

#include <kamek.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/nw4r/ut.hpp>
#include <core/egg/3D/Texture.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

using namespace nw4r;
class GameScreenEffectsMgr;
class LensFlareMgr;

class LensFlare : public StatePtmfTrigger<LensFlare> {
public:

    class Texture {
    public:
        Texture(); //8054b094
        void CopyFromEFB(); //8054b1a8
        void SetPosition(float left, float top); //8054b164
        EGG::CapTexture* capTexture;
        u16 right; //0x4
        u16 bottom;
        u16 left; //0x8
        u16 top;
        u8 unknown_0xC[4];
        u8 unknown_0x10[8];
    };
    struct QuadDrawerParams {
        u16 texIdx;
        float scale;
        ut::Color color;
    }; //0xC

    class QuadDrawer {
    public:
        QuadDrawer(const QuadDrawerParams& params, LensFlareMgr* flare); //8054ab2c
        void Draw(u8 alpha); //8054adf0 draws a quad using the viewMtx, the tevColor
        u32 idx; //0x0
        float width; //0x14
        float height; //0x18
        Mtx34 viewMtx; //0x1c
        ut::Color tevColor; //0x4c alpha not used
        u8 unknown_0x50[4];
    }; //0x54

    enum State {
        NO_TARGET, //position doesn't update based on the position of LensFX but rather stays constant
        FADE_OUT_PREPARE,
        FADE_OUT, //alpha decreases to 0
        NORMAL_STATE, //the state when the target is in view
    };
    LensFlare(LensFlareMgr* flare, u32 idx); //8054b310
    virtual ~LensFlare() override; //8054b578 vtable 808b3e70
    void Update(); //8054bb08
    void DrawQuads(); //8054be2c
    void CopyEFBToTexture(); //8054be94

    void OnNoFollowStart(); //8054b870
    void NoFollowUpdate(); //8054b8c0
    void OnFadeOutPrepareStart(); //8054b62c
    void FadeOutPrepareUpdate(); //8054b66c
    void OnFadeOutStart(); //8054b7c4
    void FadeOutUpdate(); //8054b7c8
    void OnNormalStateStart(); //8054b91c
    void NormalStateUpdate(); //8054b9cc

    LensFlareMgr* mgr; //0x20
    u16 allColorsAlpha; //0x24 alpha of all the quads
    u8 padding[2];
    Vec2 screenPos; //0x28
    u32 idx; //0x30
    Vec3* targetPos; //0x34
    u8 unknown_0x34[0x10];
    QuadDrawer* drawers[21]; //0x44
    Texture* texture; //0x98
    u8 unknown_0x9c[4];
    bool isTargetInView; //0xa0 if true
    u8 padding2[3];
}; //0xa4

class LensFXObj {
public:
    const KMP::Holder<GOBJ>& gobjHolder;
    Vec3 position; //0x4
    u8 unknown_0x10[0x18 - 0x10]; //0x10
};

class LensFlareMgr {
public:
    LensFlareMgr(GameScreenEffectsMgr* mgr, u32 screenCount); //8054bf50
    virtual ~LensFlareMgr(); //8054c350 vtable 808b3e64
    u32 GetBRRESTexCount() const; //8054c414
    const void* GetRawTexture(int texIdx) const; //8054c41c
    u16 GetTextureWidth(int texIdx) const; //8054c498
    u16 GetTextureHeight(int texIdx) const; //8054c500
    const char* GetTextureName(int texIdx) const; //8054c568
    GX::TexFmt* GetTextureFormat(int texIdx) const; //8054c5e4
    void Update(); //8054c5f4
    void DrawTextures(); //8054c660
    void Draw(); //8054c7b0 inline
    void AddLensFX(const KMP::Holder<GOBJ>& gobjHolder); //8054c8f0 inlined
    const Vec3* GetTargetPosition(u32 lensFlareIdx, Vec3* initialScreenPos) const; //8054c97c returns absolutePosition of the target (lensFX)
    u8 GetScreenPosition(u32 lensFlareIdx, Vec3* screenPos, const Vec3* targetPos) const; //8054c97c returns false if the target is not in view
    void EnableExternalLens(const Vec3& externalPosition); //8054c958
    void CopyEFBToTextures(); //8054c834 inlined
    ut::List lensFXObjList; //0x4
    g3d::ResFile lensFlareBRRES; //0x10
    GX::TexObj* lensFlareTexObjs; //0x14
    GX::TexFmt* lensFlareTexFmts; //0x18
    LensFlare** lensFlares; //0x1c size screenCount
    u32 screenCount; //0x20
    GameScreenEffectsMgr* cameraEffectsMgr; //0x24
    bool useSomePosition;
    u8 padding[3];
    bool useExternalLensAsFallback; //0x28 this is used if the sun itself is moving, so the lens needs to move with it; used by SunDS::Update
    Vec3 externalLensPosition; //0x2c
    float* efbXFBWidthRatio; //0x38 efbWidth/xfbWidth
    float* screenEFBWidthRatio; //0x3c screenWidth/EFBWidth
}; //0x40

#endif