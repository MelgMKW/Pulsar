#ifndef _NW4R_LYTARCRESOURCEACCESSOR_
#define _NW4R_LYTARCRESOURCEACCESSOR_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/ut/Font.hpp>
#include <core/rvl/arc/arc.h>
#include <core/nw4r/lyt/ResourceAccessor.hpp>

namespace nw4r {
namespace lyt {

class FontRefLink {
public:
    FontRefLink(); //80083f20
    void Set(char const *fontName, ut::Font *); //80083f40
    ut::LinkListNode link;
    char fontName[0x80]; //0x8
    ut::Font *font;
}; //0x8c

class ArcResourceAccessor {
    void FindNameResource(ARCHandle *handle, const char *stringPool); //80083d10
    void *GetResourceSub(ARCHandle *handle, const char *folderName, u32 type, const char *fileName, u32 r7); //80083de0
    ARCHandle handle;
    void *arcBuffer;
    ut::LinkList<FontRefLink, offsetof(FontRefLink, link)> fontList;
    char folderName[0x80];
}; //0x9C

class ArcResourceLink {
public:
    void Set(void *rawFile, const char *folderName); //80084000
    ut::LinkListNode link;
    ArcResourceAccessor accessor;
}; //0XA4

class MultiArcResourceAccessor : public ResourceAccessor {
public:
    MultiArcResourceAccessor(); //80084070
    ~MultiArcResourceAccessor() override; //800840e0 vt 80273820
    void *GetResource(ResType type, const char *fileName, u32 *size = 0) override; //800841b0
    ut::Font *GetFont(const char *fontName) override; //80084270
    void Attach(ArcResourceLink *link); //80084170
    void AttachFont(FontRefLink *link); //80084230

    ut::LinkList<ArcResourceLink, offsetof(ArcResourceLink, link)> arcList; //0x4 handles at +0x8
    ut::LinkList<FontRefLink, offsetof(FontRefLink, link)> fontList; //0x10
};
}//namespace lyt
}//namespace nw4r

#endif