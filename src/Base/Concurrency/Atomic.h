#ifndef ATOMIC_H
#define ATOMIC_H

#include "Common/Platform.h"

#include <type_traits>
#include <atomic>

template<typename T>
class Atomic
{
    static_assert(
        std::is_integral<T>::value ||
            std::is_pointer<T>::value ||
            std::is_enum<T>::value,
        "Not valid type for atomic operations" );

  public:
    Atomic( T val = T() ) noexcept
        : value{ val }
    {
    }

    Atomic( const Atomic& other )            = delete;
    Atomic& operator=( const Atomic& other ) = delete;

    Atomic& operator=( T val ) noexcept;

    operator T() noexcept { return Get(); }

    void Set( T val ) noexcept;
    T    Get() const noexcept;
    T    GetRelaxed() const noexcept;

    T Increment() noexcept;
    T Decrement() noexcept;

    T operator++() noexcept
    {
        return Increment();
    }
    T operator++( int ) noexcept
    {
        return Increment() - 1;
    }
    T operator--() noexcept
    {
        return Decrement();
    }
    T operator--( int ) noexcept
    {
        return Decrement() + 1;
    }

    T    Swap( T desired ) noexcept;
    bool CompareAndSwap( T expected, T desired ) noexcept;

  private:
    std::atomic<T> value;
};

/* ===== Implementation ===== */
template<typename T>
Atomic<T>& Atomic<T>::operator=( T val ) noexcept
{
    Set( val );
    return *this;
}

template<typename T>
void Atomic<T>::Set( T val ) noexcept
{
    value = val;
}

template<typename T>
T Atomic<T>::Get() const noexcept
{
    return value;
}

template<typename T>
T Atomic<T>::GetRelaxed() const noexcept
{
    return value.load( std::memory_order_relaxed );
}

template<typename T>
T Atomic<T>::Increment() noexcept
{
    return ++value;
}

template<typename T>
T Atomic<T>::Decrement() noexcept
{
    return --value;
}

template<typename T>
T Atomic<T>::Swap( T desired ) noexcept
{
    return value.exchange( desired );
}

template<typename T>
bool Atomic<T>::CompareAndSwap( T expected, T desired ) noexcept
{
    return value.compare_exchange_strong( expected, desired );
}

#endif
