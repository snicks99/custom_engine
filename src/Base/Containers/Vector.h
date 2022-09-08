#ifndef VECTOR_H
#define VECTOR_H

#include "Common/ProjectConfig.h"
#include "Memory/Allocators.h"

#if ENABLE_STL_VECTOR

#    include <vector>

template<typename T, class Allocator = HeapAllocator<T>>
using Vector = std::vector<T, Allocator>;

#elif ENABLE_BOOST_VECTOR

#    include <boost/container/vector.hpp>

template<typename T, class A = void>
using Vector = boost::container::vector<T, A, void>;

#else

#    error

#endif

#endif
