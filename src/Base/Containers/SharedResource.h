#ifndef SHARED_RESOURCE_H
#define SHARED_RESOURCE_H

#include "Common/Defines.h"
#include "Memory/MMU.h"

#include <boost/detail/compressed_pair.hpp>
#include <algorithm>
#include <functional>

/** this is SharedPtr, change name later - niccco */

/** be careful class isn't thread-safe - niccco */
class RefCountBase
{
  public:
    RefCountBase()
        : mRefCnt{ 0 }
    {
    }

    virtual ~RefCountBase() = default;

    virtual void* GetPtr() const noexcept = 0;

    int32        GetRef() const noexcept { return mRefCnt; }
    virtual void IncRef() noexcept = 0;
    virtual void DecRef() noexcept = 0;

  protected:
    int32 mRefCnt;
};

template<typename T, class D>
class SharedCount : public RefCountBase
{
  public:
    explicit SharedCount( T* p )
        : RefCountBase()
        , mPair{ p }
    {
        IncRef();
    }

    ~SharedCount() noexcept override
    {
        Dispose();
    }

    void* GetPtr() const noexcept override { return mPair.second(); }

    void IncRef() noexcept override
    {
        if ( mPair.second() )
        {
            ++mRefCnt;
        }
    }

    void DecRef() noexcept override
    {
        if ( mPair.second() && mRefCnt > 0 )
        {
            --mRefCnt;
        }
    }

  private:
    void Dispose() noexcept
    {
        mPair.first()( mPair.second() );
    }

    boost::compressed_pair<D, T*> mPair;
};

/** be careful class isn't thread-safe - niccco */
template<typename T>
class SharedResource
{
  public:
    /** Default */
    SharedResource()
        : mShrCount{ nullptr }
    {
    }

    SharedResource( std::nullptr_t )
        : mShrCount{ nullptr }
    {
    }

    SharedResource( T* p )
        : mShrCount{ new SharedCount<T, DefArrDel<T>>{ p } }
    {
    }

    template<class D>
    SharedResource( T* p, D )
        : mShrCount{ new SharedCount<T, D>( p ) }
    {
    }

    /** Copy */
    SharedResource( const SharedResource& r )
        : mShrCount{ r.mShrCount }
    {
        if ( mShrCount )
        {
            mShrCount->IncRef();
        }
    }

    SharedResource& operator=( const SharedResource& r )
    {
        if ( mShrCount != r.mShrCount )
        {
            reset();

            mShrCount = r.mShrCount;
            if ( mShrCount )
            {
                mShrCount->IncRef();
            }
        }

        return *this;
    }

    /** Move */
    SharedResource( SharedResource&& r )
        : mShrCount{ r.mShrCount }
    {
        r.mShrCount = nullptr;
    }

    SharedResource& operator=( SharedResource&& r )
    {
        reset();

        mShrCount   = r.mShrCount;
        r.mShrCount = nullptr;

        return *this;
    }

    SharedResource& operator=( T* p )
    {
        reset( p );

        return *this;
    }

    ~SharedResource()
    {
        reset();
    }

    FORCE_INLINE void reset( T* p = nullptr ) noexcept
    {
        if ( mShrCount )
        {
            mShrCount->DecRef();
            if ( mShrCount->GetRef() < 1 )
            {
                SafeDelete( mShrCount );
            }
            mShrCount = nullptr;
        }

        if ( p )
        {
            mShrCount = new SharedCount<T, DefArrDel<T>>{ p };
        }
    }

    FORCE_INLINE T* get() const noexcept { return reinterpret_cast<T*>( mShrCount->GetPtr() ); }

    FORCE_INLINE T& operator*() const noexcept { return *get(); }
    FORCE_INLINE T* operator->() const noexcept { return get(); }

    FORCE_INLINE operator T*() const noexcept { return get(); }

  protected:
    RefCountBase* mShrCount;
};

#endif
