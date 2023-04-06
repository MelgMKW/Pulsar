#ifndef _EGG_G3DUTILITY_
#define _EGG_G3DUTILITY_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

namespace EGG {
namespace G3DUtility {
struct SearchNodes {
    static SearchNodes sInstance; //802578f8
    int (*SearchNodes)(nw4r::g3d::ResMdl resMdl, const char *prefix, u32 r5, u16 *r6, u32 max); //802287e4
    int (*SearchMaterials)(nw4r::g3d::ResMdl resMdl, const char *prefix, u32 r5, u16 *r6, u32 max); //802288e0
    int (*CountTextureLinkByName)(nw4r::g3d::ResMdl resMdl, const char *name, bool isFullName, u16 *r6, u32 max); //802289dc
    //counts the textures with the same name as the char arg; is r5 is false, the name is assumed to be just a prefix (uses strstr and not strcmp)
};
};

}//namespace EGG

#endif