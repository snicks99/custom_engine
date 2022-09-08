#ifndef TIME_TYPE_H
#define TIME_TYPE_H

#include "Common/Defines.h"

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

using ClockType = int64;

#    define GET_TIMESTAMP( now ) QueryPerformanceCounter( (LARGE_INTEGER*)( &now ) )

#else

using ClockType = int64;

#    define GET_TIMESTAMP( now ) now = 0

#endif

CONSTEXPR_INLINE ClockType SEC_AS_NS{ 1'000'000'000 };
CONSTEXPR_INLINE ClockType SEC_AS_US{ 1'000'000 };
CONSTEXPR_INLINE ClockType SEC_AS_MS{ 1'000 };

constexpr ClockType CONVERT_MS_TO_US( float32 ms )
{
    return static_cast<ClockType>( ms * 1'000.0f );
}

constexpr float32 CONVERT_US_TO_MS( ClockType us )
{
    return static_cast<float32>( us ) / 1'000.0f;
}

constexpr ClockType CONVERT_S_TO_US( float32 s )
{
    return static_cast<ClockType>( s * 1'000'000.0f );
}

constexpr float32 CONVERT_US_TO_S( ClockType us )
{
    return static_cast<float32>( us ) / 1'000'000.0f;
}

consteval float32 CONVERT_US_TO_S_EVAL( ClockType us )
{
    return static_cast<float32>( us ) / 1'000'000.0f;
}

#endif
