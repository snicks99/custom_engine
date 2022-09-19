#include "Hash/String/HashString.h"
#include "Debug/MGEAssert.h"

MGE_SID HashString( const char8* str )
{
    MGE_ASSERT( str && str[0] != '\0', "Can't hash an invalid string" );

    return static_cast<MGE_SID>( CRC32::HashString( str ) );
}
