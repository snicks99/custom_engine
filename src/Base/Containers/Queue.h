#ifndef QUEUE_H
#define QUEUE_H

#include "Memory/Allocators.h"
#include "Containers/Vector.h"

#if ENABLE_STL_QUEUE

#    include "Containers/Deque.h"

#    include <queue>

template<typename T, typename C = Deque<T>>
using Queue = std::queue<T, C>;

#elif ENABLE_BOOST_QUEUE

#    include <boost/lockfree/queue.hpp>

template<typename T, typename A = HeapAllocator<T>>
using Queue = boost::lockfree::queue<T, A>;

#endif

#endif
