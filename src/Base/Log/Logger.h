#ifndef LOGGER_H
#define LOGGER_H

#include "Containers/BasicString.h"
#include "Containers/ScopedPtr.h"
#include "FileSystem/File.h"
#include "Log/LogDefines.h"

// #define DISABLE_LOGGER

class Logger
{
  public:
    /** constructor depend on platform - niccco */
    Logger( const char8* fileName );
    ~Logger();

    /**
        Write message text to platfrom specific logging facility.

        This method can be used even when Logger is not instantiated.
        Newline character is not appended to message text.
    */
    static void PlatformLog( const LogLevel& ll, const char8* msg );

    bool CanLog( const LogLevel& ll );

    /** Log without format */
    void Log( const LogLevel& ll, const char8* msg );

    /** Log with format */
    void LogFormatted( const LogLevel& ll, const char8* format, ... );
    void Logv( const LogLevel& ll, const char8* msg, va_list li );

    /** Actual log */
    void Output( const String& filePath, const LogLevel& ll, const char8* msg, size_t len );

  protected:
    uint32 AddPrefix( const LogLevel& ll, char8* prefix );

    void FileLog( const String& filePath, const LogLevel& ll, const char8* str, size_t len );

    LogLevel logLevel;
    String   logFile;
    File     mFile;
};

extern Logger gLogger;
#define sLogger ( &gLogger )

#define LOG_EXCEPTION_FREE( level__, msg__ )                                                                                        \
    {                                                                                                                               \
        try                                                                                                                         \
        {                                                                                                                           \
            sLogger->Log( level__, msg__ );                                                                                         \
        }                                                                                                                           \
        catch ( std::exception & e )                                                                                                \
        {                                                                                                                           \
            sLogger->LogFormatted( LOG_LEVEL_ERROR, "Wrong format occurred (%s) at %s ( %u ).", e.what(), __FUNCTION__, __LINE__ ); \
        }                                                                                                                           \
    }

#define LOG_EXCEPTION_FREE_FORMATTED( level__, ... )                                                                                \
    {                                                                                                                               \
        try                                                                                                                         \
        {                                                                                                                           \
            sLogger->LogFormatted( level__, ##__VA_ARGS__ );                                                                        \
        }                                                                                                                           \
        catch ( std::exception & e )                                                                                                \
        {                                                                                                                           \
            sLogger->LogFormatted( LOG_LEVEL_ERROR, "Wrong format occurred (%s) at %s ( %u ).", e.what(), __FUNCTION__, __LINE__ ); \
        }                                                                                                                           \
    }

#if DBL_COMPILER == DBL_COMPILER_MICROSOFT
#    define TC_LOG_BEGIN __pragma( warning( push ) ) __pragma( warning( disable : 4127 ) )
#    define TC_LOG_END   __pragma( warning( pop ) )
#else
#    define TC_LOG_BEGIN
#    define TC_LOG_END
#endif

#define TC_LOG_MESSAGE_BODY( level__, msg__ )     \
    TC_LOG_BEGIN                                  \
    do                                            \
    {                                             \
        if ( sLogger->CanLog( level__ ) )         \
            LOG_EXCEPTION_FREE( level__, msg__ ); \
    } while ( 0 )                                 \
        TC_LOG_END

#define TC_LOG_MESSAGE_BODY_FORMATTED( level__, ... )             \
    TC_LOG_BEGIN                                                  \
    do                                                            \
    {                                                             \
        if ( sLogger->CanLog( level__ ) )                         \
            LOG_EXCEPTION_FREE_FORMATTED( level__, __VA_ARGS__ ); \
    } while ( 0 )                                                 \
        TC_LOG_END

#if 1

#    define TC_LOG_ERROR( msg__ )         TC_LOG_MESSAGE_BODY( LOG_LEVEL_ERROR, msg__ )
#    define TC_LOG_ERROR_FORMATTED( ... ) TC_LOG_MESSAGE_BODY_FORMATTED( LOG_LEVEL_ERROR, __VA_ARGS__ )

#    define TC_LOG_WARN( msg__ )         TC_LOG_MESSAGE_BODY( LOG_LEVEL_WARN, msg__ )
#    define TC_LOG_WARN_FORMATTED( ... ) TC_LOG_MESSAGE_BODY_FORMATTED( LOG_LEVEL_WARN, __VA_ARGS__ )

#    define TC_LOG_INFO( msg__ )         TC_LOG_MESSAGE_BODY( LOG_LEVEL_INFO, msg__ )
#    define TC_LOG_INFO_FORMATTED( ... ) TC_LOG_MESSAGE_BODY_FORMATTED( LOG_LEVEL_INFO, __VA_ARGS__ )

#    define TC_LOG_TRACE( msg__ )         TC_LOG_MESSAGE_BODY( LOG_LEVEL_TRACE, msg__ )
#    define TC_LOG_TRACE_FORMATTED( ... ) TC_LOG_MESSAGE_BODY_FORMATTED( LOG_LEVEL_TRACE, __VA_ARGS__ )

#    define TC_LOG_DEBUG( msg__ )         TC_LOG_MESSAGE_BODY( LOG_LEVEL_DEBUG, msg__ )
#    define TC_LOG_DEBUG_FORMATTED( ... ) TC_LOG_MESSAGE_BODY_FORMATTED( LOG_LEVEL_DEBUG, __VA_ARGS__ )

#    define TC_LOG_FATAL( msg__ )         TC_LOG_MESSAGE_BODY( LOG_LEVEL_FATAL, msg__ )
#    define TC_LOG_FATAL_FORMATTED( ... ) TC_LOG_MESSAGE_BODY_FORMATTED( LOG_LEVEL_FATAL, __VA_ARGS__ )

#else

#    define TC_LOG_ERROR( msg__ )
#    define TC_LOG_WARN ( msg__ )
#    define TC_LOG_INFO ( msg__ )
#    define TC_LOG_TRACE( msg__ )
#    define TC_LOG_DEBUG( msg__ )

#    define TC_LOG_ERROR_FORMATTED( ... )
#    define TC_LOG_WARN_FORMATTED ( ... )
#    define TC_LOG_INFO_FORMATTED ( ... )
#    define TC_LOG_TRACE_FORMATTED( ... )
#    define TC_LOG_DEBUG_FORMATTED( ... )

#endif

#endif
