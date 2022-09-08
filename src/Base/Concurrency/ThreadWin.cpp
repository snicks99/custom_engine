#include "Platform.h"
#include "DThread.h"
#include "DBLAssert.h"

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

#    include <thread>

#    include <process.h>

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#    pragma pack( push, 8 )

typedef struct tagTHREADNAME_INFO
{
    DWORD  dwType;        // Must be 0x1000.
    LPCSTR szName;        // Pointer to name (in user addr space).
    DWORD  dwThreadID;    // DThread ID
    DWORD  dwFlags;       // Reserved for future use, must be zero.
} THREADNAME_INFO;

#    pragma pack( pop )

unsigned __stdcall ThreadFunc( void* param )
{
    DThread* t = static_cast<DThread*>( param );

    DThread::SetCurrentThreadName( t->name );

    DThread::ThreadFunction( param );

    return 0;
}

void DThread::SetCurrentThreadName( const String& str )
{
    /*
        inside that ifdef we set thread name through raising speciefic exception.
        https://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
    */

    THREADNAME_INFO info{};

    info.dwType     = 0x1000;
    info.szName     = str.c_str();
    info.dwThreadID = GetCurrentId();
    info.dwFlags    = 0;

    __try
    {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof( info ) / sizeof( ULONG_PTR ), reinterpret_cast<PULONG_PTR>( &info ) );
    }
    __except ( EXCEPTION_CONTINUE_EXECUTION )
    {
    }
}

DThread::Id DThread::GetCurrentId()
{
    return ::GetCurrentThreadId();
}

DThread::Handle DThread::GetCurrentHandle()
{
    return ::GetCurrentThread();
}

uint32 DThread::GetCurrentIdAsUInt32()
{
    return static_cast<uint32>( GetCurrentId() );
}

void DThread::Init()
{
}

void DThread::Shutdown()
{
    if ( handle != nullptr )
    {
        Join();
        CloseHandle( handle );

        handle = nullptr;
    }
}

void DThread::Start()
{
    DBL_ASSERT( state == STATE_CREATED );

    uintptr_t x = _beginthreadex( nullptr,
                                  static_cast<DWORD>( stackSize ),
                                  &ThreadFunc,
                                  this,
                                  0,
                                  nullptr );

    if ( x != 0 )
    {
        handle = reinterpret_cast<HANDLE>( x );
        isJoinable.Set( true );
        state.CompareAndSwap( STATE_CREATED, STATE_RUNNING );
    }
    else
    {
        DBL_ERROR( false, "Failed to create thread, errno = %d", errno );
    }
}

void DThread::Join()
{
    if ( isJoinable.CompareAndSwap( true, false ) )
    {
        if ( WaitForSingleObjectEx( handle, INFINITE, FALSE ) != WAIT_OBJECT_0 )
        {
            DBL_ERROR( false, "Failed in WaitForSingleObjectEx, error = %u", GetLastError() );
        }
    }
}

bool DThread::IsJoinable() const
{
    return isJoinable.Get();
}

void DThread::Kill()
{
    // it is possible to kill thread just after creating or starting and the problem is - thred changes state
    // to STATE_RUNNING insite threaded function - so that could not happens in that case. Need some time.
    DBL_ASSERT( state != STATE_CREATED );

    // Important - DO NOT try to wait RUNNING state because that state wll not appear if thread is not started!!!
    // You can wait RUNNING state, but not from thred which should call Start() for created Thread.

    if ( STATE_RUNNING == state )
    {
        KillNative();
        state = STATE_KILLED;
        // Release();
    }
}

void DThread::KillAll()
{
    /*auto threadListAccessor = GetThreadList().GetAccessor();
    for (auto& x : *threadListAccessor)
    {
        x->Kill();
    }*/
}

void DThread::Cancel()
{
    isCancelling = true;
}

bool DThread::IsCancelling() const
{
    return isCancelling.Get();
}

void DThread::CancelAll()
{
    /*auto threadListAccessor = GetThreadList().GetAccessor();
    for (auto& x : *threadListAccessor)
    {
        x->Cancel();
    }*/
}

void DThread::KillNative()
{
    if ( TerminateThread( handle, 0 ) )
    {
        CloseHandle( handle );
        handle = nullptr;
    }
}

bool DThread::BindMainToProcessor( unsigned proc )
{
    bool success{ false };

    DWORD_PTR mask = DWORD_PTR( 1 ) << proc;

    success = ( ::SetThreadAffinityMask( mainThreadHandle, mask ) != 0 );

    DBL_WARNING( success, "Failed bind thread to processor %u, error %u", proc, GetLastError() );

    return success;
}

void DThread::SetMainPriority( const ThreadPriority& priority )
{
    if ( GetMainPriority() == priority )
        return;

    int prio = THREAD_PRIORITY_NORMAL;
    switch ( priority )
    {
        case PRIORITY_LOW:
            prio = THREAD_PRIORITY_LOWEST;
            break;
        case PRIORITY_HIGH:
            prio = THREAD_PRIORITY_HIGHEST;
            break;
        default:
            break;
    }

    DBL_WARNING( ::SetThreadPriority( mainThreadHandle, prio ) != 0, "Cannot set thread priority" );
}

DThread::ThreadPriority DThread::GetMainPriority()
{
    int prio = ::GetThreadPriority( mainThreadHandle );

    switch ( prio )
    {
        case THREAD_PRIORITY_LOWEST:
            return PRIORITY_LOW;
        case THREAD_PRIORITY_HIGHEST:
            return PRIORITY_HIGH;
    }

    return PRIORITY_NORMAL;
}

bool DThread::BindToProcessor( unsigned proc )
{
    bool success{ false };

    DWORD_PTR mask = DWORD_PTR( 1 ) << proc;

    success = ( ::SetThreadAffinityMask( handle, mask ) != 0 );

    DBL_WARNING( success, "Failed bind thread to processor %u, error %u", proc, GetLastError() );

    return success;
}

void DThread::SetPriority( const ThreadPriority& priority )
{
    if ( threadPriority == priority )
        return;

    threadPriority = priority;

    int prio = THREAD_PRIORITY_NORMAL;
    switch ( threadPriority )
    {
        case PRIORITY_LOW:
            prio = THREAD_PRIORITY_LOWEST;
            break;
        case PRIORITY_HIGH:
            prio = THREAD_PRIORITY_HIGHEST;
            break;
        default:
            break;
    }

    DBL_WARNING( ::SetThreadPriority( handle, prio ) != 0, "Cannot set thread priority" );
}

#endif
