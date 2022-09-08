#ifndef LIST_H
#define LIST_H

#include "Memory/Allocators.h"

#if ENABLE_STL_LIST

#    include <list>

template<typename T, class Allocator = HeapAllocator<T>>
using List = std::list<T, Allocator>;

#elif ENABLE_BOOST_LIST

#    include <boost/container/list.hpp>

template<typename T, class Allocator = HeapAllocator<T>>
using List = boost::container::list<T, Allocator>;

#endif

#endif
