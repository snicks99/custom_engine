#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include "Memory/Allocators.h"

#if ENABLE_STL_UNORDERED_SET

#    include <unordered_set>

template<typename Key,
         typename Hash     = std::hash<Key>,
         typename KeyEqual = std::equal_to<Key>,
         class Allocator   = HeapAllocator<Key>>
using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

#elif ENABLE_BOOST_UNORDERED_SET

#    include <boost/unordered_set.hpp>

template<typename Key,
         typename Hash     = boost::hash<Key>,
         typename KeyEqual = std::equal_to<Key>,
         class Allocator   = HeapAllocator<Key>>
using UnorderedSet = boost::unordered_set<Key, Hash, KeyEqual, Allocator>;

#endif

#endif
