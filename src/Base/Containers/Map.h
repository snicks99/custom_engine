#ifndef MAP_H
#define MAP_H

#include "Memory/Allocators.h"

#if ENABLE_STL_MAP

#    include <map>

template<typename Key,
         typename T,
         class Compare   = std::less<Key>,
         class Allocator = HeapAllocator<std::pair<const Key, T>>>
using Map = std::map<Key, T, Compare, Allocator>;

template<typename Key,
         typename T,
         class Compare   = std::less<Key>,
         class Allocator = HeapAllocator<std::pair<const Key, T>>>
using MultiMap = std::multimap<Key, T, Compare, Allocator>;

#elif ENABLE_BOOST_MAP

#    include <boost/container/map.hpp>

template<typename Key,
         typename T,
         class Compare   = std::less<Key>,
         class Allocator = HeapAllocator<std::pair<const Key, T>>>
using Map = boost::container::map<Key, T, Compare, Allocator>;

template<typename Key,
         typename T,
         class Compare   = std::less<Key>,
         class Allocator = HeapAllocator<std::pair<const Key, T>>>
using MultiMap = boost::container::multimap<Key, T, Compare, Allocator>;

#endif

#endif
