#ifndef REF_PTR_H
#define REF_PTR_H

#include "Common/Defines.h"

#define FWD_DECLARE_REF_PTR( type ) \
    class type;                     \
    using type##RfPtr = RefPtr<type>

template<typename T>
class RefCount
{
  public:
    RefCount( T* p )
        : mRefCnt{ 0 }
        , mPtr{ p }
    {
        Inc();
    }

    ~RefCount()
    {
        SafeDelete( mPtr );
    }

    void Inc() { ++mRefCnt; }
    void Dec() { --mRefCnt; }

    FORCE_INLINE word_t GetRefCnt() const { mRefCnt; }

  protected:
    friend class RefPtr;

    word_t mRefCnt;
    T*     mPtr;
};

/** be careful class isn't thread-safe - niccco */
template<typename T>
class RefPtr
{
  public:
    /** Default */
    RefPtr( T* p = nullptr )
        : mRef{ nullptr }
    {
    }

    RefPtr& operator=( T* p )
    {
        reset( p );

        return *this;
    }

    /** Copy */
    RefPtr( const RefPtr& r )
        : mRef{ r.mRef }
    {
        if ( mRef )
        {
            mRef->Inc();
        }
    }

    RefPtr& operator=( const RefPtr& r )
    {
        if ( mRef != r.mRef )
        {
            reset();

            mRef = r.mRef;
            if ( mRef )
            {
                mRef->Inc();
            }
        }

        return *this;
    }

    /** Move */
    RefPtr( RefPtr&& r )
        : mRef{ r.mRef }
    {
        r.mRef = nullptr;
    }

    RefPtr& operator=( RefPtr&& r )
    {
        reset();

        mRef   = r.mRef;
        r.mRef = nullptr;

        return *this;
    }

    ~RefPtr()
    {
        reset();
    }

    FORCE_INLINE void reset( T* p = nullptr ) noexcept
    {
        if ( mRef )
        {
            mRef->Dec();
            if ( mRef->GetRefCnt() < 1 )
            {
                SafeDelete( mRef );
            }
            mRef = nullptr;
        }

        if ( p )
        {
            mRef = new RefCount{ p };
        }
    }

    FORCE_INLINE T* get() const noexcept { return mRef->mPtr; }

    FORCE_INLINE T& operator*() const noexcept { return *get(); }
    FORCE_INLINE T* operator->() const noexcept { return get(); }

    FORCE_INLINE operator T*() const noexcept { return get(); }

  protected:
    RefCount<T>* mRef;
};

#endif
