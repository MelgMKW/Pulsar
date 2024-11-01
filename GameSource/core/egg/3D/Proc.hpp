#ifndef _EGG_PROC_
#define _EGG_PROC_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

using namespace nw4r;

namespace EGG {

class ScnProcHolder;

class IScnProc {
    void CreateProcs(u16 procCount, EGG::Allocator* allocator); //8022a05c
    void Configure(u16 idxOfProcToConfig, u8 priority, bool isOpa); //8022a164
    void RemoveFromScnGroup(nw4r::g3d::ScnGroup* scnGroup); //8022a294
    static void Run(g3d::ScnProc* proc, bool isOpa); //8022a314 
    void InsertProcsToScnGroup(g3d::ScnGroup* group); //8022a210

    ScnProcHolder* holders; //0x0
    u16 procCount; //0x4 = amount of holders
    u8 padding[2];
    virtual void Draw(u16 scnProcIdx); //0x8
    virtual ~IScnProc();
}; //0xC

class ScnProcHolder { //non official sets itself as the userdata of g3d::ScnProc, which when it procs, allows IScnProc (obtained via parent) to call draw with the idx
public:
    IScnProc* parent;
    g3d::ScnProc* proc;
    u16 idx;
    bool isOpa;
    u8 unknown_0xB;
}; //0xC



}//namespace EGG
#endif