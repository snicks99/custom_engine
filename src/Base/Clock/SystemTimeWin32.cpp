#include "Clock/SystemTime.h"
#include "Debug/MGEAssert.h"

#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS

static int64   sClockFrequency{ 1 };
static float32 sClockFreqUs{ 1.0f / ( static_cast<float32>( sClockFrequency ) / SEC_AS_US ) };

void SystemTime::Init()
{
    /** get the ticks-per-second here - niccco */
    MGE_ASSERT( QueryPerformanceFrequency( (LARGE_INTEGER*)( &sClockFrequency ) ) );

    sClockFreqUs = 1.0f / ( static_cast<float32>( sClockFrequency ) / SEC_AS_US );

    GET_TIMESTAMP( mStartClock );
}

#    if 1

ClockType SystemTime::TimestampToUs( ClockType timestamp )
{
    /**
     * according to Microsoft documentation to guard against loss-of-precision
     *  convert to us before dividing by ticks-per-second - niccco
     */
    return timestamp * SEC_AS_US / static_cast<ClockType>( sClockFrequency );
}

#    else

ClockType SystemTime::TimestampToUs( ClockType timestamp )
{
    return timestamp * sClockFreqUs;
}

#    endif

ClockType SystemTime::GetUs()
{
#    if 0
    return TimestampToUs( Now() );
#    else
    return Now() * SEC_AS_US / static_cast<ClockType>( sClockFrequency );
#    endif
}

#endif
