#ifndef FILE_SYS_ASYNC_H
#define FILE_SYS_ASYNC_H

#include "Concurrency/DThread.h"
#include "Concurrency/Atomic.h"
#include "Concurrency/ConditionVariable.h"
#include "Containers/SharedPtr.h"
#include "Containers/Queue.h"
#include "Containers/PriorityQueue.h"

FWD_DECLARE_SHARED_PTR( FileAction );

class FSysAsync
{
  public:
    ~FSysAsync();

    static FSysAsync& Instance()
    {
        static FSysAsync sFSysAsync{};
        return sFSysAsync;
    }

    void Init();

    void Run();
    void Stop();

    void QueueFile( FileActionSPtr& fileAction );

  protected:
    FSysAsync()
        : mThread{ nullptr }
    {
    }

    DThread* mThread;

    Mutex                 mMutex;
    Queue<FileActionSPtr> mFiles;

    ConditionVariable mCondition;
    Atomic<bool8>     mStop;
};

extern FSysAsync& GetFSysAsync();

#endif
