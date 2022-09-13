#include "Hash/String/HashString.h"
#include "Debug/MGEAssert.h"

HashID HashString( const char8* str )
{
    MGE_ASSERT( str && str[0] != '\0', "Can't hash an invalid string" );

    return CRC32::HashString( str );
}
