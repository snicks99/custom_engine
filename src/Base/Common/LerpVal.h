#ifndef LERP_VALUE_H
#define LERP_VALUE_H

#include "Common/BaseMath.h"
#include "Clock/FixedUpdate.h"

#include <algorithm>

/** maybe a better name could be InterpolatedVal */
template<typename T>
struct LerpVal
{
  public:
    LerpVal()
        : cur{}
        , src{}
        , dst{}
        , t{ 0 }
        , alpha{ FIXED_UPDATE_SC }
    {
    }

    explicit LerpVal( const T& val, float32 t = FIXED_UPDATE_SC )
        : cur{ val }
        , src{ val }
        , dst{ val }
        , t{ 0 }
        , alpha{ t }
    {
    }

    void Lerp( float32 dt )
    {
        t   = std::clamp( t + ( dt / alpha ), 0.f, 1.f );
        cur = Math::Lerp( src, dst, t );
    }

    void SetAlpha( float32 t )
    {
        alpha = t;
    }

    FORCE_INLINE LerpVal& operator=( const T& val ) noexcept
    {
        reset();
        dst = val;
        return *this;
    }

    FORCE_INLINE void operator+=( const T& val ) noexcept
    {
        reset();
        dst += val;
    }
    FORCE_INLINE void operator-=( const T& val ) noexcept
    {
        reset();
        dst -= val;
    }
    FORCE_INLINE void operator*=( const T& val ) noexcept
    {
        reset();
        dst *= val;
    }
    FORCE_INLINE void operator/=( const T& val ) noexcept
    {
        reset();
        dst /= val;
    }

    template<typename OtherT>
    constexpr bool operator==( const LerpVal<T>& val ) const noexcept
    {
        return dst == val.dst;
    }

    constexpr bool operator==( const T& val ) const noexcept { return dst == val; }
    constexpr bool operator!=( const T& val ) const noexcept { return dst != val; }
    constexpr bool operator<( const T& val ) const noexcept { return dst < val; }
    constexpr bool operator>( const T& val ) const noexcept { return dst > val; }
    constexpr bool operator<=( const T& val ) const noexcept { return dst <= val; }
    constexpr bool operator>=( const T& val ) const noexcept { return dst >= val; }

    FORCE_INLINE operator T*() const noexcept { return dst; }

    FORCE_INLINE void init()
    {
        cur = src = dst;
        t         = 0;
    }

    FORCE_INLINE void reset()
    {
        src = cur;
        t   = 0;
    }

  public:
    T cur;
    T src;
    T dst;

    float32 t;
    float32 alpha;
};

#endif
