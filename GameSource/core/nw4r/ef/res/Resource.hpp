#ifndef _NW4R_EF_RESOURCE_
#define _NW4R_EF_RESOURCE_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/ef/LinkedObject.hpp>

namespace nw4r {
namespace ef {

class TextureData;
class EmitterResource;
class ResEmitter;

struct EffectProject { //BREFF
    u32 headersize;
    ut::Link projectlink;
    u16 projectnameLen;
    u16 padding;
    u8 projectname[4];
};

struct TextureProject { //BREFT
    u32 headersize;
    ut::Link projectlink;
    u16 projectnameLen;
    u16 padding;
    u8 projectname[4];
};

class Resource {
public:
    static Resource instance; //802b7590
    static Resource* GetInstance(); //80035940
    ResEmitter FindEmitter(const char* name, EffectProject* project = nullptr) const; //80035eb0
    TextureProject* AddTexture(u8* data); //80035f60 adds breft
    u32 RelocateCurveTexture(u8* cmdPtr, const EmitterResource* res = nullptr); //80035fe0
    u32 RelocateCurveChild(u8* cmdPtr, const EmitterResource* res = nullptr); //80036100
    u32 RelocateCommand(); //80036200
    bool RemoveEffectProject(EffectProject* data); //80036440 removes breff
    bool RemoveTextureProject(TextureProject* project); //800364e0 removes breft


    EffectProject* Add(u8* data); //80035d70 adds breff
    ut::List BREFFList;
    u32 emitterCount;
    ut::List BREFTList;
    u32 textureCount;
};

TextureData* BreftSearchName(TextureProject* project, const char* searchName); //80035cb0
EmitterResource* BreffSearchName(EffectProject* project, const char* searchName); //80035ac0

}//namespace ef
}//namespace nw4r
#endif 