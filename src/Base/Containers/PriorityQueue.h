#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Memory/Allocators.h"

#if ENABLE_STL_PRIORITY_QUEUE

#    include <queue>

template<typename T, typename C = Vector<T>, class CMP = std::less<typename C::value_type>>
using PriorityQueue = std::priority_queue<T, C, CMP>;

#elif ENABLE_BOOST_PRIORITY_QUEUE

#    include <boost/heap/priority_queue.hpp>

template<typename T, typename A = HeapAllocator<T>, class C = boost::heap::compare<T>>
using PriorityQueue = boost::heap::priority_queue<T, A, C>;

#endif

#endif
