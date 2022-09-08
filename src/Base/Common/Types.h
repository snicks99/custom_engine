#ifndef TYPES_H
#define TYPES_H

/****************************************************************************
 Includes
 */

#include "Common/CompilerDefs.h"

#include <stdint.h>
#include <inttypes.h>

/****************************************************************************
 Separator
 */

using word_t = size_t; /** the idea is if we have x32 use 4 bytes and x64 use 8 bytes - niccco */

using int8  = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using float32 = float;
using float64 = double;

using char8  = char;
using char16 = char16_t;

using bool8  = bool;
using bool32 = uint32;

using HashID = uint32;

#define SZFMTD "%" PRIuPTR
#define UI64LIT(N) UINT64_C(N)


template<typename T>
struct dependant_false
{
    static constexpr bool value = false;
};

template<typename T>
constexpr bool dependant_false_v = dependant_false<T>::value;

#endif
