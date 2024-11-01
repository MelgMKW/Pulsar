#ifndef _EGG_SCREEN_
#define _EGG_SCREEN_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Frustum.hpp>

namespace EGG {

//_sinit_ at 8023e700
struct ViewPort { //unofficial
    float left;
    float top;
    float wd;
    float ht;
    float nearz;
    float farz;
};

struct EFBParams {
    ViewPort ViewPort;
    Vector2f scissorBoxOffset; //0x18
};

class Screen : public Frustum {
public:
    struct InitParams {
        static InitParams* params; //802a3ee8
        //these are the values of the root screen, but also the values all screens use by default
        u16 width4_3; //608 
        u16 height4_3; //480 most often
        float efbScreenWidthRatio4_3; //efbWidth / screenWidth
        float efbScreenHeightRatio4_3;

        u16 width16_9; //0xc used by 8023e53c 832, which is the value used by textures
        u16 height16_9; //0xe 456
        float efbScreenWidthRatio16_9; //0x10 efbWidth / screenWidth
        float efbScreenHeightRatio16_9; //0x14

        u16 efbWidth; //0x18
        u16 efbHeight;
        float unknown_0x1c;
        float unknown_0x20;

    };
    static u32 tvMode; //80386F10 1 for 16/9
    static bool isRootCreated; //80386F30
    static Screen* root; //80386F14
    static Screen defaultRoot; //803843b0
    static void(*SetTVModeCB)(void*); //80386F18
    static void Initialize(u16* maxWidths, u16* maxHeights, Screen* root = nullptr); //8023d0f8 4/3 & 16/9, this func is used to set the params, and sets the root
    Screen(); //8023d2b4
    Screen(Screen* parent, u32 r5, float xPos, float yPos, float width, float height); //8023d380
    Screen(const Screen& other); //8023d448
    void CopyFromAnoter(const Screen& other); //8023d840

    EFBParams& GetEFBParams(); //8023dbd8

    bool IsChangeEFB(); //8023dc34
    void GetPosSizeInEFB(); //8023d934
    void CalcMtxForDrawQuad(Matrix34f& dest, float xPos, float yPos, float xScale, float yScale); //8023ddd4
    void FillBufferGX(u32 clearEfbFlags, GX::Color color, u32 unused); //8023de7c
    void GetGlobalPos(float* xPosDest, float* yPosDest); //8023e040
    Screen* GetParent(); //8023e484

    void SetTVMode(u32 mode); //8023e48c 0 4/3, 1 16/9
    void SetTVModeDefault(); //8023e53c

    ~Screen() override; //8022014c vtable 802a3f0c
    void LoadDirectly() override; //8023d4e8
    void CopyToG3D(g3d::Camera& dest) override; //8023d67c


    Screen* parent; //0x3c
    Vector2f position; //0x40
    EFBParams efbParams; //0x48
}; //0x68
}//namespace EGG
#endif