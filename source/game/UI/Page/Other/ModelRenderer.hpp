#ifndef _MODELRENDERERPAGE_
#define _MODELRENDERERPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>

enum BackGroundModelType {
    BACKGROUND_STOPWATCH,
    BACKGROUND_TROPHY,
    BACKGROUND_FLAG,
    BACKGROUND_BALOON,
};
struct ModelRendererParams {
    void Reset();
    CharacterId character;
    KartId kart;
    u8 unknown_0x8[2];
    u8 padding[2];
}; //total size 0xC

class ModelRendererValues {
public:
    void SetValues(Vec2 translation, float scale); //805f8b24
    Vec2 translation;
    float scale;
}; //0xc
//_sinit_ at 805f5fe8

struct ModelRendererValuesVariant { //3types
    ModelRendererValues values[3]; //xC to traverse the array
}; //0x24

struct ModelRendererValuesAlignment { //9 variants
    ModelRendererValuesVariant variants[9]; //x24 to traverse the array
}; //0x144


struct ModelRendererValuesFormat {
    ModelRendererValuesAlignment alignments[10]; //x144 alignment
}; //total size 0xca8

class ModelRendererValuesHolder {
    void Init(); //805f5ffc
    ModelRendererValues *GetValues(CharacterId id, u32 variantType, u32 type); //805f5fa4 variant type from model control
    ModelRendererValuesFormat modelRendererValuesFormat[2]; //widePage vs non wide page
    u8 alignment[48]; //0x1950 48 for 48 characters, 0 default, 1 centered, idk others
}; //total size 0x1980

namespace Pages {
class ModelRenderer : public Page { //ID 0x7f
public:
    ModelRenderer(); //805f4fd0
    ~ModelRenderer() override; //805f51c8 vtable 808b9c00
    void OnInit() override; //0x28 805f5230
    void OnDispose() override; //0x2c 805f5504
    void OnActivate() override; //0x30 805f5520   
    void BeforeEntranceAnimations() override; //0x38 805f56d4
    void BeforeExitAnimations() override; //0x40 805f56d8
    void BeforeControlUpdate() override; //0x48 805f56dc
    int GetRuntimeTypeInfo() const override; //0x60 805f5fdc
    void RequestCharacterModel(u8 hudSlotId, CharacterId id); //805f56e0
    void RequestKartModel(u8 hudSlotId, KartId id); //805f5958
    void RequestBackgroundModel(BackGroundModelType type); //805f5984
    void SetBackgroundModelVisibility(bool isVisible); //805f5a30
    void LoadKartModelsByCharacter(u8 hudSlotId, CharacterId id); //805f570c loads the models for a character, called when a character is selected
    static u32 GetVariantType(u8 hudSlotId); //805f5a98 depends on section Id
    static u32 GetModelCount(SectionId sectionId); //805f5d58
    GXTexObj *GetModelTexObj(u8 hudSlotId); //805f5a4c for karts and characters
    GXTexObj *GetBackgroundModelTexObj() const; //805f5a70
    ManipulatorManager manipulatorManager; //0x44
    ModelRendererParams params[4]; //one per local player
    u8 modelCount; //0x84
    u8 padding[3];
    float unknown_0x88;//0x88
    u8 unknown_0x8C[0x94 - 0x8C];
    ModelRendererValuesHolder ModelRendererValuesHolder; //0x94
}; //1a14
size_assert(ModelRenderer, 0x1A14);
}//namespace Pages
#endif