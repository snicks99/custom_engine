#ifndef PRINT_ERR_H
#define PRINT_ERR_H

#include "Common/Defines.h"
#include <algorithm>

inline void PrintErr( const char8* cond,
                      const char8* function,
                      int32        line )
{
    fprintf( stderr, "%s (%d): %s", function, line, cond );
}

inline void PrintErr( const char8* cond,
                      const char8* function,
                      int32        line,
                      const char8* format,
                      ... )
{
    char8 buffer[4 * MEMORY_KIBIBYTE]{};

    int32 i{ std::clamp( snprintf( buffer, ARRAY_SIZE( buffer ), "%s (%d): ", function, line ), 0, static_cast<int32>( ARRAY_SIZE( buffer ) - 1 ) ) };

    va_list vl{};

    va_start( vl, format );
    vsnprintf( &buffer[i], ARRAY_SIZE( buffer ) - i, format, vl );
    va_end( vl );

    fprintf( stderr, "%s", buffer );
}

#define PRINT_ERR( cond, ... )         \
    {                                  \
        if ( !( cond ) )               \
        {                              \
            PrintErr( #cond,           \
                      __FUNCTION__,    \
                      __LINE__,        \
                      ##__VA_ARGS__ ); \
            MGE_DEBUG_BREAK();         \
        }                              \
    }

#endif
