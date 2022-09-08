#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "Common/Defines.h"

#include <cmath>

constexpr float32 CONVERT_DEG2RAD( float32 deg )
{
    return deg * ( M_PI / 180.0f );
}

constexpr float32 CONVERT_RAD2DEG( float32 rad )
{
    return rad * ( 180.0f / M_PI );
}

consteval float32 CONVERT_DEG2RAD_EVAL( float32 deg )
{
    return CONVERT_DEG2RAD( deg );
}

consteval float32 CONVERT_RAD2DEG_EVAL( float32 rad )
{
    return CONVERT_RAD2DEG( rad );
}

namespace Math
{
    template<typename T>
    inline T Lerp( const T& a, const T& b, float32 t ) noexcept
    {
        return a + t * ( b - a );
    }

    inline float32 NormalizeOrientation( float32 o )
    {
        // fmod only supports positive numbers. Thus we have
        // to emulate negative numbers
        if ( o < 0 )
        {
            float32 mod = o * -1;
            mod         = std::fmod( mod, 2.0f * static_cast<float32>( M_PI ) );
            mod         = -mod + 2.0f * static_cast<float32>( M_PI );
            return mod;
        }
        return std::fmod( o, 2.0f * static_cast<float32>( M_PI ) );
    }
}    // namespace Math

#endif
