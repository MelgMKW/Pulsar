#ifndef _NW4R_LYTGROUP_
#define _NW4R_LYTGROUP_
#include <types.hpp>
#include <core/nw4r/lyt/Pane.hpp>
#include <core/nw4r/lyt/resources.hpp>

namespace nw4r {
namespace lyt {
namespace detail {
struct PaneLink {
    ut::LinkListNode link;
    Pane *target;
};
}//namespace detail

class Group {
public:
    Group(); //80079910
    Group(const res::Group *src, Pane *rootPane); //80079980
    virtual ~Group();  //80079aa0 vtable 802734b0
    void AppendPane(Pane *pane); //80079b50
    ut::LinkListNode link; //0x4
    ut::LinkList<detail::PaneLink, offsetof(detail::PaneLink, link)> paneList;
    char name[0x11]; //0x18
    u8 isUserAllocated; //0x29
    u8 padding[2];
}; //total size 0x2c

class GroupContainer {
public:
    GroupContainer() {};
    ~GroupContainer(); //80079be0
    void AppendGroup(Group *group); //80079cb0
    Group *FindGroupByName(const char *name); //80079cf0
    ut::LinkList<Group, offsetof(Group, link)>  groupList;
};
}//namespace lyt
}//namespace nw4r
#endif