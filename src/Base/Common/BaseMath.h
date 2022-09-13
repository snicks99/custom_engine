#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "Common/Defines.h"

#include <cmath>

/****************************************************************************
 Separator
 */

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_4
#    define M_PI_4 0.785398163397448309616
#endif

/****************************************************************************
 Separator
 */

namespace Math
{
    template<typename T>
    inline void Clamp( T& val, const T& min, const T& max ) noexcept
    {
        val = std::clamp( val, min, max );
    }

    template<typename T>
    inline T Lerp( const T& a, const T& b, float32 t ) noexcept
    {
        return a + t * ( b - a );
    }
}    // namespace Math

/****************************************************************************
 Separator
 */
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

#endif
