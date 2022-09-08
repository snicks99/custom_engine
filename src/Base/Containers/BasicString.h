#ifndef BASIC_STRING_H
#define BASIC_STRING_H

#include "Memory/Allocators.h"

#if ENABLE_STL_BASIC_STRING

#    include <string>

#    if ENABLE_BOOST_BASIC_STRING
#        include <boost/algorithm/string.hpp> /** apparently, boost only give's string algorithms - niccco*/
#    endif

template<typename CharT, class Allocator = HeapAllocator<CharT>>
using BasicString = std::basic_string<CharT, std::char_traits<CharT>, Allocator>;

template<typename CharT>
using BasicStringView = std::basic_string_view<CharT, std::char_traits<CharT>>;

#endif

/* ===== Using ===== */

using String     = BasicString<char8>;
using WideString = BasicString<char16>;

using StringView     = BasicStringView<char8>;
using WideStringView = BasicStringView<char16>;

inline const String EMPTY_STRING{ "" };

#endif
