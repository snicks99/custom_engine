#ifndef TYPES_H
#define TYPES_H

/****************************************************************************
 Includes
 */

#include "Common/CompilerDefs.h"

#include <stdint.h>
#include <inttypes.h>
#include <limits>

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

using bool8 = bool;

#define SZFMTD       "%" PRIuPTR
#define UI64LIT( N ) UINT64_C( N )

constexpr inline word_t INVALID_WORD{ std::numeric_limits<word_t>::max() };

constexpr inline int8  INVALID_INT8{ std::numeric_limits<int8>::max() };
constexpr inline int16 INVALID_INT16{ std::numeric_limits<int16>::max() };
constexpr inline int32 INVALID_INT32{ std::numeric_limits<int32>::max() };
constexpr inline int64 INVALID_INT64{ std::numeric_limits<int64>::max() };

constexpr inline uint8  INVALID_UINT8{ std::numeric_limits<uint8>::max() };
constexpr inline uint16 INVALID_UINT16{ std::numeric_limits<uint16>::max() };
constexpr inline uint32 INVALID_UINT32{ std::numeric_limits<uint32>::max() };
constexpr inline uint64 INVALID_UINT64{ std::numeric_limits<uint64>::max() };

constexpr inline float32 INVALID_FLOAT32{ std::numeric_limits<float32>::max() };
constexpr inline float64 INVALID_FLOAT64{ std::numeric_limits<float64>::max() };

#endif
