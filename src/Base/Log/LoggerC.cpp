#include "Log/Logger.h"
#include "FileSystem/FileIO.h"

#if ENABLE_STL_FILE_SYSTEM

#    ifndef NDEBUG
constexpr LogLevel DEFAULT_LOG_LEVEL{ LOG_LEVEL_TRACE };
#    else
constexpr LogLevel DEFAULT_LOG_LEVEL{ LOG_LEVEL_TRACE };
#    endif

Logger::Logger( const char8* fileName )
    : logLevel{ DEFAULT_LOG_LEVEL }
    , logFile{ fileName }
    , mFile{ nullptr }
{
    FileHandle fileHandle{ fopen( logFile.c_str(), "ab" ) };

    mFile = File::Create( fileHandle, logFile.c_str(), static_cast<FileIO::OpenMode>( FileIO::APPEND | FileIO::WRITE ) );
}

#endif
