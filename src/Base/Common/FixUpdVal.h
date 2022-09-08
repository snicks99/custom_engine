#ifndef FIXED_UPDATE_VALUE_H
#define FIXED_UPDATE_VALUE_H

#include "Common/Platform.h"
#include "Common/BaseMath.h"
#include "Clock/FixedUpdate.h"

#include <algorithm>

template<typename T>
struct FixUpdVal
{
  public:
    FixUpdVal()
        : cur{}
        , prv{}
        , dst{}
    {
    }

    explicit FixUpdVal( const T& val )
        : cur{ val }
        , prv{ val }
        , dst{ val }
    {
    }

    FixUpdVal( const FixUpdVal& r )
        : cur{ r.cur }
        , prv{ r.prv }
        , dst{ r.dst }
    {
    }

    void Init()
    {
        cur = prv = dst;
    }

    void Sim( float32 alpha )
    {
        cur = Math::Lerp( prv, dst, alpha );
    }

    FORCE_INLINE FixUpdVal&
    operator=( const T& val ) noexcept
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
    constexpr bool operator==( const FixUpdVal<T>& val ) const noexcept
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

    FORCE_INLINE void reset()
    {
        prv = cur;
    }

  public:
    T cur;
    T prv;
    T dst;
};

#endif
