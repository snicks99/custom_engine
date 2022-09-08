#ifndef MUTEX_H
#define MUTEX_H

#include <mutex>

template <typename T>
class MutexBase
{
	public:
		friend class ConditionVariable;

		MutexBase() :
			mutex{ }
		{
		}

		// disable copies - niccco
		MutexBase( const MutexBase& /*r*/ ) = delete;
		MutexBase& operator=( const MutexBase& /*r*/ ) = delete;

		void Lock()
		{
			mutex.lock();
		}

		bool TryLock()
		{
			return mutex.try_lock();
		}

		void Unlock()
		{
			mutex.unlock();
		}

	protected:
		T mutex;
};

class Mutex final : public MutexBase<std::mutex>
{
	public:
		Mutex();
};

class RecursiveMutex final : MutexBase<std::recursive_mutex>
{
	public:
		RecursiveMutex();
};

#endif