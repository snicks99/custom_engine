#ifndef SCOPEP_PTR_H
#define SCOPEP_PTR_H

#include "Common/Defines.h"
#include "Memory/MMU.h"

#define FWD_DECLARE_SCOPED_PTR( type ) \
    class type;                        \
    using type##ScpPtr = ScopedPtr<type>

/** be careful, don't use for containers with find implementation - niccco  */
template<typename T, class D = DefDel<T>>
class ScopedPtr
{
  public:
    /** Default */
    ScopedPtr( T* p = nullptr, D d = D() )
        : mPtr{ p }
        , mDx{ std::move( d ) }
    {
    }

    /** Copy (can't copy scoped ptr) */
    ScopedPtr( const ScopedPtr& )            = delete;
    ScopedPtr& operator=( const ScopedPtr& ) = delete;

    /** Move (to implement) - niccco */
    ScopedPtr( ScopedPtr&& r )
    {
        reset();

        mPtr = r.mPtr;
        mDx  = std::move( r.mDx );

        r.mPtr = nullptr;
        r.mDx  = nullptr;
    }

    ScopedPtr& operator=( ScopedPtr&& r )
    {
        reset();

        mPtr = r.mPtr;
        mDx  = std::move( r.mDx );

        r.mPtr = nullptr;
        r.mDx  = nullptr;
    }

    ~ScopedPtr()
    {
        reset();
    }

    ScopedPtr& operator=( T* p ) noexcept
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

template<typename T, class D>
struct std::hash<ScopedPtr<T, D>>
{
  public:
    std::size_t operator()( const ScopedPtr<T, D>& scpPtr ) const noexcept = delete;
};

//#else

namespace std
{
    template<typename T>
    struct hash<ScopedPtr<T>>
    {
    public:
        size_t operator()(const ScopedPtr<T>& scpPtr) const
        {
            return hash<T*>( scpPtr.get() );
        }
    };
}

#endif

#include <boost/container_hash/hash_fwd.hpp>

#if 0

template<typename T, class D>
struct boost::hash<ScopedPtr<T, D>>
{
  public:
    std::size_t operator()( const ScopedPtr<T, D>& scpPtr ) const noexcept = delete;
};

//#else

namespace boost
{
    template<typename T, class D>
    struct hash<ScopedPtr<T, D>>
    {
    public:
        size_t operator()(const ScopedPtr<T, D>& scpPtr) const
        {
            return hash<T*>( scpPtr.get() );
        }
    };
}

#endif

#endif
