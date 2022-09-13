#ifndef FIXED_VALUE_H
#define FIXED_VALUE_H

#include "Common/Platform.h"
#include "Common/BaseMath.h"

#include <algorithm>

template<typename T>
struct FixVal
{
  public:
    FixVal()
        : beg{}
        , end{}
        , cur{}
    {
    }

    FixVal( const T& val )
        : beg{ val }
        , end{ val }
        , cur{ val }
    {
    }

    FixVal( const FixVal& r )
        : beg{ r.beg }
        , end{ r.end }
        , cur{ r.cur }
    {
    }

    FixVal( FixVal&& r ) noexcept
        : beg{ std::move( r.beg ) }
        , end{ std::move( r.end ) }
        , cur{ std::move( r.cur ) }
    {
    }

    void Init()
    {
        cur = beg = end;
    }

    void Lerp( float32 alpha )
    {
        cur = Math::Lerp( beg, end, alpha );
    }

    FORCE_INLINE FixVal&
    operator=( const T& val ) noexcept
    {
        reset();
        end = val;
        return *this;
    }

    FORCE_INLINE void operator+=( const T& val ) noexcept
    {
        reset();
        end += val;
    }
    FORCE_INLINE void operator-=( const T& val ) noexcept
    {
        reset();
        end -= val;
    }
    FORCE_INLINE void operator*=( const T& val ) noexcept
    {
        reset();
        end *= val;
    }
    FORCE_INLINE void operator/=( const T& val ) noexcept
    {
        reset();
        end /= val;
    }

    template<typename OtherT>
    constexpr bool8 operator==( const FixVal<T>& val ) const noexcept
    {
        return end == val.end;
    }

    constexpr bool8 operator==( const T& val ) const noexcept { return end == val; }
    constexpr bool8 operator!=( const T& val ) const noexcept { return end != val; }
    constexpr bool8 operator<( const T& val ) const noexcept { return end < val; }
    constexpr bool8 operator>( const T& val ) const noexcept { return end > val; }
    constexpr bool8 operator<=( const T& val ) const noexcept { return end <= val; }
    constexpr bool8 operator>=( const T& val ) const noexcept { return end >= val; }

    FORCE_INLINE void reset() { beg = cur; }

  public:
    T beg;
    T end;
    T cur;
};

#endif
