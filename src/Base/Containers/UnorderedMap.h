#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "Memory/Allocators.h"

#if ENABLE_STL_UNORDERED_MAP

#    include <unordered_map>

template<typename Key,
         typename T,
         typename Hash     = std::hash<Key>,
         typename KeyEqual = std::equal_to<Key>,
         class Allocator   = HeapAllocator<std::pair<const Key, T>>>
using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

template<typename Key,
         typename T,
         typename Hash     = std::hash<Key>,
         typename KeyEqual = std::equal_to<Key>,
         class Allocator   = HeapAllocator<std::pair<const Key, T>>>
using UnorderedMultiMap = std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>;

#elif ENABLE_BOOST_UNORDERED_MAP

#    include <boost/unordered_map.hpp>

template<typename Key,
         typename T,
         typename Hash     = boost::hash<Key>,
         typename KeyEqual = std::equal_to<Key>,
         class Allocator   = HeapAllocator<std::pair<const Key, T>>>
using UnorderedMap = boost::unordered::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

template<typename Key,
         typename T,
         typename Hash     = boost::hash<Key>,
         typename KeyEqual = std::equal_to<Key>,
         class Allocator   = HeapAllocator<std::pair<const Key, T>>>
using UnorderedMultiMap = boost::unordered::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>;

#endif

#endif
