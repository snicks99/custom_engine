#ifndef DBL_ASSERT_H
#define DBL_ASSERT_H

#include "Common/Types.h"
#include "Log/Logger.h"

namespace DBL
{
    void Assert( const LogLevel& ll,
                 const char8*    format,
                 ... );

    void Assert( const LogLevel& ll,
                 const char8*    cond,
                 const char8*    function,
                 const int32     line );

    void Assert( const LogLevel& ll,
                 const char8*    cond,
                 const char8*    function,
                 const int32     line,
                 const char8*    format,
                 ... );

    void AssertNoLog();
};    // namespace DBL

#define DBL_CRASH( cond, ... )            \
    {                                     \
        if ( !( cond ) )                  \
        {                                 \
            DBL::Assert( LOG_LEVEL_ERROR, \
                         #cond,           \
                         __FUNCTION__,    \
                         __LINE__,        \
                         ##__VA_ARGS__ ); \
            DBL_DEBUG_BREAK();            \
        }                                 \
    }

#define DBL_ASSERT( cond, ... )           \
    {                                     \
        if ( !( cond ) )                  \
        {                                 \
            DBL::Assert( LOG_LEVEL_ERROR, \
                         #cond,           \
                         __FUNCTION__,    \
                         __LINE__,        \
                         ##__VA_ARGS__ ); \
            DBL_DEBUG_BREAK();            \
        }                                 \
    }

#define DBL_ASSERT_NO_LOG( cond ) \
    {                             \
        if ( !( cond ) )          \
        {                         \
            DBL::AssertNoLog();   \
            DBL_DEBUG_BREAK();    \
        }                         \
    }

#define DBL_ERROR( cond, ... )            \
    {                                     \
        if ( !( cond ) )                  \
        {                                 \
            DBL::Assert( LOG_LEVEL_ERROR, \
                         #cond,           \
                         __FUNCTION__,    \
                         __LINE__,        \
                         ##__VA_ARGS__ ); \
            DBL_DEBUG_BREAK();            \
        }                                 \
    }

#define DBL_WARNING( cond, ... )          \
    {                                     \
        if ( !( cond ) )                  \
        {                                 \
            DBL::Assert( LOG_LEVEL_WARN,  \
                         #cond,           \
                         __FUNCTION__,    \
                         __LINE__,        \
                         ##__VA_ARGS__ ); \
        }                                 \
    }

#define DBL_LOG( ... )                \
    {                                 \
        DBL::Assert( LOG_LEVEL_INFO,  \
                     "Log",           \
                     __FUNCTION__,    \
                     __LINE__,        \
                     ##__VA_ARGS__ ); \
    }

#define DBL_RW_LOG( ... )             \
    {                                 \
        DBL::Assert( LOG_LEVEL_INFO,  \
                     "RW",            \
                     __FUNCTION__,    \
                     __LINE__,        \
                     ##__VA_ARGS__ ); \
    }

#define DBL_LOG_MESSAGE( ... )                \
    {                                         \
        TC_LOG_INFO_FORMATTED( __VA_ARGS__ ); \
    }

#define DBL_TRACE( ... )              \
    {                                 \
        DBL::Assert( LOG_LEVEL_TRACE, \
                     "Trace",         \
                     __FUNCTION__,    \
                     __LINE__,        \
                     ##__VA_ARGS__ ); \
    }

#define DBL_DEBUG( ... )              \
    {                                 \
        DBL::Assert( LOG_LEVEL_DEBUG, \
                     "Debug",         \
                     __FUNCTION__,    \
                     __LINE__,        \
                     ##__VA_ARGS__ ); \
    }

#endif
