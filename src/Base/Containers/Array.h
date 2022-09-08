#ifndef ARRAY_H
#define ARRAY_H

#include "Common/ProjectConfig.h"

#if ENABLE_STL_ARRAY

#    include <array>

template<typename T, std::size_t N>
using Array = std::array<T, N>;

#elif ENABLE_BOOST_ARRAY

#    include <boost/array.hpp>

template<typename T, std::size_t N>
using Array = boost::array<T, N>;

#endif

#endif
