#ifndef FIXED_UPDATE_H
#define FIXED_UPDATE_H

#include "Clock/TimeType.h"

CONSTEXPR_INLINE uint32 FIXED_UPDATE_FRAMES{ 30 };

CONSTEXPR_INLINE ClockType FIXED_UPDATE_US{ SEC_AS_US / FIXED_UPDATE_FRAMES };
CONSTEXPR_INLINE float32   FIXED_UPDATE_SC{ CONVERT_US_TO_S( FIXED_UPDATE_US ) };

CONSTEXPR_INLINE ClockType MAX_FRAME_SKIP{ FIXED_UPDATE_US * 10 };

#endif
