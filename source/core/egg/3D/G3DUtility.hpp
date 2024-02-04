#ifndef _EGG_G3DUTILITY_
#define _EGG_G3DUTILITY_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

namespace EGG {
using namespace nw4r;
namespace G3DUtility {
struct SearchNodes {
    static SearchNodes sInstance; //802578f8
    int (*SearchNodes)(g3d::ResMdl resMdl, const char* prefix, u32 r5, u16* r6, u32 max); //802287e4
    int (*SearchMaterials)(g3d::ResMdl resMdl, const char* prefix, u32 r5, u16* r6, u32 max); //802288e0
    int (*CountTextureLinkByName)(g3d::ResMdl resMdl, const char* name, bool isFullName, u16* r6, u32 max); //802289dc commonly called "texture refs"
    //counts the textures with the same name as the char arg; if r5 is false, the name is assumed to be just a prefix (uses strstr and not strcmp)
};

u32 SetMaterialTexObj(g3d::ResMat resMat, g3d::ScnMdl::CopiedMatAccess* copiedMatAccess, const char* texName,
    GX::TexObj* texObj, bool setFilterAndWrapMode, u32 r8, u8 countSetFilterAndWrap); //80228b18 returns number of modified textures

}//namespace G3DUtility

}//namespace EGG

#endif