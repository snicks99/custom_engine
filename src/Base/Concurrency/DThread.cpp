#include "DThread.h"
#include "DBLAssert.h"

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

DThread::Handle DThread::mainThreadHandle{};
DThread::Id     DThread::mainThreadId{};

const char8 DThread::MainThreadName[] = "MainThread";

void DThread::InitMainThread()
{
    mainThreadHandle = GetCurrentThread();
    mainThreadId     = GetCurrentId();

    DThread::SetCurrentThreadName( MainThreadName );
}

bool DThread::IsMainThread()
{
    if ( DThread::Id{} == mainThreadId )
    {
        DBL_ERROR( false, "Main thread not initialized" );
        return false;
    }

    Id currentId = GetCurrentId();

    return currentId == mainThreadId;
}

void DThread::TYield()
{
    std::this_thread::yield();
}

void DThread::Sleep( uint32 timeMS )
{
    std::chrono::milliseconds ms( timeMS );

    std::this_thread::sleep_for( ms );
}

DThread* DThread::Create( const Procedure& proc )
{
    return new DThread( proc );
}

/*DThread* DThread::Create( const Message& msg )
{
    return new DThread( msg );
}*/

void DThread::ThreadFunction( void* param )
{
    DThread* t{ reinterpret_cast<DThread*>( param ) };

    t->id = GetCurrentId();

    t->threadFunc();

    // Zero id to mark thread as finished in thread list obtained through GetThreadList() function.
    // This prevents from retrieving invalid DThread instance through DThread::Current()
    // as system can reuse thread ids.
    std::memset( &t->id, 0, sizeof( t->id ) );

    t->state = STATE_ENDED;
}

DThread::DThread()
    : state{ STATE_CREATED }
    , isCancelling{ false }
    , isJoinable{ false }
    , stackSize{ 0 }
    , handle{ Handle{} }
    , id{ Id{} }
    , name{ "DThread" }
{
    Init();

    // auto threadListAccessor = GetThreadList().GetAccessor();
    // threadListAccessor->insert(this);
}

/*DThread::DThread( const Message& msg ) :
    DThread()
{
    Message message = msg;
    DThread* caller = this;
    threadFunc = [=] { message(caller); };
}*/

DThread::DThread( const Procedure& proc )
    : DThread{}
{
    threadFunc = proc;
}

DThread::~DThread()
{
    Cancel();
    Shutdown();

    // auto threadListAccessor = GetThreadList().GetAccessor();
    // threadListAccessor->erase(this);
}

void DThread::SetName( const String& _name )
{
    // name sets inside thread function, so we cannot change thread name after starting.
    DBL_ASSERT( STATE_CREATED == state );

    name = _name;
}

const String& DThread::GetName() const
{
    return name;
}

DThread::ThreadState DThread::GetState() const
{
    return state.Get();
}

DThread::Id DThread::GetId() const
{
    return id;
}

DThread::ThreadPriority DThread::GetPriority() const
{
    return threadPriority;
}

#endif
