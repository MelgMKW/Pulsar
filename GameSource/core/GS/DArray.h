#ifndef _DARRAY_
#define _DARRAY_
#include <types.hpp>


namespace GS {

typedef void (*ArrayElementFreeFn)(void* elem);

struct DArray {
    int count;
    int capacity;
    int elemsize;
    int growby;
    ArrayElementFreeFn elemfreefn;
    void* list; //array of elements
};

}//namespace GS


#endif