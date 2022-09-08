#ifndef SET_H
#define SET_H

#include "Memory/Allocators.h"

#if ENABLE_STL_SET

#    include <set>

template<typename Key,
         typename Compare = std::less<Key>,
         class Allocator  = HeapAllocator<Key>>
using Set = std::set<Key, Compare, Allocator>;

#elif ENABLE_BOOST_SET

#    include <boost/container/set.hpp>

template<typename Key,
         typename Compare = std::less<Key>,
         class Allocator  = HeapAllocator<Key>>
using Set = boost::container::set<Key, Compare, Allocator>;

#endif

#endif
