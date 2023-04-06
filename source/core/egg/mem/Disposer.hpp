#ifndef _EGGDISPOSER_
#define _EGGDISPOSER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>

namespace EGG {
class Heap;
class Disposer { //a way to garbage collect objects when a heap is destroyed
    friend class Heap;
protected:
    Disposer(); //8021a0f0
    virtual ~Disposer(); //8021a144 vtable 802a2b48

private:
    Heap *heap;
    nw4r::ut::LinkListNode link; //the heap traverses the link list on destruction and calls all the dtors
}; // Total size 0x10

template<class T>
class TDisposer : public Disposer {
public:
    //code for the dtor
    ~TDisposer() override;
    /*code for it
        T::sInstance = NULL;
        delete(t);
        Disposer::~Disposer();
    */
};
size_assert(Disposer, 0x10);
}//namespace EGG


#endif