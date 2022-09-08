#ifndef LOCK_GUARD_H
#define LOCK_GUARD_H

#include "Mutex.h"

template <typename T>
class LockGuard
{
	public:
		explicit LockGuard( T& mtx ) :
			mutex{ mtx }
		{
			mutex.Lock();
		}

		~LockGuard()
		{
			mutex.Unlock();
		}

		// disable copies - niccco
		LockGuard( const LockGuard& /*r*/ ) = delete;
		LockGuard& operator=( const LockGuard& /*r*/ ) = delete;

	protected:
		T& mutex;
};

#endif