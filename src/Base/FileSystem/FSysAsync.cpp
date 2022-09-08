#include "FileSystem/FSysAsync.h"
#include "FileSystem/File.h"
#include "FileSystem/FileAction.h"
#include "Profiler/Profiler.h"
#include "Debug/DBLAssert.h"

FSysAsync& GetFSysAsync()
{
    return FSysAsync::Instance();
}

FSysAsync::~FSysAsync()
{
    if ( mThread )
    {
        Stop();
        mThread->Join();

        DBL_ASSERT( mThread->GetState() == DThread::ThreadState::STATE_ENDED, "FSAsync thread didn't end" );

        SafeDelete( mThread );
    }
}

void FSysAsync::Init()
{
    /** lambda's are faster than bind due to compile optimization - niccco */
    mThread = DThread::Create( [this]()
                               { Run(); } );

    mThread->SetName( "FSAsync" );

    mThread->Start();

    mThread->BindToProcessor( 2 );
    mThread->SetPriority( DThread::ThreadPriority::PRIORITY_NORMAL );
}

void FSysAsync::Run()
{
    // OPTICK_THREAD( "FS" );

    while ( true )
    {
        FileActionSPtr action{};

        {
            UniqueLock lock{ mMutex };

            mCondition.Wait( lock,
                             [=]
                             {
                                 return mStop || mFiles.empty() == false;
                             } );

            if ( mStop && mFiles.empty() )
                return;

            action = std::move( mFiles.front() );
            mFiles.pop();
        }

        action->RunAction();
        action = nullptr;
    }
}

void FSysAsync::Stop()
{
    UniqueLock lock{ mMutex };

    mStop = true;

    mCondition.NotifyAll();
}

void FSysAsync::QueueFile( FileActionSPtr& fileAction )
{
    UniqueLock lock{ mMutex };

    if ( mStop )
        return;

    mFiles.push( fileAction );

    mCondition.NotifyOne();
}
