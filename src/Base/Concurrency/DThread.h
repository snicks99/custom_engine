#ifndef THREAD_H
#define THREAD_H

#include "BasicString.h"
#include "Atomic.h"
#include "Mutex.h"
#include "Function.h"

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

#    if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

class ThreadIdentifier
{
  public:
    using Id = DWORD;

  protected:
    using Handle = HANDLE;
};

#    endif

class DThread : public ThreadIdentifier
{
#    if DBL_PLATFORM == DBL_PLATFORM_WINDOWS
    friend unsigned __stdcall ThreadFunc( void* param );
#    endif

  public:
    enum ThreadPriority
    {
        PRIORITY_LOW = 0,
        PRIORITY_NORMAL,
        PRIORITY_HIGH
    };

    enum ThreadState
    {
        STATE_CREATED = 0,
        STATE_RUNNING,
        STATE_ENDED,
        STATE_KILLED
    };

    using Procedure = Function<void()>;

    // ===== Static ===== //
    static const char MainThreadName[];

    static void InitMainThread();

    static void SetCurrentThreadName( const String& str );

    static bool     IsMainThread();
    static DThread* Current();

    /**
        \brief static function to create instance of thread object based on Procedure.
        This functions create thread based on function with signature 'void()'.
        It do not start the thread until Start function called.
        \returns ptr to thread object
    */
    static DThread* Create( const Procedure& proc );

    static Id     GetCurrentId();
    static Handle GetCurrentHandle();

    static uint32 GetCurrentIdAsUInt32();

    /** Notify the scheduler that the current thread is willing to release its processor
        to other threads of the same or higher priority.
     */
    static void TYield();

    static bool BindMainToProcessor( unsigned proc );

    static void           SetMainPriority( const ThreadPriority& priority );
    static ThreadPriority GetMainPriority();

    // ===== Thread ===== //
    ~DThread();

    /** Set thread name. You should to use it before Thread::Start(). */
    void          SetName( const String& _name );
    const String& GetName() const;

    /** Start execution of the thread */
    void Start();

    /** Wait until thread's finished. */
    void Join();
    bool IsJoinable() const;

    /** Kill thread by OS. No signals will be sent. */
    void        Kill();
    static void KillAll();

    /** Ask to cancel thread. User should to check state variable */
    void Cancel();

    /** Check if someone asked thread to cancel */
    bool        IsCancelling() const;
    static void CancelAll();

    /** Suspend the execution of the current thread until the time-out interval elapses */
    static void Sleep( uint32 timeMS );

    Id GetId() const;

    bool BindToProcessor( unsigned proc );

    ThreadState GetState() const;

    void           SetPriority( const ThreadPriority& priority );
    ThreadPriority GetPriority() const;

  private:
    DThread();
    // DThread( const Message& msg );
    DThread( const Procedure& proc );

    void Init();
    void Shutdown();

    /** Kill thread native implementation (contains no Thread logic) */
    void KillNative();

    /** Function which processes in separate thread. Used to launch user defined code and handle state. */
    static void ThreadFunction( void* param );

    Procedure           threadFunc;
    Atomic<ThreadState> state;
    Atomic<bool>        isCancelling;
    Atomic<bool>        isJoinable;
    size_t              stackSize;
    ThreadPriority      threadPriority;

    /** Native thread handle - variable which used to thread manipulations */
    Handle handle;
    /* OS */
    Id id;

    /** Name of the thread. */
    String name;

    /* Full list of created Thread's. Main thread is not Thread, so it is not there. */
    static HANDLE mainThreadHandle;
    static Id     mainThreadId;
    static Id     glThreadId;
};

#endif

#endif
