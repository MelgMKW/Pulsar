
#ifndef _NW4R_UTLINKLIST_
#define _NW4R_UTLINKLIST_
#include <types.hpp>
#include <core/nw4r/ut/Misc.hpp>


namespace nw4r {
namespace ut {

class LinkListNode : private NonCopyable {
public:
    LinkListNode* next;
    LinkListNode* prev;
}; // Total size 0x8
size_assert(LinkListNode, 0x8);

namespace detail {
class LinkListImpl : private NonCopyable {
public:

    class IteratorImpl;

    explicit LinkListImpl() {
        count = 0;
        node.next = &node;
        node.prev = &node;
    }

    ~LinkListImpl(); //800af210 just clears the list
    u32 GetSize() const { return count; }
    bool IsEmpty() const { return count == 0; }

    void Clear(); //800af2f0
    IteratorImpl Erase(IteratorImpl itFirst, IteratorImpl itLast);//800af2a0 removes in btw
    IteratorImpl Erase(LinkListNode* node); //800af370 removes from the list 
    IteratorImpl Erase(IteratorImpl it) {
        IteratorImpl itNext=it;
        ++itNext;
        return Erase(it, itNext);
    }
    IteratorImpl LinkListImpl::Insert(IteratorImpl it, LinkListNode* node); //800af340


    void PopFront() { this->Erase(GetBeginIter()); }
    void PopBack() { this->Erase(--GetEndIter()); }

    class IteratorImpl {
    public:
        explicit IteratorImpl(LinkListNode* ptr): ptr(ptr) {}
        explicit IteratorImpl(): ptr(nullptr) {}
        LinkListNode& operator*() const { return *ptr; }
        LinkListNode* operator->() const { return ptr; }
        IteratorImpl& operator++() { ptr = ptr->next; return *this; }
        IteratorImpl operator++(int) { const IteratorImpl it(*this); ++*this; return it; }
        IteratorImpl& operator--() { ptr = ptr->prev; return *this; }
        IteratorImpl operator--(int) { const IteratorImpl it(*this); --*this; return it; }
        friend bool operator==(IteratorImpl it1, IteratorImpl it2) { return it1.ptr == it2.ptr; }
        friend bool operator!=(IteratorImpl it1, IteratorImpl it2) { return !(it1 == it2); }

        LinkListNode* ptr;
    };
    IteratorImpl GetBeginIter() { return IteratorImpl(node.next); }
    IteratorImpl GetEndIter() { return IteratorImpl(&node); }

    int count;
    LinkListNode node; //last node of list, which is the 1st one if only 1 element ofc
};
}//namespace detail


template <class T, s32 offset>
class LinkList : private detail::LinkListImpl {
public:

    class Iterator {
    public:
        Iterator() {}
        T& operator*() const {
            return *operator->();
        }
        T* operator->() const { return GetPointerFromNode(it.operator->()); }
        Iterator& operator++() { ++it; return *this; }
        Iterator operator++(int) { const Iterator it(*this); ++*this; return it; }
        Iterator& operator--() { --it; return *this; }
        Iterator operator--(int) { const Iterator it(*this); --*this; return it; }
        friend bool operator==(Iterator it1, Iterator it2) { return it1.it == it2.it; }
        friend bool operator!=(Iterator it1, Iterator it2) { return !(it1 == it2); }

    private:
        explicit Iterator(LinkListImpl::IteratorImpl it): it(it) {}

        LinkListImpl::IteratorImpl it;
        friend class LinkList;
    };


    explicit LinkList() {}

    using detail::LinkListImpl::GetSize;
    using detail::LinkListImpl::IsEmpty;
    Iterator GetBeginIter() { return Iterator(detail::LinkListImpl::GetBeginIter()); }
    Iterator GetEndIter() { return Iterator(detail::LinkListImpl::GetEndIter()); }

    T& GetFront() { return *GetBeginIter(); }
    T& GetBack() { return *--GetEndIter(); }

    Iterator Insert(Iterator it, T* ptr) { return Iterator(detail::LinkListImpl::Insert(it.it, GetNodeFromPointer(ptr))); }
    void PushFront(T* ptr) { this->Insert(GetBeginIter(), ptr); }
    void PushBack(T* ptr) { this->Insert(GetEndIter(), ptr); }

    using detail::LinkListImpl::PopFront;
    using detail::LinkListImpl::PopBack;

    //Iterator Erase(Iterator it) { return Iterator(detail::LinkListImpl::Erase(it.it)); }
    //Iterator Erase(Iterator itFirst, Iterator itLast) { return Iterator(detail::LinkListImpl::Erase(itFirst.it, itLast.it)); }
    Iterator Erase(T* ptr) { return Iterator(detail::LinkListImpl::Erase(GetNodeFromPointer(ptr))); }
    using detail::LinkListImpl::Clear;

    static LinkListNode* GetNodeFromPointer(T* ptr) {
        return reinterpret_cast<LinkListNode*>(reinterpret_cast<u32>(ptr) + offset);
    }
    static const LinkListNode* GetNodeFromPointer(const T* ptr) {
        return reinterpret_cast<const LinkListNode*>(reinterpret_cast<u32>(ptr) + offset);
    }
    static T* GetPointerFromNode(LinkListNode* ptr) {
        return reinterpret_cast<T*>(reinterpret_cast<u32>(ptr) - offset);
    }
    static const T* GetPointerFromNode(const LinkListNode* ptr) {
        return reinterpret_cast<const T*>(reinterpret_cast<u32>(ptr) - offset);
    }
}; // Total size 0xc

}//namespace ut
}//namespace nw4r
#endif