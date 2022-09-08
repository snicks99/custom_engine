#include "Log/Logger.h"
#include "FileSystem/FileIO.h"

#if ENABLE_STL_FILE_SYSTEM == 0 && DBL_PLATFORM == DBL_PLATFORM_WINDOWS

void Logger::PlatformLog( const LogLevel& ll, const char8* msg )
{
#    ifndef DISABLE_LOGGER
    OutputDebugString( msg );
#    endif
}

#endif
