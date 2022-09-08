#include "Debug/DBLAssert.h"

namespace DBL
{

    constexpr uint32 ASSERT_BUFFER_SIZE{ 4 * 1024 - 1 };

    void Assert( const LogLevel& ll,
                 const char8*    format,
                 ... )
    {
        char8 buffer[ASSERT_BUFFER_SIZE]{};

        va_list vl{};

        va_start( vl, format );
        vsnprintf( buffer, ASSERT_BUFFER_SIZE, format, vl );
        va_end( vl );

        TC_LOG_MESSAGE_BODY( ll, buffer );
    }

    void Assert( const LogLevel& ll,
                 const char8*    cond,
                 const char8*    function,
                 const int32     line )
    {
        TC_LOG_MESSAGE_BODY_FORMATTED( ll, "%s (%d): %s", function, line, cond );
    }

    void Assert( const LogLevel& ll,
                 const char8*    cond,
                 const char8*    function,
                 const int32     line,
                 const char8*    format,
                 ... )
    {
        char8 buffer[ASSERT_BUFFER_SIZE]{};

        int32 i{ std::max( 0, snprintf( buffer, ASSERT_BUFFER_SIZE, "%s (%d): ", function, line ) ) };

        va_list vl{};

        va_start( vl, format );
        vsnprintf( &buffer[i], ASSERT_BUFFER_SIZE, format, vl );
        va_end( vl );

        TC_LOG_MESSAGE_BODY( ll, buffer );
    }

    void AssertNoLog()
    {
        // fprintf( stderr, "Internal error" );
    }

};    // namespace DBL
