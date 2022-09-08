#ifndef DEQUE_H
#define DEQUE_H

#include "Memory/Allocators.h"

#if ENABLE_STL_DEQUEUE

#    include <deque>

template<typename T, class A = HeapAllocator<T>>
using Deque = std::deque<T, A>;

#elif ENABLE_BOOST_DEQUEUE

#    include <boost/container/deque.hpp>

template<typename T, class A = HeapAllocator<T>>
using Deque = boost::container::deque<T, A>;

#endif

#endif
