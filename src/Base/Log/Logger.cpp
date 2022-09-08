#include "Log/Logger.h"
#include "Common/Defines.h"
#include "Containers/Array.h"
#include "FileSystem/File.h"

#include <time.h>

constexpr word_t DEFAULT_PREFIX_SIZE{ 64 };
constexpr word_t DEFAULT_BUFFER_SIZE{ DEFAULT_PREFIX_SIZE + ( 4 * MEMORY_KIBIBYTE ) };

constexpr const char8* LLTAG[] = {
    "DISABLED",    // LOG_LEVEL_DISABLED

    "ERROR",    // LOG_LEVEL_ERROR
    "WARN",     // LOG_LEVEL_WARN
    "INFO",     // LOG_LEVEL_INFO
    "TRACE",    // LOG_LEVEL_TRACE
    "DEBUG",    // LOG_LEVEL_DEBUG
};

/* ===== Logger ===== */
#if BUILD_TARGET >= BUILD_TARGET_DEBUG
constexpr LogLevel DEFAULT_LOG_LEVEL{ LOG_LEVEL_TRACE };
#else
constexpr LogLevel DEFAULT_LOG_LEVEL{ LOG_LEVEL_INFO };
#endif

Logger::Logger( const char8* fileName )
    : logLevel{ DEFAULT_LOG_LEVEL }
    , logFile{ fileName }
    , mFile{}
{
#ifndef DISABLE_LOGGER
    if ( mFile.Open( logFile.c_str(), IO_OPEN_WRITE, Disposition::APPEND ) == false )
    {
        char8 buffer[512]{};
        snprintf( buffer, ARRAY_SIZE( buffer ), "Couldn't create log %s ( win32 error %u )", logFile.c_str(), GetLastError() );
        PlatformLog( LOG_LEVEL_ERROR, buffer );
    }
#endif
}

Logger::~Logger()
{
}

bool Logger::CanLog( const LogLevel& ll )
{
    return ll <= logLevel;
}

void Logger::Log( const LogLevel& ll, const char8* msg )
{
    if ( msg == nullptr || msg[0] == '\0' )
        return;

    if ( CanLog( ll ) == false )
        return;

#ifndef DISABLE_LOGGER

    char8 prefix[DEFAULT_PREFIX_SIZE]{};

    uint32 preLen{ AddPrefix( ll, prefix ) };
    word_t len{ static_cast<word_t>( strlen( msg ) ) };

    if ( preLen + len >= DEFAULT_BUFFER_SIZE - 1 )
    {
        String buffer{};

        buffer += prefix;
        buffer += msg;
        buffer += '\n';

        Output( logFile, ll, buffer.c_str(), buffer.size() );

        return;
    }

    char8 buffer[DEFAULT_BUFFER_SIZE]{};

    std::memcpy( &buffer[0], prefix, preLen );
    std::memcpy( &buffer[preLen], msg, len );

    buffer[preLen + len + 0] = '\n';
    buffer[preLen + len + 1] = '\0';

    Output( logFile, ll, buffer, preLen + len + 1 );

#endif
}

void Logger::LogFormatted( const LogLevel& ll, const char8* format, ... )
{
#ifndef DISABLE_LOGGER
    va_list vl{};

    va_start( vl, format );
    Logv( ll, format, vl );
    va_end( vl );
#endif
}

void Logger::Logv( const LogLevel& ll, const char8* format, va_list li )
{
    if ( format == nullptr || format[0] == '\0' )
        return;

    if ( CanLog( ll ) == false )
        return;

#ifndef DISABLE_LOGGER

    /** don't use Array, so we can debug content - niccco */
    char8 buffer[DEFAULT_BUFFER_SIZE]{};

    uint32 preLen{ AddPrefix( ll, buffer ) };

    va_list tmp{};

    va_copy( tmp, li );
    int32 len{ vsnprintf( &buffer[preLen], DEFAULT_BUFFER_SIZE - 1, format, tmp ) };
    va_end( tmp );

    // we don't support more than DEFAULT_BUFFER_SIZE for log - niccco
    if ( len < 0 || preLen + len >= DEFAULT_BUFFER_SIZE - 1 )
    {
        /*String str{ };

        str += prefix;
        str += ConvertCFormatListToString( msg, li );
        str += '\n';

        Log( logFile, ll, str.c_str() );*/

        return;
    }

    buffer[preLen + len + 0] = '\n';
    buffer[preLen + len + 1] = '\0';

    Output( logFile, ll, buffer, preLen + len + 1 );

#endif
}

void Logger::Output( const String& filePath, const LogLevel& ll, const char8* msg, size_t len )
{
    PlatformLog( ll, msg );
    FileLog( filePath, ll, msg, len );
}

uint32 Logger::AddPrefix( const LogLevel& ll, char8* prefix )
{
    uint32 ret{ 0 };

    tm*    timeInfo{ nullptr };
    time_t rawtime{};

    time( &rawtime );
    timeInfo = localtime( &rawtime );

    ret += strftime( &prefix[ret], DEFAULT_PREFIX_SIZE - ret, "[%Y/%m/%d %A %H:%M:%S %p]", timeInfo );
#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS
    ret += std::max( 0, sprintf_s( &prefix[ret], DEFAULT_PREFIX_SIZE - ret, "[%-5s] ", LLTAG[ll] ) );
#endif

    return ret;
}

void Logger::FileLog( const String& logFile, const LogLevel& ll, const char8* msg, size_t len )
{
    mFile.Write( msg, len );
}
