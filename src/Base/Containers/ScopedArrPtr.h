#ifndef SCOPEP_ARR_PTR_H
#define SCOPEP_ARR_PTR_H

#include "Common/Defines.h"
#include "Memory/MMU.h"

template<typename T, class D = DefArrDel<T>>
class ScopedArrPtr
{
  public:
    /** Default */
    ScopedArrPtr( T* p = nullptr, D d = D() )
        : mPtr{ p }
        , mDx{ std::move( d ) }
    {
    }

    /** Copy (can't copy scoped ptr) */
    ScopedArrPtr( const ScopedArrPtr& )            = delete;
    ScopedArrPtr& operator=( const ScopedArrPtr& ) = delete;

    /** Move (to implement) - niccco */
    ScopedArrPtr( ScopedArrPtr&& )            = delete;
    ScopedArrPtr& operator=( ScopedArrPtr&& ) = delete;

    ~ScopedArrPtr()
    {
        reset();
    }

    ScopedArrPtr& operator=( T* p )
    {
        reset( p );
        return *this;
    }

    FORCE_INLINE void reset( T* p = nullptr ) noexcept
    {
        mDx( mPtr );
        mPtr = p;
    }

    FORCE_INLINE T* get() const noexcept { return mPtr; }

    FORCE_INLINE T& operator*() const noexcept { return *get(); }
    FORCE_INLINE T* operator->() const noexcept { return get(); }

    FORCE_INLINE operator T*() const noexcept { return get(); }

    template<typename OtherT>
    constexpr bool operator==( T* r ) const noexcept
    {
        return get() == r;
    }

  protected:
    T* mPtr;
    D  mDx;
};

#if 0

namespace std
{
    template<typename T, class D>
    struct hash<ScopedArrPtr<T, D>>
    {
      public:
        size_t operator()( const ScopedArrPtr<T, D>& scpPtr ) const
        {
            return std::hash<T*>()( scpPtr.get() );
        }
    };
}    // namespace std

#endif

#endif
