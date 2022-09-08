#ifndef UNIQUE_LOCK_H
#define UNIQUE_LOCK_H

#include "Defines.h"
#include "Mutex.h"

struct AdoptLock
{
};

struct DeferLock
{
};

struct TryToLock
{
};

template<class T>
class UniqueLock
{
  public:
    using MutexT = T;

    UniqueLock();

    explicit UniqueLock( T& mtx );

    UniqueLock( T& mtx, AdoptLock );
    UniqueLock( T& mtx, DeferLock ) noexcept;
    UniqueLock( T& mtx, TryToLock );

    UniqueLock( UniqueLock&& r );
    UniqueLock& operator=( UniqueLock&& r );

    ~UniqueLock() noexcept;

    // disable copies - niccco
    UniqueLock( const UniqueLock& /*r*/ )            = delete;
    UniqueLock& operator=( const UniqueLock& /*r*/ ) = delete;

    void Lock();

    bool TryLock();

    void Unlock();

    bool OwnsLock() const noexcept;

    T* GetMutex() const;
    T* Release();

  protected:
    T*   mutex;
    bool owns;
};

// ===== Declatarion ===== //
template<class T>
UniqueLock<T>::UniqueLock() :
    mutex{ nullptr },
    owns{ false }
{
}

template<class T>
UniqueLock<T>::UniqueLock( T& mtx ) :
    mutex{ &mtx },
    owns{ false }
{
    mutex->Lock();
    owns = true;
}

template<class T>
UniqueLock<T>::UniqueLock( T& mtx, AdoptLock ) :
    mutex{ &mtx },
    owns{ true }
{
}

template<class T>
UniqueLock<T>::UniqueLock( T& mtx, DeferLock ) noexcept :
    mutex{ &mtx },
    owns{ false }
{
}

template<class T>
UniqueLock<T>::UniqueLock( T& mtx, TryToLock ) :
    mutex{ &mtx },
    owns{ mutex->TryLock() }
{
}

template<class T>
UniqueLock<T>::UniqueLock( UniqueLock&& r ) :
    mutex{ r.mutex },
    owns{ r.owns }
{
    r.mutex = nullptr;
    r.owns  = false;
}

template<class T>
UniqueLock<T>& UniqueLock<T>::operator=( UniqueLock&& r )
{
    if ( this != &r )
    {
        if ( owns )
            mutex->Unlock();

        mutex = r.mutex;
        owns  = r.owns;

        r.mutex = nullptr;
        r.owns  = false;
    }

    return ( *this );
}

template<class T>
UniqueLock<T>::~UniqueLock() noexcept
{
    if ( owns )
        mutex->Unlock();
}

template<class T>
void UniqueLock<T>::Lock()
{
    mutex->Lock();

    owns = true;
}

template<class T>
bool UniqueLock<T>::TryLock()
{
    owns = mutex->TryLock();

    return owns;
}

template<class T>
void UniqueLock<T>::Unlock()
{
    mutex->Unlock();

    owns = false;
}

template<class T>
bool UniqueLock<T>::OwnsLock() const noexcept
{
    return owns;
}

template<class T>
typename UniqueLock<T>::MutexT* UniqueLock<T>::GetMutex() const
{
    return mutex;
}

template<class T>
typename UniqueLock<T>::MutexT* UniqueLock<T>::Release()
{
    MutexT* mtx{ mutex };

    mutex = nullptr;
    owns  = false;

    return mtx;
}

#endif
