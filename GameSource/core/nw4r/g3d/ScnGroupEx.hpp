#ifndef _NW4R_G3D_SCNGROUPEX_
#define _NW4R_G3D_SCNGROUPEX_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/nw4r/g3d/ScnRoot.hpp>

namespace nw4r {
namespace g3d {

//the class that actually renders the identical materials
class ScnObjGatherEx : public ScnObjGather {
public:
    ~ScnObjGatherEx() override;
    virtual void SetResMdl(ResMdl);
    virtual ResMdl GetResMdl() const;
    virtual u32 TypeID() const = 0;
    virtual bool HasEqualTarget(ScnObjGatherEx* other) = 0;
};

class ScnObjGatherExScnMdl : public ScnObjGatherEx {
public:
    ScnObjGatherExScnMdl(ScnObj** bufferOpa, ScnObj** bufferXlu, u32 size, ResMdl mdl); //inlined
    ~ScnObjGatherExScnMdl() override; //80076670 vtable 80273290
    void DrawOpa(ResMdlDrawMode* forceDrawMode) override; //800759f0
    void DrawXlu(ResMdlDrawMode* forceDrawMode) override; //80075a20
    CheckStatus CheckScnObj(ScnObj* obj) override; //80075a50
    void SetResMdl(ResMdl) override; //800765c0
    ResMdl GetResMdl() const override; //80075bd0
    u32 TypeID() const override; //80076060
    bool HasEqualTarget(ScnObjGatherEx* other) override; //80075fd0

    void DrawLoop(const u8* byteCode, u32 scnObjCount, ScnObj** array, ResMdlDrawMode* forceDrawMode, bool opacity); //80075be0

    ResMdl mdl;
    const u8* byteCodeOpa;
    const u8* byteCodeXlu;
};

//A group that draws objects which share the same model data all at once
class ScnGroupEx : public ScnGroup {
public:
    //maxMdlCount: max amount of objects that can be rendered together; resMdl: the model data shared by all children
    static ScnGroupEx* Construct(G3dHeap* heap, u32* size, u32 maxChildren, u32 maxMdlCount, ResMdl resMdl); //80076070
    ScnGroupEx(G3dHeap* heap, ScnObj** array, u32 maxNumChildren, ScnObjGatherEx* collection,
        bool gatherOpa, bool gatherXlu);
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80076710 vtable 802732f8
    void G3dProc(u32 g3dproc, u32 param, void* info); //0xC 80076250
    ~ScnGroupEx() override; //0x10 80076580
    TypeObj GetTypeObj() const override; //0x14 800767b0
    const char* GetTypeName() const override; //0x18 80076780

    void SetResMdl(ResMdl resMdl); //800761d0

    ScnObjGatherEx* collection;
}; //0xe8



}//namespace g3d  
}//namespace nw4r 


#endif