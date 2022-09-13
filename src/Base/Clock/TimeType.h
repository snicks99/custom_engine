#ifndef TIME_TYPE_H
#define TIME_TYPE_H

#include "Common/Defines.h"

#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS

using ClockType = int64;

#    define GET_TIMESTAMP( now ) QueryPerformanceCounter( (LARGE_INTEGER*)( &now ) )

#else

using ClockType = int64;

#    define GET_TIMESTAMP( now ) now = 0

#endif

CONSTEXPR_INLINE ClockType SEC_AS_US{ 1'000'000 };
CONSTEXPR_INLINE ClockType SEC_AS_MS{ 1'000 };

constexpr ClockType CONVERT_MS_TO_US( float32 ms )
{
    return static_cast<ClockType>( ms * SEC_AS_MS );
}

constexpr ClockType CONVERT_S_TO_US( float32 s )
{
    return static_cast<ClockType>( s * SEC_AS_US );
}

constexpr float32 CONVERT_US_TO_MS( ClockType us )
{
    return static_cast<float32>( us ) / SEC_AS_MS;
}

constexpr float32 CONVERT_US_TO_S( ClockType us )
{
    return static_cast<float32>( us ) / SEC_AS_US;
}

#endif
