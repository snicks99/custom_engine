#include "OS/OS.h"
#include "Debug/MGEAssert.h"

#if MGE_PLATFORM == MGE_PLATFORM_UNIX

void OS::Initialize()
{
    MGE_LOG_MESSAGE( "OS: UNIX" );
}

void OS::Finalize()
{
}

#endif
