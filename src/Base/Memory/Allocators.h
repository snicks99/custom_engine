#ifndef ALLOCATORS_H
#define ALLOCATORS_H

#include "Memory/MMU.h"

#define AllocatorAlloc( alloc, bytes ) alloc.allocate( bytes )
#define AllocatorDealloc( alloc, p )   alloc.allocate( p )

/**
 * Can't name it as Allocator, or it will have issues with template<class Allocator>
 */

#if ENABLE_STL_ALLOCATOR
#    include <memory>

/**
 * We can use the default STL allocator, since it will call global new operator and we have it overridden - niccco
 */
template<typename T>
using HeapAllocator = std::allocator<T>;

#elif ENABLE_BOOST_ALLOCATOR

#    include <boost/container/allocator.hpp>
// #    include <boost/container/new_allocator.hpp>

template<typename T>
using HeapAllocator = boost::container::allocator<T>;

#endif

/************************************************************************/
/************************************************************************/

#endif
