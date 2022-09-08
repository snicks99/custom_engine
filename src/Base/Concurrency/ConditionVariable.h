#ifndef CONDITION_VARIABLE_H
#define CONDITION_VARIABLE_H

#include "Common/Platform.h"
#include "Concurrency/Mutex.h"
#include "Concurrency/UniqueLock.h"
#include "Debug/DBLAssert.h"

#include <condition_variable>

class ConditionVariable
{
  public:
    ConditionVariable();
    ~ConditionVariable() noexcept;

    ConditionVariable( const ConditionVariable& )            = delete;
    ConditionVariable& operator=( const ConditionVariable& ) = delete;

    template<typename Predicate>
    void Wait( UniqueLock<Mutex>& guard, Predicate pred );
    void Wait( UniqueLock<Mutex>& guard );

    // mutex must be locked
    template<typename Predicate>
    void Wait( Mutex& mutex, Predicate pred );
    void Wait( Mutex& mutex );

    void NotifyOne();
    void NotifyAll();

  private:
    std::condition_variable cv;
};

template<typename Predicate>
void ConditionVariable::Wait( UniqueLock<Mutex>& guard, Predicate pred )
{
    while ( !pred() )
    {
        Wait( guard );
    }
}

template<typename Predicate>
void ConditionVariable::Wait( Mutex& mutex, Predicate pred )
{
    UniqueLock<Mutex> lock( mutex, AdoptLock() );
    Wait( lock, pred );
    lock.Release();
}

inline void ConditionVariable::Wait( Mutex& mutex )
{
    UniqueLock<Mutex> lock( mutex, AdoptLock() );
    Wait( lock );
    lock.Release();
}

inline ConditionVariable::ConditionVariable()
{
}
inline ConditionVariable::~ConditionVariable() noexcept
{
}

inline void ConditionVariable::Wait( UniqueLock<Mutex>& guard )
{
    DBL_ASSERT( guard.OwnsLock(), "Mutex must be locked and UniqueLock must own it" );

    std::unique_lock<std::mutex> lock( guard.GetMutex()->mutex, std::adopt_lock_t() );
    cv.wait( lock );
    lock.release();
}

inline void ConditionVariable::NotifyOne()
{
    cv.notify_one();
}

inline void ConditionVariable::NotifyAll()
{
    cv.notify_all();
}

#endif
