#include "OS/OS.h"
#include "Debug/DBLAssert.h"

#if DBL_PLATFORM == DBL_PLATFORM_UNIX

void OS::Initialize()
{
    DBL_LOG_MESSAGE( "OS: UNIX" );
}

#endif