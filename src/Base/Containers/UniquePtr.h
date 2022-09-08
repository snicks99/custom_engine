#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include "Memory/MMU.h"

#if 0

#    include <memory>

template<typename T, class D = DefDel<T>>
using UniquePtr = std::unique_ptr<T, D>;

#else

template<typename T, class D = DefDel<T>>
class UniquePtr
{
  public:
    /** Default */
    UniquePtr( T* p = nullptr, D d = D() )
        : mPtr{ p }
        , mDx{ std::move( d ) }
    {
    }

    /** Copy */
    UniquePtr( const UniquePtr& )            = delete;
    UniquePtr& operator=( const UniquePtr& ) = delete;

    ~UniquePtr()
    {
        reset();
    }

    UniquePtr& operator=( T* p )
    {
        reset( p );

        return *this;
    }

    FORCE_INLINE T& operator*() const { return *get(); }
    FORCE_INLINE T* operator->() const { return get(); }

    FORCE_INLINE operator T*() const { return get(); }

    FORCE_INLINE T* get() const { return mPtr; }

    void reset( T* p = nullptr )
    {
        mDx( mPtr );
        mPtr = p;
    }

  protected:
    T* mPtr;
    D  mDx;
};

#endif

#endif
